/*
 * z80.c -- Zilog Z80 interpreter. See z80.h.
 *
 * Decoding follows the standard x/y/z/p/q field split of the opcode byte.
 * T-state counts are the documented ones; a DD/FD prefix adds its own 4, and
 * (IX+d)/(IY+d) operands add the displacement fetch and address add (8, or 5
 * for LD (IX+d),n where the immediate byte overlaps that time).
 */
#include "z80.h"

#define FC 0x01
#define FN 0x02
#define FP 0x04
#define FX 0x08
#define FH 0x10
#define FY 0x20
#define FZ 0x40
#define FS 0x80

static uint8_t s_sz53[256];
static uint8_t s_sz53p[256];
static int s_tables_ready;

static void init_tables(void)
{
    for (int i = 0; i < 256; ++i) {
        uint8_t f = (uint8_t)(i & (FS | FY | FX));
        int parity = 0;
        if (i == 0) f |= FZ;
        for (int b = 0; b < 8; ++b) parity ^= (i >> b) & 1;
        s_sz53[i] = f;
        s_sz53p[i] = (uint8_t)(f | (parity ? 0 : FP));
    }
    s_tables_ready = 1;
}

/* ---------------------------------------------------------------- access */

static uint8_t rd(Z80 *z, uint16_t addr) { return z->read(z->user, addr); }
static void wr(Z80 *z, uint16_t addr, uint8_t v) { z->write(z->user, addr, v); }

static uint8_t port_in(Z80 *z, uint16_t port)
{
    return z->in ? z->in(z->user, port) : 0xFF;
}

static void port_out(Z80 *z, uint16_t port, uint8_t v)
{
    if (z->out) z->out(z->user, port, v);
}

static uint8_t fetch(Z80 *z) { return rd(z, z->pc++); }

static uint16_t fetch16(Z80 *z)
{
    const uint8_t lo = fetch(z);
    const uint8_t hi = fetch(z);
    return (uint16_t)(lo | (hi << 8));
}

static uint16_t rd16(Z80 *z, uint16_t addr)
{
    const uint8_t lo = rd(z, addr);
    const uint8_t hi = rd(z, (uint16_t)(addr + 1));
    return (uint16_t)(lo | (hi << 8));
}

static void wr16(Z80 *z, uint16_t addr, uint16_t v)
{
    wr(z, addr, (uint8_t)v);
    wr(z, (uint16_t)(addr + 1), (uint8_t)(v >> 8));
}

static void inc_r(Z80 *z) { z->r = (uint8_t)((z->r & 0x80) | ((z->r + 1) & 0x7F)); }

static void push16(Z80 *z, uint16_t v)
{
    wr(z, --z->sp, (uint8_t)(v >> 8));
    wr(z, --z->sp, (uint8_t)v);
}

static uint16_t pop16(Z80 *z)
{
    const uint8_t lo = rd(z, z->sp++);
    const uint8_t hi = rd(z, z->sp++);
    return (uint16_t)(lo | (hi << 8));
}

static uint16_t get_bc(const Z80 *z) { return (uint16_t)((z->b << 8) | z->c); }
static uint16_t get_de(const Z80 *z) { return (uint16_t)((z->d << 8) | z->e); }
static uint16_t get_hl(const Z80 *z) { return (uint16_t)((z->h << 8) | z->l); }
static void set_bc(Z80 *z, uint16_t v) { z->b = (uint8_t)(v >> 8); z->c = (uint8_t)v; }
static void set_de(Z80 *z, uint16_t v) { z->d = (uint8_t)(v >> 8); z->e = (uint8_t)v; }
static void set_hl(Z80 *z, uint16_t v) { z->h = (uint8_t)(v >> 8); z->l = (uint8_t)v; }

/* HL, or IX/IY under a DD/FD prefix. */
static uint16_t get_xhl(const Z80 *z, int pfx)
{
    return pfx == 0xDD ? z->ix : pfx == 0xFD ? z->iy : get_hl(z);
}

static void set_xhl(Z80 *z, int pfx, uint16_t v)
{
    if (pfx == 0xDD) z->ix = v;
    else if (pfx == 0xFD) z->iy = v;
    else set_hl(z, v);
}

/* rp table: BC, DE, HL (IX/IY), SP. */
static uint16_t get_rp(const Z80 *z, int p, int pfx)
{
    switch (p) {
    case 0: return get_bc(z);
    case 1: return get_de(z);
    case 2: return get_xhl(z, pfx);
    default: return z->sp;
    }
}

static void set_rp(Z80 *z, int p, int pfx, uint16_t v)
{
    switch (p) {
    case 0: set_bc(z, v); break;
    case 1: set_de(z, v); break;
    case 2: set_xhl(z, pfx, v); break;
    default: z->sp = v; break;
    }
}

/* r table without (HL): B C D E H L - A, where H/L mean IXH/IXL etc. under
 * a prefix. Index 6 is never passed here. */
static uint8_t get_reg(const Z80 *z, int idx, int pfx)
{
    switch (idx) {
    case 0: return z->b;
    case 1: return z->c;
    case 2: return z->d;
    case 3: return z->e;
    case 4: return pfx ? (uint8_t)(get_xhl(z, pfx) >> 8) : z->h;
    case 5: return pfx ? (uint8_t)get_xhl(z, pfx) : z->l;
    default: return z->a;
    }
}

static void set_reg(Z80 *z, int idx, int pfx, uint8_t v)
{
    switch (idx) {
    case 0: z->b = v; break;
    case 1: z->c = v; break;
    case 2: z->d = v; break;
    case 3: z->e = v; break;
    case 4:
        if (pfx) set_xhl(z, pfx, (uint16_t)((get_xhl(z, pfx) & 0x00FF) | (v << 8)));
        else z->h = v;
        break;
    case 5:
        if (pfx) set_xhl(z, pfx, (uint16_t)((get_xhl(z, pfx) & 0xFF00) | v));
        else z->l = v;
        break;
    default: z->a = v; break;
    }
}

/* The (HL) operand address; under a prefix, (IX+d)/(IY+d) with d fetched. */
static uint16_t mem_operand(Z80 *z, int pfx)
{
    if (pfx) {
        const int8_t d = (int8_t)fetch(z);
        z->wz = (uint16_t)(get_xhl(z, pfx) + d);
        return z->wz;
    }
    return get_hl(z);
}

static int condition(const Z80 *z, int cc)
{
    switch (cc) {
    case 0: return !(z->f & FZ);
    case 1: return (z->f & FZ) != 0;
    case 2: return !(z->f & FC);
    case 3: return (z->f & FC) != 0;
    case 4: return !(z->f & FP);
    case 5: return (z->f & FP) != 0;
    case 6: return !(z->f & FS);
    default: return (z->f & FS) != 0;
    }
}

/* ------------------------------------------------------------ arithmetic */

static void alu(Z80 *z, int op, uint8_t v)
{
    const uint8_t a = z->a;
    unsigned res;
    uint8_t r8;

    switch (op) {
    case 0: /* ADD */
    case 1: /* ADC */
        res = (unsigned)a + v + (op == 1 ? (z->f & FC) : 0u);
        r8 = (uint8_t)res;
        z->f = (uint8_t)(s_sz53[r8] | ((res >> 8) & FC) | ((a ^ v ^ r8) & FH) |
                         ((~(a ^ v) & (a ^ r8) & 0x80) ? FP : 0));
        z->a = r8;
        break;
    case 2: /* SUB */
    case 3: /* SBC */
    case 7: /* CP */
        res = (unsigned)a - v - (op == 3 ? (z->f & FC) : 0u);
        r8 = (uint8_t)res;
        z->f = (uint8_t)(FN | (s_sz53[r8] & (FS | FZ)) | ((res >> 8) & FC) |
                         ((a ^ v ^ r8) & FH) |
                         (((a ^ v) & (a ^ r8) & 0x80) ? FP : 0));
        if (op == 7) {
            z->f |= (uint8_t)(v & (FX | FY));
        } else {
            z->f |= (uint8_t)(r8 & (FX | FY));
            z->a = r8;
        }
        break;
    case 4: /* AND */
        z->a = (uint8_t)(a & v);
        z->f = (uint8_t)(s_sz53p[z->a] | FH);
        break;
    case 5: /* XOR */
        z->a = (uint8_t)(a ^ v);
        z->f = s_sz53p[z->a];
        break;
    default: /* OR */
        z->a = (uint8_t)(a | v);
        z->f = s_sz53p[z->a];
        break;
    }
}

static uint8_t inc8(Z80 *z, uint8_t v)
{
    const uint8_t r = (uint8_t)(v + 1);
    z->f = (uint8_t)((z->f & FC) | s_sz53[r] | ((r & 0x0F) == 0 ? FH : 0) |
                     (v == 0x7F ? FP : 0));
    return r;
}

static uint8_t dec8(Z80 *z, uint8_t v)
{
    const uint8_t r = (uint8_t)(v - 1);
    z->f = (uint8_t)((z->f & FC) | FN | s_sz53[r] | ((v & 0x0F) == 0 ? FH : 0) |
                     (v == 0x80 ? FP : 0));
    return r;
}

static uint16_t add16(Z80 *z, uint16_t a, uint16_t b)
{
    const uint32_t res = (uint32_t)a + b;
    z->wz = (uint16_t)(a + 1);
    z->f = (uint8_t)((z->f & (FS | FZ | FP)) | ((res >> 16) & FC) |
                     (((a ^ b ^ res) >> 8) & FH) | ((res >> 8) & (FX | FY)));
    return (uint16_t)res;
}

static uint16_t adc16(Z80 *z, uint16_t a, uint16_t b)
{
    const uint32_t res = (uint32_t)a + b + (z->f & FC);
    const uint16_t r = (uint16_t)res;
    z->wz = (uint16_t)(a + 1);
    z->f = (uint8_t)(((res >> 16) & FC) | (((a ^ b ^ res) >> 8) & FH) |
                     ((r >> 8) & (FS | FX | FY)) | (r == 0 ? FZ : 0) |
                     ((~(a ^ b) & (a ^ r) & 0x8000) ? FP : 0));
    return r;
}

static uint16_t sbc16(Z80 *z, uint16_t a, uint16_t b)
{
    const uint32_t res = (uint32_t)a - b - (z->f & FC);
    const uint16_t r = (uint16_t)res;
    z->wz = (uint16_t)(a + 1);
    z->f = (uint8_t)(FN | ((res >> 16) & FC) | (((a ^ b ^ res) >> 8) & FH) |
                     ((r >> 8) & (FS | FX | FY)) | (r == 0 ? FZ : 0) |
                     (((a ^ b) & (a ^ r) & 0x8000) ? FP : 0));
    return r;
}

static uint8_t cb_rotate(Z80 *z, int op, uint8_t v)
{
    uint8_t c, r;
    switch (op) {
    case 0: c = (uint8_t)(v >> 7); r = (uint8_t)((v << 1) | c); break;            /* RLC */
    case 1: c = (uint8_t)(v & 1); r = (uint8_t)((v >> 1) | (c << 7)); break;      /* RRC */
    case 2: c = (uint8_t)(v >> 7); r = (uint8_t)((v << 1) | (z->f & FC)); break;  /* RL  */
    case 3: c = (uint8_t)(v & 1); r = (uint8_t)((v >> 1) | ((z->f & FC) << 7)); break; /* RR */
    case 4: c = (uint8_t)(v >> 7); r = (uint8_t)(v << 1); break;                  /* SLA */
    case 5: c = (uint8_t)(v & 1); r = (uint8_t)((v >> 1) | (v & 0x80)); break;    /* SRA */
    case 6: c = (uint8_t)(v >> 7); r = (uint8_t)((v << 1) | 1); break;            /* SLL */
    default: c = (uint8_t)(v & 1); r = (uint8_t)(v >> 1); break;                  /* SRL */
    }
    z->f = (uint8_t)(s_sz53p[r] | c);
    return r;
}

static void bit_test(Z80 *z, int n, uint8_t v, uint8_t xy_source)
{
    const uint8_t m = (uint8_t)(v & (1u << n));
    z->f = (uint8_t)((z->f & FC) | FH | (xy_source & (FX | FY)) |
                     (m ? (m & FS) : (FZ | FP)));
}

static void daa(Z80 *z)
{
    const uint8_t a = z->a;
    uint8_t corr = 0, carry = (uint8_t)(z->f & FC), r;
    int half;

    if ((z->f & FH) || (a & 0x0F) > 9) corr |= 0x06;
    if (carry || a > 0x99) {
        corr |= 0x60;
        carry = FC;
    }
    if (z->f & FN) {
        half = (z->f & FH) && (a & 0x0F) < 6;
        r = (uint8_t)(a - corr);
    } else {
        half = (a & 0x0F) > 9;
        r = (uint8_t)(a + corr);
    }
    z->f = (uint8_t)(s_sz53p[r] | carry | (half ? FH : 0) | (z->f & FN));
    z->a = r;
}

/* --------------------------------------------------------------- CB/ED */

/* CB xx, or DD CB d xx / FD CB d xx. Returns T-states excluding a DD/FD
 * prefix's own 4. */
static int exec_cb(Z80 *z, int pfx)
{
    uint16_t addr = 0;
    uint8_t op, v, r;
    int x, y, idx;

    if (pfx) {
        addr = mem_operand(z, pfx);   /* displacement precedes the opcode */
        op = fetch(z);                /* not an M1 cycle: R is unchanged */
    } else {
        op = fetch(z);
        inc_r(z);
    }
    x = op >> 6;
    y = (op >> 3) & 7;
    idx = op & 7;

    if (pfx || idx == 6) {
        if (!pfx) addr = get_hl(z);
        v = rd(z, addr);
        if (x == 1) {
            bit_test(z, y, v, (uint8_t)(z->wz >> 8));
            return pfx ? 16 : 12;
        }
        if (x == 0) r = cb_rotate(z, y, v);
        else if (x == 2) r = (uint8_t)(v & ~(1u << y));
        else r = (uint8_t)(v | (1u << y));
        wr(z, addr, r);
        /* DDCB/FDCB with a register operand also copy the result there. */
        if (pfx && idx != 6) set_reg(z, idx, 0, r);
        return pfx ? 19 : 15;
    }

    v = get_reg(z, idx, 0);
    if (x == 1) {
        bit_test(z, y, v, v);
        return 8;
    }
    if (x == 0) r = cb_rotate(z, y, v);
    else if (x == 2) r = (uint8_t)(v & ~(1u << y));
    else r = (uint8_t)(v | (1u << y));
    set_reg(z, idx, 0, r);
    return 8;
}

static int exec_ed(Z80 *z)
{
    const uint8_t op = fetch(z);
    const int x = op >> 6, y = (op >> 3) & 7, zz = op & 7;
    const int p = y >> 1, q = y & 1;

    inc_r(z);
    if (x == 1) {
        switch (zz) {
        case 0: { /* IN r,(C) */
            const uint8_t v = port_in(z, get_bc(z));
            z->wz = (uint16_t)(get_bc(z) + 1);
            z->f = (uint8_t)((z->f & FC) | s_sz53p[v]);
            if (y != 6) set_reg(z, y, 0, v);
            return 12;
        }
        case 1: /* OUT (C),r */
            port_out(z, get_bc(z), y == 6 ? 0 : get_reg(z, y, 0));
            z->wz = (uint16_t)(get_bc(z) + 1);
            return 12;
        case 2:
            if (q == 0) set_hl(z, sbc16(z, get_hl(z), get_rp(z, p, 0)));
            else set_hl(z, adc16(z, get_hl(z), get_rp(z, p, 0)));
            return 15;
        case 3: {
            const uint16_t nn = fetch16(z);
            if (q == 0) wr16(z, nn, get_rp(z, p, 0));
            else set_rp(z, p, 0, rd16(z, nn));
            z->wz = (uint16_t)(nn + 1);
            return 20;
        }
        case 4: { /* NEG */
            const uint8_t v = z->a;
            z->a = 0;
            alu(z, 2, v);
            return 8;
        }
        case 5: /* RETN / RETI */
            z->iff1 = z->iff2;
            z->pc = pop16(z);
            z->wz = z->pc;
            return 14;
        case 6: {
            static const uint8_t k_im[8] = { 0, 0, 1, 2, 0, 0, 1, 2 };
            z->im = k_im[y];
            return 8;
        }
        default:
            switch (y) {
            case 0: z->i = z->a; return 9;
            case 1: z->r = z->a; return 9;
            case 2:
            case 3:
                z->a = y == 2 ? z->i : z->r;
                z->f = (uint8_t)((z->f & FC) | s_sz53[z->a] | (z->iff2 ? FP : 0));
                return 9;
            case 4: { /* RRD */
                const uint16_t hl = get_hl(z);
                const uint8_t v = rd(z, hl);
                wr(z, hl, (uint8_t)((z->a << 4) | (v >> 4)));
                z->a = (uint8_t)((z->a & 0xF0) | (v & 0x0F));
                z->f = (uint8_t)((z->f & FC) | s_sz53p[z->a]);
                z->wz = (uint16_t)(hl + 1);
                return 18;
            }
            case 5: { /* RLD */
                const uint16_t hl = get_hl(z);
                const uint8_t v = rd(z, hl);
                wr(z, hl, (uint8_t)((v << 4) | (z->a & 0x0F)));
                z->a = (uint8_t)((z->a & 0xF0) | (v >> 4));
                z->f = (uint8_t)((z->f & FC) | s_sz53p[z->a]);
                z->wz = (uint16_t)(hl + 1);
                return 18;
            }
            default:
                return 8;
            }
        }
    }

    if (x == 2 && y >= 4 && zz <= 3) {
        const int dec = (y & 1) != 0;
        const int repeat = y >= 6;
        const int16_t step = dec ? -1 : 1;
        uint16_t hl = get_hl(z);
        uint16_t bc = get_bc(z);

        switch (zz) {
        case 0: { /* LDI/LDD/LDIR/LDDR */
            const uint8_t v = rd(z, hl);
            const uint8_t n = (uint8_t)(v + z->a);
            uint16_t de = get_de(z);
            wr(z, de, v);
            de = (uint16_t)(de + step);
            hl = (uint16_t)(hl + step);
            bc = (uint16_t)(bc - 1);
            set_de(z, de);
            set_hl(z, hl);
            set_bc(z, bc);
            z->f = (uint8_t)((z->f & (FS | FZ | FC)) | (bc ? FP : 0) |
                             (n & FX) | ((n << 4) & FY));
            if (repeat && bc) {
                z->pc = (uint16_t)(z->pc - 2);
                z->wz = (uint16_t)(z->pc + 1);
                return 21;
            }
            return 16;
        }
        case 1: { /* CPI/CPD/CPIR/CPDR */
            const uint8_t v = rd(z, hl);
            const uint8_t r = (uint8_t)(z->a - v);
            const uint8_t half = (uint8_t)((z->a ^ v ^ r) & FH);
            const uint8_t n = (uint8_t)(r - (half ? 1 : 0));
            hl = (uint16_t)(hl + step);
            bc = (uint16_t)(bc - 1);
            set_hl(z, hl);
            set_bc(z, bc);
            z->wz = (uint16_t)(z->wz + step);
            z->f = (uint8_t)((z->f & FC) | FN | (s_sz53[r] & (FS | FZ)) | half |
                             (bc ? FP : 0) | (n & FX) | ((n << 4) & FY));
            if (repeat && bc && r) {
                z->pc = (uint16_t)(z->pc - 2);
                z->wz = (uint16_t)(z->pc + 1);
                return 21;
            }
            return 16;
        }
        case 2: { /* INI/IND/INIR/INDR */
            const uint8_t v = port_in(z, bc);
            uint8_t b;
            wr(z, hl, v);
            z->wz = (uint16_t)(bc + step);
            b = (uint8_t)(z->b - 1);
            z->b = b;
            set_hl(z, (uint16_t)(hl + step));
            {
                const unsigned k = (unsigned)v + (uint8_t)(z->c + step);
                z->f = (uint8_t)((s_sz53[b] & (FS | FZ | FX | FY)) |
                                 ((v & 0x80) ? FN : 0) | (k > 0xFF ? (FH | FC) : 0) |
                                 (s_sz53p[(uint8_t)((k & 7) ^ b)] & FP));
            }
            if (repeat && b) {
                z->pc = (uint16_t)(z->pc - 2);
                return 21;
            }
            return 16;
        }
        default: { /* OUTI/OUTD/OTIR/OTDR */
            const uint8_t v = rd(z, hl);
            uint8_t b = (uint8_t)(z->b - 1);
            z->b = b;
            port_out(z, get_bc(z), v);
            z->wz = (uint16_t)(get_bc(z) + step);
            hl = (uint16_t)(hl + step);
            set_hl(z, hl);
            {
                const unsigned k = (unsigned)v + z->l;
                z->f = (uint8_t)((s_sz53[b] & (FS | FZ | FX | FY)) |
                                 ((v & 0x80) ? FN : 0) | (k > 0xFF ? (FH | FC) : 0) |
                                 (s_sz53p[(uint8_t)((k & 7) ^ b)] & FP));
            }
            if (repeat && b) {
                z->pc = (uint16_t)(z->pc - 2);
                return 21;
            }
            return 16;
        }
        }
    }

    return 8;   /* undefined ED opcodes behave as two NOPs */
}

/* ----------------------------------------------------------------- main */

static int exec_main(Z80 *z, int pfx)
{
    const int pre = pfx ? 4 : 0;
    const uint8_t op = fetch(z);
    const int x = op >> 6, y = (op >> 3) & 7, zz = op & 7;
    const int p = y >> 1, q = y & 1;

    inc_r(z);

    switch (x) {
    case 0:
        switch (zz) {
        case 0:
            switch (y) {
            case 0: return pre + 4;                                  /* NOP */
            case 1: {                                                /* EX AF,AF' */
                uint8_t t = z->a; z->a = z->a_; z->a_ = t;
                t = z->f; z->f = z->f_; z->f_ = t;
                return pre + 4;
            }
            case 2: {                                                /* DJNZ d */
                const int8_t d = (int8_t)fetch(z);
                if (--z->b) {
                    z->pc = (uint16_t)(z->pc + d);
                    z->wz = z->pc;
                    return pre + 13;
                }
                return pre + 8;
            }
            case 3: {                                                /* JR d */
                const int8_t d = (int8_t)fetch(z);
                z->pc = (uint16_t)(z->pc + d);
                z->wz = z->pc;
                return pre + 12;
            }
            default: {                                               /* JR cc,d */
                const int8_t d = (int8_t)fetch(z);
                if (condition(z, y - 4)) {
                    z->pc = (uint16_t)(z->pc + d);
                    z->wz = z->pc;
                    return pre + 12;
                }
                return pre + 7;
            }
            }
        case 1:
            if (q == 0) {                                            /* LD rp,nn */
                set_rp(z, p, pfx, fetch16(z));
                return pre + 10;
            }
            set_xhl(z, pfx, add16(z, get_xhl(z, pfx), get_rp(z, p, pfx)));  /* ADD HL,rp */
            return pre + 11;
        case 2:
            switch (y) {
            case 0:                                                  /* LD (BC),A */
                wr(z, get_bc(z), z->a);
                z->wz = (uint16_t)((z->a << 8) | ((get_bc(z) + 1) & 0xFF));
                return pre + 7;
            case 1:                                                  /* LD A,(BC) */
                z->a = rd(z, get_bc(z));
                z->wz = (uint16_t)(get_bc(z) + 1);
                return pre + 7;
            case 2:                                                  /* LD (DE),A */
                wr(z, get_de(z), z->a);
                z->wz = (uint16_t)((z->a << 8) | ((get_de(z) + 1) & 0xFF));
                return pre + 7;
            case 3:                                                  /* LD A,(DE) */
                z->a = rd(z, get_de(z));
                z->wz = (uint16_t)(get_de(z) + 1);
                return pre + 7;
            case 4: {                                                /* LD (nn),HL */
                const uint16_t nn = fetch16(z);
                wr16(z, nn, get_xhl(z, pfx));
                z->wz = (uint16_t)(nn + 1);
                return pre + 16;
            }
            case 5: {                                                /* LD HL,(nn) */
                const uint16_t nn = fetch16(z);
                set_xhl(z, pfx, rd16(z, nn));
                z->wz = (uint16_t)(nn + 1);
                return pre + 16;
            }
            case 6: {                                                /* LD (nn),A */
                const uint16_t nn = fetch16(z);
                wr(z, nn, z->a);
                z->wz = (uint16_t)((z->a << 8) | ((nn + 1) & 0xFF));
                return pre + 13;
            }
            default: {                                               /* LD A,(nn) */
                const uint16_t nn = fetch16(z);
                z->a = rd(z, nn);
                z->wz = (uint16_t)(nn + 1);
                return pre + 13;
            }
            }
        case 3:                                                      /* INC/DEC rp */
            set_rp(z, p, pfx, (uint16_t)(get_rp(z, p, pfx) + (q ? -1 : 1)));
            return pre + 6;
        case 4:
        case 5:                                                      /* INC/DEC r */
            if (y == 6) {
                const uint16_t addr = mem_operand(z, pfx);
                const uint8_t v = rd(z, addr);
                wr(z, addr, zz == 4 ? inc8(z, v) : dec8(z, v));
                return pre + (pfx ? 19 : 11);
            }
            set_reg(z, y, pfx, zz == 4 ? inc8(z, get_reg(z, y, pfx))
                                       : dec8(z, get_reg(z, y, pfx)));
            return pre + 4;
        case 6:                                                      /* LD r,n */
            if (y == 6) {
                const uint16_t addr = mem_operand(z, pfx);
                wr(z, addr, fetch(z));
                return pre + (pfx ? 15 : 10);
            }
            set_reg(z, y, pfx, fetch(z));
            return pre + 7;
        default:
            switch (y) {
            case 0: {                                                /* RLCA */
                const uint8_t c = (uint8_t)(z->a >> 7);
                z->a = (uint8_t)((z->a << 1) | c);
                z->f = (uint8_t)((z->f & (FS | FZ | FP)) | (z->a & (FX | FY)) | c);
                return pre + 4;
            }
            case 1: {                                                /* RRCA */
                const uint8_t c = (uint8_t)(z->a & 1);
                z->a = (uint8_t)((z->a >> 1) | (c << 7));
                z->f = (uint8_t)((z->f & (FS | FZ | FP)) | (z->a & (FX | FY)) | c);
                return pre + 4;
            }
            case 2: {                                                /* RLA */
                const uint8_t c = (uint8_t)(z->a >> 7);
                z->a = (uint8_t)((z->a << 1) | (z->f & FC));
                z->f = (uint8_t)((z->f & (FS | FZ | FP)) | (z->a & (FX | FY)) | c);
                return pre + 4;
            }
            case 3: {                                                /* RRA */
                const uint8_t c = (uint8_t)(z->a & 1);
                z->a = (uint8_t)((z->a >> 1) | ((z->f & FC) << 7));
                z->f = (uint8_t)((z->f & (FS | FZ | FP)) | (z->a & (FX | FY)) | c);
                return pre + 4;
            }
            case 4: daa(z); return pre + 4;                          /* DAA */
            case 5:                                                  /* CPL */
                z->a = (uint8_t)~z->a;
                z->f = (uint8_t)((z->f & (FS | FZ | FP | FC)) | FH | FN |
                                 (z->a & (FX | FY)));
                return pre + 4;
            case 6:                                                  /* SCF */
                z->f = (uint8_t)((z->f & (FS | FZ | FP)) | FC | (z->a & (FX | FY)));
                return pre + 4;
            default:                                                 /* CCF */
                z->f = (uint8_t)(((z->f & (FS | FZ | FP | FC)) |
                                  ((z->f & FC) ? FH : 0) | (z->a & (FX | FY))) ^ FC);
                return pre + 4;
            }
        }

    case 1:
        if (y == 6 && zz == 6) {                                     /* HALT */
            z->halted = 1;
            return pre + 4;
        }
        if (y == 6) {                                                /* LD (HL),r */
            const uint16_t addr = mem_operand(z, pfx);
            wr(z, addr, get_reg(z, zz, 0));
            return pre + (pfx ? 15 : 7);
        }
        if (zz == 6) {                                               /* LD r,(HL) */
            const uint16_t addr = mem_operand(z, pfx);
            set_reg(z, y, 0, rd(z, addr));
            return pre + (pfx ? 15 : 7);
        }
        set_reg(z, y, pfx, get_reg(z, zz, pfx));                     /* LD r,r' */
        return pre + 4;

    case 2:                                                          /* ALU r */
        if (zz == 6) {
            const uint16_t addr = mem_operand(z, pfx);
            alu(z, y, rd(z, addr));
            return pre + (pfx ? 15 : 7);
        }
        alu(z, y, get_reg(z, zz, pfx));
        return pre + 4;

    default:
        switch (zz) {
        case 0:                                                      /* RET cc */
            if (condition(z, y)) {
                z->pc = pop16(z);
                z->wz = z->pc;
                return pre + 11;
            }
            return pre + 5;
        case 1:
            if (q == 0) {                                            /* POP rp2 */
                const uint16_t v = pop16(z);
                if (p == 3) {
                    z->a = (uint8_t)(v >> 8);
                    z->f = (uint8_t)v;
                } else {
                    set_rp(z, p, pfx, v);
                }
                return pre + 10;
            }
            switch (p) {
            case 0:                                                  /* RET */
                z->pc = pop16(z);
                z->wz = z->pc;
                return pre + 10;
            case 1: {                                                /* EXX */
                uint8_t t;
                t = z->b; z->b = z->b_; z->b_ = t;
                t = z->c; z->c = z->c_; z->c_ = t;
                t = z->d; z->d = z->d_; z->d_ = t;
                t = z->e; z->e = z->e_; z->e_ = t;
                t = z->h; z->h = z->h_; z->h_ = t;
                t = z->l; z->l = z->l_; z->l_ = t;
                return pre + 4;
            }
            case 2:                                                  /* JP (HL) */
                z->pc = get_xhl(z, pfx);
                return pre + 4;
            default:                                                 /* LD SP,HL */
                z->sp = get_xhl(z, pfx);
                return pre + 6;
            }
        case 2: {                                                    /* JP cc,nn */
            const uint16_t nn = fetch16(z);
            z->wz = nn;
            if (condition(z, y)) z->pc = nn;
            return pre + 10;
        }
        case 3:
            switch (y) {
            case 0: {                                                /* JP nn */
                const uint16_t nn = fetch16(z);
                z->pc = nn;
                z->wz = nn;
                return pre + 10;
            }
            case 1:                                                  /* CB prefix */
                return pre + exec_cb(z, pfx);
            case 2: {                                                /* OUT (n),A */
                const uint8_t n = fetch(z);
                port_out(z, (uint16_t)((z->a << 8) | n), z->a);
                z->wz = (uint16_t)((z->a << 8) | ((n + 1) & 0xFF));
                return pre + 11;
            }
            case 3: {                                                /* IN A,(n) */
                const uint8_t n = fetch(z);
                const uint16_t port = (uint16_t)((z->a << 8) | n);
                z->a = port_in(z, port);
                z->wz = (uint16_t)(port + 1);
                return pre + 11;
            }
            case 4: {                                                /* EX (SP),HL */
                const uint16_t v = rd16(z, z->sp);
                wr16(z, z->sp, get_xhl(z, pfx));
                set_xhl(z, pfx, v);
                z->wz = v;
                return pre + 19;
            }
            case 5: {                                                /* EX DE,HL */
                const uint16_t t = get_de(z);
                set_de(z, get_hl(z));
                set_hl(z, t);
                return pre + 4;
            }
            case 6:                                                  /* DI */
                z->iff1 = z->iff2 = 0;
                return pre + 4;
            default:                                                 /* EI */
                z->iff1 = z->iff2 = 1;
                z->ei_pending = 1;
                return pre + 4;
            }
        case 4: {                                                    /* CALL cc,nn */
            const uint16_t nn = fetch16(z);
            z->wz = nn;
            if (condition(z, y)) {
                push16(z, z->pc);
                z->pc = nn;
                return pre + 17;
            }
            return pre + 10;
        }
        case 5:
            if (q == 0) {                                            /* PUSH rp2 */
                push16(z, p == 3 ? (uint16_t)((z->a << 8) | z->f)
                                 : get_rp(z, p, pfx));
                return pre + 11;
            }
            switch (p) {
            case 0: {                                                /* CALL nn */
                const uint16_t nn = fetch16(z);
                push16(z, z->pc);
                z->pc = nn;
                z->wz = nn;
                return pre + 17;
            }
            case 1:                                                  /* DD */
                return pre + exec_main(z, 0xDD);
            case 2:                                                  /* ED */
                return pre + exec_ed(z);
            default:                                                 /* FD */
                return pre + exec_main(z, 0xFD);
            }
        case 6:                                                      /* ALU n */
            alu(z, y, fetch(z));
            return pre + 7;
        default:                                                     /* RST */
            push16(z, z->pc);
            z->pc = (uint16_t)(y * 8);
            z->wz = z->pc;
            return pre + 11;
        }
    }
}

/* ------------------------------------------------------------------ API */

void z80_reset(Z80 *z)
{
    if (!s_tables_ready) init_tables();
    z->a = z->f = 0xFF;
    z->b = z->c = z->d = z->e = z->h = z->l = 0xFF;
    z->a_ = z->f_ = z->b_ = z->c_ = z->d_ = z->e_ = z->h_ = z->l_ = 0xFF;
    z->ix = z->iy = 0xFFFF;
    z->sp = 0xFFFF;
    z->pc = 0;
    z->wz = 0;
    z->i = z->r = 0;
    z->iff1 = z->iff2 = 0;
    z->im = 0;
    z->halted = 0;
    z->ei_pending = 0;
    z->nmi_pending = 0;
}

int z80_step(Z80 *z)
{
    int t;

    if (z->nmi_pending) {
        z->nmi_pending = 0;
        z->halted = 0;
        z->iff1 = 0;
        inc_r(z);
        push16(z, z->pc);
        z->pc = 0x0066;
        z->wz = z->pc;
        z->ei_pending = 0;
        z->cycles += 11;
        return 11;
    }
    if (z->int_line && z->iff1 && !z->ei_pending) {
        z->halted = 0;
        z->iff1 = z->iff2 = 0;
        inc_r(z);
        switch (z->im) {
        case 2: {
            const uint16_t vec = (uint16_t)((z->i << 8) | z->int_vector);
            push16(z, z->pc);
            z->pc = rd16(z, vec);
            t = 19;
            break;
        }
        default:
            /* IM 1, and IM 0 with the pulled-up bus reading RST 38h. */
            push16(z, z->pc);
            z->pc = 0x0038;
            t = 13;
            break;
        }
        z->wz = z->pc;
        z->cycles += (uint64_t)t;
        return t;
    }

    z->ei_pending = 0;
    if (z->halted) {
        inc_r(z);
        z->cycles += 4;
        return 4;
    }
    t = exec_main(z, 0);
    z->cycles += (uint64_t)t;
    return t;
}
