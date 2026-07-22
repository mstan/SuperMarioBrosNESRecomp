/* super-mario-bros_full_bank01_part11.c — PRG bank 1 function bodies (sub-part 11).
 * STANDALONE translation unit — compiled independently (in
 * parallel with every other bank part/sub-part and the
 * umbrella super-mario-bros_full.c). Do not compile as part of another TU or
 * edit directly; the source of truth is the recompiler's
 * code_generator.c. Renamed to drop the _partNN suffix if
 * this bank turned out to fit in a single sub-part. */

#include "super-mario-bros_full_decls.h"

void func_E83F(void) {
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_E83F");
#endif
label_E83F:;
    /* $E83F: FC */ maybe_trigger_vblank(4); (void)nes_read((0x0C0C + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_E842:;
    /* $E842: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xE842); return;
}

void func_F118(void) {
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_F118");
#endif
label_F118:;
    /* $F118: 1A */ maybe_trigger_vblank(2); /* NOP */
label_F119:;
    /* $F119: 02 */ maybe_trigger_vblank(2); /* ILLEGAL $02 — skip 1 */
label_F11A:;
    /* $F11A: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x3F; FLAG_NZ(g_cpu.A);
label_F11C:;
    /* $F11C: 99 */ maybe_trigger_vblank(5); nes_write((0x021A + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_F11F:;
    /* $F11F: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x021E + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_F122:;
    /* $F122: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x3F; FLAG_NZ(g_cpu.A);
label_F124:;
    /* $F124: 09 */ maybe_trigger_vblank(2); g_cpu.A |= 0x40; FLAG_NZ(g_cpu.A);
label_F126:;
    /* $F126: 99 */ maybe_trigger_vblank(5); nes_write((0x021E + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_F129:; /* ExPlyrAt */
    /* $F129: 60 */ maybe_trigger_vblank(6); 
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
    return;
}

void func_F144(void) {
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_F144");
#endif
label_F144:;
    /* $F144: F1 */ maybe_trigger_vblank(5); { uint8_t m=nes_read((nes_read16zp(0xA6) + g_cpu.Y) & 0xFFFF); int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_F146:;
    /* $F146: 08 */ maybe_trigger_vblank(3); { uint8_t p = (g_cpu.N<<7)|(g_cpu.V<<6)|0x30|(g_cpu.D<<3)|(g_cpu.I<<2)|(g_cpu.Z<<1)|g_cpu.C;
  g_ram[0x100 + g_cpu.S] = p; g_cpu.S--; }
label_F147:;
    /* $F147: 60 */ maybe_trigger_vblank(6); 
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
    return;
}

void func_D61A(void) {
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_D61A");
#endif
label_D61A:;
    /* $D61A: 86 */ maybe_trigger_vblank(3); nes_write(0xA5, g_cpu.X);
label_D61C:;
    /* $D61C: 6D */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x00A4); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_D61F:;
    /* $D61F: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) { maybe_trigger_vblank(1); goto label_D626; }
label_D621:;
    /* $D621: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x00 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x00); g_cpu.A=r&0xFF; }
label_D623:;
    /* $D623: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); func_D628(); return;
label_D626:; /* PPHSubt */
    /* $D626: E9 */ maybe_trigger_vblank(2); { uint8_t m=0x00; int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_D628:; /* SetPVar */
    /* $D628: 85 */ maybe_trigger_vblank(3); nes_write(0x6D, g_cpu.A);
label_D62A:;
    /* $D62A: 8C */ maybe_trigger_vblank(4); nes_write(0x03A1, g_cpu.Y);
label_D62D:;
    /* $D62D: 20 */ maybe_trigger_vblank(6); func_DC21();
label_D630:; /* ExXMP */
    /* $D630: 60 */ maybe_trigger_vblank(6); 
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
    return;
}

void func_D7A9(void) {
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_D7A9");
#endif
label_D7A9:;
    /* $D7A9: 20 */ maybe_trigger_vblank(6); nes_dispatch_call(0x1E95, -1);
label_D7AC:;
    /* $D7AC: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x02; FLAG_NZ(g_cpu.A);
label_D7AE:;
    /* $D7AE: B4 */ maybe_trigger_vblank(4); g_cpu.Y = nes_read((0x16 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.Y);
label_D7B0:;
    /* $D7B0: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x05; g_cpu.C=(g_cpu.Y>=0x05)?1:0; FLAG_NZ(r&0xFF); }
label_D7B2:;
    /* $D7B2: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_D7B6; }
label_D7B4:;
    /* $D7B4: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x06; FLAG_NZ(g_cpu.A);
label_D7B6:; /* GoombaPoints */
    /* $D7B6: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x06; g_cpu.C=(g_cpu.Y>=0x06)?1:0; FLAG_NZ(r&0xFF); }
label_D7B8:;
    /* $D7B8: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_D7BC; }
label_D7BA:;
    /* $D7BA: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x01; FLAG_NZ(g_cpu.A);
label_D7BC:; /* EnemySmackScore */
    /* $D7BC: 20 */ maybe_trigger_vblank(6); func_DA11();
label_D7BF:;
    /* $D7BF: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x08; FLAG_NZ(g_cpu.A);
label_D7C1:;
    /* $D7C1: 85 */ maybe_trigger_vblank(3); nes_write(0xFF, g_cpu.A);
label_D7C3:; /* ExHCF */
    /* $D7C3: 60 */ maybe_trigger_vblank(6); 
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
    return;
}

void func_D8C4(void) {
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_D8C4");
#endif
label_D8C4:;
    /* $D8C4: 34 */ maybe_trigger_vblank(4); (void)nes_read((0xB5 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_D8C6:;
    /* $D8C6: 1E */ maybe_trigger_vblank(7); { uint16_t a=(0x0729 + g_cpu.X) & 0xFFFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_D8C9:;
    /* $D8C9: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x02; g_cpu.C=(g_cpu.A>=0x02)?1:0; FLAG_NZ(r&0xFF); }
label_D8CB:;
    /* $D8CB: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) { maybe_trigger_vblank(1); goto label_D8F9; }
label_D8CD:;
    /* $D8CD: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x16 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_D8CF:;
    /* $D8CF: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x06; g_cpu.C=(g_cpu.A>=0x06)?1:0; FLAG_NZ(r&0xFF); }
label_D8D1:;
    /* $D8D1: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_D8F8; }
label_D8D3:;
    /* $D8D3: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x08; FLAG_NZ(g_cpu.A);
label_D8D5:;
    /* $D8D5: 85 */ maybe_trigger_vblank(3); nes_write(0xFF, g_cpu.A);
label_D8D7:;
    /* $D8D7: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x1E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_D8D9:;
    /* $D8D9: 09 */ maybe_trigger_vblank(2); g_cpu.A |= 0x80; FLAG_NZ(g_cpu.A);
label_D8DB:;
    /* $D8DB: 95 */ maybe_trigger_vblank(4); nes_write((0x1E + g_cpu.X) & 0xFF, g_cpu.A);
label_D8DD:;
    /* $D8DD: 20 */ maybe_trigger_vblank(6); func_DA05();
label_D8E0:;
    /* $D8E0: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xD84F + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_D8E3:;
    /* $D8E3: 95 */ maybe_trigger_vblank(4); nes_write((0x58 + g_cpu.X) & 0xFF, g_cpu.A);
label_D8E5:;
    /* $D8E5: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x03; FLAG_NZ(g_cpu.A);
label_D8E7:;
    /* $D8E7: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_D8E8:;
    /* $D8E8: 6D */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x0484); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_D8EB:;
    /* $D8EB: BC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read((0x0796 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.Y);
label_D8EE:;
    /* $D8EE: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x03; g_cpu.C=(g_cpu.Y>=0x03)?1:0; FLAG_NZ(r&0xFF); }
label_D8F0:;
    /* $D8F0: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_D8F5; }
label_D8F2:;
    /* $D8F2: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xD892 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_D8F5:; /* KSPts */
    /* $D8F5: 20 */ maybe_trigger_vblank(6); func_DA11();
label_D8F8:; /* ExPEC */
    /* $D8F8: 60 */ maybe_trigger_vblank(6); 
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
    return;
label_D8F9:; /* ChkForPlayerInjury */
    /* $D8F9: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x9F); FLAG_NZ(g_cpu.A);
label_D8FB:;
    /* $D8FB: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) { maybe_trigger_vblank(1); goto label_D8FF; }
label_D8FD:;
    /* $D8FD: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(2); call_by_address(0xD969); return; }
label_D8FF:; /* ChkInj */
    /* $D8FF: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x16 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_D901:;
    /* $D901: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x07; g_cpu.C=(g_cpu.A>=0x07)?1:0; FLAG_NZ(r&0xFF); }
label_D903:;
    /* $D903: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) { maybe_trigger_vblank(1); goto label_D90E; }
label_D905:;
    /* $D905: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xCE); FLAG_NZ(g_cpu.A);
label_D907:;
    /* $D907: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_D908:;
    /* $D908: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x0C + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x0C); g_cpu.A=r&0xFF; }
label_D90A:;
    /* $D90A: D5 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0xCF + g_cpu.X) & 0xFF); int r=g_cpu.A-m; g_cpu.C=(g_cpu.A>=m)?1:0; FLAG_NZ(r&0xFF); }
label_D90C:;
    /* $D90C: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) { maybe_trigger_vblank(1); call_by_address(0xD969); return; }
label_D90E:; /* ChkETmrs */
    /* $D90E: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0791); FLAG_NZ(g_cpu.A);
label_D911:;
    /* $D911: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); call_by_address(0xD969); return; }
label_D913:;
    /* $D913: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x079E); FLAG_NZ(g_cpu.A);
label_D916:;
    /* $D916: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_D955; }
label_D918:;
    /* $D918: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read_hooked(0xD918, 0x03AD); FLAG_NZ(g_cpu.A);
label_D91B:;
    /* $D91B: CD */ maybe_trigger_vblank(4); { uint8_t m=nes_read_hooked(0xD91B, 0x03AE); int r=g_cpu.A-m; g_cpu.C=(g_cpu.A>=m)?1:0; FLAG_NZ(r&0xFF); }
label_D91E:;
    /* $D91E: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) { maybe_trigger_vblank(1); goto label_D923; }
label_D920:;
    /* $D920: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); func_D9F6(); return;
label_D923:; /* TInjE */
    /* $D923: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x46 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_D925:;
    /* $D925: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x01; g_cpu.C=(g_cpu.A>=0x01)?1:0; FLAG_NZ(r&0xFF); }
label_D927:;
    /* $D927: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_D92C; }
label_D929:;
    /* $D929: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); func_D9FF(); return;
label_D92C:; /* InjurePlayer */
    /* $D92C: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x079E); FLAG_NZ(g_cpu.A);
label_D92F:;
    /* $D92F: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_D955; }
label_D931:; /* ForceInjury */
    /* $D931: AE */ maybe_trigger_vblank(4); g_cpu.X = nes_read(0x0756); FLAG_NZ(g_cpu.X);
label_D934:;
    /* $D934: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_D958; }
label_D936:;
    /* $D936: 8D */ maybe_trigger_vblank(4); nes_write(0x0756, g_cpu.A);
label_D939:;
    /* $D939: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x08; FLAG_NZ(g_cpu.A);
label_D93B:;
    /* $D93B: 8D */ maybe_trigger_vblank(4); nes_write(0x079E, g_cpu.A);
label_D93E:;
    /* $D93E: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_D93F:;
    /* $D93F: 85 */ maybe_trigger_vblank(3); nes_write(0xFF, g_cpu.A);
label_D941:;
    /* $D941: 20 */ maybe_trigger_vblank(6); nes_dispatch_call(0x85F1, -1);
label_D944:;
    /* $D944: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x0A; FLAG_NZ(g_cpu.A);
label_D946:; /* SetKRout */
    /* $D946: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x01; FLAG_NZ(g_cpu.Y);
label_D948:; /* SetPRout */
    /* $D948: 85 */ maybe_trigger_vblank(3); nes_write(0x0E, g_cpu.A);
label_D94A:;
    /* $D94A: 84 */ maybe_trigger_vblank(3); nes_write(0x1D, g_cpu.Y);
label_D94C:;
    /* $D94C: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0xFF; FLAG_NZ(g_cpu.Y);
label_D94E:;
    /* $D94E: 8C */ maybe_trigger_vblank(4); nes_write(0x0747, g_cpu.Y);
label_D951:;
    /* $D951: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_D952:;
    /* $D952: 8C */ maybe_trigger_vblank(4); nes_write(0x0775, g_cpu.Y);
label_D955:; /* ExInjColRoutines */
    /* $D955: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x08); FLAG_NZ(g_cpu.X);
label_D957:;
    /* $D957: 60 */ maybe_trigger_vblank(6); 
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
    return;
label_D958:; /* KillPlayer */
    /* $D958: 86 */ maybe_trigger_vblank(3); nes_write(0x57, g_cpu.X);
label_D95A:;
    /* $D95A: E8 */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X+1)&0xFF; FLAG_NZ(g_cpu.X);
label_D95B:;
    /* $D95B: 86 */ maybe_trigger_vblank(3); nes_write(0xFC, g_cpu.X);
label_D95D:;
    /* $D95D: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xFC; FLAG_NZ(g_cpu.A);
label_D95F:;
    /* $D95F: 85 */ maybe_trigger_vblank(3); nes_write(0x9F, g_cpu.A);
label_D961:;
    /* $D961: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x0B; FLAG_NZ(g_cpu.A);
label_D963:;
    /* $D963: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) {
    maybe_trigger_vblank(1);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_D946;
    }
label_D965:; /* StompedEnemyPtsData */
    /* $D965: 02 */ maybe_trigger_vblank(2); /* ILLEGAL $02 — skip 1 */
label_D966:;
    /* $D966: 06 */ maybe_trigger_vblank(5); { uint16_t a=0x05; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_D968:;
    /* $D968: 06 */ maybe_trigger_vblank(5); { uint16_t a=0xB5; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_D96A:;
    /* $D96A: 16 */ maybe_trigger_vblank(6); { uint16_t a=(0xC9 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_D96C:;
    /* $D96C: 12 */ maybe_trigger_vblank(2); /* ILLEGAL $12 — skip 1 */
label_D96D:;
    /* $D96D: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) {
    maybe_trigger_vblank(1);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_D92C;
    }
label_D96F:;
    /* $D96F: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x04; FLAG_NZ(g_cpu.A);
label_D971:;
    /* $D971: 85 */ maybe_trigger_vblank(3); nes_write(0xFF, g_cpu.A);
label_D973:;
    /* $D973: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x16 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_D975:;
    /* $D975: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x00; FLAG_NZ(g_cpu.Y);
label_D977:;
    /* $D977: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x14; g_cpu.C=(g_cpu.A>=0x14)?1:0; FLAG_NZ(r&0xFF); }
label_D979:;
    /* $D979: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_D996; }
label_D97B:;
    /* $D97B: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x08; g_cpu.C=(g_cpu.A>=0x08)?1:0; FLAG_NZ(r&0xFF); }
label_D97D:;
    /* $D97D: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_D996; }
label_D97F:;
    /* $D97F: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x33; g_cpu.C=(g_cpu.A>=0x33)?1:0; FLAG_NZ(r&0xFF); }
label_D981:;
    /* $D981: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_D996; }
label_D983:;
    /* $D983: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x0C; g_cpu.C=(g_cpu.A>=0x0C)?1:0; FLAG_NZ(r&0xFF); }
label_D985:;
    /* $D985: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_D996; }
label_D987:;
    /* $D987: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_D988:;
    /* $D988: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x05; g_cpu.C=(g_cpu.A>=0x05)?1:0; FLAG_NZ(r&0xFF); }
label_D98A:;
    /* $D98A: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_D996; }
label_D98C:;
    /* $D98C: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_D98D:;
    /* $D98D: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x11; g_cpu.C=(g_cpu.A>=0x11)?1:0; FLAG_NZ(r&0xFF); }
label_D98F:;
    /* $D98F: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_D996; }
label_D991:;
    /* $D991: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_D992:;
    /* $D992: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x07; g_cpu.C=(g_cpu.A>=0x07)?1:0; FLAG_NZ(r&0xFF); }
label_D994:;
    /* $D994: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_D9B3; }
label_D996:; /* EnemyStompedPts */
    /* $D996: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xD965 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_D999:;
    /* $D999: 20 */ maybe_trigger_vblank(6); func_DA11();
label_D99C:;
    /* $D99C: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x46 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_D99E:;
    /* $D99E: 48 */ maybe_trigger_vblank(3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_D99F:;
    /* $D99F: 20 */ maybe_trigger_vblank(6); func_E02F();
label_D9A2:;
    /* $D9A2: 68 */ maybe_trigger_vblank(4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_D9A3:;
    /* $D9A3: 95 */ maybe_trigger_vblank(4); nes_write((0x46 + g_cpu.X) & 0xFF, g_cpu.A);
label_D9A5:;
    /* $D9A5: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x20; FLAG_NZ(g_cpu.A);
label_D9A7:;
    /* $D9A7: 95 */ maybe_trigger_vblank(4); nes_write((0x1E + g_cpu.X) & 0xFF, g_cpu.A);
label_D9A9:;
    /* $D9A9: 20 */ maybe_trigger_vblank(6); func_C363();
label_D9AC:;
    /* $D9AC: 95 */ maybe_trigger_vblank(4); nes_write((0x58 + g_cpu.X) & 0xFF, g_cpu.A);
label_D9AE:;
    /* $D9AE: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xFD; FLAG_NZ(g_cpu.A);
label_D9B0:;
    /* $D9B0: 85 */ maybe_trigger_vblank(3); nes_write(0x9F, g_cpu.A);
label_D9B2:;
    /* $D9B2: 60 */ maybe_trigger_vblank(6); 
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
    return;
label_D9B3:; /* ChkForDemoteKoopa */
    /* $D9B3: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x09; g_cpu.C=(g_cpu.A>=0x09)?1:0; FLAG_NZ(r&0xFF); }
label_D9B5:;
    /* $D9B5: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) { maybe_trigger_vblank(1); goto label_D9D4; }
label_D9B7:;
    /* $D9B7: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x01; FLAG_NZ(g_cpu.A);
label_D9B9:;
    /* $D9B9: 95 */ maybe_trigger_vblank(4); nes_write((0x16 + g_cpu.X) & 0xFF, g_cpu.A);
label_D9BB:;
    /* $D9BB: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x00; FLAG_NZ(g_cpu.Y);
label_D9BD:;
    /* $D9BD: 94 */ maybe_trigger_vblank(4); nes_write((0x1E + g_cpu.X) & 0xFF, g_cpu.Y);
label_D9BF:;
    /* $D9BF: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x03; FLAG_NZ(g_cpu.A);
label_D9C1:;
    /* $D9C1: 20 */ maybe_trigger_vblank(6); func_DA11();
label_D9C4:;
    /* $D9C4: 20 */ maybe_trigger_vblank(6); func_C363();
label_D9C7:;
    /* $D9C7: 20 */ maybe_trigger_vblank(6); func_DA05();
label_D9CA:;
    /* $D9CA: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xD851 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_D9CD:;
    /* $D9CD: 95 */ maybe_trigger_vblank(4); nes_write((0x58 + g_cpu.X) & 0xFF, g_cpu.A);
label_D9CF:;
    /* $D9CF: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); func_D9F1(); return;
label_D9D4:; /* HandleStompedShellE */
    /* $D9D4: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x04; FLAG_NZ(g_cpu.A);
label_D9D6:;
    /* $D9D6: 95 */ maybe_trigger_vblank(4); nes_write((0x1E + g_cpu.X) & 0xFF, g_cpu.A);
label_D9D8:;
    /* $D9D8: EE */ maybe_trigger_vblank(6); { uint16_t a=0x0484; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_D9DB:;
    /* $D9DB: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0484); FLAG_NZ(g_cpu.A);
label_D9DE:;
    /* $D9DE: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_D9DF:;
    /* $D9DF: 6D */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x0791); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_D9E2:;
    /* $D9E2: 20 */ maybe_trigger_vblank(6); func_DA11();
label_D9E5:;
    /* $D9E5: EE */ maybe_trigger_vblank(6); { uint16_t a=0x0791; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_D9E8:;
    /* $D9E8: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x076A); FLAG_NZ(g_cpu.Y);
label_D9EB:;
    /* $D9EB: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xD9D2 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_D9EE:;
    /* $D9EE: 9D */ maybe_trigger_vblank(5); nes_write((0x0796 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_D9F1:; /* SBnce */
    /* $D9F1: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xFC; FLAG_NZ(g_cpu.A);
label_D9F3:;
    /* $D9F3: 85 */ maybe_trigger_vblank(3); nes_write(0x9F, g_cpu.A);
label_D9F5:;
    /* $D9F5: 60 */ maybe_trigger_vblank(6); 
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
    return;
label_D9F6:; return;
label_D9F8:; return;
label_D9FA:; return;
label_D9FC:; return;
label_D9FF:; return;
label_DA02:; return;
label_DA05:; return;
label_DA07:; return;
label_DA0A:; return;
label_DA0C:; return;
label_DA0D:; return;
label_DA0F:; return;
label_DA10:; return;
label_DA11:; return;
label_DA14:; return;
label_DA16:; return;
label_DA19:; return;
label_DA1B:; return;
label_DA1E:; return;
label_DA21:; return;
label_DA24:; return;
label_DA25:; return;
label_DA27:; return;
label_DA2A:; return;
label_DA2C:; return;
label_DA2F:; return;
label_DA32:; return;
label_DA35:; return;
label_DA36:; return;
label_DA38:; return;
label_DA3B:; return;
label_DA3D:; return;
label_DA3F:; return;
label_DA41:; return;
label_DA43:; return;
label_DA45:; return;
label_DA47:; return;
label_DA49:; return;
label_DA4B:; return;
label_DA4E:; return;
label_DA50:; return;
label_DA53:; return;
label_DA54:; return;
label_DA56:; return;
label_DA58:; return;
label_DA59:; return;
label_DA5A:; return;
label_DA5C:; return;
label_DA5E:; return;
label_DA60:; return;
label_DA62:; return;
label_DA64:; return;
label_DA66:; return;
label_DA68:; return;
label_DA6A:; return;
label_DA6C:; return;
label_DA6F:; return;
label_DA71:; return;
label_DA72:; return;
label_DA73:; return;
label_DA74:; return;
label_DA75:; return;
label_DA77:; return;
label_DA78:; return;
label_DA7B:; return;
label_DA7D:; return;
label_DA7F:; return;
label_DA81:; return;
label_DA83:; return;
label_DA86:; return;
label_DA88:; return;
label_DA8A:; return;
label_DA8D:; return;
label_DA90:; return;
label_DA92:; return;
label_DA95:; return;
label_DA98:; return;
label_DA9B:; return;
label_DA9E:; return;
label_DAA1:; return;
label_DAA4:; return;
label_DAA7:; return;
label_DAAA:; return;
label_DAAB:; return;
label_DAAC:; return;
label_DAAE:; return;
label_DAAF:; return;
label_DAB1:; return;
label_DAB3:; return;
label_DAB4:; return;
label_DAB7:; return;
label_DAB9:; return;
label_DABB:; return;
label_DABD:; return;
label_DABF:; return;
label_DAC1:; return;
label_DAC3:; return;
label_DAC5:; return;
label_DAC7:; return;
label_DAC9:; return;
label_DACC:; return;
label_DACD:; return;
label_DACF:; return;
label_DAD1:; return;
label_DAD4:; return;
label_DAD7:; return;
label_DAD9:; return;
label_DADA:; return;
label_DADB:; return;
label_DADE:; return;
label_DAE0:; return;
label_DAE3:; return;
label_DAE4:; return;
label_DAE6:; return;
label_DAE8:; return;
label_DAEB:; return;
label_DAED:; return;
label_DAF0:; return;
label_DAF1:; return;
label_DAF4:; return;
label_DAF6:; return;
label_DAF8:; return;
label_DAFB:; return;
label_DAFD:; return;
label_DAFF:; return;
label_DB02:; return;
label_DB04:; return;
label_DB07:; return;
label_DB08:; return;
label_DB0A:; return;
label_DB0C:; return;
label_DB0F:; return;
label_DB11:; return;
label_DB14:; return;
label_DB15:; return;
label_DB16:; return;
label_DB17:; return;
label_DB1A:; return;
label_DB1C:; return;
label_DB1E:; return;
label_DB20:; return;
label_DB22:; return;
label_DB24:; return;
label_DB26:; return;
label_DB28:; return;
label_DB2A:; return;
label_DB2C:; return;
label_DB2E:; return;
label_DB30:; return;
label_DB32:; return;
label_DB34:; return;
label_DB36:; return;
label_DB38:; return;
label_DB3A:; return;
label_DB3B:; return;
label_DB3C:; return;
label_DB3E:; return;
label_DB40:; return;
label_DB42:; return;
label_DB44:; return;
label_DB45:; return;
label_DB47:; return;
label_DB4A:; return;
label_DB4D:; return;
label_DB4F:; return;
label_DB51:; return;
label_DB53:; return;
label_DB55:; return;
label_DB57:; return;
label_DB59:; return;
label_DB5B:; return;
label_DB5C:; return;
label_DB5F:; return;
label_DB62:; return;
label_DB64:; return;
label_DB65:; return;
label_DB68:; return;
label_DB6A:; return;
label_DB6C:; return;
label_DB6D:; return;
label_DB6E:; return;
label_DB71:; return;
label_DB72:; return;
label_DB73:; return;
label_DB75:; return;
label_DB78:; return;
label_DB7A:; return;
label_DB7B:; return;
label_DB7E:; return;
label_DB80:; return;
label_DB83:; return;
label_DB86:; return;
label_DB88:; return;
label_DB8A:; return;
label_DB8C:; return;
label_DB8E:; return;
label_DB91:; return;
label_DB93:; return;
label_DB95:; return;
label_DB98:; return;
label_DB9A:; return;
label_DB9C:; return;
label_DB9F:; return;
label_DBA1:; return;
label_DBA4:; return;
label_DBA5:; return;
label_DBA7:; return;
label_DBAA:; return;
label_DBAD:; return;
label_DBAE:; return;
label_DBB0:; return;
label_DBB3:; return;
label_DBB5:; return;
label_DBB7:; return;
label_DBB9:; return;
label_DBBA:; return;
label_DBBC:; return;
label_DBBF:; return;
label_DBC0:; return;
label_DBC3:; return;
label_DBC5:; return;
label_DBC7:; return;
label_DBC9:; return;
label_DBCB:; return;
label_DBCD:; return;
label_DBCF:; return;
label_DBD2:; return;
label_DBD3:; return;
label_DBD6:; return;
label_DBD8:; return;
label_DBDA:; return;
label_DBDC:; return;
label_DBDE:; return;
label_DBE0:; return;
label_DBE2:; return;
label_DBE4:; return;
label_DBE6:; return;
label_DBE8:; return;
label_DBEA:; return;
label_DBEB:; return;
label_DBED:; return;
label_DBF0:; return;
label_DBF2:; return;
label_DBF4:; return;
label_DBF5:; return;
label_DBF7:; return;
label_DBF9:; return;
label_DBFC:; return;
label_DBFD:; return;
label_DC00:; return;
label_DC02:; return;
label_DC04:; return;
label_DC06:; return;
label_DC09:; return;
label_DC0A:; return;
label_DC0D:; return;
label_DC0F:; return;
label_DC11:; return;
label_DC14:; return;
label_DC16:; return;
label_DC17:; return;
label_DC19:; return;
label_DC1A:; return;
label_DC1C:; return;
label_DC1D:; return;
label_DC20:; return;
label_DC23:; return;
label_DC25:; return;
label_DC27:; return;
label_DC29:; return;
label_DC2B:; return;
label_DC2D:; return;
label_DC2F:; return;
label_DC30:; return;
label_DC32:; return;
label_DC34:; return;
label_DC35:; return;
label_DC37:; return;
label_DC39:; return;
label_DC3B:; return;
label_DC3D:; return;
label_DC40:; return;
label_DC41:; return;
label_DC44:; return;
label_DC46:; return;
label_DC48:; return;
label_DC4A:; return;
label_DC4B:; return;
label_DC4D:; return;
label_DC4F:; return;
label_DC51:; return;
label_DC52:; return;
label_DC54:; return;
label_DC55:; return;
label_DC56:; return;
label_DC57:; return;
label_DC59:; return;
label_DC5A:; return;
label_DC5D:; return;
label_DC5F:; return;
label_DC61:; return;
label_DC62:; return;
label_DC65:; return;
label_DC67:; return;
label_DC69:; return;
label_DC6B:; return;
label_DC6D:; return;
label_DC6F:; return;
label_DC71:; return;
label_DC73:; return;
label_DC75:; return;
label_DC78:; return;
label_DC7A:; return;
label_DC7C:; return;
label_DC7E:; return;
label_DC80:; return;
label_DC82:; return;
label_DC84:; return;
label_DC86:; return;
label_DC88:; return;
label_DC8A:; return;
label_DC8C:; return;
label_DC8E:; return;
label_DC91:; return;
label_DC93:; return;
label_DC95:; return;
label_DC97:; return;
label_DC98:; return;
label_DC9A:; return;
label_DC9D:; return;
label_DC9F:; return;
label_DCA2:; return;
label_DCA4:; return;
label_DCA5:; return;
label_DCA8:; return;
label_DCAA:; return;
label_DCAB:; return;
label_DCAE:; return;
label_DCB0:; return;
label_DCB1:; return;
label_DCB4:; return;
label_DCB7:; return;
label_DCB9:; return;
label_DCBA:; return;
label_DCBC:; return;
label_DCBF:; return;
label_DCC1:; return;
label_DCC4:; return;
label_DCC6:; return;
label_DCC9:; return;
label_DCCB:; return;
label_DCCD:; return;
label_DCCF:; return;
label_DCD1:; return;
label_DCD3:; return;
label_DCD5:; return;
label_DCD8:; return;
label_DCDA:; return;
label_DCDD:; return;
label_DCDF:; return;
label_DCE2:; return;
label_DCE4:; return;
label_DCE7:; return;
label_DCEA:; return;
label_DCEC:; return;
label_DCEE:; return;
label_DCF0:; return;
label_DCF2:; return;
label_DCF4:; return;
label_DCF6:; return;
label_DCF8:; return;
label_DCFA:; return;
label_DCFC:; return;
label_DCFE:; return;
label_DD01:; return;
label_DD04:; return;
label_DD06:; return;
label_DD07:; return;
label_DD0A:; return;
label_DD0C:; return;
label_DD0D:; return;
label_DD0F:; return;
label_DD11:; return;
label_DD13:; return;
label_DD15:; return;
label_DD18:; return;
label_DD1A:; return;
label_DD1D:; return;
label_DD20:; return;
label_DD22:; return;
label_DD24:; return;
label_DD26:; return;
label_DD28:; return;
label_DD2A:; return;
label_DD2D:; return;
label_DD30:; return;
label_DD32:; return;
label_DD35:; return;
label_DD37:; return;
label_DD39:; return;
label_DD3B:; return;
label_DD3D:; return;
label_DD3F:; return;
label_DD41:; return;
label_DD44:; return;
label_DD47:; return;
label_DD49:; return;
label_DD4B:; return;
label_DD4D:; return;
label_DD50:; return;
label_DD52:; return;
label_DD54:; return;
label_DD57:; return;
label_DD5A:; return;
label_DD5C:; return;
label_DD5E:; return;
label_DD60:; return;
label_DD61:; return;
label_DD62:; return;
label_DD64:; return;
label_DD66:; return;
label_DD67:; return;
label_DD69:; return;
label_DD6B:; return;
label_DD6D:; return;
label_DD6F:; return;
label_DD71:; return;
label_DD73:; return;
label_DD76:; return;
label_DD78:; return;
label_DD7A:; return;
label_DD7C:; return;
label_DD7E:; return;
label_DD80:; return;
label_DD83:; return;
label_DD85:; return;
label_DD87:; return;
label_DD88:; return;
label_DD8A:; return;
label_DD8C:; return;
label_DD8E:; return;
label_DD90:; return;
label_DD92:; return;
label_DD95:; return;
label_DD97:; return;
label_DD99:; return;
label_DD9B:; return;
label_DD9C:; return;
label_DD9F:; return;
label_DDA1:; return;
label_DDA4:; return;
label_DDA6:; return;
label_DDA9:; return;
label_DDAC:; return;
label_DDAE:; return;
label_DDB1:; return;
label_DDB3:; return;
label_DDB6:; return;
label_DDB8:; return;
label_DDBB:; return;
label_DDBD:; return;
label_DDBF:; return;
label_DDC1:; return;
label_DDC3:; return;
label_DDC4:; return;
label_DDC6:; return;
label_DDC8:; return;
label_DDCA:; return;
label_DDCC:; return;
label_DDCE:; return;
label_DDD1:; return;
label_DDD3:; return;
label_DDD5:; return;
label_DDD7:; return;
label_DDD9:; return;
label_DDDC:; return;
label_DDDE:; return;
label_DDE0:; return;
label_DDE2:; return;
label_DDE4:; return;
label_DDE7:; return;
label_DDE9:; return;
label_DDEA:; return;
label_DDED:; return;
label_DDF0:; return;
label_DDF2:; return;
label_DDF4:; return;
label_DDF6:; return;
label_DDF8:; return;
label_DDFA:; return;
label_DDFC:; return;
label_DDFE:; return;
label_DDFF:; return;
label_DE02:; return;
label_DE03:; return;
label_DE05:; return;
label_DE08:; return;
label_DE0B:; return;
label_DE0E:; return;
label_DE10:; return;
label_DE13:; return;
label_DE15:; return;
label_DE18:; return;
label_DE1A:; return;
label_DE1C:; return;
label_DE1E:; return;
label_DE20:; return;
label_DE22:; return;
label_DE25:; return;
label_DE28:; return;
label_DE29:; return;
label_DE2A:; return;
label_DE2B:; return;
label_DE2D:; return;
label_DE2F:; return;
label_DE31:; return;
label_DE33:; return;
label_DE35:; return;
label_DE36:; return;
label_DE38:; return;
label_DE39:; return;
label_DE3B:; return;
label_DE3D:; return;
label_DE3F:; return;
label_DE41:; return;
label_DE43:; return;
label_DE45:; return;
label_DE47:; return;
label_DE49:; return;
label_DE4B:; return;
label_DE4E:; return;
label_DE50:; return;
label_DE52:; return;
label_DE54:; return;
label_DE56:; return;
label_DE59:; return;
label_DE5B:; return;
label_DE5D:; return;
label_DE5E:; return;
label_DE61:; return;
label_DE63:; return;
label_DE65:; return;
label_DE68:; return;
label_DE6B:; return;
label_DE6D:; return;
label_DE6E:; return;
label_DE70:; return;
label_DE73:; return;
label_DE75:; return;
label_DE77:; return;
label_DE7A:; return;
label_DE7C:; return;
label_DE7E:; return;
label_DE80:; return;
label_DE82:; return;
label_DE84:; return;
label_DE86:; return;
label_DE88:; return;
label_DE8A:; return;
label_DE8C:; return;
label_DE8E:; return;
label_DE90:; return;
label_DE93:; return;
label_DE95:; return;
label_DE96:; return;
label_DE99:; return;
label_DE9B:; return;
label_DE9D:; return;
label_DE9F:; return;
label_DEA1:; return;
label_DEA3:; return;
label_DEA5:; return;
label_DEA6:; return;
label_DEA7:; return;
label_DEA8:; return;
label_DEA9:; return;
label_DEAA:; return;
label_DEAD:; return;
label_DEAF:; return;
label_DEB1:; return;
label_DEB3:; return;
label_DEB6:; return;
label_DEB7:; return;
label_DEBA:; return;
label_DEBC:; return;
label_DEBD:; return;
label_DEBF:; return;
label_DEC1:; return;
label_DEC3:; return;
label_DEC4:; return;
label_DEC7:; return;
label_DEC9:; return;
label_DECB:; return;
label_DECE:; return;
label_DED0:; return;
label_DED3:; return;
label_DED5:; return;
label_DED8:; return;
label_DED9:; return;
label_DEDC:; return;
label_DEDD:; return;
label_DEDF:; return;
label_DEE1:; return;
label_DEE3:; return;
label_DEE4:; return;
label_DEE6:; return;
label_DEE7:; return;
label_DEE8:; return;
label_DEEA:; return;
label_DEEC:; return;
label_DEEE:; return;
label_DEF0:; return;
label_DEF2:; return;
label_DEF4:; return;
label_DEF6:; return;
label_DEF8:; return;
label_DEFA:; return;
label_DEFC:; return;
label_DEFF:; return;
label_DF01:; return;
label_DF03:; return;
label_DF05:; return;
label_DF07:; return;
label_DF09:; return;
label_DF0C:; return;
label_DF0F:; return;
label_DF11:; return;
label_DF13:; return;
label_DF14:; return;
label_DF15:; return;
label_DF16:; return;
label_DF18:; return;
label_DF1A:; return;
label_DF1C:; return;
label_DF1D:; return;
label_DF1F:; return;
label_DF21:; return;
label_DF22:; return;
label_DF25:; return;
label_DF26:; return;
label_DF29:; return;
label_DF2C:; return;
label_DF2F:; return;
label_DF32:; return;
label_DF34:; return;
label_DF36:; return;
label_DF38:; return;
label_DF3B:; return;
label_DF3E:; return;
label_DF41:; return;
label_DF44:; return;
label_DF47:; return;
label_DF4A:; return;
label_DF4B:; return;
label_DF4D:; return;
label_DF4F:; return;
label_DF51:; return;
label_DF52:; return;
label_DF54:; return;
label_DF55:; return;
label_DF57:; return;
label_DF59:; return;
label_DF5B:; return;
label_DF5E:; return;
label_DF60:; return;
label_DF62:; return;
label_DF64:; return;
label_DF66:; return;
label_DF68:; return;
label_DF6B:; return;
label_DF6D:; return;
label_DF6F:; return;
label_DF71:; return;
label_DF73:; return;
label_DF74:; return;
label_DF76:; return;
label_DF77:; return;
label_DF79:; return;
label_DF7B:; return;
label_DF7D:; return;
label_DF7F:; return;
label_DF81:; return;
label_DF82:; return;
label_DF84:; return;
label_DF87:; return;
label_DF8A:; return;
label_DF8B:; return;
label_DF8D:; return;
label_DF8E:; return;
label_DF90:; return;
label_DF92:; return;
label_DF95:; return;
label_DF96:; return;
label_DF98:; return;
label_DF99:; return;
label_DF9B:; return;
label_DF9D:; return;
label_DFA0:; return;
label_DFA1:; return;
label_DFA3:; return;
label_DFA5:; return;
label_DFA7:; return;
label_DFA9:; return;
label_DFAA:; return;
label_DFAB:; return;
label_DFAD:; return;
label_DFAF:; return;
label_DFB0:; return;
label_DFB1:; return;
label_DFB3:; return;
label_DFB4:; return;
label_DFB5:; return;
label_DFB6:; return;
label_DFB7:; return;
label_DFB8:; return;
label_DFB9:; return;
label_DFBB:; return;
label_DFBC:; return;
label_DFBD:; return;
label_DFBE:; return;
label_DFC0:; return;
label_DFC2:; return;
label_DFC5:; return;
label_DFC7:; return;
label_DFCA:; return;
label_DFCC:; return;
label_DFCE:; return;
label_DFD0:; return;
label_DFD2:; return;
label_DFD4:; return;
label_DFD6:; return;
label_DFD8:; return;
label_DFDA:; return;
label_DFDC:; return;
label_DFDF:; return;
label_DFE1:; return;
label_DFE3:; return;
label_DFE6:; return;
label_DFE8:; return;
label_DFEA:; return;
label_DFEC:; return;
label_DFEE:; return;
label_DFF0:; return;
label_DFF2:; return;
label_DFF5:; return;
label_DFF7:; return;
label_DFFA:; return;
label_DFFD:; return;
label_DFFF:; return;
label_E001:; return;
label_E003:; return;
label_E005:; return;
label_E007:; return;
label_E009:; return;
label_E00B:; return;
label_E00D:; return;
label_E00F:; return;
label_E011:; return;
label_E013:; return;
label_E016:; return;
label_E018:; return;
label_E01B:; return;
label_E01D:; return;
label_E01F:; return;
label_E021:; return;
label_E023:; return;
label_E025:; return;
label_E027:; return;
label_E029:; return;
label_E02B:; return;
label_E02D:; return;
label_E02F:; return;
label_E031:; return;
label_E033:; return;
label_E035:; return;
label_E037:; return;
label_E039:; return;
label_E03B:; return;
label_E03D:; return;
label_E03F:; return;
label_E041:; return;
label_E043:; return;
label_E046:; return;
label_E048:; return;
label_E04A:; return;
label_E04C:; return;
label_E04E:; return;
label_E051:; return;
label_E053:; return;
label_E054:; return;
label_E056:; return;
label_E058:; return;
label_E05A:; return;
label_E05C:; return;
label_E05E:; return;
label_E060:; return;
label_E061:; return;
label_E064:; return;
label_E066:; return;
label_E067:; return;
label_E069:; return;
label_E06A:; return;
label_E06C:; return;
label_E06E:; return;
label_E070:; return;
label_E072:; return;
label_E074:; return;
label_E076:; return;
label_E078:; return;
label_E079:; return;
label_E07B:; return;
label_E07E:; return;
label_E080:; return;
label_E082:; return;
label_E084:; return;
label_E086:; return;
label_E088:; return;
label_E08A:; return;
label_E08C:; return;
label_E08E:; return;
label_E090:; return;
label_E092:; return;
label_E094:; return;
label_E096:; return;
label_E098:; return;
label_E09A:; return;
label_E09D:; return;
label_E09F:; return;
label_E0A1:; return;
label_E0A4:; return;
label_E0A5:; return;
label_E0A7:; return;
label_E0A9:; return;
label_E0AB:; return;
label_E0AD:; return;
label_E0AF:; return;
label_E0B1:; return;
label_E0B3:; return;
label_E0B5:; return;
label_E0B7:; return;
label_E0B9:; return;
label_E0BB:; return;
label_E0BD:; return;
label_E0BF:; return;
label_E0C2:; return;
label_E0C4:; return;
label_E0C5:; return;
label_E0C6:; return;
label_E0C8:; return;
label_E0CA:; return;
label_E0CD:; return;
label_E0D0:; return;
label_E0D2:; return;
label_E0D4:; return;
label_E0D6:; return;
label_E0D8:; return;
label_E0DA:; return;
label_E0DB:; return;
label_E0DD:; return;
label_E0DF:; return;
label_E0E1:; return;
label_E0E2:; return;
label_E0E4:; return;
label_E0E6:; return;
label_E0E8:; return;
label_E0EA:; return;
label_E0EC:; return;
label_E0EE:; return;
label_E0EF:; return;
label_E0F0:; return;
label_E0F2:; return;
label_E0F4:; return;
label_E0F6:; return;
label_E0F9:; return;
label_E0FC:; return;
label_E0FE:; return;
label_E100:; return;
label_E102:; return;
label_E104:; return;
label_E106:; return;
label_E108:; return;
label_E10A:; return;
label_E10C:; return;
label_E10E:; return;
label_E110:; return;
label_E112:; return;
label_E115:; return;
label_E117:; return;
label_E11A:; return;
label_E11C:; return;
label_E11E:; return;
label_E11F:; return;
label_E121:; return;
label_E123:; return;
label_E124:; return;
label_E126:; return;
label_E128:; return;
label_E12A:; return;
label_E12B:; return;
label_E12D:; return;
label_E12F:; return;
label_E131:; return;
label_E133:; return;
label_E135:; return;
label_E137:; return;
label_E139:; return;
label_E13B:; return;
label_E13D:; return;
label_E140:; return;
label_E143:; return;
label_E145:; return;
label_E146:; return;
label_E148:; return;
label_E14A:; return;
label_E14C:; return;
label_E14E:; return;
label_E14F:; return;
label_E152:; return;
label_E154:; return;
label_E156:; return;
label_E158:; return;
label_E15A:; return;
label_E15B:; return;
label_E15D:; return;
label_E15E:; return;
label_E160:; return;
label_E162:; return;
label_E163:; return;
label_E166:; return;
label_E168:; return;
label_E16A:; return;
label_E16B:; return;
label_E16D:; return;
label_E16F:; return;
label_E171:; return;
label_E174:; return;
label_E176:; return;
label_E179:; return;
label_E17B:; return;
label_E17E:; return;
label_E180:; return;
label_E182:; return;
label_E185:; return;
label_E188:; return;
label_E18A:; return;
label_E18C:; return;
label_E18E:; return;
label_E191:; return;
label_E193:; return;
label_E195:; return;
label_E196:; return;
label_E199:; return;
label_E19B:; return;
label_E19D:; return;
label_E19F:; return;
label_E1A1:; return;
label_E1A4:; return;
label_E1A7:; return;
label_E1A9:; return;
label_E1AB:; return;
label_E1AD:; return;
label_E1AE:; return;
label_E1B0:; return;
label_E1B2:; return;
label_E1B5:; return;
label_E1B7:; return;
label_E1B9:; return;
label_E1BB:; return;
label_E1BD:; return;
label_E1BF:; return;
label_E1C1:; return;
label_E1C3:; return;
label_E1C5:; return;
label_E1C7:; return;
label_E1C8:; return;
label_E1CA:; return;
label_E1CC:; return;
label_E1CE:; return;
label_E1D1:; return;
label_E1D3:; return;
label_E1D6:; return;
label_E1D8:; return;
label_E1DA:; return;
label_E1DC:; return;
label_E1DE:; return;
label_E1E0:; return;
label_E1E2:; return;
label_E1E4:; return;
label_E1E6:; return;
label_E1E8:; return;
label_E1EA:; return;
label_E1EC:; return;
label_E1EE:; return;
label_E1EF:; return;
label_E1F1:; return;
label_E1F3:; return;
label_E1F4:; return;
label_E1F6:; return;
label_E1F8:; return;
label_E1FA:; return;
label_E1FC:; return;
label_E1FD:; return;
label_E1FE:; return;
label_E1FF:; return;
label_E202:; return;
label_E204:; return;
label_E207:; return;
label_E20A:; return;
label_E20C:; return;
label_E20E:; return;
label_E20F:; return;
label_E210:; return;
label_E212:; return;
label_E213:; return;
label_E216:; return;
label_E217:; return;
label_E219:; return;
label_E21A:; return;
label_E21B:; return;
label_E21C:; return;
label_E21D:; return;
label_E21F:; return;
label_E220:; return;
label_E221:; return;
label_E223:; return;
label_E226:; return;
label_E227:; return;
label_E229:; return;
label_E22B:; return;
label_E22E:; return;
label_E22F:; return;
label_E231:; return;
label_E232:; return;
label_E234:; return;
label_E236:; return;
label_E237:; return;
label_E238:; return;
label_E23A:; return;
label_E23B:; return;
label_E23D:; return;
label_E240:; return;
label_E243:; return;
label_E245:; return;
label_E247:; return;
label_E249:; return;
label_E24C:; return;
label_E24E:; return;
label_E250:; return;
label_E252:; return;
label_E254:; return;
label_E255:; return;
label_E258:; return;
label_E25A:; return;
label_E25C:; return;
label_E25F:; return;
label_E261:; return;
label_E263:; return;
label_E265:; return;
label_E267:; return;
label_E268:; return;
label_E26B:; return;
label_E26E:; return;
label_E270:; return;
label_E289:; return;
label_E28A:; return;
label_E28B:; return;
label_E28C:; return;
label_E28D:; return;
label_E28F:; return;
label_E292:; return;
label_E295:; return;
label_E298:; return;
label_E29B:; return;
label_E29C:; return;
label_E29E:; return;
label_E2A1:; return;
label_E2A3:; return;
label_E2A6:; return;
label_E2A8:; return;
label_E2A9:; return;
label_E2AA:; return;
label_E2AB:; return;
label_E2AC:; return;
label_E2AD:; return;
label_E2B0:; return;
label_E2B1:; return;
label_E2B2:; return;
label_E2B3:; return;
label_E2B5:; return;
label_E2B6:; return;
label_E2B9:; return;
label_E2BC:; return;
label_E2BE:; return;
label_E2BF:; return;
label_E2C2:; return;
label_E2C5:; return;
label_E2C6:; return;
label_E2C7:; return;
label_E2C9:; return;
label_E2CA:; return;
label_E2CD:; return;
label_E2D0:; return;
label_E2D2:; return;
label_E2D3:; return;
label_E2D6:; return;
label_E2D9:; return;
label_E2DA:; return;
label_E2DB:; return;
label_E2DD:; return;
label_E2DE:; return;
label_E2E1:; return;
label_E2E2:; return;
label_E2E4:; return;
label_E2E6:; return;
label_E2E9:; return;
label_E2EB:; return;
label_E2ED:; return;
label_E2EF:; return;
label_E2F1:; return;
label_E2F3:; return;
label_E2F5:; return;
label_E2F7:; return;
label_E2FA:; return;
label_E2FC:; return;
label_E2FE:; return;
label_E301:; return;
label_E303:; return;
label_E306:; return;
label_E309:; return;
label_E30B:; return;
label_E30C:; return;
label_E30F:; return;
label_E311:; return;
label_E313:; return;
label_E315:; return;
label_E317:; return;
label_E31A:; return;
label_E31C:; return;
label_E31F:; return;
label_E322:; return;
label_E324:; return;
label_E325:; return;
label_E327:; return;
label_E329:; return;
label_E32B:; return;
label_E32D:; return;
label_E330:; return;
label_E333:; return;
label_E335:; return;
label_E338:; return;
label_E33A:; return;
label_E33C:; return;
label_E33F:; return;
label_E342:; return;
label_E344:; return;
label_E347:; return;
label_E349:; return;
label_E34B:; return;
label_E34C:; return;
label_E34F:; return;
label_E352:; return;
label_E354:; return;
label_E357:; return;
label_E35A:; return;
label_E35C:; return;
label_E35E:; return;
label_E35F:; return;
label_E362:; return;
label_E364:; return;
label_E367:; return;
label_E369:; return;
label_E36B:; return;
label_E36E:; return;
label_E370:; return;
label_E372:; return;
label_E375:; return;
label_E378:; return;
label_E37A:; return;
label_E37B:; return;
label_E37D:; return;
label_E37E:; return;
label_E37F:; return;
label_E380:; return;
label_E382:; return;
label_E384:; return;
label_E385:; return;
label_E387:; return;
label_E388:; return;
label_E389:; return;
label_E38A:; return;
label_E38B:; return;
label_E38D:; return;
label_E38E:; return;
label_E38F:; return;
label_E392:; return;
label_E393:; return;
label_E394:; return;
label_E396:; return;
label_E397:; return;
label_E399:; return;
label_E39C:; return;
label_E39E:; return;
label_E39F:; return;
label_E3A0:; return;
label_E3A2:; return;
label_E3A3:; return;
label_E3A5:; return;
label_E3A8:; return;
label_E3AA:; return;
label_E3AC:; return;
label_E3AD:; return;
label_E3AE:; return;
label_E3B0:; return;
label_E3B1:; return;
label_E3B3:; return;
label_E3B4:; return;
label_E3B5:; return;
label_E3B8:; return;
label_E3BA:; return;
label_E3BB:; return;
label_E3BC:; return;
label_E3BF:; return;
label_E3C1:; return;
label_E3C2:; return;
label_E3C3:; return;
label_E3C6:; return;
label_E3C7:; return;
label_E3C9:; return;
label_E3CB:; return;
label_E3CD:; return;
label_E3D0:; return;
label_E3D1:; return;
label_E3D2:; return;
label_E3D3:; return;
label_E3D4:; return;
label_E3D7:; return;
label_E3D8:; return;
label_E3D9:; return;
label_E3DA:; return;
label_E3DB:; return;
label_E3DE:; return;
label_E3DF:; return;
label_E3E0:; return;
label_E3E1:; return;
label_E3E2:; return;
label_E3E4:; return;
label_E3E6:; return;
label_E3E7:; return;
label_E3E9:; return;
label_E3EB:; return;
label_E3EE:; return;
label_E3F0:; return;
label_E3F1:; return;
label_E3F3:; return;
label_E3F6:; return;
label_E3F7:; return;
label_E3F9:; return;
label_E3FB:; return;
label_E3FD:; return;
label_E3FF:; return;
label_E401:; return;
label_E402:; return;
label_E404:; return;
label_E405:; return;
label_E406:; return;
label_E407:; return;
label_E408:; return;
label_E40B:; return;
label_E40D:; return;
label_E40F:; return;
label_E410:; return;
label_E413:; return;
label_E415:; return;
label_E416:; return;
label_E418:; return;
label_E41A:; return;
label_E41B:; return;
label_E41D:; return;
label_E41F:; return;
label_E421:; return;
label_E422:; return;
label_E424:; return;
label_E426:; return;
label_E429:; return;
label_E42B:; return;
label_E42D:; return;
label_E42F:; return;
label_E431:; return;
label_E432:; return;
label_E435:; return;
label_E437:; return;
label_E43A:; return;
label_E43B:; return;
label_E43E:; return;
label_E441:; return;
label_E444:; return;
label_E446:; return;
label_E449:; return;
label_E44C:; return;
label_E44F:; return;
label_E452:; return;
label_E455:; return;
label_E456:; return;
label_E458:; return;
label_E45B:; return;
label_E45E:; return;
label_E461:; return;
label_E463:; return;
label_E466:; return;
label_E469:; return;
label_E46C:; return;
label_E46E:; return;
label_E471:; return;
label_E474:; return;
label_E477:; return;
label_E479:; return;
label_E47B:; return;
label_E47E:; return;
label_E47F:; return;
label_E480:; return;
label_E481:; return;
label_E482:; return;
label_E483:; return;
label_E485:; return;
label_E487:; return;
label_E489:; return;
label_E48B:; return;
label_E48D:; return;
label_E490:; return;
label_E492:; return;
label_E495:; return;
label_E496:; return;
label_E499:; return;
label_E49B:; return;
label_E49D:; return;
label_E49F:; return;
label_E4A2:; return;
label_E4A3:; return;
label_E4A4:; return;
label_E4A5:; return;
label_E4A6:; return;
label_E4A7:; return;
label_E4A9:; return;
label_E4AB:; return;
label_E4AD:; return;
label_E4AE:; return;
label_E4B0:; return;
label_E4B3:; return;
label_E4B4:; return;
label_E4B6:; return;
label_E4B7:; return;
label_E4B8:; return;
label_E4B9:; return;
label_E4BA:; return;
label_E4BB:; return;
label_E4BD:; return;
label_E4BF:; return;
label_E4C0:; return;
label_E4C2:; return;
label_E4C4:; return;
label_E4C5:; return;
label_E4C7:; return;
label_E4C9:; return;
label_E4CA:; return;
label_E4CB:; return;
label_E4CC:; return;
label_E4CD:; return;
label_E4CE:; return;
label_E4CF:; return;
label_E4D0:; return;
label_E4D2:; return;
label_E4D4:; return;
label_E4D6:; return;
label_E4D8:; return;
label_E4DA:; return;
label_E4DC:; return;
label_E4DF:; return;
label_E4E2:; return;
label_E4E4:; return;
label_E4E6:; return;
label_E4E8:; return;
label_E4EA:; return;
label_E4EC:; return;
label_E4EE:; return;
label_E4F0:; return;
label_E4F2:; return;
label_E4F3:; return;
label_E4F4:; return;
label_E4F6:; return;
label_E4F7:; return;
label_E4FA:; return;
label_E4FB:; return;
label_E4FE:; return;
label_E501:; return;
label_E502:; return;
label_E505:; return;
label_E508:; return;
label_E50B:; return;
label_E50C:; return;
label_E50F:; return;
label_E512:; return;
label_E513:; return;
label_E516:; return;
label_E519:; return;
label_E51C:; return;
label_E51F:; return;
label_E522:; return;
label_E525:; return;
label_E528:; return;
label_E52B:; return;
label_E52E:; return;
label_E530:; return;
label_E533:; return;
label_E535:; return;
label_E537:; return;
label_E539:; return;
label_E53B:; return;
label_E53D:; return;
label_E540:; return;
label_E541:; return;
label_E544:; return;
label_E546:; return;
label_E549:; return;
label_E54B:; return;
label_E54E:; return;
label_E551:; return;
label_E554:; return;
label_E555:; return;
label_E557:; return;
label_E55A:; return;
label_E55D:; return;
label_E55E:; return;
label_E560:; return;
label_E562:; return;
label_E564:; return;
label_E567:; return;
label_E569:; return;
label_E56C:; return;
label_E56F:; return;
label_E571:; return;
label_E573:; return;
label_E575:; return;
label_E577:; return;
label_E57A:; return;
label_E57D:; return;
label_E580:; return;
label_E582:; return;
label_E585:; return;
label_E588:; return;
label_E58A:; return;
label_E58D:; return;
label_E590:; return;
label_E592:; return;
label_E593:; return;
label_E594:; return;
label_E596:; return;
label_E597:; return;
label_E59A:; return;
label_E59B:; return;
label_E59C:; return;
label_E59F:; return;
label_E5A1:; return;
label_E5A4:; return;
label_E5A7:; return;
label_E5A9:; return;
label_E5AC:; return;
label_E5AF:; return;
label_E5B1:; return;
label_E5B3:; return;
label_E5B5:; return;
label_E5B8:; return;
label_E5BB:; return;
label_E5BE:; return;
label_E5C1:; return;
label_E5C4:; return;
label_E5C7:; return;
label_E5C8:; return;
label_E5CB:; return;
label_E5CD:; return;
label_E5CE:; return;
label_E5CF:; return;
label_E5D0:; return;
label_E5D3:; return;
label_E5D6:; return;
label_E5D8:; return;
label_E5DA:; return;
label_E5DD:; return;
label_E5E0:; return;
label_E5E2:; return;
label_E5E4:; return;
label_E5E7:; return;
label_E5E9:; return;
label_E5EB:; return;
label_E5EE:; return;
label_E5F1:; return;
label_E5F4:; return;
label_E5F6:; return;
label_E5F9:; return;
label_E5FB:; return;
label_E5FD:; return;
label_E5FF:; return;
label_E600:; return;
label_E603:; return;
label_E605:; return;
label_E606:; return;
label_E609:; return;
label_E60A:; return;
label_E60D:; return;
label_E60E:; return;
label_E611:; return;
label_E612:; return;
label_E613:; return;
label_E615:; return;
label_E617:; return;
label_E61A:; return;
label_E61B:; return;
label_E61C:; return;
label_E61D:; return;
label_E61F:; return;
label_E621:; return;
label_E624:; return;
label_E625:; return;
label_E626:; return;
label_E627:; return;
label_E629:; return;
label_E62B:; return;
label_E62E:; return;
label_E62F:; return;
label_E630:; return;
label_E631:; return;
label_E633:; return;
label_E635:; return;
label_E638:; return;
label_E639:; return;
label_E63A:; return;
label_E63B:; return;
label_E63D:; return;
label_E63F:; return;
label_E642:; return;
label_E643:; return;
label_E644:; return;
label_E646:; return;
label_E648:; return;
label_E64B:; return;
label_E64E:; return;
label_E64F:; return;
label_E651:; return;
label_E654:; return;
label_E655:; return;
label_E657:; return;
label_E658:; return;
label_E65A:; return;
label_E65C:; return;
label_E65E:; return;
label_E661:; return;
label_E664:; return;
label_E667:; return;
label_E668:; return;
label_E66A:; return;
label_E66D:; return;
label_E66F:; return;
label_E672:; return;
label_E675:; return;
label_E677:; return;
label_E67A:; return;
label_E67C:; return;
label_E67F:; return;
label_E682:; return;
label_E683:; return;
label_E685:; return;
label_E687:; return;
label_E689:; return;
label_E68B:; return;
label_E68D:; return;
label_E68F:; return;
label_E691:; return;
label_E694:; return;
label_E695:; return;
label_E697:; return;
label_E69A:; return;
label_E69D:; return;
label_E6A0:; return;
label_E6A3:; return;
label_E6A5:; return;
label_E6A6:; return;
label_E6A8:; return;
label_E6A9:; return;
label_E6AC:; return;
label_E6AD:; return;
label_E6B0:; return;
label_E6B1:; return;
label_E6B3:; return;
label_E6B6:; return;
label_E6B8:; return;
label_E6BB:; return;
label_E6BD:; return;
label_E6BE:; return;
label_E6C0:; return;
label_E6C1:; return;
label_E6C4:; return;
label_E6C7:; return;
label_E6CA:; return;
label_E6CC:; return;
label_E6CD:; return;
label_E6D0:; return;
label_E6D1:; return;
label_E6D3:; return;
label_E6D4:; return;
label_E6D6:; return;
label_E6D9:; return;
label_E6DB:; return;
label_E6DD:; return;
label_E6E0:; return;
label_E6E2:; return;
label_E6E4:; return;
label_E6E7:; return;
label_E6EA:; return;
label_E6EC:; return;
label_E6ED:; return;
label_E6EE:; return;
label_E6EF:; return;
label_E6F0:; return;
label_E6F1:; return;
label_E6F3:; return;
label_E6F5:; return;
label_E6F7:; return;
label_E6FA:; return;
label_E6FC:; return;
label_E6FF:; return;
label_E702:; return;
label_E704:; return;
label_E706:; return;
label_E709:; return;
label_E70A:; return;
label_E70C:; return;
label_E70E:; return;
label_E710:; return;
label_E712:; return;
label_E714:; return;
label_E715:; return;
label_E717:; return;
label_E71A:; return;
label_E71D:; return;
label_E720:; return;
label_E722:; return;
label_E723:; return;
label_E725:; return;
label_E728:; return;
label_E72B:; return;
label_E72E:; return;
label_E730:; return;
label_E733:; return;
label_E736:; return;
label_E738:; return;
label_E73B:; return;
label_E73E:; return;
label_E741:; return;
label_E743:; return;
label_E746:; return;
label_E749:; return;
label_E74B:; return;
label_E74D:; return;
label_E74F:; return;
label_E751:; return;
label_E753:; return;
label_E755:; return;
label_E757:; return;
label_E759:; return;
label_E75B:; return;
label_E75D:; return;
label_E75F:; return;
label_E761:; return;
label_E763:; return;
label_E766:; return;
label_E767:; return;
label_E76A:; return;
label_E76B:; return;
label_E76E:; return;
label_E771:; return;
label_E774:; return;
label_E777:; return;
label_E779:; return;
label_E77B:; return;
label_E77E:; return;
label_E781:; return;
label_E784:; return;
label_E787:; return;
label_E78A:; return;
label_E78C:; return;
label_E78F:; return;
label_E791:; return;
label_E793:; return;
label_E796:; return;
label_E797:; return;
label_E799:; return;
label_E79C:; return;
label_E79F:; return;
label_E7A2:; return;
label_E7A5:; return;
label_E7A8:; return;
label_E7AB:; return;
label_E7AE:; return;
label_E7B1:; return;
label_E7B4:; return;
label_E7B6:; return;
label_E7B9:; return;
label_E7BB:; return;
label_E7BD:; return;
label_E7C0:; return;
label_E7C2:; return;
label_E7C5:; return;
label_E7C7:; return;
label_E7C9:; return;
label_E7CC:; return;
label_E7CF:; return;
label_E7D0:; return;
label_E7D3:; return;
label_E7D6:; return;
label_E7D9:; return;
label_E7DC:; return;
label_E7DD:; return;
label_E7E0:; return;
label_E7E3:; return;
label_E7E6:; return;
label_E7E9:; return;
label_E7EC:; return;
label_E7EF:; return;
label_E7F0:; return;
label_E7F2:; return;
label_E7F4:; return;
label_E7F6:; return;
label_E7F8:; return;
label_E7FA:; return;
label_E7FC:; return;
label_E7FE:; return;
label_E800:; return;
label_E802:; return;
label_E804:; return;
label_E807:; return;
label_E80A:; return;
label_E80D:; return;
label_E80F:; return;
label_E811:; return;
label_E814:; return;
label_E816:; return;
label_E818:; return;
label_E81A:; return;
label_E81B:; return;
label_E81D:; return;
label_E820:; return;
label_E822:; return;
label_E824:; return;
label_E826:; return;
label_E829:; return;
label_E82C:; return;
label_E82D:; return;
label_E82F:; return;
label_E830:; return;
label_E832:; return;
label_E833:; return;
label_E834:; return;
label_E836:; return;
label_E838:; return;
label_E83B:; return;
label_E83D:; return;
label_E840:; return;
label_E843:; return;
label_E846:; return;
label_E848:; return;
label_E849:; return;
label_E84A:; return;
label_E84B:; return;
label_E84C:; return;
label_E84F:; return;
label_E850:; return;
label_E851:; return;
label_E853:; return;
label_E856:; return;
label_E857:; return;
label_E858:; return;
label_E85A:; return;
label_E85D:; return;
label_E85F:; return;
label_E861:; return;
label_E863:; return;
label_E865:; return;
label_E867:; return;
label_E868:; return;
label_E86A:; return;
label_E86B:; return;
label_E86D:; return;
label_E86E:; return;
label_E871:; return;
label_E873:; return;
label_E874:; return;
label_E875:; return;
label_E876:; return;
label_E877:; return;
label_E878:; return;
label_E879:; return;
label_E87C:; return;
label_E87D:; return;
label_E87F:; return;
label_E881:; return;
label_E884:; return;
label_E886:; return;
label_E889:; return;
label_E88B:; return;
label_E88D:; return;
label_E890:; return;
label_E892:; return;
label_E894:; return;
label_E897:; return;
label_E899:; return;
label_E89B:; return;
label_E89D:; return;
label_E89F:; return;
label_E8A1:; return;
label_E8A3:; return;
label_E8A6:; return;
label_E8A8:; return;
label_E8A9:; return;
label_E8AB:; return;
label_E8AD:; return;
label_E8AF:; return;
label_E8B0:; return;
label_E8B2:; return;
label_E8B4:; return;
label_E8B6:; return;
label_E8B8:; return;
label_E8BA:; return;
label_E8BC:; return;
label_E8BE:; return;
label_E8C0:; return;
label_E8C2:; return;
label_E8C4:; return;
label_E8C6:; return;
label_E8C9:; return;
label_E8CB:; return;
label_E8CD:; return;
label_E8CF:; return;
label_E8D1:; return;
label_E8D3:; return;
label_E8D5:; return;
label_E8D7:; return;
label_E8D9:; return;
label_E8DB:; return;
label_E8DE:; return;
label_E8E1:; return;
label_E8E3:; return;
label_E8E5:; return;
label_E8E7:; return;
label_E8E9:; return;
label_E8EB:; return;
label_E8ED:; return;
label_E8EF:; return;
label_E8F2:; return;
label_E8F5:; return;
label_E8F7:; return;
label_E8F9:; return;
label_E8FB:; return;
label_E8FD:; return;
label_E8FE:; return;
label_E900:; return;
label_E902:; return;
label_E904:; return;
label_E906:; return;
label_E908:; return;
label_E90A:; return;
label_E90C:; return;
label_E90E:; return;
label_E910:; return;
label_E912:; return;
label_E915:; return;
label_E917:; return;
label_E919:; return;
label_E91B:; return;
label_E91D:; return;
label_E91F:; return;
label_E921:; return;
label_E923:; return;
label_E926:; return;
label_E928:; return;
label_E92A:; return;
label_E92D:; return;
label_E92E:; return;
label_E930:; return;
label_E933:; return;
label_E935:; return;
label_E937:; return;
label_E939:; return;
label_E93C:; return;
label_E93E:; return;
label_E940:; return;
label_E942:; return;
label_E944:; return;
label_E946:; return;
label_E949:; return;
label_E94C:; return;
label_E94F:; return;
label_E951:; return;
label_E953:; return;
label_E955:; return;
label_E957:; return;
label_E959:; return;
label_E95B:; return;
}

void func_DD56_body(int _entry) {
    switch (_entry) {
        case 1: goto label_DD66;
        case 2: goto label_DD5C;
    }
label_DD56:;
    /* $DD56: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x8D); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_DD58:;
    /* $DD58: 84 */ maybe_trigger_vblank(3); nes_write(0x04, g_cpu.Y);
label_DD5A:; /* InitSteP */
    /* $DD5A: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_DD5C:;
    /* $DD5C: 85 */ maybe_trigger_vblank(3); nes_write(0x1D, g_cpu.A);
label_DD5E:; /* DoPlayerSideCheck */
    /* $DD5E: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0xEB); FLAG_NZ(g_cpu.Y);
label_DD60:;
    /* $DD60: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_DD61:;
    /* $DD61: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_DD62:;
    /* $DD62: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x02; FLAG_NZ(g_cpu.A);
label_DD64:;
    /* $DD64: 85 */ maybe_trigger_vblank(3); nes_write(0x00, g_cpu.A);
label_DD66:; /* SideCheckLoop */
    /* $DD66: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_DD67:;
    /* $DD67: 84 */ maybe_trigger_vblank(3); nes_write(0xEB, g_cpu.Y);
label_DD69:;
    /* $DD69: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xCE); FLAG_NZ(g_cpu.A);
label_DD6B:;
    /* $DD6B: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x20; g_cpu.C=(g_cpu.A>=0x20)?1:0; FLAG_NZ(r&0xFF); }
label_DD6D:;
    /* $DD6D: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) { maybe_trigger_vblank(1); goto label_DD85; }
label_DD6F:;
    /* $DD6F: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0xE4; g_cpu.C=(g_cpu.A>=0xE4)?1:0; FLAG_NZ(r&0xFF); }
label_DD71:;
    /* $DD71: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_DD9B; }
label_DD73:;
    /* $DD73: 20 */ maybe_trigger_vblank(6); func_E3EC();
label_DD76:;
    /* $DD76: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_DD85; }
label_DD78:;
    /* $DD78: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x1C; g_cpu.C=(g_cpu.A>=0x1C)?1:0; FLAG_NZ(r&0xFF); }
label_DD7A:;
    /* $DD7A: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_DD85; }
label_DD7C:;
    /* $DD7C: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x6B; g_cpu.C=(g_cpu.A>=0x6B)?1:0; FLAG_NZ(r&0xFF); }
label_DD7E:;
    /* $DD7E: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_DD85; }
label_DD80:;
    /* $DD80: 20 */ maybe_trigger_vblank(6); func_DF9A();
label_DD83:;
    /* $DD83: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) { maybe_trigger_vblank(1); goto label_DD9C; }
label_DD85:; /* BHalf */
    /* $DD85: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0xEB); FLAG_NZ(g_cpu.Y);
label_DD87:;
    /* $DD87: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_DD88:;
    /* $DD88: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xCE); FLAG_NZ(g_cpu.A);
label_DD8A:;
    /* $DD8A: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x08; g_cpu.C=(g_cpu.A>=0x08)?1:0; FLAG_NZ(r&0xFF); }
label_DD8C:;
    /* $DD8C: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) { maybe_trigger_vblank(1); goto label_DD9B; }
label_DD8E:;
    /* $DD8E: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0xD0; g_cpu.C=(g_cpu.A>=0xD0)?1:0; FLAG_NZ(r&0xFF); }
label_DD90:;
    /* $DD90: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_DD9B; }
label_DD92:;
    /* $DD92: 20 */ maybe_trigger_vblank(6); func_E3EC();
label_DD95:;
    /* $DD95: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_DD9C; }
label_DD97:;
    /* $DD97: C6 */ maybe_trigger_vblank(5); { uint16_t a=0x00; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_DD99:;
    /* $DD99: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) {
    maybe_trigger_vblank(1);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_DD66;
    }
label_DD9B:; /* ExSCH */
    /* $DD9B: 60 */ maybe_trigger_vblank(6); 
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
    return;
label_DD9C:; /* CheckSideMTiles */
    /* $DD9C: 20 */ maybe_trigger_vblank(6); func_DEBD();
label_DD9F:;
    /* $DD9F: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) { maybe_trigger_vblank(2); goto label_DE02; }
label_DDA1:;
    /* $DDA1: 20 */ maybe_trigger_vblank(6); func_DF9A();
label_DDA4:;
    /* $DDA4: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) { maybe_trigger_vblank(1); goto label_DDA9; }
label_DDA6:;
    /* $DDA6: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); func_DE2E(); return;
label_DDA9:; /* ContSChk */
    /* $DDA9: 20 */ maybe_trigger_vblank(6); func_DFA1();
label_DDAC:;
    /* $DDAC: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { maybe_trigger_vblank(2); goto label_DE05; }
label_DDAE:;
    /* $DDAE: 20 */ maybe_trigger_vblank(6); func_DEDD();
label_DDB1:;
    /* $DDB1: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) { maybe_trigger_vblank(1); goto label_DDBB; }
label_DDB3:;
    /* $DDB3: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x070E); FLAG_NZ(g_cpu.A);
label_DDB6:;
    /* $DDB6: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(2); goto label_DE02; }
label_DDB8:;
    /* $DDB8: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); func_DDFF(); return;
label_DDBB:; /* ChkPBtm */
    /* $DDBB: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0x1D); FLAG_NZ(g_cpu.Y);
label_DDBD:;
    /* $DDBD: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x00; g_cpu.C=(g_cpu.Y>=0x00)?1:0; FLAG_NZ(r&0xFF); }
label_DDBF:;
    /* $DDBF: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_DDFF; }
label_DDC1:;
    /* $DDC1: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0x33); FLAG_NZ(g_cpu.Y);
label_DDC3:;
    /* $DDC3: 88 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y-1)&0xFF; FLAG_NZ(g_cpu.Y);
label_DDC4:;
    /* $DDC4: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_DDFF; }
label_DDC6:;
    /* $DDC6: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x6C; g_cpu.C=(g_cpu.A>=0x6C)?1:0; FLAG_NZ(r&0xFF); }
label_DDC8:;
    /* $DDC8: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_DDCE; }
label_DDCA:;
    /* $DDCA: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x1F; g_cpu.C=(g_cpu.A>=0x1F)?1:0; FLAG_NZ(r&0xFF); }
label_DDCC:;
    /* $DDCC: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_DDFF; }
label_DDCE:; /* PipeDwnS */
    /* $DDCE: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x03C4); FLAG_NZ(g_cpu.A);
label_DDD1:;
    /* $DDD1: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_DDD7; }
label_DDD3:;
    /* $DDD3: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x10; FLAG_NZ(g_cpu.Y);
label_DDD5:;
    /* $DDD5: 84 */ maybe_trigger_vblank(3); nes_write(0xFF, g_cpu.Y);
label_DDD7:; /* PlyrPipe */
    /* $DDD7: 09 */ maybe_trigger_vblank(2); g_cpu.A |= 0x20; FLAG_NZ(g_cpu.A);
label_DDD9:;
    /* $DDD9: 8D */ maybe_trigger_vblank(4); nes_write(0x03C4, g_cpu.A);
label_DDDC:;
    /* $DDDC: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x86); FLAG_NZ(g_cpu.A);
label_DDDE:;
    /* $DDDE: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x0F; FLAG_NZ(g_cpu.A);
label_DDE0:;
    /* $DDE0: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_DDF0; }
label_DDE2:;
    /* $DDE2: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x00; FLAG_NZ(g_cpu.Y);
label_DDE4:;
    /* $DDE4: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read_hooked(0xDDE4, 0x071A); FLAG_NZ(g_cpu.A);
label_DDE7:;
    /* $DDE7: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_DDEA; }
label_DDE9:;
    /* $DDE9: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_DDEA:; /* SetCATmr */
    /* $DDEA: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xDE03 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_DDED:;
    /* $DDED: 8D */ maybe_trigger_vblank(4); nes_write(0x06DE, g_cpu.A);
label_DDF0:; /* ChkGERtn */
    /* $DDF0: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x0E); FLAG_NZ(g_cpu.A);
label_DDF2:;
    /* $DDF2: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x07; g_cpu.C=(g_cpu.A>=0x07)?1:0; FLAG_NZ(r&0xFF); }
label_DDF4:;
    /* $DDF4: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) { maybe_trigger_vblank(2); goto label_DE02; }
label_DDF6:;
    /* $DDF6: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x08; g_cpu.C=(g_cpu.A>=0x08)?1:0; FLAG_NZ(r&0xFF); }
label_DDF8:;
    /* $DDF8: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(2); goto label_DE02; }
label_DDFA:;
    /* $DDFA: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x02; FLAG_NZ(g_cpu.A);
label_DDFC:;
    /* $DDFC: 85 */ maybe_trigger_vblank(3); nes_write(0x0E, g_cpu.A);
label_DDFE:;
    /* $DDFE: 60 */ maybe_trigger_vblank(6); 
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
    return;
label_DDFF:; /* StopPlayerMove */
    /* $DDFF: 20 */ maybe_trigger_vblank(6); func_DF4B();
label_DE02:; /* ExCSM */
    /* $DE02: 60 */ maybe_trigger_vblank(6); 
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
    return;
label_DE03:; /* AreaChangeTimerData */
    /* $DE03: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x34; FLAG_NZ(g_cpu.Y);
label_DE05:; /* HandleCoinMetatile */
    /* $DE05: 20 */ maybe_trigger_vblank(6); func_DE1C();
label_DE08:;
    /* $DE08: EE */ maybe_trigger_vblank(6); { uint16_t a=0x0748; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_DE0B:;
    /* $DE0B: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address_tail(0xBBFE, -1); return;
}

void func_DD56(void) {
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_DD56");
#endif
    func_DD56_body(0);
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
}

void func_DD66(void) { /* SideCheckLoop */
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_DD66");
#endif
    func_DD56_body(1);
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
}

void func_DD5C(void) {
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_DD5C");
#endif
    func_DD56_body(2);
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
}

void func_F611_body(int _entry) {
    switch (_entry) {
        case 1: goto label_F617;
    }
label_F611:;
    /* $F611: 07 */ maybe_trigger_vblank(5); { uint16_t a=0xAD; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); g_cpu.A|=v; FLAG_NZ(g_cpu.A); }
label_F613:;
    /* $F613: BE */ maybe_trigger_vblank(4); g_cpu.X = nes_read((0x4A07 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.X);
label_F616:;
    /* $F616: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_F617:;
    /* $F617: CC */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x07BD); int r=g_cpu.Y-m; g_cpu.C=(g_cpu.Y>=m)?1:0; FLAG_NZ(r&0xFF); }
label_F61A:;
    /* $F61A: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_F628; }
label_F61C:;
    /* $F61C: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x9D; FLAG_NZ(g_cpu.A);
label_F61E:;
    /* $F61E: 8D */ maybe_trigger_vblank(4); nes_write(0x4004, g_cpu.A);
label_F621:;
    /* $F621: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xF4F8 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_F624:;
    /* $F624: 20 */ maybe_trigger_vblank(6); func_F3A9();
label_F627:;
    /* $F627: 60 */ maybe_trigger_vblank(6); 
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
    return;
label_F628:; /* StopGrowItems */
    /* $F628: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); func_F56D(); return;
}

void func_F611(void) {
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_F611");
#endif
    func_F611_body(0);
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
}

void func_F617(void) {
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_F617");
#endif
    func_F611_body(1);
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
}

void func_F693_body(int _entry) {
    switch (_entry) {
        case 1: goto label_F695;
    }
label_F693:;
    /* $F693: F7 */ maybe_trigger_vblank(6); { uint16_t a=(0xA5 + g_cpu.X) & 0xFF; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); int16_t r=g_cpu.A-v-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,v); g_cpu.A=r&0xFF; }
label_F695:;
    /* $F695: FC */ maybe_trigger_vblank(4); (void)nes_read((0x0CD0 + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_F698:;
    /* $F698: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xFB); FLAG_NZ(g_cpu.A);
label_F69A:;
    /* $F69A: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_F6C8; }
label_F69C:;
    /* $F69C: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07B1); FLAG_NZ(g_cpu.A);
label_F69F:;
    /* $F69F: 05 */ maybe_trigger_vblank(3); g_cpu.A |= nes_read(0xF4); FLAG_NZ(g_cpu.A);
label_F6A1:;
    /* $F6A1: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); call_by_address(0xF691); return; }
label_F6A3:;
    /* $F6A3: 60 */ maybe_trigger_vblank(6); 
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
    return;
label_F6A4:; /* LoadEventMusic */
    /* $F6A4: 8D */ maybe_trigger_vblank(4); nes_write(0x07B1, g_cpu.A);
label_F6A7:;
    /* $F6A7: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x01; g_cpu.C=(g_cpu.A>=0x01)?1:0; FLAG_NZ(r&0xFF); }
label_F6A9:;
    /* $F6A9: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_F6B1; }
label_F6AB:;
    /* $F6AB: 20 */ maybe_trigger_vblank(6); func_F4A7();
label_F6AE:;
    /* $F6AE: 20 */ maybe_trigger_vblank(6); func_F571();
label_F6B1:; /* NoStopSfx */
    /* $F6B1: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0xF4); FLAG_NZ(g_cpu.X);
label_F6B3:;
    /* $F6B3: 8E */ maybe_trigger_vblank(4); nes_write(0x07C5, g_cpu.X);
label_F6B6:;
    /* $F6B6: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x00; FLAG_NZ(g_cpu.Y);
label_F6B8:;
    /* $F6B8: 8C */ maybe_trigger_vblank(4); nes_write(0x07C4, g_cpu.Y);
label_F6BB:;
    /* $F6BB: 84 */ maybe_trigger_vblank(3); nes_write(0xF4, g_cpu.Y);
label_F6BD:;
    /* $F6BD: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x40; g_cpu.C=(g_cpu.A>=0x40)?1:0; FLAG_NZ(r&0xFF); }
label_F6BF:;
    /* $F6BF: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_F6F1; }
label_F6C1:;
    /* $F6C1: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x08; FLAG_NZ(g_cpu.X);
label_F6C3:;
    /* $F6C3: 8E */ maybe_trigger_vblank(4); nes_write(0x07C4, g_cpu.X);
label_F6C6:;
    /* $F6C6: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_F6F1; }
label_F6C8:; /* LoadAreaMusic */
    /* $F6C8: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x04; g_cpu.C=(g_cpu.A>=0x04)?1:0; FLAG_NZ(r&0xFF); }
label_F6CA:;
    /* $F6CA: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_F6CF; }
label_F6CC:;
    /* $F6CC: 20 */ maybe_trigger_vblank(6); func_F4A7();
label_F6CF:; /* NoStop1 */
    /* $F6CF: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x10; FLAG_NZ(g_cpu.Y);
label_F6D1:; /* GMLoopB */
    /* $F6D1: 8C */ maybe_trigger_vblank(4); nes_write(0x07C7, g_cpu.Y);
label_F6D4:; /* HandleAreaMusicLoopB */
    /* $F6D4: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x00; FLAG_NZ(g_cpu.Y);
label_F6D6:;
    /* $F6D6: 8C */ maybe_trigger_vblank(4); nes_write(0x07B1, g_cpu.Y);
label_F6D9:;
    /* $F6D9: 85 */ maybe_trigger_vblank(3); nes_write(0xF4, g_cpu.A);
label_F6DB:;
    /* $F6DB: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x01; g_cpu.C=(g_cpu.A>=0x01)?1:0; FLAG_NZ(r&0xFF); }
label_F6DD:;
    /* $F6DD: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_F6ED; }
label_F6DF:;
    /* $F6DF: EE */ maybe_trigger_vblank(6); { uint16_t a=0x07C7; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_F6E2:;
    /* $F6E2: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x07C7); FLAG_NZ(g_cpu.Y);
label_F6E5:;
    /* $F6E5: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x32; g_cpu.C=(g_cpu.Y>=0x32)?1:0; FLAG_NZ(r&0xFF); }
label_F6E7:;
    /* $F6E7: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_F6F5; }
label_F6E9:;
    /* $F6E9: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x11; FLAG_NZ(g_cpu.Y);
label_F6EB:;
    /* $F6EB: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) {
    maybe_trigger_vblank(1);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_F6D1;
    }
label_F6ED:; /* FindAreaMusicHeader */
    /* $F6ED: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x08; FLAG_NZ(g_cpu.Y);
label_F6EF:;
    /* $F6EF: 84 */ maybe_trigger_vblank(3); nes_write(0xF7, g_cpu.Y);
label_F6F1:; /* FindEventMusicHeader */
    /* $F6F1: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_F6F2:;
    /* $F6F2: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_F6F3:;
    /* $F6F3: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) {
    maybe_trigger_vblank(1);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_F6F1;
    }
label_F6F5:; /* LoadHeader */
    /* $F6F5: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xF90C + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_F6F8:;
    /* $F6F8: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_F6F9:;
    /* $F6F9: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xF90D + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_F6FC:;
    /* $F6FC: 85 */ maybe_trigger_vblank(3); nes_write(0xF0, g_cpu.A);
label_F6FE:;
    /* $F6FE: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xF90E + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_F701:;
    /* $F701: 85 */ maybe_trigger_vblank(3); nes_write(0xF5, g_cpu.A);
label_F703:;
    /* $F703: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xF90F + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_F706:;
    /* $F706: 85 */ maybe_trigger_vblank(3); nes_write(0xF6, g_cpu.A);
label_F708:;
    /* $F708: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xF910 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_F70B:;
    /* $F70B: 85 */ maybe_trigger_vblank(3); nes_write(0xF9, g_cpu.A);
label_F70D:;
    /* $F70D: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xF911 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_F710:;
    /* $F710: 85 */ maybe_trigger_vblank(3); nes_write(0xF8, g_cpu.A);
label_F712:;
    /* $F712: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xF912 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_F715:;
    /* $F715: 8D */ maybe_trigger_vblank(4); nes_write(0x07B0, g_cpu.A);
label_F718:;
    /* $F718: 8D */ maybe_trigger_vblank(4); nes_write(0x07C1, g_cpu.A);
label_F71B:;
    /* $F71B: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x01; FLAG_NZ(g_cpu.A);
label_F71D:;
    /* $F71D: 8D */ maybe_trigger_vblank(4); nes_write(0x07B4, g_cpu.A);
label_F720:;
    /* $F720: 8D */ maybe_trigger_vblank(4); nes_write(0x07B6, g_cpu.A);
label_F723:;
    /* $F723: 8D */ maybe_trigger_vblank(4); nes_write(0x07B9, g_cpu.A);
label_F726:;
    /* $F726: 8D */ maybe_trigger_vblank(4); nes_write(0x07BA, g_cpu.A);
label_F729:;
    /* $F729: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_F72B:;
    /* $F72B: 85 */ maybe_trigger_vblank(3); nes_write(0xF7, g_cpu.A);
label_F72D:;
    /* $F72D: 8D */ maybe_trigger_vblank(4); nes_write(0x07CA, g_cpu.A);
label_F730:;
    /* $F730: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x0B; FLAG_NZ(g_cpu.A);
label_F732:;
    /* $F732: 8D */ maybe_trigger_vblank(4); nes_write(0x4015, g_cpu.A);
label_F735:;
    /* $F735: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x0F; FLAG_NZ(g_cpu.A);
label_F737:;
    /* $F737: 8D */ maybe_trigger_vblank(4); nes_write(0x4015, g_cpu.A);
label_F73A:; /* HandleSquare2Music */
    /* $F73A: CE */ maybe_trigger_vblank(6); { uint16_t a=0x07B4; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_F73D:;
    /* $F73D: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_F79E; }
label_F73F:;
    /* $F73F: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0xF7); FLAG_NZ(g_cpu.Y);
label_F741:;
    /* $F741: E6 */ maybe_trigger_vblank(5); { uint16_t a=0xF7; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_F743:;
    /* $F743: B1 */ maybe_trigger_vblank(5); g_cpu.A = nes_read((nes_read16zp(0xF5) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_F745:;
    /* $F745: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_F74B; }
label_F747:;
    /* $F747: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) { maybe_trigger_vblank(1); goto label_F786; }
label_F749:;
    /* $F749: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_F77A; }
label_F74B:; /* EndOfMusicData */
    /* $F74B: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07B1); FLAG_NZ(g_cpu.A);
label_F74E:;
    /* $F74E: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x40; g_cpu.C=(g_cpu.A>=0x40)?1:0; FLAG_NZ(r&0xFF); }
label_F750:;
    /* $F750: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_F757; }
label_F752:;
    /* $F752: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07C5); FLAG_NZ(g_cpu.A);
label_F755:;
    /* $F755: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_F774; }
label_F757:; /* NotTRO */
    /* $F757: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x04; FLAG_NZ(g_cpu.A);
label_F759:;
    /* $F759: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_F777; }
label_F75B:;
    /* $F75B: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xF4); FLAG_NZ(g_cpu.A);
label_F75D:;
    /* $F75D: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x5F; FLAG_NZ(g_cpu.A);
label_F75F:;
    /* $F75F: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_F774; }
label_F761:;
    /* $F761: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_F763:;
    /* $F763: 85 */ maybe_trigger_vblank(3); nes_write(0xF4, g_cpu.A);
label_F765:;
    /* $F765: 8D */ maybe_trigger_vblank(4); nes_write(0x07B1, g_cpu.A);
label_F768:;
    /* $F768: 8D */ maybe_trigger_vblank(4); nes_write(0x4008, g_cpu.A);
label_F76B:;
    /* $F76B: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x90; FLAG_NZ(g_cpu.A);
label_F76D:;
    /* $F76D: 8D */ maybe_trigger_vblank(4); nes_write(0x4000, g_cpu.A);
label_F770:;
    /* $F770: 8D */ maybe_trigger_vblank(4); nes_write(0x4004, g_cpu.A);
label_F773:;
    /* $F773: 60 */ maybe_trigger_vblank(6); 
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
    return;
label_F774:; /* MusicLoopBack */
    /* $F774: 4C */ maybe_trigger_vblank(3); goto label_F6D4;
label_F777:; /* VictoryMLoopBack */
    /* $F777: 4C */ maybe_trigger_vblank(3); goto label_F6A4;
label_F77A:; /* Squ2LengthHandler */
    /* $F77A: 20 */ maybe_trigger_vblank(6); func_F8CB();
label_F77D:;
    /* $F77D: 8D */ maybe_trigger_vblank(4); nes_write(0x07B3, g_cpu.A);
label_F780:;
    /* $F780: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0xF7); FLAG_NZ(g_cpu.Y);
label_F782:;
    /* $F782: E6 */ maybe_trigger_vblank(5); { uint16_t a=0xF7; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_F784:;
    /* $F784: B1 */ maybe_trigger_vblank(5); g_cpu.A = nes_read((nes_read16zp(0xF5) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_F786:; /* Squ2NoteHandler */
    /* $F786: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0xF2); FLAG_NZ(g_cpu.X);
label_F788:;
    /* $F788: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_F798; }
label_F78A:;
    /* $F78A: 20 */ maybe_trigger_vblank(6); func_F3A9();
label_F78D:;
    /* $F78D: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_F792; }
label_F78F:;
    /* $F78F: 20 */ maybe_trigger_vblank(6); func_F8D8();
label_F792:; /* Rest */
    /* $F792: 8D */ maybe_trigger_vblank(4); nes_write(0x07B5, g_cpu.A);
label_F795:;
    /* $F795: 20 */ maybe_trigger_vblank(6); func_F39F();
label_F798:; /* SkipFqL1 */
    /* $F798: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07B3); FLAG_NZ(g_cpu.A);
label_F79B:;
    /* $F79B: 8D */ maybe_trigger_vblank(4); nes_write(0x07B4, g_cpu.A);
label_F79E:; /* MiscSqu2MusicTasks */
    /* $F79E: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xF2); FLAG_NZ(g_cpu.A);
label_F7A0:;
    /* $F7A0: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_F7BC; }
label_F7A2:;
    /* $F7A2: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07B1); FLAG_NZ(g_cpu.A);
label_F7A5:;
    /* $F7A5: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x91; FLAG_NZ(g_cpu.A);
label_F7A7:;
    /* $F7A7: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_F7BC; }
label_F7A9:;
    /* $F7A9: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x07B5); FLAG_NZ(g_cpu.Y);
label_F7AC:;
    /* $F7AC: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_F7B1; }
label_F7AE:;
    /* $F7AE: CE */ maybe_trigger_vblank(6); { uint16_t a=0x07B5; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_F7B1:; /* NoDecEnv1 */
    /* $F7B1: 20 */ maybe_trigger_vblank(6); func_F8F4();
label_F7B4:;
    /* $F7B4: 8D */ maybe_trigger_vblank(4); nes_write(0x4004, g_cpu.A);
label_F7B7:;
    /* $F7B7: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x7F; FLAG_NZ(g_cpu.X);
label_F7B9:;
    /* $F7B9: 8E */ maybe_trigger_vblank(4); nes_write(0x4005, g_cpu.X);
label_F7BC:; /* HandleSquare1Music */
    /* $F7BC: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0xF8); FLAG_NZ(g_cpu.Y);
label_F7BE:;
    /* $F7BE: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) { maybe_trigger_vblank(2); goto label_F81A; }
label_F7C0:;
    /* $F7C0: CE */ maybe_trigger_vblank(6); { uint16_t a=0x07B6; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_F7C3:;
    /* $F7C3: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_F7F7; }
label_F7C5:; /* FetchSqu1MusicData */
    /* $F7C5: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0xF8); FLAG_NZ(g_cpu.Y);
label_F7C7:;
    /* $F7C7: E6 */ maybe_trigger_vblank(5); { uint16_t a=0xF8; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_F7C9:;
    /* $F7C9: B1 */ maybe_trigger_vblank(5); g_cpu.A = nes_read((nes_read16zp(0xF5) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_F7CB:;
    /* $F7CB: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_F7DC; }
label_F7CD:;
    /* $F7CD: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x83; FLAG_NZ(g_cpu.A);
label_F7CF:;
    /* $F7CF: 8D */ maybe_trigger_vblank(4); nes_write(0x4000, g_cpu.A);
label_F7D2:;
    /* $F7D2: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x94; FLAG_NZ(g_cpu.A);
label_F7D4:;
    /* $F7D4: 8D */ maybe_trigger_vblank(4); nes_write(0x4001, g_cpu.A);
label_F7D7:;
    /* $F7D7: 8D */ maybe_trigger_vblank(4); nes_write(0x07CA, g_cpu.A);
label_F7DA:;
    /* $F7DA: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) {
    maybe_trigger_vblank(1);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_F7C5;
    }
label_F7DC:; /* Squ1NoteHandler */
    /* $F7DC: 20 */ maybe_trigger_vblank(6); func_F8C5();
label_F7DF:;
    /* $F7DF: 8D */ maybe_trigger_vblank(4); nes_write(0x07B6, g_cpu.A);
label_F7E2:;
    /* $F7E2: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0xF1); FLAG_NZ(g_cpu.Y);
label_F7E4:;
    /* $F7E4: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(2); goto label_F81A; }
label_F7E6:;
    /* $F7E6: 8A */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.X; FLAG_NZ(g_cpu.A);
label_F7E7:;
    /* $F7E7: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x3E; FLAG_NZ(g_cpu.A);
label_F7E9:;
    /* $F7E9: 20 */ maybe_trigger_vblank(6); func_F38B();
label_F7EC:;
    /* $F7EC: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_F7F1; }
label_F7EE:;
    /* $F7EE: 20 */ maybe_trigger_vblank(6); func_F8D8();
label_F7F1:; /* SkipCtrlL */
    /* $F7F1: 8D */ maybe_trigger_vblank(4); nes_write(0x07B7, g_cpu.A);
label_F7F4:;
    /* $F7F4: 20 */ maybe_trigger_vblank(6); func_F381();
label_F7F7:; /* MiscSqu1MusicTasks */
    /* $F7F7: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xF1); FLAG_NZ(g_cpu.A);
label_F7F9:;
    /* $F7F9: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(2); goto label_F81A; }
label_F7FB:;
    /* $F7FB: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07B1); FLAG_NZ(g_cpu.A);
label_F7FE:;
    /* $F7FE: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x91; FLAG_NZ(g_cpu.A);
label_F800:;
    /* $F800: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_F810; }
label_F802:;
    /* $F802: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x07B7); FLAG_NZ(g_cpu.Y);
label_F805:;
    /* $F805: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_F80A; }
label_F807:;
    /* $F807: CE */ maybe_trigger_vblank(6); { uint16_t a=0x07B7; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_F80A:; /* NoDecEnv2 */
    /* $F80A: 20 */ maybe_trigger_vblank(6); func_F8F4();
label_F80D:;
    /* $F80D: 8D */ maybe_trigger_vblank(4); nes_write(0x4000, g_cpu.A);
label_F810:; /* DeathMAltReg */
    /* $F810: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07CA); FLAG_NZ(g_cpu.A);
label_F813:;
    /* $F813: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_F817; }
label_F815:;
    /* $F815: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x7F; FLAG_NZ(g_cpu.A);
label_F817:; /* DoAltLoad */
    /* $F817: 8D */ maybe_trigger_vblank(4); nes_write(0x4001, g_cpu.A);
label_F81A:; /* HandleTriangleMusic */
    /* $F81A: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xF9); FLAG_NZ(g_cpu.A);
label_F81C:;
    /* $F81C: CE */ maybe_trigger_vblank(6); { uint16_t a=0x07B9; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_F81F:;
    /* $F81F: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_F86D; }
label_F821:;
    /* $F821: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0xF9); FLAG_NZ(g_cpu.Y);
label_F823:;
    /* $F823: E6 */ maybe_trigger_vblank(5); { uint16_t a=0xF9; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_F825:;
    /* $F825: B1 */ maybe_trigger_vblank(5); g_cpu.A = nes_read((nes_read16zp(0xF5) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_F827:;
    /* $F827: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_F86A; }
label_F829:;
    /* $F829: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) { maybe_trigger_vblank(1); goto label_F83E; }
label_F82B:;
    /* $F82B: 20 */ maybe_trigger_vblank(6); func_F8CB();
label_F82E:;
    /* $F82E: 8D */ maybe_trigger_vblank(4); nes_write(0x07B8, g_cpu.A);
label_F831:;
    /* $F831: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x1F; FLAG_NZ(g_cpu.A);
label_F833:;
    /* $F833: 8D */ maybe_trigger_vblank(4); nes_write(0x4008, g_cpu.A);
label_F836:;
    /* $F836: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0xF9); FLAG_NZ(g_cpu.Y);
label_F838:;
    /* $F838: E6 */ maybe_trigger_vblank(5); { uint16_t a=0xF9; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_F83A:;
    /* $F83A: B1 */ maybe_trigger_vblank(5); g_cpu.A = nes_read((nes_read16zp(0xF5) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_F83C:;
    /* $F83C: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_F86A; }
label_F83E:; /* TriNoteHandler */
    /* $F83E: 20 */ maybe_trigger_vblank(6); func_F3AD();
label_F841:;
    /* $F841: AE */ maybe_trigger_vblank(4); g_cpu.X = nes_read(0x07B8); FLAG_NZ(g_cpu.X);
label_F844:;
    /* $F844: 8E */ maybe_trigger_vblank(4); nes_write(0x07B9, g_cpu.X);
label_F847:;
    /* $F847: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07B1); FLAG_NZ(g_cpu.A);
label_F84A:;
    /* $F84A: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x6E; FLAG_NZ(g_cpu.A);
label_F84C:;
    /* $F84C: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_F854; }
label_F84E:;
    /* $F84E: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xF4); FLAG_NZ(g_cpu.A);
label_F850:;
    /* $F850: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x0A; FLAG_NZ(g_cpu.A);
label_F852:;
    /* $F852: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_F86D; }
label_F854:; /* NotDOrD4 */
    /* $F854: 8A */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.X; FLAG_NZ(g_cpu.A);
label_F855:;
    /* $F855: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x12; g_cpu.C=(g_cpu.A>=0x12)?1:0; FLAG_NZ(r&0xFF); }
label_F857:;
    /* $F857: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_F868; }
label_F859:;
    /* $F859: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07B1); FLAG_NZ(g_cpu.A);
label_F85C:;
    /* $F85C: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x08; FLAG_NZ(g_cpu.A);
label_F85E:;
    /* $F85E: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_F864; }
label_F860:;
    /* $F860: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x0F; FLAG_NZ(g_cpu.A);
label_F862:;
    /* $F862: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_F86A; }
label_F864:; /* MediN */
    /* $F864: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x1F; FLAG_NZ(g_cpu.A);
label_F866:;
    /* $F866: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_F86A; }
label_F868:; /* LongN */
    /* $F868: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xFF; FLAG_NZ(g_cpu.A);
label_F86A:; /* LoadTriCtrlReg */
    /* $F86A: 8D */ maybe_trigger_vblank(4); nes_write(0x4008, g_cpu.A);
label_F86D:; /* HandleNoiseMusic */
    /* $F86D: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xF4); FLAG_NZ(g_cpu.A);
label_F86F:;
    /* $F86F: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0xF3; FLAG_NZ(g_cpu.A);
label_F871:;
    /* $F871: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_F8C4; }
label_F873:;
    /* $F873: CE */ maybe_trigger_vblank(6); { uint16_t a=0x07BA; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_F876:;
    /* $F876: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_F8C4; }
label_F878:; /* FetchNoiseBeatData */
    /* $F878: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x07B0); FLAG_NZ(g_cpu.Y);
label_F87B:;
    /* $F87B: EE */ maybe_trigger_vblank(6); { uint16_t a=0x07B0; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_F87E:;
    /* $F87E: B1 */ maybe_trigger_vblank(5); g_cpu.A = nes_read((nes_read16zp(0xF5) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_F880:;
    /* $F880: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_F88A; }
label_F882:;
    /* $F882: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07C1); FLAG_NZ(g_cpu.A);
label_F885:;
    /* $F885: 8D */ maybe_trigger_vblank(4); nes_write(0x07B0, g_cpu.A);
label_F888:;
    /* $F888: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) {
    maybe_trigger_vblank(1);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_F878;
    }
label_F88A:; /* NoiseBeatHandler */
    /* $F88A: 20 */ maybe_trigger_vblank(6); func_F8C5();
label_F88D:;
    /* $F88D: 8D */ maybe_trigger_vblank(4); nes_write(0x07BA, g_cpu.A);
label_F890:;
    /* $F890: 8A */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.X; FLAG_NZ(g_cpu.A);
label_F891:;
    /* $F891: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x3E; FLAG_NZ(g_cpu.A);
label_F893:;
    /* $F893: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_F8B9; }
label_F895:;
    /* $F895: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x30; g_cpu.C=(g_cpu.A>=0x30)?1:0; FLAG_NZ(r&0xFF); }
label_F897:;
    /* $F897: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_F8B1; }
label_F899:;
    /* $F899: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x20; g_cpu.C=(g_cpu.A>=0x20)?1:0; FLAG_NZ(r&0xFF); }
label_F89B:;
    /* $F89B: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_F8A9; }
label_F89D:;
    /* $F89D: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x10; FLAG_NZ(g_cpu.A);
label_F89F:;
    /* $F89F: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_F8B9; }
label_F8A1:;
    /* $F8A1: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x1C; FLAG_NZ(g_cpu.A);
label_F8A3:;
    /* $F8A3: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x03; FLAG_NZ(g_cpu.X);
label_F8A5:;
    /* $F8A5: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x18; FLAG_NZ(g_cpu.Y);
label_F8A7:;
    /* $F8A7: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_F8BB; }
label_F8A9:; /* StrongBeat */
    /* $F8A9: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x1C; FLAG_NZ(g_cpu.A);
label_F8AB:;
    /* $F8AB: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x0C; FLAG_NZ(g_cpu.X);
label_F8AD:;
    /* $F8AD: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x18; FLAG_NZ(g_cpu.Y);
label_F8AF:;
    /* $F8AF: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_F8BB; }
label_F8B1:; /* LongBeat */
    /* $F8B1: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x1C; FLAG_NZ(g_cpu.A);
label_F8B3:;
    /* $F8B3: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x03; FLAG_NZ(g_cpu.X);
label_F8B5:;
    /* $F8B5: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x58; FLAG_NZ(g_cpu.Y);
label_F8B7:;
    /* $F8B7: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_F8BB; }
label_F8B9:; /* SilentBeat */
    /* $F8B9: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x10; FLAG_NZ(g_cpu.A);
label_F8BB:; /* PlayBeat */
    /* $F8BB: 8D */ maybe_trigger_vblank(4); nes_write(0x400C, g_cpu.A);
label_F8BE:;
    /* $F8BE: 8E */ maybe_trigger_vblank(4); nes_write(0x400E, g_cpu.X);
label_F8C1:;
    /* $F8C1: 8C */ maybe_trigger_vblank(4); nes_write(0x400F, g_cpu.Y);
label_F8C4:; /* ExitMusicHandler */
    /* $F8C4: 60 */ maybe_trigger_vblank(6); 
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
    return;
}

void func_F693(void) {
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_F693");
#endif
    func_F693_body(0);
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
}

void func_F695(void) {
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_F695");
#endif
    func_F693_body(1);
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
}

void func_F9DA(void) {
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_F9DA");
#endif
label_F9DA:;
    /* $F9DA: 98 */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.Y; FLAG_NZ(g_cpu.A);
label_F9DB:;
    /* $F9DB: 1F */ maybe_trigger_vblank(7); { uint16_t a=(0x1D1D + g_cpu.X) & 0xFFFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); g_cpu.A|=v; FLAG_NZ(g_cpu.A); }
label_F9DE:;
    /* $F9DE: 1D */ maybe_trigger_vblank(4); g_cpu.A |= nes_read((0x1D94 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_F9E1:;
    /* $F9E1: 1D */ maybe_trigger_vblank(4); g_cpu.A |= nes_read((0x9C94 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_F9E4:;
    /* $F9E4: 94 */ maybe_trigger_vblank(4); nes_write((0x1D + g_cpu.X) & 0xFF, g_cpu.Y);
label_F9E6:;
    /* $F9E6: 86 */ maybe_trigger_vblank(3); nes_write(0x18, g_cpu.X);
label_F9E8:;
    /* $F9E8: 85 */ maybe_trigger_vblank(3); nes_write(0x26, g_cpu.A);
label_F9EA:;
    /* $F9EA: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) { maybe_trigger_vblank(1); call_by_address(0xF970); return; }
label_F9EC:;
    /* $F9EC: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x26); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_F9EE:;
    /* $F9EE: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) { maybe_trigger_vblank(1); call_by_address(0xF976); return; }
label_F9F0:;
    /* $F9F0: 14 */ maybe_trigger_vblank(4); (void)nes_read((0x85 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_F9F2:;
    /* $F9F2: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_F9F3:;
    /* $F9F3: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x0484); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_F9F6:;
    /* $F9F6: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_F9F7:;
    /* $F9F7: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0xD021); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_F9FA:;
    /* $F9FA: C4 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0xD0); int r=g_cpu.Y-m; g_cpu.C=(g_cpu.Y>=m)?1:0; FLAG_NZ(r&0xFF); }
label_F9FC:;
    /* $F9FC: 31 */ maybe_trigger_vblank(5); g_cpu.A &= nes_read((nes_read16zp(0xD0) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_F9FE:;
    /* $F9FE: C4 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0xD0); int r=g_cpu.Y-m; g_cpu.C=(g_cpu.Y>=m)?1:0; FLAG_NZ(r&0xFF); }
label_FA00:;
    /* $FA00: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xFA00); return;
}

void func_FB5D(void) {
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_FB5D");
#endif
label_FB5D:;
    /* $FB5D: F7 */ maybe_trigger_vblank(6); { uint16_t a=(0xF5 + g_cpu.X) & 0xFF; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); int16_t r=g_cpu.A-v-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,v); g_cpu.A=r&0xFF; }
label_FB5F:;
    /* $FB5F: F1 */ maybe_trigger_vblank(5); { uint8_t m=nes_read((nes_read16zp(0xAC) + g_cpu.Y) & 0xFFFF); int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_FB61:;
    /* $FB61: 27 */ maybe_trigger_vblank(5); { uint16_t a=0x9E; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); g_cpu.A&=v; FLAG_NZ(g_cpu.A); }
label_FB63:;
    /* $FB63: 9D */ maybe_trigger_vblank(5); nes_write((0x1885 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_FB66:;
    /* $FB66: 82 */ maybe_trigger_vblank(2); /* NOP */
label_FB68:;
    /* $FB68: 84 */ maybe_trigger_vblank(3); nes_write(0x22, g_cpu.Y);
label_FB6A:;
    /* $FB6A: 2A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_FB6B:;
    /* $FB6B: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_FB6C:;
    /* $FB6C: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_FB6D:;
    /* $FB6D: 82 */ maybe_trigger_vblank(2); /* NOP */
label_FB6F:;
    /* $FB6F: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x0422); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_FB72:; /* DeathMusData */
    /* $FB72: 86 */ maybe_trigger_vblank(3); nes_write(0x04, g_cpu.X);
label_FB74:; /* GroundM_P4CData */
    /* $FB74: 82 */ maybe_trigger_vblank(2); /* NOP */
label_FB76:;
    /* $FB76: 36 */ maybe_trigger_vblank(6); { uint16_t a=(0x04 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FB78:;
    /* $FB78: 36 */ maybe_trigger_vblank(6); { uint16_t a=(0x87 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FB7A:;
    /* $FB7A: 36 */ maybe_trigger_vblank(6); { uint16_t a=(0x34 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FB7C:;
    /* $FB7C: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) { maybe_trigger_vblank(1); call_by_address(0xFB04); return; }
label_FB7E:;
    /* $FB7E: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x0004); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_FB81:;
    /* $FB81: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xFB81); return;
}

void func_FBCB(void) {
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_FBCB");
#endif
label_FBCB:;
    /* $FBCB: 20 */ maybe_trigger_vblank(6); nes_dispatch_call(0x2028, -1);
label_FBCE:;
    /* $FBCE: 26 */ maybe_trigger_vblank(5); { uint16_t a=0x20; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FBD0:;
    /* $FBD0: 28 */ maybe_trigger_vblank(4); { g_cpu.S++; uint8_t p = g_ram[0x100 + g_cpu.S];
  g_cpu.N=(p>>7)&1; g_cpu.V=(p>>6)&1; g_cpu.D=(p>>3)&1;
  g_cpu.I=(p>>2)&1; g_cpu.Z=(p>>1)&1; g_cpu.C=p&1; }
label_FBD1:;
    /* $FBD1: 20 */ maybe_trigger_vblank(6); nes_dispatch_call(0x2026, -1);
label_FBD4:;
    /* $FBD4: 24 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x20); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_FBD6:;
    /* $FBD6: 26 */ maybe_trigger_vblank(5); { uint16_t a=0x20; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FBD8:;
    /* $FBD8: 24 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x20); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_FBDA:;
    /* $FBDA: 26 */ maybe_trigger_vblank(5); { uint16_t a=0x20; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FBDC:;
    /* $FBDC: 28 */ maybe_trigger_vblank(4); { g_cpu.S++; uint8_t p = g_ram[0x100 + g_cpu.S];
  g_cpu.N=(p>>7)&1; g_cpu.V=(p>>6)&1; g_cpu.D=(p>>3)&1;
  g_cpu.I=(p>>2)&1; g_cpu.Z=(p>>1)&1; g_cpu.C=p&1; }
label_FBDD:;
    /* $FBDD: 20 */ maybe_trigger_vblank(6); nes_dispatch_call(0x2026, -1);
label_FBE0:;
    /* $FBE0: 28 */ maybe_trigger_vblank(4); { g_cpu.S++; uint8_t p = g_ram[0x100 + g_cpu.S];
  g_cpu.N=(p>>7)&1; g_cpu.V=(p>>6)&1; g_cpu.D=(p>>3)&1;
  g_cpu.I=(p>>2)&1; g_cpu.Z=(p>>1)&1; g_cpu.C=p&1; }
label_FBE1:;
    /* $FBE1: 20 */ maybe_trigger_vblank(6); nes_dispatch_call(0x2026, -1);
label_FBE4:;
    /* $FBE4: 24 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x28); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_FBE6:;
    /* $FBE6: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) { maybe_trigger_vblank(2); goto label_FC10; }
label_FBE8:;
    /* $FBE8: 32 */ maybe_trigger_vblank(2); /* ILLEGAL $32 — skip 1 */
label_FBE9:;
    /* $FBE9: 28 */ maybe_trigger_vblank(4); { g_cpu.S++; uint8_t p = g_ram[0x100 + g_cpu.S];
  g_cpu.N=(p>>7)&1; g_cpu.V=(p>>6)&1; g_cpu.D=(p>>3)&1;
  g_cpu.I=(p>>2)&1; g_cpu.Z=(p>>1)&1; g_cpu.C=p&1; }
label_FBEA:;
    /* $FBEA: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) { maybe_trigger_vblank(2); call_by_address(0xFC14); return; }
label_FBEC:;
    /* $FBEC: 2E */ maybe_trigger_vblank(6); { uint16_t a=0x3028; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FBEF:;
    /* $FBEF: 28 */ maybe_trigger_vblank(4); { g_cpu.S++; uint8_t p = g_ram[0x100 + g_cpu.S];
  g_cpu.N=(p>>7)&1; g_cpu.V=(p>>6)&1; g_cpu.D=(p>>3)&1;
  g_cpu.I=(p>>2)&1; g_cpu.Z=(p>>1)&1; g_cpu.C=p&1; }
label_FBF0:;
    /* $FBF0: 2E */ maybe_trigger_vblank(6); { uint16_t a=0x2C28; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FBF3:;
    /* $FBF3: 28 */ maybe_trigger_vblank(4); { g_cpu.S++; uint8_t p = g_ram[0x100 + g_cpu.S];
  g_cpu.N=(p>>7)&1; g_cpu.V=(p>>6)&1; g_cpu.D=(p>>3)&1;
  g_cpu.I=(p>>2)&1; g_cpu.Z=(p>>1)&1; g_cpu.C=p&1; }
label_FBF4:;
    /* $FBF4: 2E */ maybe_trigger_vblank(6); { uint16_t a=0x3028; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FBF7:;
    /* $FBF7: 28 */ maybe_trigger_vblank(4); { g_cpu.S++; uint8_t p = g_ram[0x100 + g_cpu.S];
  g_cpu.N=(p>>7)&1; g_cpu.V=(p>>6)&1; g_cpu.D=(p>>3)&1;
  g_cpu.I=(p>>2)&1; g_cpu.Z=(p>>1)&1; g_cpu.C=p&1; }
label_FBF8:;
    /* $FBF8: 32 */ maybe_trigger_vblank(2); /* ILLEGAL $32 — skip 1 */
label_FBF9:;
    /* $FBF9: 28 */ maybe_trigger_vblank(4); { g_cpu.S++; uint8_t p = g_ram[0x100 + g_cpu.S];
  g_cpu.N=(p>>7)&1; g_cpu.V=(p>>6)&1; g_cpu.D=(p>>3)&1;
  g_cpu.I=(p>>2)&1; g_cpu.Z=(p>>1)&1; g_cpu.C=p&1; }
label_FBFA:;
    /* $FBFA: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) { maybe_trigger_vblank(2); goto label_FC24; }
label_FBFC:;
    /* $FBFC: 2E */ maybe_trigger_vblank(6); { uint16_t a=0x3028; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FBFF:;
    /* $FBFF: 28 */ maybe_trigger_vblank(4); { g_cpu.S++; uint8_t p = g_ram[0x100 + g_cpu.S];
  g_cpu.N=(p>>7)&1; g_cpu.V=(p>>6)&1; g_cpu.D=(p>>3)&1;
  g_cpu.I=(p>>2)&1; g_cpu.Z=(p>>1)&1; g_cpu.C=p&1; }
label_FC00:;
    /* $FC00: 2E */ maybe_trigger_vblank(6); { uint16_t a=0x2C28; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FC03:;
    /* $FC03: 28 */ maybe_trigger_vblank(4); { g_cpu.S++; uint8_t p = g_ram[0x100 + g_cpu.S];
  g_cpu.N=(p>>7)&1; g_cpu.V=(p>>6)&1; g_cpu.D=(p>>3)&1;
  g_cpu.I=(p>>2)&1; g_cpu.Z=(p>>1)&1; g_cpu.C=p&1; }
label_FC04:;
    /* $FC04: 2E */ maybe_trigger_vblank(6); { uint16_t a=0x0400; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FC07:;
    /* $FC07: 70 */ maybe_trigger_vblank(2); if (g_cpu.V) { maybe_trigger_vblank(1); goto label_FC77; }
label_FC09:;
    /* $FC09: 6C */ maybe_trigger_vblank(5); { uint16_t _jt = nes_read16_jmpbug(0x706E); nes_trace_indirect_jump(0xFC09, _jt); maybe_trigger_vblank(2); call_by_address_tail(_jt, -1); return; }
label_FC10:;
    /* $FC10: 6E */ maybe_trigger_vblank(6); { uint16_t a=0x6E6C; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=v&1; v=((v>>1)|(c<<7))&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FC13:;
    /* $FC13: 70 */ maybe_trigger_vblank(2); if (g_cpu.V) { maybe_trigger_vblank(1); call_by_address(0xFC87); return; }
label_FC15:;
    /* $FC15: 70 */ maybe_trigger_vblank(2); if (g_cpu.V) { maybe_trigger_vblank(1); call_by_address(0xFC85); return; }
label_FC17:;
    /* $FC17: 6E */ maybe_trigger_vblank(6); { uint16_t a=0x6E6C; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=v&1; v=((v>>1)|(c<<7))&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FC1A:;
    /* $FC1A: 70 */ maybe_trigger_vblank(2); if (g_cpu.V) { maybe_trigger_vblank(1); goto label_FC8A; }
label_FC1C:;
    /* $FC1C: 70 */ maybe_trigger_vblank(2); if (g_cpu.V) { maybe_trigger_vblank(1); goto label_FC8C; }
label_FC1E:;
    /* $FC1E: 6C */ maybe_trigger_vblank(5); { uint16_t _jt = nes_read16_jmpbug(0x6C6E); nes_trace_indirect_jump(0xFC1E, _jt); maybe_trigger_vblank(2); call_by_address_tail(_jt, -1); return; }
label_FC24:;
    /* $FC24: 70 */ maybe_trigger_vblank(2); if (g_cpu.V) { maybe_trigger_vblank(1); goto label_FC94; }
label_FC26:;
    /* $FC26: 6C */ maybe_trigger_vblank(5); { uint16_t _jt = nes_read16_jmpbug(0x7876); nes_trace_indirect_jump(0xFC26, _jt); maybe_trigger_vblank(2); call_by_address_tail(_jt, -1); return; }
label_FC77:;
    /* $FC77: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) { maybe_trigger_vblank(1); goto label_FC7D; }
label_FC79:;
    /* $FC79: 1E */ maybe_trigger_vblank(7); { uint16_t a=(0x0432 + g_cpu.X) & 0xFFFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FC7C:;
    /* $FC7C: 32 */ maybe_trigger_vblank(2); /* ILLEGAL $32 — skip 1 */
label_FC7D:;
    /* $FC7D: 32 */ maybe_trigger_vblank(2); /* ILLEGAL $32 — skip 1 */
label_FC7E:;
    /* $FC7E: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x20); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FC80:;
    /* $FC80: 34 */ maybe_trigger_vblank(4); (void)nes_read((0x04 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FC82:;
    /* $FC82: 34 */ maybe_trigger_vblank(4); (void)nes_read((0x34 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FC84:;
    /* $FC84: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x36); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FC86:;
    /* $FC86: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x84); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FC88:;
    /* $FC88: 36 */ maybe_trigger_vblank(6); { uint16_t a=(0x00 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FC8A:;
    /* $FC8A: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xA4; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_FC8C:;
    /* $FC8C: 64 */ maybe_trigger_vblank(3); (void)nes_read(0xA4); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FC8E:;
    /* $FC8E: 48 */ maybe_trigger_vblank(3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_FC8F:;
    /* $FC8F: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x66); FLAG_NZ(g_cpu.X);
label_FC91:;
    /* $FC91: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x4A); FLAG_NZ(g_cpu.X);
label_FC93:;
    /* $FC93: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_FC94:;
    /* $FC94: 68 */ maybe_trigger_vblank(4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_FC95:;
    /* $FC95: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_FC96:;
    /* $FC96: 6A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=g_cpu.A&1; g_cpu.A=((g_cpu.A>>1)|(c<<7))&0xFF; FLAG_NZ(g_cpu.A); }
label_FC97:;
    /* $FC97: 44 */ maybe_trigger_vblank(3); (void)nes_read(0x2B); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FC99:;
    /* $FC99: 81 */ maybe_trigger_vblank(6); nes_write(nes_read16zp((0x2A + g_cpu.X) & 0xFF), g_cpu.A);
label_FC9B:;
    /* $FC9B: 42 */ maybe_trigger_vblank(2); /* ILLEGAL $42 — skip 1 */
label_FC9C:;
    /* $FC9C: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x42); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FC9E:;
    /* $FC9E: 42 */ maybe_trigger_vblank(2); /* ILLEGAL $42 — skip 1 */
label_FC9F:;
    /* $FC9F: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x2C); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FCA1:;
    /* $FCA1: 64 */ maybe_trigger_vblank(3); (void)nes_read(0x04); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FCA3:;
    /* $FCA3: 64 */ maybe_trigger_vblank(3); (void)nes_read(0x64); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FCA5:;
    /* $FCA5: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x2E); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FCA7:;
    /* $FCA7: 46 */ maybe_trigger_vblank(5); { uint16_t a=0x04; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_FCA9:;
    /* $FCA9: 46 */ maybe_trigger_vblank(5); { uint16_t a=0x46; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_FCAB:;
    /* $FCAB: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x22); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FCAD:;
    /* $FCAD: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x84); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FCAF:;
    /* $FCAF: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_FCB0:; /* WinLevelMusData */
    /* $FCB0: 87 */ maybe_trigger_vblank(3); nes_write(0x04, g_cpu.A & g_cpu.X); /* SAX */
label_FCB2:;
    /* $FCB2: 06 */ maybe_trigger_vblank(5); { uint16_t a=0x0C; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FCB4:;
    /* $FCB4: 14 */ maybe_trigger_vblank(4); (void)nes_read((0x1C + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FCB6:;
    /* $FCB6: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_FCB7:;
    /* $FCB7: 86 */ maybe_trigger_vblank(3); nes_write(0x2C, g_cpu.X);
label_FCB9:;
    /* $FCB9: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_FCBA:;
    /* $FCBA: 87 */ maybe_trigger_vblank(3); nes_write(0x04, g_cpu.A & g_cpu.X); /* SAX */
label_FCBC:;
    /* $FCBC: 60 */ maybe_trigger_vblank(6); 
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
    return;
label_FCBD:; return;
label_FCC0:; return;
label_FCC2:; return;
label_FCC5:; return;
label_FCC7:; return;
label_FCC9:; return;
label_FCCC:; return;
label_FCCE:; return;
label_FCD0:; return;
label_FCD1:; return;
label_FCD4:; return;
label_FCD6:; return;
label_FCD8:; return;
label_FCDA:; return;
label_FCDC:; return;
label_FCDE:; return;
label_FCE0:; return;
label_FCE2:; return;
label_FCE5:; return;
label_FCE7:; return;
label_FCEA:; return;
label_FCED:; return;
label_FCEF:; return;
label_FCF1:; return;
label_FCF4:; return;
label_FCF6:; return;
label_FCF9:; return;
label_FCFB:; return;
label_FCFD:; return;
label_FCFF:; return;
label_FD00:; return;
label_FD02:; return;
label_FD04:; return;
label_FD06:; return;
label_FD07:; return;
label_FD0A:; return;
label_FD0C:; return;
label_FD0E:; return;
label_FD10:; return;
label_FD13:; return;
label_FD16:; return;
label_FD18:; return;
label_FD1A:; return;
label_FD1C:; return;
label_FD1F:; return;
label_FD21:; return;
label_FD23:; return;
label_FD25:; return;
label_FD28:; return;
label_FD29:; return;
label_FD2A:; return;
label_FD2C:; return;
label_FD2E:; return;
label_FD31:; return;
label_FD32:; return;
label_FD33:; return;
label_FD35:; return;
label_FD37:; return;
label_FD38:; return;
label_FD3A:; return;
label_FD3C:; return;
label_FD3D:; return;
label_FD40:; return;
label_FD42:; return;
label_FD45:; return;
label_FD46:; return;
label_FD48:; return;
label_FD4A:; return;
label_FD4B:; return;
label_FD4D:; return;
label_FD50:; return;
label_FD52:; return;
label_FD54:; return;
label_FD57:; return;
label_FD59:; return;
label_FD5B:; return;
label_FD5C:; return;
label_FD5D:; return;
label_FD5F:; return;
label_FD61:; return;
label_FD62:; return;
label_FD64:; return;
label_FD66:; return;
label_FD67:; return;
label_FD69:; return;
label_FD6B:; return;
label_FD6D:; return;
label_FD70:; return;
label_FD72:; return;
label_FD73:; return;
label_FD75:; return;
label_FD77:; return;
label_FD79:; return;
label_FD7B:; return;
label_FD7D:; return;
label_FD80:; return;
label_FD82:; return;
label_FD84:; return;
label_FD87:; return;
label_FD89:; return;
label_FD8A:; return;
label_FD8C:; return;
label_FD8E:; return;
label_FD90:; return;
label_FD92:; return;
label_FD94:; return;
label_FD95:; return;
label_FD96:; return;
label_FD98:; return;
label_FD9A:; return;
label_FD9C:; return;
label_FD9E:; return;
label_FDA0:; return;
label_FDA2:; return;
label_FDA4:; return;
label_FDA6:; return;
label_FDA8:; return;
label_FDAA:; return;
label_FDAC:; return;
label_FDAE:; return;
label_FDAF:; return;
label_FDB1:; return;
label_FDB3:; return;
label_FDB5:; return;
label_FDB7:; return;
label_FDB9:; return;
label_FDBA:; return;
label_FDBC:; return;
label_FDBE:; return;
label_FDC0:; return;
label_FDC2:; return;
label_FDC3:; return;
label_FDC5:; return;
label_FDC6:; return;
label_FDC8:; return;
label_FDC9:; return;
label_FDCA:; return;
label_FDCB:; return;
label_FDCD:; return;
label_FDCF:; return;
label_FDD1:; return;
label_FDD3:; return;
label_FDD5:; return;
label_FDD7:; return;
label_FDD9:; return;
label_FDDC:; return;
label_FDDF:; return;
label_FDE1:; return;
label_FDE3:; return;
label_FDE6:; return;
label_FDE9:; return;
label_FDEB:; return;
label_FDED:; return;
label_FDEE:; return;
label_FDEF:; return;
label_FDF1:; return;
label_FDF4:; return;
label_FDF6:; return;
label_FDF7:; return;
label_FDF9:; return;
label_FDFB:; return;
label_FDFC:; return;
label_FDFF:; return;
label_FE00:; return;
label_FE02:; return;
label_FE05:; return;
label_FE08:; return;
label_FE0B:; return;
label_FE0C:; return;
label_FE0E:; return;
label_FE11:; return;
label_FE14:; return;
label_FE15:; return;
label_FE17:; return;
label_FE18:; return;
label_FE19:; return;
label_FE1A:; return;
label_FE1B:; return;
label_FE1C:; return;
label_FE1D:; return;
label_FE1E:; return;
label_FE1F:; return;
label_FE20:; return;
label_FE21:; return;
label_FE22:; return;
label_FE23:; return;
label_FE24:; return;
label_FE26:; return;
label_FE29:; return;
label_FE2C:; return;
label_FE2E:; return;
label_FE2F:; return;
label_FE31:; return;
label_FE32:; return;
label_FE35:; return;
label_FE37:; return;
label_FE39:; return;
label_FE3B:; return;
label_FE3D:; return;
label_FE3F:; return;
label_FE40:; return;
label_FE41:; return;
label_FE43:; return;
label_FE44:; return;
label_FE46:; return;
label_FE47:; return;
label_FE48:; return;
label_FE4A:; return;
label_FE4D:; return;
label_FE4F:; return;
label_FE51:; return;
label_FE53:; return;
label_FE54:; return;
label_FE57:; return;
label_FE5A:; return;
label_FE5C:; return;
label_FE5F:; return;
label_FE62:; return;
label_FE64:; return;
label_FE66:; return;
label_FE67:; return;
label_FE68:; return;
label_FE69:; return;
label_FE6A:; return;
label_FE6B:; return;
label_FE6C:; return;
label_FE6E:; return;
label_FE70:; return;
label_FE72:; return;
label_FE74:; return;
label_FE75:; return;
label_FE78:; return;
label_FE7B:; return;
label_FE7E:; return;
label_FE81:; return;
label_FE84:; return;
label_FE87:; return;
label_FE8A:; return;
label_FE8D:; return;
label_FE90:; return;
label_FE91:; return;
label_FE93:; return;
label_FE94:; return;
label_FE96:; return;
label_FE97:; return;
label_FE98:; return;
label_FE99:; return;
label_FE9B:; return;
label_FE9D:; return;
label_FE9F:; return;
label_FEA1:; return;
label_FEA3:; return;
label_FEA5:; return;
label_FEA7:; return;
label_FEA9:; return;
label_FEAB:; return;
label_FEAD:; return;
label_FEAF:; return;
label_FEB1:; return;
label_FEB3:; return;
label_FEB5:; return;
label_FEB7:; return;
label_FEB8:; return;
label_FEB9:; return;
label_FEBA:; return;
label_FEBB:; return;
label_FEBC:; return;
label_FEBD:; return;
label_FEBF:; return;
label_FEC0:; return;
label_FEC2:; return;
label_FEC4:; return;
label_FEC7:; return;
label_FEC9:; return;
label_FECB:; return;
label_FECE:; return;
label_FED0:; return;
label_FED1:; return;
label_FED3:; return;
label_FED4:; return;
label_FED7:; return;
label_FED8:; return;
label_FEDB:; return;
label_FEDC:; return;
label_FEDE:; return;
label_FEE0:; return;
label_FEE3:; return;
label_FEE6:; return;
label_FEE8:; return;
label_FEEA:; return;
label_FEEC:; return;
label_FEEE:; return;
label_FEF0:; return;
label_FEF1:; return;
label_FEF2:; return;
label_FEF5:; return;
label_FEF6:; return;
label_FEF9:; return;
label_FEFC:; return;
label_FEFE:; return;
label_FF01:; return;
label_FF02:; return;
label_FF03:; return;
label_FF06:; return;
label_FF07:; return;
label_FF09:; return;
label_FF0B:; return;
label_FF0E:; return;
label_FF0F:; return;
label_FF10:; return;
label_FF12:; return;
label_FF14:; return;
label_FF16:; return;
label_FF18:; return;
label_FF1A:; return;
label_FF1C:; return;
label_FF1E:; return;
label_FF20:; return;
label_FF22:; return;
label_FF24:; return;
label_FF26:; return;
label_FF27:; return;
label_FF2A:; return;
label_FF2B:; return;
label_FF2D:; return;
label_FF2F:; return;
label_FF31:; return;
label_FF34:; return;
label_FF35:; return;
label_FF37:; return;
label_FF39:; return;
label_FF3B:; return;
label_FF3E:; return;
label_FF3F:; return;
label_FF41:; return;
label_FF44:; return;
label_FF45:; return;
label_FF47:; return;
label_FF49:; return;
label_FF4C:; return;
label_FF4D:; return;
label_FF4F:; return;
label_FF51:; return;
label_FF53:; return;
label_FF56:; return;
label_FF57:; return;
label_FF58:; return;
label_FF59:; return;
label_FF5B:; return;
label_FF5D:; return;
label_FF5F:; return;
label_FF62:; return;
label_FF64:; return;
label_FF65:; return;
label_FF66:; return;
label_FF68:; return;
label_FF6A:; return;
label_FF6C:; return;
label_FF6F:; return;
label_FF70:; return;
label_FF72:; return;
label_FF73:; return;
label_FF74:; return;
label_FF76:; return;
label_FF78:; return;
label_FF7B:; return;
label_FF7C:; return;
label_FF7E:; return;
label_FF80:; return;
label_FF82:; return;
label_FF83:; return;
label_FF86:; return;
label_FF88:; return;
label_FF8A:; return;
label_FF8D:; return;
label_FF8E:; return;
label_FF8F:; return;
label_FF91:; return;
label_FF92:; return;
label_FF94:; return;
label_FF97:; return;
label_FF9A:; return;
label_FF9C:; return;
label_FF9E:; return;
label_FFA0:; return;
label_FFA2:; return;
label_FFA4:; return;
label_FFA5:; return;
label_FFA6:; return;
label_FFA8:; return;
label_FFAA:; return;
label_FFAC:; return;
label_FFAE:; return;
label_FFB0:; return;
label_FFB2:; return;
label_FFB4:; return;
label_FFB6:; return;
label_FFB8:; return;
label_FFBA:; return;
label_FFBC:; return;
label_FFBE:; return;
label_FFC0:; return;
label_FFC2:; return;
label_FFC4:; return;
label_FFC6:; return;
label_FFC8:; return;
label_FFCA:; return;
label_FFCC:; return;
label_FFCE:; return;
label_FFD0:; return;
label_FFD3:; return;
label_FFD4:; return;
label_FFD7:; return;
label_FFDA:; return;
label_FFDD:; return;
label_FFE0:; return;
label_FFE3:; return;
label_FFE6:; return;
label_FFE7:; return;
label_FFE8:; return;
label_FFEA:; return;
label_FFEC:; return;
label_FFEE:; return;
label_FFF0:; return;
label_FFF3:; return;
label_FFF4:; return;
label_FFF7:; return;
label_FFFA:; return;
label_FFFC:; return;
label_FFFD:; return;
label_FFFF:; return;
}

void func_8286_b1(void) {
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_8286_b1");
#endif
label_8286:;
    /* $8286: 0E */ maybe_trigger_vblank(6); { uint16_t a=0x1EC3; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_8289:;
    /* $8289: C3 */ maybe_trigger_vblank(8); { uint16_t a=nes_read16zp((0xF0 + g_cpu.X) & 0xFF); uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); g_cpu.C=(g_cpu.A>=v)?1:0; FLAG_NZ((uint8_t)(g_cpu.A-v)); }
label_828B:;
    /* $828B: C2 */ maybe_trigger_vblank(2); /* NOP */
label_828D:;
    /* $828D: C3 */ maybe_trigger_vblank(8); { uint16_t a=nes_read16zp((0xF1 + g_cpu.X) & 0xFF); uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); g_cpu.C=(g_cpu.A>=v)?1:0; FLAG_NZ((uint8_t)(g_cpu.A-v)); }
label_828F:;
    /* $828F: C2 */ maybe_trigger_vblank(2); /* NOP */
label_8291:;
    /* $8291: C3 */ maybe_trigger_vblank(8); { uint16_t a=nes_read16zp((0x6B + g_cpu.X) & 0xFF); uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); g_cpu.C=(g_cpu.A>=v)?1:0; FLAG_NZ((uint8_t)(g_cpu.A-v)); }
label_8293:;
    /* $8293: C3 */ maybe_trigger_vblank(8); { uint16_t a=nes_read16zp((0xF0 + g_cpu.X) & 0xFF); uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); g_cpu.C=(g_cpu.A>=v)?1:0; FLAG_NZ((uint8_t)(g_cpu.A-v)); }
label_8295:;
    /* $8295: C2 */ maybe_trigger_vblank(2); /* NOP */
label_8297:;
    /* $8297: C3 */ maybe_trigger_vblank(8); { uint16_t a=nes_read16zp((0x75 + g_cpu.X) & 0xFF); uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); g_cpu.C=(g_cpu.A>=v)?1:0; FLAG_NZ((uint8_t)(g_cpu.A-v)); }
label_8299:;
    /* $8299: C3 */ maybe_trigger_vblank(8); { uint16_t a=nes_read16zp((0xF7 + g_cpu.X) & 0xFF); uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); g_cpu.C=(g_cpu.A>=v)?1:0; FLAG_NZ((uint8_t)(g_cpu.A-v)); }
label_829B:;
    /* $829B: C2 */ maybe_trigger_vblank(2); /* NOP */
label_829D:;
    /* $829D: C7 */ maybe_trigger_vblank(5); { uint16_t a=0xD1; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); g_cpu.C=(g_cpu.A>=v)?1:0; FLAG_NZ((uint8_t)(g_cpu.A-v)); }
label_829F:;
    /* $829F: C7 */ maybe_trigger_vblank(5); { uint16_t a=0x4A; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); g_cpu.C=(g_cpu.A>=v)?1:0; FLAG_NZ((uint8_t)(g_cpu.A-v)); }
label_82A1:;
    /* $82A1: C3 */ maybe_trigger_vblank(8); { uint16_t a=nes_read16zp((0x3D + g_cpu.X) & 0xFF); uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); g_cpu.C=(g_cpu.A>=v)?1:0; FLAG_NZ((uint8_t)(g_cpu.A-v)); }
label_82A3:;
    /* $82A3: C3 */ maybe_trigger_vblank(8); { uint16_t a=nes_read16zp((0x85 + g_cpu.X) & 0xFF); uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); g_cpu.C=(g_cpu.A>=v)?1:0; FLAG_NZ((uint8_t)(g_cpu.A-v)); }
label_82A5:;
    /* $82A5: C3 */ maybe_trigger_vblank(8); { uint16_t a=nes_read16zp((0xA0 + g_cpu.X) & 0xFF); uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); g_cpu.C=(g_cpu.A>=v)?1:0; FLAG_NZ((uint8_t)(g_cpu.A-v)); }
label_82A7:;
    /* $82A7: C7 */ maybe_trigger_vblank(5); { uint16_t a=0xF0; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); g_cpu.C=(g_cpu.A>=v)?1:0; FLAG_NZ((uint8_t)(g_cpu.A-v)); }
label_82A9:; /* UpdateShroom */
    /* $82A9: C2 */ maybe_trigger_vblank(2); /* NOP */
label_82AB:;
    /* $82AB: C7 */ maybe_trigger_vblank(5); { uint16_t a=0xA0; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); g_cpu.C=(g_cpu.A>=v)?1:0; FLAG_NZ((uint8_t)(g_cpu.A-v)); }
label_82AD:;
    /* $82AD: C7 */ maybe_trigger_vblank(5); { uint16_t a=0xA0; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); g_cpu.C=(g_cpu.A>=v)?1:0; FLAG_NZ((uint8_t)(g_cpu.A-v)); }
label_82AF:;
    /* $82AF: C7 */ maybe_trigger_vblank(5); { uint16_t a=0xA0; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); g_cpu.C=(g_cpu.A>=v)?1:0; FLAG_NZ((uint8_t)(g_cpu.A-v)); }
label_82B1:;
    /* $82B1: C7 */ maybe_trigger_vblank(5); { uint16_t a=0xB8; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); g_cpu.C=(g_cpu.A>=v)?1:0; FLAG_NZ((uint8_t)(g_cpu.A-v)); }
label_82B3:;
    /* $82B3: C7 */ maybe_trigger_vblank(5); { uint16_t a=0xF0; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); g_cpu.C=(g_cpu.A>=v)?1:0; FLAG_NZ((uint8_t)(g_cpu.A-v)); }
label_82B5:;
    /* $82B5: C2 */ maybe_trigger_vblank(2); /* NOP */
label_82B7:;
    /* $82B7: C2 */ maybe_trigger_vblank(2); /* NOP */
label_82B9:;
    /* $82B9: C4 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x5C); int r=g_cpu.Y-m; g_cpu.C=(g_cpu.Y>=m)?1:0; FLAG_NZ(r&0xFF); }
label_82BB:; /* NullJoypad */
    /* $82BB: C4 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x5C); int r=g_cpu.Y-m; g_cpu.C=(g_cpu.Y>=m)?1:0; FLAG_NZ(r&0xFF); }
label_82BD:;
    /* $82BD: C4 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x5C); int r=g_cpu.Y-m; g_cpu.C=(g_cpu.Y>=m)?1:0; FLAG_NZ(r&0xFF); }
label_82BF:;
    /* $82BF: C4 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x59); int r=g_cpu.Y-m; g_cpu.C=(g_cpu.Y>=m)?1:0; FLAG_NZ(r&0xFF); }
label_82C1:;
    /* $82C1: C4 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0xF0); int r=g_cpu.Y-m; g_cpu.C=(g_cpu.Y>=m)?1:0; FLAG_NZ(r&0xFF); }
label_82C3:;
    /* $82C3: C2 */ maybe_trigger_vblank(2); /* NOP */
label_82C5:;
    /* $82C5: C2 */ maybe_trigger_vblank(2); /* NOP */
label_82C7:;
    /* $82C7: C2 */ maybe_trigger_vblank(2); /* NOP */
label_82C9:; /* ResetTitle */
    /* $82C9: C2 */ maybe_trigger_vblank(2); /* NOP */
label_82CB:;
    /* $82CB: C7 */ maybe_trigger_vblank(5); { uint16_t a=0x12; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); g_cpu.C=(g_cpu.A>=v)?1:0; FLAG_NZ((uint8_t)(g_cpu.A-v)); }
label_82CD:;
    /* $82CD: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_82CE:;
    /* $82CE: 3F */ maybe_trigger_vblank(7); { uint16_t a=(0x45C8 + g_cpu.X) & 0xFFFF; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); g_cpu.A&=v; FLAG_NZ(g_cpu.A); }
label_82D1:;
    /* $82D1: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_82D2:;
    /* $82D2: 0B */ maybe_trigger_vblank(2); g_cpu.A &= 0xC8; FLAG_NZ(g_cpu.A); g_cpu.C=(g_cpu.A>>7)&1;
label_82D4:;
    /* $82D4: 03 */ maybe_trigger_vblank(8); { uint16_t a=nes_read16zp((0xC8 + g_cpu.X) & 0xFF); uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); g_cpu.A|=v; FLAG_NZ(g_cpu.A); }
label_82D6:;
    /* $82D6: 0B */ maybe_trigger_vblank(2); g_cpu.A &= 0xC8; FLAG_NZ(g_cpu.A); g_cpu.C=(g_cpu.A>>7)&1;
label_82D8:; /* ChkContinue */
    /* $82D8: 4B */ maybe_trigger_vblank(2); g_cpu.A &= 0xC8; g_cpu.C=g_cpu.A&1; g_cpu.A>>=1; FLAG_NZ(g_cpu.A);
label_82DA:;
    /* $82DA: 57 */ maybe_trigger_vblank(6); { uint16_t a=(0xC8 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); g_cpu.A^=v; FLAG_NZ(g_cpu.A); }
label_82DC:;
    /* $82DC: 49 */ maybe_trigger_vblank(2); g_cpu.A ^= 0xC5; FLAG_NZ(g_cpu.A);
label_82DE:;
    /* $82DE: 60 */ maybe_trigger_vblank(6); 
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
    return;
}

void func_8288_b1(void) {
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_8288_b1");
#endif
label_8288:;
    /* $8288: 1E */ maybe_trigger_vblank(7); { uint16_t a=(0xF0C3 + g_cpu.X) & 0xFFFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_828B:;
    /* $828B: C2 */ maybe_trigger_vblank(2); /* NOP */
label_828D:;
    /* $828D: C3 */ maybe_trigger_vblank(8); { uint16_t a=nes_read16zp((0xF1 + g_cpu.X) & 0xFF); uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); g_cpu.C=(g_cpu.A>=v)?1:0; FLAG_NZ((uint8_t)(g_cpu.A-v)); }
label_828F:;
    /* $828F: C2 */ maybe_trigger_vblank(2); /* NOP */
label_8291:;
    /* $8291: C3 */ maybe_trigger_vblank(8); { uint16_t a=nes_read16zp((0x6B + g_cpu.X) & 0xFF); uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); g_cpu.C=(g_cpu.A>=v)?1:0; FLAG_NZ((uint8_t)(g_cpu.A-v)); }
label_8293:;
    /* $8293: C3 */ maybe_trigger_vblank(8); { uint16_t a=nes_read16zp((0xF0 + g_cpu.X) & 0xFF); uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); g_cpu.C=(g_cpu.A>=v)?1:0; FLAG_NZ((uint8_t)(g_cpu.A-v)); }
label_8295:;
    /* $8295: C2 */ maybe_trigger_vblank(2); /* NOP */
label_8297:;
    /* $8297: C3 */ maybe_trigger_vblank(8); { uint16_t a=nes_read16zp((0x75 + g_cpu.X) & 0xFF); uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); g_cpu.C=(g_cpu.A>=v)?1:0; FLAG_NZ((uint8_t)(g_cpu.A-v)); }
label_8299:;
    /* $8299: C3 */ maybe_trigger_vblank(8); { uint16_t a=nes_read16zp((0xF7 + g_cpu.X) & 0xFF); uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); g_cpu.C=(g_cpu.A>=v)?1:0; FLAG_NZ((uint8_t)(g_cpu.A-v)); }
label_829B:;
    /* $829B: C2 */ maybe_trigger_vblank(2); /* NOP */
label_829D:;
    /* $829D: C7 */ maybe_trigger_vblank(5); { uint16_t a=0xD1; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); g_cpu.C=(g_cpu.A>=v)?1:0; FLAG_NZ((uint8_t)(g_cpu.A-v)); }
label_829F:;
    /* $829F: C7 */ maybe_trigger_vblank(5); { uint16_t a=0x4A; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); g_cpu.C=(g_cpu.A>=v)?1:0; FLAG_NZ((uint8_t)(g_cpu.A-v)); }
label_82A1:;
    /* $82A1: C3 */ maybe_trigger_vblank(8); { uint16_t a=nes_read16zp((0x3D + g_cpu.X) & 0xFF); uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); g_cpu.C=(g_cpu.A>=v)?1:0; FLAG_NZ((uint8_t)(g_cpu.A-v)); }
label_82A3:;
    /* $82A3: C3 */ maybe_trigger_vblank(8); { uint16_t a=nes_read16zp((0x85 + g_cpu.X) & 0xFF); uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); g_cpu.C=(g_cpu.A>=v)?1:0; FLAG_NZ((uint8_t)(g_cpu.A-v)); }
label_82A5:;
    /* $82A5: C3 */ maybe_trigger_vblank(8); { uint16_t a=nes_read16zp((0xA0 + g_cpu.X) & 0xFF); uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); g_cpu.C=(g_cpu.A>=v)?1:0; FLAG_NZ((uint8_t)(g_cpu.A-v)); }
label_82A7:;
    /* $82A7: C7 */ maybe_trigger_vblank(5); { uint16_t a=0xF0; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); g_cpu.C=(g_cpu.A>=v)?1:0; FLAG_NZ((uint8_t)(g_cpu.A-v)); }
label_82A9:; /* UpdateShroom */
    /* $82A9: C2 */ maybe_trigger_vblank(2); /* NOP */
label_82AB:;
    /* $82AB: C7 */ maybe_trigger_vblank(5); { uint16_t a=0xA0; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); g_cpu.C=(g_cpu.A>=v)?1:0; FLAG_NZ((uint8_t)(g_cpu.A-v)); }
label_82AD:;
    /* $82AD: C7 */ maybe_trigger_vblank(5); { uint16_t a=0xA0; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); g_cpu.C=(g_cpu.A>=v)?1:0; FLAG_NZ((uint8_t)(g_cpu.A-v)); }
label_82AF:;
    /* $82AF: C7 */ maybe_trigger_vblank(5); { uint16_t a=0xA0; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); g_cpu.C=(g_cpu.A>=v)?1:0; FLAG_NZ((uint8_t)(g_cpu.A-v)); }
label_82B1:;
    /* $82B1: C7 */ maybe_trigger_vblank(5); { uint16_t a=0xB8; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); g_cpu.C=(g_cpu.A>=v)?1:0; FLAG_NZ((uint8_t)(g_cpu.A-v)); }
label_82B3:;
    /* $82B3: C7 */ maybe_trigger_vblank(5); { uint16_t a=0xF0; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); g_cpu.C=(g_cpu.A>=v)?1:0; FLAG_NZ((uint8_t)(g_cpu.A-v)); }
label_82B5:;
    /* $82B5: C2 */ maybe_trigger_vblank(2); /* NOP */
label_82B7:;
    /* $82B7: C2 */ maybe_trigger_vblank(2); /* NOP */
label_82B9:;
    /* $82B9: C4 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x5C); int r=g_cpu.Y-m; g_cpu.C=(g_cpu.Y>=m)?1:0; FLAG_NZ(r&0xFF); }
label_82BB:; /* NullJoypad */
    /* $82BB: C4 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x5C); int r=g_cpu.Y-m; g_cpu.C=(g_cpu.Y>=m)?1:0; FLAG_NZ(r&0xFF); }
label_82BD:;
    /* $82BD: C4 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x5C); int r=g_cpu.Y-m; g_cpu.C=(g_cpu.Y>=m)?1:0; FLAG_NZ(r&0xFF); }
label_82BF:;
    /* $82BF: C4 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x59); int r=g_cpu.Y-m; g_cpu.C=(g_cpu.Y>=m)?1:0; FLAG_NZ(r&0xFF); }
label_82C1:;
    /* $82C1: C4 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0xF0); int r=g_cpu.Y-m; g_cpu.C=(g_cpu.Y>=m)?1:0; FLAG_NZ(r&0xFF); }
label_82C3:;
    /* $82C3: C2 */ maybe_trigger_vblank(2); /* NOP */
label_82C5:;
    /* $82C5: C2 */ maybe_trigger_vblank(2); /* NOP */
label_82C7:;
    /* $82C7: C2 */ maybe_trigger_vblank(2); /* NOP */
label_82C9:; /* ResetTitle */
    /* $82C9: C2 */ maybe_trigger_vblank(2); /* NOP */
label_82CB:;
    /* $82CB: C7 */ maybe_trigger_vblank(5); { uint16_t a=0x12; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); g_cpu.C=(g_cpu.A>=v)?1:0; FLAG_NZ((uint8_t)(g_cpu.A-v)); }
label_82CD:;
    /* $82CD: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_82CE:;
    /* $82CE: 3F */ maybe_trigger_vblank(7); { uint16_t a=(0x45C8 + g_cpu.X) & 0xFFFF; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); g_cpu.A&=v; FLAG_NZ(g_cpu.A); }
label_82D1:;
    /* $82D1: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_82D2:;
    /* $82D2: 0B */ maybe_trigger_vblank(2); g_cpu.A &= 0xC8; FLAG_NZ(g_cpu.A); g_cpu.C=(g_cpu.A>>7)&1;
label_82D4:;
    /* $82D4: 03 */ maybe_trigger_vblank(8); { uint16_t a=nes_read16zp((0xC8 + g_cpu.X) & 0xFF); uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); g_cpu.A|=v; FLAG_NZ(g_cpu.A); }
label_82D6:;
    /* $82D6: 0B */ maybe_trigger_vblank(2); g_cpu.A &= 0xC8; FLAG_NZ(g_cpu.A); g_cpu.C=(g_cpu.A>>7)&1;
label_82D8:; /* ChkContinue */
    /* $82D8: 4B */ maybe_trigger_vblank(2); g_cpu.A &= 0xC8; g_cpu.C=g_cpu.A&1; g_cpu.A>>=1; FLAG_NZ(g_cpu.A);
label_82DA:;
    /* $82DA: 57 */ maybe_trigger_vblank(6); { uint16_t a=(0xC8 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); g_cpu.A^=v; FLAG_NZ(g_cpu.A); }
label_82DC:;
    /* $82DC: 49 */ maybe_trigger_vblank(2); g_cpu.A ^= 0xC5; FLAG_NZ(g_cpu.A);
label_82DE:;
    /* $82DE: 60 */ maybe_trigger_vblank(6); 
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
    return;
}

void func_828A_b1(void) {
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_828A_b1");
#endif
label_828A:;
    /* $828A: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) { maybe_trigger_vblank(1); call_by_address(0x824E); return; }
label_828C:;
    /* $828C: 28 */ maybe_trigger_vblank(4); { g_cpu.S++; uint8_t p = g_ram[0x100 + g_cpu.S];
  g_cpu.N=(p>>7)&1; g_cpu.V=(p>>6)&1; g_cpu.D=(p>>3)&1;
  g_cpu.I=(p>>2)&1; g_cpu.Z=(p>>1)&1; g_cpu.C=p&1; }
label_828D:;
    /* $828D: C3 */ maybe_trigger_vblank(8); { uint16_t a=nes_read16zp((0xF1 + g_cpu.X) & 0xFF); uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); g_cpu.C=(g_cpu.A>=v)?1:0; FLAG_NZ((uint8_t)(g_cpu.A-v)); }
label_828F:;
    /* $828F: C2 */ maybe_trigger_vblank(2); /* NOP */
label_8291:;
    /* $8291: C3 */ maybe_trigger_vblank(8); { uint16_t a=nes_read16zp((0x6B + g_cpu.X) & 0xFF); uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); g_cpu.C=(g_cpu.A>=v)?1:0; FLAG_NZ((uint8_t)(g_cpu.A-v)); }
label_8293:;
    /* $8293: C3 */ maybe_trigger_vblank(8); { uint16_t a=nes_read16zp((0xF0 + g_cpu.X) & 0xFF); uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); g_cpu.C=(g_cpu.A>=v)?1:0; FLAG_NZ((uint8_t)(g_cpu.A-v)); }
label_8295:;
    /* $8295: C2 */ maybe_trigger_vblank(2); /* NOP */
label_8297:;
    /* $8297: C3 */ maybe_trigger_vblank(8); { uint16_t a=nes_read16zp((0x75 + g_cpu.X) & 0xFF); uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); g_cpu.C=(g_cpu.A>=v)?1:0; FLAG_NZ((uint8_t)(g_cpu.A-v)); }
label_8299:;
    /* $8299: C3 */ maybe_trigger_vblank(8); { uint16_t a=nes_read16zp((0xF7 + g_cpu.X) & 0xFF); uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); g_cpu.C=(g_cpu.A>=v)?1:0; FLAG_NZ((uint8_t)(g_cpu.A-v)); }
label_829B:;
    /* $829B: C2 */ maybe_trigger_vblank(2); /* NOP */
label_829D:;
    /* $829D: C7 */ maybe_trigger_vblank(5); { uint16_t a=0xD1; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); g_cpu.C=(g_cpu.A>=v)?1:0; FLAG_NZ((uint8_t)(g_cpu.A-v)); }
label_829F:;
    /* $829F: C7 */ maybe_trigger_vblank(5); { uint16_t a=0x4A; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); g_cpu.C=(g_cpu.A>=v)?1:0; FLAG_NZ((uint8_t)(g_cpu.A-v)); }
label_82A1:;
    /* $82A1: C3 */ maybe_trigger_vblank(8); { uint16_t a=nes_read16zp((0x3D + g_cpu.X) & 0xFF); uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); g_cpu.C=(g_cpu.A>=v)?1:0; FLAG_NZ((uint8_t)(g_cpu.A-v)); }
label_82A3:;
    /* $82A3: C3 */ maybe_trigger_vblank(8); { uint16_t a=nes_read16zp((0x85 + g_cpu.X) & 0xFF); uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); g_cpu.C=(g_cpu.A>=v)?1:0; FLAG_NZ((uint8_t)(g_cpu.A-v)); }
label_82A5:;
    /* $82A5: C3 */ maybe_trigger_vblank(8); { uint16_t a=nes_read16zp((0xA0 + g_cpu.X) & 0xFF); uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); g_cpu.C=(g_cpu.A>=v)?1:0; FLAG_NZ((uint8_t)(g_cpu.A-v)); }
label_82A7:;
    /* $82A7: C7 */ maybe_trigger_vblank(5); { uint16_t a=0xF0; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); g_cpu.C=(g_cpu.A>=v)?1:0; FLAG_NZ((uint8_t)(g_cpu.A-v)); }
label_82A9:; /* UpdateShroom */
    /* $82A9: C2 */ maybe_trigger_vblank(2); /* NOP */
label_82AB:;
    /* $82AB: C7 */ maybe_trigger_vblank(5); { uint16_t a=0xA0; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); g_cpu.C=(g_cpu.A>=v)?1:0; FLAG_NZ((uint8_t)(g_cpu.A-v)); }
label_82AD:;
    /* $82AD: C7 */ maybe_trigger_vblank(5); { uint16_t a=0xA0; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); g_cpu.C=(g_cpu.A>=v)?1:0; FLAG_NZ((uint8_t)(g_cpu.A-v)); }
label_82AF:;
    /* $82AF: C7 */ maybe_trigger_vblank(5); { uint16_t a=0xA0; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); g_cpu.C=(g_cpu.A>=v)?1:0; FLAG_NZ((uint8_t)(g_cpu.A-v)); }
label_82B1:;
    /* $82B1: C7 */ maybe_trigger_vblank(5); { uint16_t a=0xB8; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); g_cpu.C=(g_cpu.A>=v)?1:0; FLAG_NZ((uint8_t)(g_cpu.A-v)); }
label_82B3:;
    /* $82B3: C7 */ maybe_trigger_vblank(5); { uint16_t a=0xF0; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); g_cpu.C=(g_cpu.A>=v)?1:0; FLAG_NZ((uint8_t)(g_cpu.A-v)); }
label_82B5:;
    /* $82B5: C2 */ maybe_trigger_vblank(2); /* NOP */
label_82B7:;
    /* $82B7: C2 */ maybe_trigger_vblank(2); /* NOP */
label_82B9:;
    /* $82B9: C4 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x5C); int r=g_cpu.Y-m; g_cpu.C=(g_cpu.Y>=m)?1:0; FLAG_NZ(r&0xFF); }
label_82BB:; /* NullJoypad */
    /* $82BB: C4 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x5C); int r=g_cpu.Y-m; g_cpu.C=(g_cpu.Y>=m)?1:0; FLAG_NZ(r&0xFF); }
label_82BD:;
    /* $82BD: C4 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x5C); int r=g_cpu.Y-m; g_cpu.C=(g_cpu.Y>=m)?1:0; FLAG_NZ(r&0xFF); }
label_82BF:;
    /* $82BF: C4 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x59); int r=g_cpu.Y-m; g_cpu.C=(g_cpu.Y>=m)?1:0; FLAG_NZ(r&0xFF); }
label_82C1:;
    /* $82C1: C4 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0xF0); int r=g_cpu.Y-m; g_cpu.C=(g_cpu.Y>=m)?1:0; FLAG_NZ(r&0xFF); }
label_82C3:;
    /* $82C3: C2 */ maybe_trigger_vblank(2); /* NOP */
label_82C5:;
    /* $82C5: C2 */ maybe_trigger_vblank(2); /* NOP */
label_82C7:;
    /* $82C7: C2 */ maybe_trigger_vblank(2); /* NOP */
label_82C9:; /* ResetTitle */
    /* $82C9: C2 */ maybe_trigger_vblank(2); /* NOP */
label_82CB:;
    /* $82CB: C7 */ maybe_trigger_vblank(5); { uint16_t a=0x12; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); g_cpu.C=(g_cpu.A>=v)?1:0; FLAG_NZ((uint8_t)(g_cpu.A-v)); }
label_82CD:;
    /* $82CD: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_82CE:;
    /* $82CE: 3F */ maybe_trigger_vblank(7); { uint16_t a=(0x45C8 + g_cpu.X) & 0xFFFF; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); g_cpu.A&=v; FLAG_NZ(g_cpu.A); }
label_82D1:;
    /* $82D1: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_82D2:;
    /* $82D2: 0B */ maybe_trigger_vblank(2); g_cpu.A &= 0xC8; FLAG_NZ(g_cpu.A); g_cpu.C=(g_cpu.A>>7)&1;
label_82D4:;
    /* $82D4: 03 */ maybe_trigger_vblank(8); { uint16_t a=nes_read16zp((0xC8 + g_cpu.X) & 0xFF); uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); g_cpu.A|=v; FLAG_NZ(g_cpu.A); }
label_82D6:;
    /* $82D6: 0B */ maybe_trigger_vblank(2); g_cpu.A &= 0xC8; FLAG_NZ(g_cpu.A); g_cpu.C=(g_cpu.A>>7)&1;
label_82D8:; /* ChkContinue */
    /* $82D8: 4B */ maybe_trigger_vblank(2); g_cpu.A &= 0xC8; g_cpu.C=g_cpu.A&1; g_cpu.A>>=1; FLAG_NZ(g_cpu.A);
label_82DA:;
    /* $82DA: 57 */ maybe_trigger_vblank(6); { uint16_t a=(0xC8 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); g_cpu.A^=v; FLAG_NZ(g_cpu.A); }
label_82DC:;
    /* $82DC: 49 */ maybe_trigger_vblank(2); g_cpu.A ^= 0xC5; FLAG_NZ(g_cpu.A);
label_82DE:;
    /* $82DE: 60 */ maybe_trigger_vblank(6); 
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
    return;
}

void func_828C_b1_body(int _entry) {
    switch (_entry) {
        case 1: goto label_82BD;
    }
label_828C:;
    /* $828C: 28 */ maybe_trigger_vblank(4); { g_cpu.S++; uint8_t p = g_ram[0x100 + g_cpu.S];
  g_cpu.N=(p>>7)&1; g_cpu.V=(p>>6)&1; g_cpu.D=(p>>3)&1;
  g_cpu.I=(p>>2)&1; g_cpu.Z=(p>>1)&1; g_cpu.C=p&1; }
label_828D:;
    /* $828D: C3 */ maybe_trigger_vblank(8); { uint16_t a=nes_read16zp((0xF1 + g_cpu.X) & 0xFF); uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); g_cpu.C=(g_cpu.A>=v)?1:0; FLAG_NZ((uint8_t)(g_cpu.A-v)); }
label_828F:;
    /* $828F: C2 */ maybe_trigger_vblank(2); /* NOP */
label_8291:;
    /* $8291: C3 */ maybe_trigger_vblank(8); { uint16_t a=nes_read16zp((0x6B + g_cpu.X) & 0xFF); uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); g_cpu.C=(g_cpu.A>=v)?1:0; FLAG_NZ((uint8_t)(g_cpu.A-v)); }
label_8293:;
    /* $8293: C3 */ maybe_trigger_vblank(8); { uint16_t a=nes_read16zp((0xF0 + g_cpu.X) & 0xFF); uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); g_cpu.C=(g_cpu.A>=v)?1:0; FLAG_NZ((uint8_t)(g_cpu.A-v)); }
label_8295:;
    /* $8295: C2 */ maybe_trigger_vblank(2); /* NOP */
label_8297:;
    /* $8297: C3 */ maybe_trigger_vblank(8); { uint16_t a=nes_read16zp((0x75 + g_cpu.X) & 0xFF); uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); g_cpu.C=(g_cpu.A>=v)?1:0; FLAG_NZ((uint8_t)(g_cpu.A-v)); }
label_8299:;
    /* $8299: C3 */ maybe_trigger_vblank(8); { uint16_t a=nes_read16zp((0xF7 + g_cpu.X) & 0xFF); uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); g_cpu.C=(g_cpu.A>=v)?1:0; FLAG_NZ((uint8_t)(g_cpu.A-v)); }
label_829B:;
    /* $829B: C2 */ maybe_trigger_vblank(2); /* NOP */
label_829D:;
    /* $829D: C7 */ maybe_trigger_vblank(5); { uint16_t a=0xD1; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); g_cpu.C=(g_cpu.A>=v)?1:0; FLAG_NZ((uint8_t)(g_cpu.A-v)); }
label_829F:;
    /* $829F: C7 */ maybe_trigger_vblank(5); { uint16_t a=0x4A; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); g_cpu.C=(g_cpu.A>=v)?1:0; FLAG_NZ((uint8_t)(g_cpu.A-v)); }
label_82A1:;
    /* $82A1: C3 */ maybe_trigger_vblank(8); { uint16_t a=nes_read16zp((0x3D + g_cpu.X) & 0xFF); uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); g_cpu.C=(g_cpu.A>=v)?1:0; FLAG_NZ((uint8_t)(g_cpu.A-v)); }
label_82A3:;
    /* $82A3: C3 */ maybe_trigger_vblank(8); { uint16_t a=nes_read16zp((0x85 + g_cpu.X) & 0xFF); uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); g_cpu.C=(g_cpu.A>=v)?1:0; FLAG_NZ((uint8_t)(g_cpu.A-v)); }
label_82A5:;
    /* $82A5: C3 */ maybe_trigger_vblank(8); { uint16_t a=nes_read16zp((0xA0 + g_cpu.X) & 0xFF); uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); g_cpu.C=(g_cpu.A>=v)?1:0; FLAG_NZ((uint8_t)(g_cpu.A-v)); }
label_82A7:;
    /* $82A7: C7 */ maybe_trigger_vblank(5); { uint16_t a=0xF0; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); g_cpu.C=(g_cpu.A>=v)?1:0; FLAG_NZ((uint8_t)(g_cpu.A-v)); }
label_82A9:; /* UpdateShroom */
    /* $82A9: C2 */ maybe_trigger_vblank(2); /* NOP */
label_82AB:;
    /* $82AB: C7 */ maybe_trigger_vblank(5); { uint16_t a=0xA0; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); g_cpu.C=(g_cpu.A>=v)?1:0; FLAG_NZ((uint8_t)(g_cpu.A-v)); }
label_82AD:;
    /* $82AD: C7 */ maybe_trigger_vblank(5); { uint16_t a=0xA0; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); g_cpu.C=(g_cpu.A>=v)?1:0; FLAG_NZ((uint8_t)(g_cpu.A-v)); }
label_82AF:;
    /* $82AF: C7 */ maybe_trigger_vblank(5); { uint16_t a=0xA0; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); g_cpu.C=(g_cpu.A>=v)?1:0; FLAG_NZ((uint8_t)(g_cpu.A-v)); }
label_82B1:;
    /* $82B1: C7 */ maybe_trigger_vblank(5); { uint16_t a=0xB8; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); g_cpu.C=(g_cpu.A>=v)?1:0; FLAG_NZ((uint8_t)(g_cpu.A-v)); }
label_82B3:;
    /* $82B3: C7 */ maybe_trigger_vblank(5); { uint16_t a=0xF0; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); g_cpu.C=(g_cpu.A>=v)?1:0; FLAG_NZ((uint8_t)(g_cpu.A-v)); }
label_82B5:;
    /* $82B5: C2 */ maybe_trigger_vblank(2); /* NOP */
label_82B7:;
    /* $82B7: C2 */ maybe_trigger_vblank(2); /* NOP */
label_82B9:;
    /* $82B9: C4 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x5C); int r=g_cpu.Y-m; g_cpu.C=(g_cpu.Y>=m)?1:0; FLAG_NZ(r&0xFF); }
label_82BB:; /* NullJoypad */
    /* $82BB: C4 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x5C); int r=g_cpu.Y-m; g_cpu.C=(g_cpu.Y>=m)?1:0; FLAG_NZ(r&0xFF); }
label_82BD:;
    /* $82BD: C4 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x5C); int r=g_cpu.Y-m; g_cpu.C=(g_cpu.Y>=m)?1:0; FLAG_NZ(r&0xFF); }
label_82BF:;
    /* $82BF: C4 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x59); int r=g_cpu.Y-m; g_cpu.C=(g_cpu.Y>=m)?1:0; FLAG_NZ(r&0xFF); }
label_82C1:;
    /* $82C1: C4 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0xF0); int r=g_cpu.Y-m; g_cpu.C=(g_cpu.Y>=m)?1:0; FLAG_NZ(r&0xFF); }
label_82C3:;
    /* $82C3: C2 */ maybe_trigger_vblank(2); /* NOP */
label_82C5:;
    /* $82C5: C2 */ maybe_trigger_vblank(2); /* NOP */
label_82C7:;
    /* $82C7: C2 */ maybe_trigger_vblank(2); /* NOP */
label_82C9:; /* ResetTitle */
    /* $82C9: C2 */ maybe_trigger_vblank(2); /* NOP */
label_82CB:;
    /* $82CB: C7 */ maybe_trigger_vblank(5); { uint16_t a=0x12; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); g_cpu.C=(g_cpu.A>=v)?1:0; FLAG_NZ((uint8_t)(g_cpu.A-v)); }
label_82CD:;
    /* $82CD: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_82CE:;
    /* $82CE: 3F */ maybe_trigger_vblank(7); { uint16_t a=(0x45C8 + g_cpu.X) & 0xFFFF; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); g_cpu.A&=v; FLAG_NZ(g_cpu.A); }
label_82D1:;
    /* $82D1: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_82D2:;
    /* $82D2: 0B */ maybe_trigger_vblank(2); g_cpu.A &= 0xC8; FLAG_NZ(g_cpu.A); g_cpu.C=(g_cpu.A>>7)&1;
label_82D4:;
    /* $82D4: 03 */ maybe_trigger_vblank(8); { uint16_t a=nes_read16zp((0xC8 + g_cpu.X) & 0xFF); uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); g_cpu.A|=v; FLAG_NZ(g_cpu.A); }
label_82D6:;
    /* $82D6: 0B */ maybe_trigger_vblank(2); g_cpu.A &= 0xC8; FLAG_NZ(g_cpu.A); g_cpu.C=(g_cpu.A>>7)&1;
label_82D8:; /* ChkContinue */
    /* $82D8: 4B */ maybe_trigger_vblank(2); g_cpu.A &= 0xC8; g_cpu.C=g_cpu.A&1; g_cpu.A>>=1; FLAG_NZ(g_cpu.A);
label_82DA:;
    /* $82DA: 57 */ maybe_trigger_vblank(6); { uint16_t a=(0xC8 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); g_cpu.A^=v; FLAG_NZ(g_cpu.A); }
label_82DC:;
    /* $82DC: 49 */ maybe_trigger_vblank(2); g_cpu.A ^= 0xC5; FLAG_NZ(g_cpu.A);
label_82DE:;
    /* $82DE: 60 */ maybe_trigger_vblank(6); 
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
    return;
}

void func_828C_b1(void) {
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_828C_b1");
#endif
    func_828C_b1_body(0);
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
}

void func_82BD_b1(void) {
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_82BD_b1");
#endif
    func_828C_b1_body(1);
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
}

void func_8752_b1_body(int _entry) { /* TopStatusBarLine */
    switch (_entry) {
        case 1: goto label_8759;
    }
label_8752:; /* TopStatusBarLine */
    /* $8752: E8 */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X+1)&0xFF; FLAG_NZ(g_cpu.X);
label_8753:;
    /* $8753: E0 */ maybe_trigger_vblank(2); { int r=g_cpu.X-0x05; g_cpu.C=(g_cpu.X>=0x05)?1:0; FLAG_NZ(r&0xFF); }
label_8755:;
    /* $8755: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_8784; }
label_8757:;
    /* $8757: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0F + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_8759:;
    /* $8759: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) {
    maybe_trigger_vblank(1);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_8752;
    }
label_875B:;
    /* $875B: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x01); FLAG_NZ(g_cpu.A);
label_875D:;
    /* $875D: 95 */ maybe_trigger_vblank(4); nes_write((0x16 + g_cpu.X) & 0xFF, g_cpu.A);
label_875F:;
    /* $875F: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x02); FLAG_NZ(g_cpu.A);
label_8761:;
    /* $8761: 95 */ maybe_trigger_vblank(4); nes_write((0x6E + g_cpu.X) & 0xFF, g_cpu.A);
label_8763:;
    /* $8763: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x03); FLAG_NZ(g_cpu.A);
label_8765:;
    /* $8765: 95 */ maybe_trigger_vblank(4); nes_write((0x87 + g_cpu.X) & 0xFF, g_cpu.A);
label_8767:;
    /* $8767: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_8768:;
    /* $8768: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x18 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x18); g_cpu.A=r&0xFF; }
label_876A:;
    /* $876A: 85 */ maybe_trigger_vblank(3); nes_write(0x03, g_cpu.A);
label_876C:;
    /* $876C: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x02); FLAG_NZ(g_cpu.A);
label_876E:;
    /* $876E: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x00 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x00); g_cpu.A=r&0xFF; }
label_8770:;
    /* $8770: 85 */ maybe_trigger_vblank(3); nes_write(0x02, g_cpu.A);
label_8772:;
    /* $8772: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x00); FLAG_NZ(g_cpu.A);
label_8774:;
    /* $8774: 95 */ maybe_trigger_vblank(4); nes_write((0xCF + g_cpu.X) & 0xFF, g_cpu.A);
label_8776:;
    /* $8776: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x01; FLAG_NZ(g_cpu.A);
label_8778:;
    /* $8778: 95 */ maybe_trigger_vblank(4); nes_write((0xB6 + g_cpu.X) & 0xFF, g_cpu.A);
label_877A:;
    /* $877A: 95 */ maybe_trigger_vblank(4); nes_write((0x0F + g_cpu.X) & 0xFF, g_cpu.A);
label_877C:;
    /* $877C: 20 */ maybe_trigger_vblank(6); func_C26C();
label_877F:;
    /* $877F: CE */ maybe_trigger_vblank(6); { uint16_t a=0x06D3; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_8782:;
    /* $8782: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); call_by_address(0x8750); return; }
label_8784:;
    /* $8784: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); func_C25E(); return;
}

void func_8752_b1(void) { /* TopStatusBarLine */
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_8752_b1");
#endif
    func_8752_b1_body(0);
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
}

void func_8759_b1(void) {
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_8759_b1");
#endif
    func_8752_b1_body(1);
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
}

void func_8750_b1(void) {
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_8750_b1");
#endif
label_8750:;
    /* $8750: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0xFF; FLAG_NZ(g_cpu.X);
label_8752:; /* TopStatusBarLine */
    /* $8752: E8 */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X+1)&0xFF; FLAG_NZ(g_cpu.X);
label_8753:;
    /* $8753: E0 */ maybe_trigger_vblank(2); { int r=g_cpu.X-0x05; g_cpu.C=(g_cpu.X>=0x05)?1:0; FLAG_NZ(r&0xFF); }
label_8755:;
    /* $8755: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_8784; }
label_8757:;
    /* $8757: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0F + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_8759:;
    /* $8759: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) {
    maybe_trigger_vblank(1);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_8752;
    }
label_875B:;
    /* $875B: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x01); FLAG_NZ(g_cpu.A);
label_875D:;
    /* $875D: 95 */ maybe_trigger_vblank(4); nes_write((0x16 + g_cpu.X) & 0xFF, g_cpu.A);
label_875F:;
    /* $875F: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x02); FLAG_NZ(g_cpu.A);
label_8761:;
    /* $8761: 95 */ maybe_trigger_vblank(4); nes_write((0x6E + g_cpu.X) & 0xFF, g_cpu.A);
label_8763:;
    /* $8763: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x03); FLAG_NZ(g_cpu.A);
label_8765:;
    /* $8765: 95 */ maybe_trigger_vblank(4); nes_write((0x87 + g_cpu.X) & 0xFF, g_cpu.A);
label_8767:;
    /* $8767: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_8768:;
    /* $8768: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x18 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x18); g_cpu.A=r&0xFF; }
label_876A:;
    /* $876A: 85 */ maybe_trigger_vblank(3); nes_write(0x03, g_cpu.A);
label_876C:;
    /* $876C: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x02); FLAG_NZ(g_cpu.A);
label_876E:;
    /* $876E: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x00 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x00); g_cpu.A=r&0xFF; }
label_8770:;
    /* $8770: 85 */ maybe_trigger_vblank(3); nes_write(0x02, g_cpu.A);
label_8772:;
    /* $8772: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x00); FLAG_NZ(g_cpu.A);
label_8774:;
    /* $8774: 95 */ maybe_trigger_vblank(4); nes_write((0xCF + g_cpu.X) & 0xFF, g_cpu.A);
label_8776:;
    /* $8776: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x01; FLAG_NZ(g_cpu.A);
label_8778:;
    /* $8778: 95 */ maybe_trigger_vblank(4); nes_write((0xB6 + g_cpu.X) & 0xFF, g_cpu.A);
label_877A:;
    /* $877A: 95 */ maybe_trigger_vblank(4); nes_write((0x0F + g_cpu.X) & 0xFF, g_cpu.A);
label_877C:;
    /* $877C: 20 */ maybe_trigger_vblank(6); func_C26C();
label_877F:;
    /* $877F: CE */ maybe_trigger_vblank(6); { uint16_t a=0x06D3; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_8782:;
    /* $8782: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) {
    maybe_trigger_vblank(1);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_8750;
    }
label_8784:;
    /* $8784: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); func_C25E(); return;
}

void func_9A24_b1(void) {
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_9A24_b1");
#endif
label_9A24:;
    /* $9A24: 60 */ maybe_trigger_vblank(6); 
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
    return;
}

void func_9A56_b1_body(int _entry) {
    switch (_entry) {
        case 1: goto label_9A5C;
    }
label_9A56:;
    /* $9A56: 86 */ maybe_trigger_vblank(3); nes_write(0x01, g_cpu.X);
label_9A58:;
    /* $9A58: 98 */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.Y; FLAG_NZ(g_cpu.A);
label_9A59:; /* ColumnOfSolidBlocks */
    /* $9A59: 48 */ maybe_trigger_vblank(3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_9A5A:;
    /* $9A5A: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0F + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_9A5C:;
    /* $9A5C: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_9AAA; }
label_9A5E:;
    /* $9A5E: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x16 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_9A60:;
    /* $9A60: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x15; g_cpu.C=(g_cpu.A>=0x15)?1:0; FLAG_NZ(r&0xFF); }
label_9A62:;
    /* $9A62: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_9AAA; }
label_9A64:;
    /* $9A64: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x11; g_cpu.C=(g_cpu.A>=0x11)?1:0; FLAG_NZ(r&0xFF); }
label_9A66:;
    /* $9A66: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_9AAA; }
label_9A68:;
    /* $9A68: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x0D; g_cpu.C=(g_cpu.A>=0x0D)?1:0; FLAG_NZ(r&0xFF); }
label_9A6A:;
    /* $9A6A: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_9AAA; }
label_9A6C:;
    /* $9A6C: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x03D8 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_9A6F:;
    /* $9A6F: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_9AAA; }
label_9A71:;
    /* $9A71: 8A */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.X; FLAG_NZ(g_cpu.A);
label_9A72:;
    /* $9A72: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_9A73:;
    /* $9A73: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_9A74:;
    /* $9A74: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_9A75:;
    /* $9A75: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x04 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x04); g_cpu.A=r&0xFF; }
label_9A77:;
    /* $9A77: AA */ maybe_trigger_vblank(2); g_cpu.X = g_cpu.A; FLAG_NZ(g_cpu.X);
label_9A78:;
    /* $9A78: 20 */ maybe_trigger_vblank(6); func_E327();
label_9A7B:;
    /* $9A7B: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x08); FLAG_NZ(g_cpu.X);
label_9A7D:;
    /* $9A7D: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0x01); FLAG_NZ(g_cpu.Y);
label_9A7F:;
    /* $9A7F: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) { maybe_trigger_vblank(1); goto label_9AA1; }
label_9A81:;
    /* $9A81: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x1E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_9A83:;
    /* $9A83: 19 */ maybe_trigger_vblank(4); g_cpu.A |= nes_read((0x001E + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_9A86:;
    /* $9A86: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x80; FLAG_NZ(g_cpu.A);
label_9A88:;
    /* $9A88: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_9A9B; }
label_9A8A:;
    /* $9A8A: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0491 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_9A8D:;
    /* $9A8D: 3D */ maybe_trigger_vblank(4); g_cpu.A &= nes_read((0xDA25 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_9A90:;
    /* $9A90: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_9AAA; }
label_9A92:;
    /* $9A92: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0491 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_9A95:;
    /* $9A95: 1D */ maybe_trigger_vblank(4); g_cpu.A |= nes_read((0xDA25 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_9A98:;
    /* $9A98: 99 */ maybe_trigger_vblank(5); nes_write((0x0491 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_9A9B:;
    /* $9A9B: 20 */ maybe_trigger_vblank(6); func_DAB4();
label_9A9E:;
    /* $9A9E: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); func_DAAA(); return;
label_9AA1:; /* StrCOffset */
    /* $9AA1: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0491 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_9AA4:;
    /* $9AA4: 3D */ maybe_trigger_vblank(4); g_cpu.A &= nes_read((0xDA2C + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_9AA7:;
    /* $9AA7: 99 */ maybe_trigger_vblank(5); nes_write((0x0491 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_9AAA:;
    /* $9AAA: 68 */ maybe_trigger_vblank(4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_9AAB:;
    /* $9AAB: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_9AAC:;
    /* $9AAC: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x01); FLAG_NZ(g_cpu.X);
label_9AAE:; /* StaircaseRowData */
    /* $9AAE: CA */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X-1)&0xFF; FLAG_NZ(g_cpu.X);
label_9AAF:;
    /* $9AAF: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) {
    maybe_trigger_vblank(1);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_9A56;
    }
label_9AB1:;
    /* $9AB1: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x08); FLAG_NZ(g_cpu.X);
label_9AB3:;
    /* $9AB3: 60 */ maybe_trigger_vblank(6); 
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
    return;
}

void func_9A56_b1(void) {
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_9A56_b1");
#endif
    func_9A56_b1_body(0);
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
}

void func_9A5C_b1(void) {
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_9A5C_b1");
#endif
    func_9A56_b1_body(1);
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
}

void func_B3BF_b1(void) {
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_B3BF_b1");
#endif
label_B3BF:;
    /* $B3BF: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x40; FLAG_NZ(g_cpu.A);
label_B3C1:;
    /* $B3C1: 8D */ maybe_trigger_vblank(4); nes_write(0x07BB, g_cpu.A);
label_B3C4:; /* ExitMov1 */
    /* $B3C4: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x62; FLAG_NZ(g_cpu.A);
label_B3C6:;
    /* $B3C6: 20 */ maybe_trigger_vblank(6); func_F38B();
label_B3C9:;
    /* $B3C9: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x99; FLAG_NZ(g_cpu.X);
label_B3CB:; /* ClimbAdderHigh */
    /* $B3CB: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B3F2; }
label_B3CD:;
    /* $B3CD: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x26; FLAG_NZ(g_cpu.A);
label_B3CF:; /* ClimbingSub */
    /* $B3CF: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B3D3; }
label_B3D1:;
    /* $B3D1: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x18; FLAG_NZ(g_cpu.A);
label_B3D3:;
    /* $B3D3: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x82; FLAG_NZ(g_cpu.X);
label_B3D5:;
    /* $B3D5: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0xA7; FLAG_NZ(g_cpu.Y);
label_B3D7:;
    /* $B3D7: 20 */ maybe_trigger_vblank(6); func_F388();
label_B3DA:;
    /* $B3DA: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x28; FLAG_NZ(g_cpu.A);
label_B3DC:;
    /* $B3DC: 8D */ maybe_trigger_vblank(4); nes_write(0x07BB, g_cpu.A);
label_B3DF:;
    /* $B3DF: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07BB); FLAG_NZ(g_cpu.A);
label_B3E2:;
    /* $B3E2: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x25; g_cpu.C=(g_cpu.A>=0x25)?1:0; FLAG_NZ(r&0xFF); }
label_B3E4:;
    /* $B3E4: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B3EC; }
label_B3E6:;
    /* $B3E6: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x5F; FLAG_NZ(g_cpu.X);
label_B3E8:;
    /* $B3E8: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0xF6; FLAG_NZ(g_cpu.Y);
label_B3EA:;
    /* $B3EA: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B3F4; }
label_B3EC:;
    /* $B3EC: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x20; g_cpu.C=(g_cpu.A>=0x20)?1:0; FLAG_NZ(r&0xFF); }
label_B3EE:;
    /* $B3EE: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(2); goto label_B419; }
label_B3F0:;
    /* $B3F0: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x48; FLAG_NZ(g_cpu.X);
label_B3F2:;
    /* $B3F2: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0xBC; FLAG_NZ(g_cpu.Y);
label_B3F4:;
    /* $B3F4: 20 */ maybe_trigger_vblank(6); func_F381();
label_B3F7:;
    /* $B3F7: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(2); goto label_B419; }
label_B3F9:;
    /* $B3F9: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x05; FLAG_NZ(g_cpu.A);
label_B3FB:;
    /* $B3FB: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x99; FLAG_NZ(g_cpu.Y);
label_B3FD:;
    /* $B3FD: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(2); goto label_B403; }
label_B3FF:;
    /* $B3FF: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x0A; FLAG_NZ(g_cpu.A);
label_B401:;
    /* $B401: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x93; FLAG_NZ(g_cpu.Y);
label_B403:;
    /* $B403: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x9E; FLAG_NZ(g_cpu.X);
label_B405:;
    /* $B405: 8D */ maybe_trigger_vblank(4); nes_write(0x07BB, g_cpu.A);
label_B408:;
    /* $B408: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x0C; FLAG_NZ(g_cpu.A);
label_B40A:; /* CSetFDir */
    /* $B40A: 20 */ maybe_trigger_vblank(6); func_F388();
label_B40D:;
    /* $B40D: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07BB); FLAG_NZ(g_cpu.A);
label_B410:;
    /* $B410: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x06; g_cpu.C=(g_cpu.A>=0x06)?1:0; FLAG_NZ(r&0xFF); }
label_B412:;
    /* $B412: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B419; }
label_B414:;
    /* $B414: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xBB; FLAG_NZ(g_cpu.A);
label_B416:;
    /* $B416: 8D */ maybe_trigger_vblank(4); nes_write(0x4001, g_cpu.A);
label_B419:;
    /* $B419: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B47B; }
label_B41B:;
    /* $B41B: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0xFF); FLAG_NZ(g_cpu.Y);
label_B41D:;
    /* $B41D: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_B43F; }
label_B41F:; /* ExitCSub */
    /* $B41F: 84 */ maybe_trigger_vblank(3); nes_write(0xF1, g_cpu.Y);
label_B421:;
    /* $B421: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_B3CD;
    }
label_B423:;
    /* $B423: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_B425:;
    /* $B425: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_B3D1;
    }
label_B427:;
    /* $B427: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_B429:;
    /* $B429: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_B3FF;
    }
label_B42B:; /* FallMForceData */
    /* $B42B: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_B42D:;
    /* $B42D: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_B45B; }
label_B42F:;
    /* $B42F: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_B431:;
    /* $B431: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_B47D; }
label_B433:;
    /* $B433: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_B435:;
    /* $B435: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_B4B6; }
label_B437:;
    /* $B437: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_B439:; /* InitMForceData */
    /* $B439: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_B3F9;
    }
label_B43B:;
    /* $B43B: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_B43D:;
    /* $B43D: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_B3BF;
    }
label_B43F:;
    /* $B43F: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xF1); FLAG_NZ(g_cpu.A);
label_B441:;
    /* $B441: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_B45A; }
label_B443:; /* MaxRightXSpdData */
    /* $B443: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_B3DF;
    }
label_B445:;
    /* $B445: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B446:;
    /* $B446: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_B3DF;
    }
label_B448:;
    /* $B448: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B449:;
    /* $B449: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) {
    maybe_trigger_vblank(1);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_B40D;
    }
label_B44B:;
    /* $B44B: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B44C:;
    /* $B44C: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_B469; }
label_B44E:;
    /* $B44E: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B44F:;
    /* $B44F: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_B48D; }
label_B451:;
    /* $B451: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B452:;
    /* $B452: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_B4BB; }
label_B454:;
    /* $B454: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B455:;
    /* $B455: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) {
    maybe_trigger_vblank(1);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_B40D;
    }
label_B457:;
    /* $B457: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B458:;
    /* $B458: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_B4A2; }
label_B45A:;
    /* $B45A: 60 */
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
    return; /* branch-target RTS */
label_B45B:;
    /* $B45B: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x0E; FLAG_NZ(g_cpu.A);
label_B45D:;
    /* $B45D: 8D */ maybe_trigger_vblank(4); nes_write(0x07BB, g_cpu.A);
label_B460:;
    /* $B460: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x9C; FLAG_NZ(g_cpu.Y);
label_B462:;
    /* $B462: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x9E; FLAG_NZ(g_cpu.X);
label_B464:;
    /* $B464: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x26; FLAG_NZ(g_cpu.A);
label_B466:;
    /* $B466: 20 */ maybe_trigger_vblank(6); func_F388();
label_B469:;
    /* $B469: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x07BB); FLAG_NZ(g_cpu.Y);
label_B46C:;
    /* $B46C: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xF3B0 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_B46F:;
    /* $B46F: 8D */ maybe_trigger_vblank(4); nes_write(0x4000, g_cpu.A);
label_B472:;
    /* $B472: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x06; g_cpu.C=(g_cpu.Y>=0x06)?1:0; FLAG_NZ(r&0xFF); }
label_B474:;
    /* $B474: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B47B; }
label_B476:;
    /* $B476: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x9E; FLAG_NZ(g_cpu.A);
label_B478:;
    /* $B478: 8D */ maybe_trigger_vblank(4); nes_write(0x4002, g_cpu.A);
label_B47B:;
    /* $B47B: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B4A2; }
label_B47D:;
    /* $B47D: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x0E; FLAG_NZ(g_cpu.A);
label_B47F:;
    /* $B47F: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0xCB; FLAG_NZ(g_cpu.Y);
label_B481:;
    /* $B481: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x9F; FLAG_NZ(g_cpu.X);
label_B483:;
    /* $B483: 8D */ maybe_trigger_vblank(4); nes_write(0x07BB, g_cpu.A);
label_B486:;
    /* $B486: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x28; FLAG_NZ(g_cpu.A);
label_B488:; /* NoJump */
    /* $B488: 20 */ maybe_trigger_vblank(6); func_F388();
label_B48B:; /* ProcJumping */
    /* $B48B: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B4A2; }
label_B48D:;
    /* $B48D: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x07BB); FLAG_NZ(g_cpu.Y);
label_B490:;
    /* $B490: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x08; g_cpu.C=(g_cpu.Y>=0x08)?1:0; FLAG_NZ(r&0xFF); }
label_B492:;
    /* $B492: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B49D; }
label_B494:;
    /* $B494: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xA0; FLAG_NZ(g_cpu.A);
label_B496:;
    /* $B496: 8D */ maybe_trigger_vblank(4); nes_write(0x4002, g_cpu.A);
label_B499:;
    /* $B499: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x9F; FLAG_NZ(g_cpu.A);
label_B49B:;
    /* $B49B: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B49F; }
label_B49D:;
    /* $B49D: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x90; FLAG_NZ(g_cpu.A);
label_B49F:;
    /* $B49F: 8D */ maybe_trigger_vblank(4); nes_write(0x4000, g_cpu.A);
label_B4A2:;
    /* $B4A2: CE */ maybe_trigger_vblank(6); { uint16_t a=0x07BB; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_B4A5:;
    /* $B4A5: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B4B5; }
label_B4A7:;
    /* $B4A7: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x00; FLAG_NZ(g_cpu.X);
label_B4A9:;
    /* $B4A9: 86 */ maybe_trigger_vblank(3); nes_write(0xF1, g_cpu.X);
label_B4AB:;
    /* $B4AB: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x0E; FLAG_NZ(g_cpu.X);
label_B4AD:;
    /* $B4AD: 8E */ maybe_trigger_vblank(4); nes_write(0x4015, g_cpu.X);
label_B4B0:;
    /* $B4B0: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x0F; FLAG_NZ(g_cpu.X);
label_B4B2:;
    /* $B4B2: 8E */ maybe_trigger_vblank(4); nes_write(0x4015, g_cpu.X);
label_B4B5:;
    /* $B4B5: 60 */ maybe_trigger_vblank(6); 
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
    return;
label_B4B6:;
    /* $B4B6: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x2F; FLAG_NZ(g_cpu.A);
label_B4B8:;
    /* $B4B8: 8D */ maybe_trigger_vblank(4); nes_write(0x07BB, g_cpu.A);
label_B4BB:;
    /* $B4BB: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07BB); FLAG_NZ(g_cpu.A);
label_B4BE:;
    /* $B4BE: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B4BF:;
    /* $B4BF: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_B4D1; }
label_B4C1:;
    /* $B4C1: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B4C2:;
    /* $B4C2: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_B4D1; }
label_B4C4:;
    /* $B4C4: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x02; FLAG_NZ(g_cpu.A);
label_B4C6:;
    /* $B4C6: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_B4D1; }
label_B4C8:;
    /* $B4C8: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x91; FLAG_NZ(g_cpu.Y);
label_B4CA:;
    /* $B4CA: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x9A; FLAG_NZ(g_cpu.X);
label_B4CC:;
    /* $B4CC: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x44; FLAG_NZ(g_cpu.A);
label_B4CE:;
    /* $B4CE: 20 */ maybe_trigger_vblank(6); func_F388();
label_B4D1:;
    /* $B4D1: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); func_F4A2(); return;
}

void func_B3DF_b1(void) {
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_B3DF_b1");
#endif
label_B3DF:;
    /* $B3DF: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07BB); FLAG_NZ(g_cpu.A);
label_B3E2:;
    /* $B3E2: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x25; g_cpu.C=(g_cpu.A>=0x25)?1:0; FLAG_NZ(r&0xFF); }
label_B3E4:;
    /* $B3E4: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B3EC; }
label_B3E6:;
    /* $B3E6: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x5F; FLAG_NZ(g_cpu.X);
label_B3E8:;
    /* $B3E8: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0xF6; FLAG_NZ(g_cpu.Y);
label_B3EA:;
    /* $B3EA: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B3F4; }
label_B3EC:;
    /* $B3EC: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x20; g_cpu.C=(g_cpu.A>=0x20)?1:0; FLAG_NZ(r&0xFF); }
label_B3EE:;
    /* $B3EE: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(2); goto label_B419; }
label_B3F0:;
    /* $B3F0: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x48; FLAG_NZ(g_cpu.X);
label_B3F2:;
    /* $B3F2: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0xBC; FLAG_NZ(g_cpu.Y);
label_B3F4:;
    /* $B3F4: 20 */ maybe_trigger_vblank(6); func_F381();
label_B3F7:;
    /* $B3F7: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(2); goto label_B419; }
label_B3F9:;
    /* $B3F9: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x05; FLAG_NZ(g_cpu.A);
label_B3FB:;
    /* $B3FB: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x99; FLAG_NZ(g_cpu.Y);
label_B3FD:;
    /* $B3FD: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(2); goto label_B403; }
label_B3FF:;
    /* $B3FF: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x0A; FLAG_NZ(g_cpu.A);
label_B401:;
    /* $B401: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x93; FLAG_NZ(g_cpu.Y);
label_B403:;
    /* $B403: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x9E; FLAG_NZ(g_cpu.X);
label_B405:;
    /* $B405: 8D */ maybe_trigger_vblank(4); nes_write(0x07BB, g_cpu.A);
label_B408:;
    /* $B408: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x0C; FLAG_NZ(g_cpu.A);
label_B40A:; /* CSetFDir */
    /* $B40A: 20 */ maybe_trigger_vblank(6); func_F388();
label_B40D:;
    /* $B40D: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07BB); FLAG_NZ(g_cpu.A);
label_B410:;
    /* $B410: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x06; g_cpu.C=(g_cpu.A>=0x06)?1:0; FLAG_NZ(r&0xFF); }
label_B412:;
    /* $B412: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B419; }
label_B414:;
    /* $B414: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xBB; FLAG_NZ(g_cpu.A);
label_B416:;
    /* $B416: 8D */ maybe_trigger_vblank(4); nes_write(0x4001, g_cpu.A);
label_B419:;
    /* $B419: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B47B; }
label_B41B:;
    /* $B41B: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0xFF); FLAG_NZ(g_cpu.Y);
label_B41D:;
    /* $B41D: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_B43F; }
label_B41F:; /* ExitCSub */
    /* $B41F: 84 */ maybe_trigger_vblank(3); nes_write(0xF1, g_cpu.Y);
label_B421:;
    /* $B421: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) { maybe_trigger_vblank(2); call_by_address(0xB3CD); return; }
label_B423:;
    /* $B423: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_B425:;
    /* $B425: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { maybe_trigger_vblank(2); call_by_address(0xB3D1); return; }
label_B427:;
    /* $B427: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_B429:;
    /* $B429: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_B3FF;
    }
label_B42B:; /* FallMForceData */
    /* $B42B: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_B42D:;
    /* $B42D: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_B45B; }
label_B42F:;
    /* $B42F: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_B431:;
    /* $B431: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_B47D; }
label_B433:;
    /* $B433: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_B435:;
    /* $B435: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_B4B6; }
label_B437:;
    /* $B437: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_B439:; /* InitMForceData */
    /* $B439: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_B3F9;
    }
label_B43B:;
    /* $B43B: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_B43D:;
    /* $B43D: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { maybe_trigger_vblank(2); call_by_address(0xB3BF); return; }
label_B43F:;
    /* $B43F: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xF1); FLAG_NZ(g_cpu.A);
label_B441:;
    /* $B441: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_B45A; }
label_B443:; /* MaxRightXSpdData */
    /* $B443: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_B3DF;
    }
label_B445:;
    /* $B445: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B446:;
    /* $B446: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_B3DF;
    }
label_B448:;
    /* $B448: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B449:;
    /* $B449: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) {
    maybe_trigger_vblank(1);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_B40D;
    }
label_B44B:;
    /* $B44B: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B44C:;
    /* $B44C: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_B469; }
label_B44E:;
    /* $B44E: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B44F:;
    /* $B44F: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_B48D; }
label_B451:;
    /* $B451: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B452:;
    /* $B452: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_B4BB; }
label_B454:;
    /* $B454: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B455:;
    /* $B455: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) {
    maybe_trigger_vblank(1);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_B40D;
    }
label_B457:;
    /* $B457: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B458:;
    /* $B458: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_B4A2; }
label_B45A:;
    /* $B45A: 60 */
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
    return; /* branch-target RTS */
label_B45B:;
    /* $B45B: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x0E; FLAG_NZ(g_cpu.A);
label_B45D:;
    /* $B45D: 8D */ maybe_trigger_vblank(4); nes_write(0x07BB, g_cpu.A);
label_B460:;
    /* $B460: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x9C; FLAG_NZ(g_cpu.Y);
label_B462:;
    /* $B462: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x9E; FLAG_NZ(g_cpu.X);
label_B464:;
    /* $B464: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x26; FLAG_NZ(g_cpu.A);
label_B466:;
    /* $B466: 20 */ maybe_trigger_vblank(6); func_F388();
label_B469:;
    /* $B469: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x07BB); FLAG_NZ(g_cpu.Y);
label_B46C:;
    /* $B46C: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xF3B0 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_B46F:;
    /* $B46F: 8D */ maybe_trigger_vblank(4); nes_write(0x4000, g_cpu.A);
label_B472:;
    /* $B472: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x06; g_cpu.C=(g_cpu.Y>=0x06)?1:0; FLAG_NZ(r&0xFF); }
label_B474:;
    /* $B474: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B47B; }
label_B476:;
    /* $B476: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x9E; FLAG_NZ(g_cpu.A);
label_B478:;
    /* $B478: 8D */ maybe_trigger_vblank(4); nes_write(0x4002, g_cpu.A);
label_B47B:;
    /* $B47B: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B4A2; }
label_B47D:;
    /* $B47D: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x0E; FLAG_NZ(g_cpu.A);
label_B47F:;
    /* $B47F: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0xCB; FLAG_NZ(g_cpu.Y);
label_B481:;
    /* $B481: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x9F; FLAG_NZ(g_cpu.X);
label_B483:;
    /* $B483: 8D */ maybe_trigger_vblank(4); nes_write(0x07BB, g_cpu.A);
label_B486:;
    /* $B486: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x28; FLAG_NZ(g_cpu.A);
label_B488:; /* NoJump */
    /* $B488: 20 */ maybe_trigger_vblank(6); func_F388();
label_B48B:; /* ProcJumping */
    /* $B48B: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B4A2; }
label_B48D:;
    /* $B48D: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x07BB); FLAG_NZ(g_cpu.Y);
label_B490:;
    /* $B490: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x08; g_cpu.C=(g_cpu.Y>=0x08)?1:0; FLAG_NZ(r&0xFF); }
label_B492:;
    /* $B492: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B49D; }
label_B494:;
    /* $B494: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xA0; FLAG_NZ(g_cpu.A);
label_B496:;
    /* $B496: 8D */ maybe_trigger_vblank(4); nes_write(0x4002, g_cpu.A);
label_B499:;
    /* $B499: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x9F; FLAG_NZ(g_cpu.A);
label_B49B:;
    /* $B49B: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B49F; }
label_B49D:;
    /* $B49D: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x90; FLAG_NZ(g_cpu.A);
label_B49F:;
    /* $B49F: 8D */ maybe_trigger_vblank(4); nes_write(0x4000, g_cpu.A);
label_B4A2:;
    /* $B4A2: CE */ maybe_trigger_vblank(6); { uint16_t a=0x07BB; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_B4A5:;
    /* $B4A5: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B4B5; }
label_B4A7:;
    /* $B4A7: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x00; FLAG_NZ(g_cpu.X);
label_B4A9:;
    /* $B4A9: 86 */ maybe_trigger_vblank(3); nes_write(0xF1, g_cpu.X);
label_B4AB:;
    /* $B4AB: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x0E; FLAG_NZ(g_cpu.X);
label_B4AD:;
    /* $B4AD: 8E */ maybe_trigger_vblank(4); nes_write(0x4015, g_cpu.X);
label_B4B0:;
    /* $B4B0: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x0F; FLAG_NZ(g_cpu.X);
label_B4B2:;
    /* $B4B2: 8E */ maybe_trigger_vblank(4); nes_write(0x4015, g_cpu.X);
label_B4B5:;
    /* $B4B5: 60 */ maybe_trigger_vblank(6); 
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
    return;
label_B4B6:;
    /* $B4B6: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x2F; FLAG_NZ(g_cpu.A);
label_B4B8:;
    /* $B4B8: 8D */ maybe_trigger_vblank(4); nes_write(0x07BB, g_cpu.A);
label_B4BB:;
    /* $B4BB: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07BB); FLAG_NZ(g_cpu.A);
label_B4BE:;
    /* $B4BE: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B4BF:;
    /* $B4BF: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_B4D1; }
label_B4C1:;
    /* $B4C1: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B4C2:;
    /* $B4C2: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_B4D1; }
label_B4C4:;
    /* $B4C4: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x02; FLAG_NZ(g_cpu.A);
label_B4C6:;
    /* $B4C6: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_B4D1; }
label_B4C8:;
    /* $B4C8: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x91; FLAG_NZ(g_cpu.Y);
label_B4CA:;
    /* $B4CA: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x9A; FLAG_NZ(g_cpu.X);
label_B4CC:;
    /* $B4CC: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x44; FLAG_NZ(g_cpu.A);
label_B4CE:;
    /* $B4CE: 20 */ maybe_trigger_vblank(6); func_F388();
label_B4D1:;
    /* $B4D1: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); func_F4A2(); return;
}

void func_B40D_b1(void) {
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_B40D_b1");
#endif
label_B40D:;
    /* $B40D: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07BB); FLAG_NZ(g_cpu.A);
label_B410:;
    /* $B410: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x06; g_cpu.C=(g_cpu.A>=0x06)?1:0; FLAG_NZ(r&0xFF); }
label_B412:;
    /* $B412: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B419; }
label_B414:;
    /* $B414: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xBB; FLAG_NZ(g_cpu.A);
label_B416:;
    /* $B416: 8D */ maybe_trigger_vblank(4); nes_write(0x4001, g_cpu.A);
label_B419:;
    /* $B419: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B47B; }
label_B41B:;
    /* $B41B: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0xFF); FLAG_NZ(g_cpu.Y);
label_B41D:;
    /* $B41D: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_B43F; }
label_B41F:; /* ExitCSub */
    /* $B41F: 84 */ maybe_trigger_vblank(3); nes_write(0xF1, g_cpu.Y);
label_B421:;
    /* $B421: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) { maybe_trigger_vblank(2); call_by_address(0xB3CD); return; }
label_B423:;
    /* $B423: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_B425:;
    /* $B425: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { maybe_trigger_vblank(2); call_by_address(0xB3D1); return; }
label_B427:;
    /* $B427: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_B429:;
    /* $B429: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { maybe_trigger_vblank(2); call_by_address(0xB3FF); return; }
label_B42B:; /* FallMForceData */
    /* $B42B: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_B42D:;
    /* $B42D: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_B45B; }
label_B42F:;
    /* $B42F: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_B431:;
    /* $B431: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_B47D; }
label_B433:;
    /* $B433: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_B435:;
    /* $B435: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_B4B6; }
label_B437:;
    /* $B437: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_B439:; /* InitMForceData */
    /* $B439: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { maybe_trigger_vblank(2); call_by_address(0xB3F9); return; }
label_B43B:;
    /* $B43B: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_B43D:;
    /* $B43D: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { maybe_trigger_vblank(2); call_by_address(0xB3BF); return; }
label_B43F:;
    /* $B43F: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xF1); FLAG_NZ(g_cpu.A);
label_B441:;
    /* $B441: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_B45A; }
label_B443:; /* MaxRightXSpdData */
    /* $B443: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) { maybe_trigger_vblank(2); call_by_address(0xB3DF); return; }
label_B445:;
    /* $B445: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B446:;
    /* $B446: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { maybe_trigger_vblank(2); call_by_address(0xB3DF); return; }
label_B448:;
    /* $B448: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B449:;
    /* $B449: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) {
    maybe_trigger_vblank(1);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_B40D;
    }
label_B44B:;
    /* $B44B: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B44C:;
    /* $B44C: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_B469; }
label_B44E:;
    /* $B44E: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B44F:;
    /* $B44F: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_B48D; }
label_B451:;
    /* $B451: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B452:;
    /* $B452: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_B4BB; }
label_B454:;
    /* $B454: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B455:;
    /* $B455: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) {
    maybe_trigger_vblank(1);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_B40D;
    }
label_B457:;
    /* $B457: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B458:;
    /* $B458: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_B4A2; }
label_B45A:;
    /* $B45A: 60 */
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
    return; /* branch-target RTS */
label_B45B:;
    /* $B45B: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x0E; FLAG_NZ(g_cpu.A);
label_B45D:;
    /* $B45D: 8D */ maybe_trigger_vblank(4); nes_write(0x07BB, g_cpu.A);
label_B460:;
    /* $B460: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x9C; FLAG_NZ(g_cpu.Y);
label_B462:;
    /* $B462: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x9E; FLAG_NZ(g_cpu.X);
label_B464:;
    /* $B464: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x26; FLAG_NZ(g_cpu.A);
label_B466:;
    /* $B466: 20 */ maybe_trigger_vblank(6); func_F388();
label_B469:;
    /* $B469: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x07BB); FLAG_NZ(g_cpu.Y);
label_B46C:;
    /* $B46C: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xF3B0 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_B46F:;
    /* $B46F: 8D */ maybe_trigger_vblank(4); nes_write(0x4000, g_cpu.A);
label_B472:;
    /* $B472: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x06; g_cpu.C=(g_cpu.Y>=0x06)?1:0; FLAG_NZ(r&0xFF); }
label_B474:;
    /* $B474: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B47B; }
label_B476:;
    /* $B476: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x9E; FLAG_NZ(g_cpu.A);
label_B478:;
    /* $B478: 8D */ maybe_trigger_vblank(4); nes_write(0x4002, g_cpu.A);
label_B47B:;
    /* $B47B: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B4A2; }
label_B47D:;
    /* $B47D: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x0E; FLAG_NZ(g_cpu.A);
label_B47F:;
    /* $B47F: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0xCB; FLAG_NZ(g_cpu.Y);
label_B481:;
    /* $B481: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x9F; FLAG_NZ(g_cpu.X);
label_B483:;
    /* $B483: 8D */ maybe_trigger_vblank(4); nes_write(0x07BB, g_cpu.A);
label_B486:;
    /* $B486: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x28; FLAG_NZ(g_cpu.A);
label_B488:; /* NoJump */
    /* $B488: 20 */ maybe_trigger_vblank(6); func_F388();
label_B48B:; /* ProcJumping */
    /* $B48B: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B4A2; }
label_B48D:;
    /* $B48D: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x07BB); FLAG_NZ(g_cpu.Y);
label_B490:;
    /* $B490: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x08; g_cpu.C=(g_cpu.Y>=0x08)?1:0; FLAG_NZ(r&0xFF); }
label_B492:;
    /* $B492: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B49D; }
label_B494:;
    /* $B494: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xA0; FLAG_NZ(g_cpu.A);
label_B496:;
    /* $B496: 8D */ maybe_trigger_vblank(4); nes_write(0x4002, g_cpu.A);
label_B499:;
    /* $B499: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x9F; FLAG_NZ(g_cpu.A);
label_B49B:;
    /* $B49B: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B49F; }
label_B49D:;
    /* $B49D: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x90; FLAG_NZ(g_cpu.A);
label_B49F:;
    /* $B49F: 8D */ maybe_trigger_vblank(4); nes_write(0x4000, g_cpu.A);
label_B4A2:;
    /* $B4A2: CE */ maybe_trigger_vblank(6); { uint16_t a=0x07BB; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_B4A5:;
    /* $B4A5: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B4B5; }
label_B4A7:;
    /* $B4A7: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x00; FLAG_NZ(g_cpu.X);
label_B4A9:;
    /* $B4A9: 86 */ maybe_trigger_vblank(3); nes_write(0xF1, g_cpu.X);
label_B4AB:;
    /* $B4AB: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x0E; FLAG_NZ(g_cpu.X);
label_B4AD:;
    /* $B4AD: 8E */ maybe_trigger_vblank(4); nes_write(0x4015, g_cpu.X);
label_B4B0:;
    /* $B4B0: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x0F; FLAG_NZ(g_cpu.X);
label_B4B2:;
    /* $B4B2: 8E */ maybe_trigger_vblank(4); nes_write(0x4015, g_cpu.X);
label_B4B5:;
    /* $B4B5: 60 */ maybe_trigger_vblank(6); 
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
    return;
label_B4B6:;
    /* $B4B6: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x2F; FLAG_NZ(g_cpu.A);
label_B4B8:;
    /* $B4B8: 8D */ maybe_trigger_vblank(4); nes_write(0x07BB, g_cpu.A);
label_B4BB:;
    /* $B4BB: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07BB); FLAG_NZ(g_cpu.A);
label_B4BE:;
    /* $B4BE: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B4BF:;
    /* $B4BF: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_B4D1; }
label_B4C1:;
    /* $B4C1: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B4C2:;
    /* $B4C2: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_B4D1; }
label_B4C4:;
    /* $B4C4: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x02; FLAG_NZ(g_cpu.A);
label_B4C6:;
    /* $B4C6: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_B4D1; }
label_B4C8:;
    /* $B4C8: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x91; FLAG_NZ(g_cpu.Y);
label_B4CA:;
    /* $B4CA: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x9A; FLAG_NZ(g_cpu.X);
label_B4CC:;
    /* $B4CC: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x44; FLAG_NZ(g_cpu.A);
label_B4CE:;
    /* $B4CE: 20 */ maybe_trigger_vblank(6); func_F388();
label_B4D1:;
    /* $B4D1: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); func_F4A2(); return;
}

void func_B568_b1(void) {
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_B568_b1");
#endif
label_B568:;
    /* $B568: CE */ maybe_trigger_vblank(6); { uint16_t a=0x07BD; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_B56B:;
    /* $B56B: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B57B; }
label_B56D:;
    /* $B56D: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x00; FLAG_NZ(g_cpu.X);
label_B56F:;
    /* $B56F: 86 */ maybe_trigger_vblank(3); nes_write(0xF2, g_cpu.X);
label_B571:;
    /* $B571: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x0D; FLAG_NZ(g_cpu.X);
label_B573:;
    /* $B573: 8E */ maybe_trigger_vblank(4); nes_write(0x4015, g_cpu.X);
label_B576:;
    /* $B576: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x0F; FLAG_NZ(g_cpu.X);
label_B578:;
    /* $B578: 8E */ maybe_trigger_vblank(4); nes_write(0x4015, g_cpu.X);
label_B57B:;
    /* $B57B: 60 */ maybe_trigger_vblank(6); 
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
    return;
}

void func_B565_b1(void) {
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_B565_b1");
#endif
label_B565:;
    /* $B565: 20 */ maybe_trigger_vblank(6); func_F3A6();
label_B568:;
    /* $B568: CE */ maybe_trigger_vblank(6); { uint16_t a=0x07BD; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_B56B:;
    /* $B56B: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B57B; }
label_B56D:;
    /* $B56D: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x00; FLAG_NZ(g_cpu.X);
label_B56F:;
    /* $B56F: 86 */ maybe_trigger_vblank(3); nes_write(0xF2, g_cpu.X);
label_B571:;
    /* $B571: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x0D; FLAG_NZ(g_cpu.X);
label_B573:;
    /* $B573: 8E */ maybe_trigger_vblank(4); nes_write(0x4015, g_cpu.X);
label_B576:;
    /* $B576: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x0F; FLAG_NZ(g_cpu.X);
label_B578:;
    /* $B578: 8E */ maybe_trigger_vblank(4); nes_write(0x4015, g_cpu.X);
label_B57B:;
    /* $B57B: 60 */ maybe_trigger_vblank(6); 
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
    return;
}

void func_B5C5_b1(void) { /* SetAnimSpd */
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_B5C5_b1");
#endif
label_B5C5:; /* SetAnimSpd */
    /* $B5C5: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); func_F568(); return;
}

void func_B64D_b1(void) {
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_B64D_b1");
#endif
label_B64D:;
    /* $B64D: 8D */ maybe_trigger_vblank(4); nes_write(0x400C, g_cpu.A);
label_B650:;
    /* $B650: 8E */ maybe_trigger_vblank(4); nes_write(0x400E, g_cpu.X);
label_B653:;
    /* $B653: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x18; FLAG_NZ(g_cpu.A);
label_B655:;
    /* $B655: 8D */ maybe_trigger_vblank(4); nes_write(0x400F, g_cpu.A);
label_B658:;
    /* $B658: CE */ maybe_trigger_vblank(6); { uint16_t a=0x07BF; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_B65B:;
    /* $B65B: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B666; }
label_B65D:;
    /* $B65D: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xF0; FLAG_NZ(g_cpu.A);
label_B65F:;
    /* $B65F: 8D */ maybe_trigger_vblank(4); nes_write(0x400C, g_cpu.A);
label_B662:;
    /* $B662: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_B664:; /* ProcFireballs */
    /* $B664: 85 */ maybe_trigger_vblank(3); nes_write(0xF3, g_cpu.A);
label_B666:;
    /* $B666: 60 */ maybe_trigger_vblank(6); 
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
    return;
}

void func_B6D1_b1(void) {
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_B6D1_b1");
#endif
label_B6D1:;
    /* $B6D1: 8C */ maybe_trigger_vblank(4); nes_write(0x07C7, g_cpu.Y);
label_B6D4:;
    /* $B6D4: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x00; FLAG_NZ(g_cpu.Y);
label_B6D6:;
    /* $B6D6: 8C */ maybe_trigger_vblank(4); nes_write(0x07B1, g_cpu.Y);
label_B6D9:;
    /* $B6D9: 85 */ maybe_trigger_vblank(3); nes_write(0xF4, g_cpu.A);
label_B6DB:;
    /* $B6DB: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x01; g_cpu.C=(g_cpu.A>=0x01)?1:0; FLAG_NZ(r&0xFF); }
label_B6DD:;
    /* $B6DD: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B6ED; }
label_B6DF:;
    /* $B6DF: EE */ maybe_trigger_vblank(6); { uint16_t a=0x07C7; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_B6E2:;
    /* $B6E2: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x07C7); FLAG_NZ(g_cpu.Y);
label_B6E5:;
    /* $B6E5: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x32; g_cpu.C=(g_cpu.Y>=0x32)?1:0; FLAG_NZ(r&0xFF); }
label_B6E7:;
    /* $B6E7: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B6F5; }
label_B6E9:;
    /* $B6E9: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x11; FLAG_NZ(g_cpu.Y);
label_B6EB:;
    /* $B6EB: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) {
    maybe_trigger_vblank(1);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_B6D1;
    }
label_B6ED:;
    /* $B6ED: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x08; FLAG_NZ(g_cpu.Y);
label_B6EF:;
    /* $B6EF: 84 */ maybe_trigger_vblank(3); nes_write(0xF7, g_cpu.Y);
label_B6F1:;
    /* $B6F1: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_B6F2:; /* NoFBall */
    /* $B6F2: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B6F3:; /* FireballExplosion */
    /* $B6F3: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) {
    maybe_trigger_vblank(1);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_B6F1;
    }
label_B6F5:;
    /* $B6F5: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xF90C + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_B6F8:;
    /* $B6F8: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_B6F9:; /* BubbleCheck */
    /* $B6F9: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xF90D + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_B6FC:;
    /* $B6FC: 85 */ maybe_trigger_vblank(3); nes_write(0xF0, g_cpu.A);
label_B6FE:;
    /* $B6FE: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xF90E + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_B701:;
    /* $B701: 85 */ maybe_trigger_vblank(3); nes_write(0xF5, g_cpu.A);
label_B703:;
    /* $B703: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xF90F + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_B706:;
    /* $B706: 85 */ maybe_trigger_vblank(3); nes_write(0xF6, g_cpu.A);
label_B708:;
    /* $B708: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xF910 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_B70B:; /* SetupBubble */
    /* $B70B: 85 */ maybe_trigger_vblank(3); nes_write(0xF9, g_cpu.A);
label_B70D:;
    /* $B70D: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xF911 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_B710:;
    /* $B710: 85 */ maybe_trigger_vblank(3); nes_write(0xF8, g_cpu.A);
label_B712:;
    /* $B712: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xF912 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_B715:;
    /* $B715: 8D */ maybe_trigger_vblank(4); nes_write(0x07B0, g_cpu.A);
label_B718:;
    /* $B718: 8D */ maybe_trigger_vblank(4); nes_write(0x07C1, g_cpu.A);
label_B71B:;
    /* $B71B: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x01; FLAG_NZ(g_cpu.A);
label_B71D:;
    /* $B71D: 8D */ maybe_trigger_vblank(4); nes_write(0x07B4, g_cpu.A);
label_B720:;
    /* $B720: 8D */ maybe_trigger_vblank(4); nes_write(0x07B6, g_cpu.A);
label_B723:;
    /* $B723: 8D */ maybe_trigger_vblank(4); nes_write(0x07B9, g_cpu.A);
label_B726:;
    /* $B726: 8D */ maybe_trigger_vblank(4); nes_write(0x07BA, g_cpu.A);
label_B729:;
    /* $B729: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_B72B:;
    /* $B72B: 85 */ maybe_trigger_vblank(3); nes_write(0xF7, g_cpu.A);
label_B72D:;
    /* $B72D: 8D */ maybe_trigger_vblank(4); nes_write(0x07CA, g_cpu.A);
label_B730:;
    /* $B730: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x0B; FLAG_NZ(g_cpu.A);
label_B732:; /* MoveBubl */
    /* $B732: 8D */ maybe_trigger_vblank(4); nes_write(0x4015, g_cpu.A);
label_B735:;
    /* $B735: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x0F; FLAG_NZ(g_cpu.A);
label_B737:;
    /* $B737: 8D */ maybe_trigger_vblank(4); nes_write(0x4015, g_cpu.A);
label_B73A:;
    /* $B73A: CE */ maybe_trigger_vblank(6); { uint16_t a=0x07B4; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_B73D:;
    /* $B73D: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B79E; }
label_B73F:;
    /* $B73F: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0xF7); FLAG_NZ(g_cpu.Y);
label_B741:;
    /* $B741: E6 */ maybe_trigger_vblank(5); { uint16_t a=0xF7; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_B743:;
    /* $B743: B1 */ maybe_trigger_vblank(5); g_cpu.A = nes_read((nes_read16zp(0xF5) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_B745:;
    /* $B745: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_B74B; }
label_B747:;
    /* $B747: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) { maybe_trigger_vblank(1); goto label_B786; }
label_B749:;
    /* $B749: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B77A; }
label_B74B:; /* Bubble_MForceData */
    /* $B74B: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07B1); FLAG_NZ(g_cpu.A);
label_B74E:;
    /* $B74E: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x40; g_cpu.C=(g_cpu.A>=0x40)?1:0; FLAG_NZ(r&0xFF); }
label_B750:;
    /* $B750: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B757; }
label_B752:;
    /* $B752: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07C5); FLAG_NZ(g_cpu.A);
label_B755:;
    /* $B755: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B774; }
label_B757:;
    /* $B757: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x04; FLAG_NZ(g_cpu.A);
label_B759:;
    /* $B759: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B777; }
label_B75B:;
    /* $B75B: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xF4); FLAG_NZ(g_cpu.A);
label_B75D:;
    /* $B75D: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x5F; FLAG_NZ(g_cpu.A);
label_B75F:;
    /* $B75F: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B774; }
label_B761:;
    /* $B761: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_B763:;
    /* $B763: 85 */ maybe_trigger_vblank(3); nes_write(0xF4, g_cpu.A);
label_B765:;
    /* $B765: 8D */ maybe_trigger_vblank(4); nes_write(0x07B1, g_cpu.A);
label_B768:;
    /* $B768: 8D */ maybe_trigger_vblank(4); nes_write(0x4008, g_cpu.A);
label_B76B:;
    /* $B76B: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x90; FLAG_NZ(g_cpu.A);
label_B76D:;
    /* $B76D: 8D */ maybe_trigger_vblank(4); nes_write(0x4000, g_cpu.A);
label_B770:;
    /* $B770: 8D */ maybe_trigger_vblank(4); nes_write(0x4004, g_cpu.A);
label_B773:;
    /* $B773: 60 */ maybe_trigger_vblank(6); 
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
    return;
label_B774:;
    /* $B774: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); func_F6D4(); return;
label_B777:;
    /* $B777: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); func_F6A4(); return;
label_B77A:;
    /* $B77A: 20 */ maybe_trigger_vblank(6); func_F8CB();
label_B77D:;
    /* $B77D: 8D */ maybe_trigger_vblank(4); nes_write(0x07B3, g_cpu.A);
label_B780:;
    /* $B780: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0xF7); FLAG_NZ(g_cpu.Y);
label_B782:;
    /* $B782: E6 */ maybe_trigger_vblank(5); { uint16_t a=0xF7; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_B784:;
    /* $B784: B1 */ maybe_trigger_vblank(5); g_cpu.A = nes_read((nes_read16zp(0xF5) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_B786:; /* ResGTCtrl */
    /* $B786: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0xF2); FLAG_NZ(g_cpu.X);
label_B788:;
    /* $B788: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B798; }
label_B78A:;
    /* $B78A: 20 */ maybe_trigger_vblank(6); func_F3A9();
label_B78D:;
    /* $B78D: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_B792; }
label_B78F:;
    /* $B78F: 20 */ maybe_trigger_vblank(6); func_F8D8();
label_B792:;
    /* $B792: 8D */ maybe_trigger_vblank(4); nes_write(0x07B5, g_cpu.A);
label_B795:;
    /* $B795: 20 */ maybe_trigger_vblank(6); func_F39F();
label_B798:;
    /* $B798: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07B3); FLAG_NZ(g_cpu.A);
label_B79B:;
    /* $B79B: 8D */ maybe_trigger_vblank(4); nes_write(0x07B4, g_cpu.A);
label_B79E:;
    /* $B79E: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xF2); FLAG_NZ(g_cpu.A);
label_B7A0:;
    /* $B7A0: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B7BC; }
label_B7A2:;
    /* $B7A2: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07B1); FLAG_NZ(g_cpu.A);
label_B7A5:;
    /* $B7A5: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x91; FLAG_NZ(g_cpu.A);
label_B7A7:;
    /* $B7A7: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B7BC; }
label_B7A9:;
    /* $B7A9: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x07B5); FLAG_NZ(g_cpu.Y);
label_B7AC:;
    /* $B7AC: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_B7B1; }
label_B7AE:;
    /* $B7AE: CE */ maybe_trigger_vblank(6); { uint16_t a=0x07B5; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_B7B1:;
    /* $B7B1: 20 */ maybe_trigger_vblank(6); func_F8F4();
label_B7B4:;
    /* $B7B4: 8D */ maybe_trigger_vblank(4); nes_write(0x4004, g_cpu.A);
label_B7B7:;
    /* $B7B7: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x7F; FLAG_NZ(g_cpu.X);
label_B7B9:;
    /* $B7B9: 8E */ maybe_trigger_vblank(4); nes_write(0x4005, g_cpu.X);
label_B7BC:;
    /* $B7BC: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0xF8); FLAG_NZ(g_cpu.Y);
label_B7BE:;
    /* $B7BE: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) { maybe_trigger_vblank(2); goto label_B81A; }
label_B7C0:;
    /* $B7C0: CE */ maybe_trigger_vblank(6); { uint16_t a=0x07B6; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_B7C3:;
    /* $B7C3: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B7F7; }
label_B7C5:;
    /* $B7C5: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0xF8); FLAG_NZ(g_cpu.Y);
label_B7C7:; /* WhLoop */
    /* $B7C7: E6 */ maybe_trigger_vblank(5); { uint16_t a=0xF8; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_B7C9:;
    /* $B7C9: B1 */ maybe_trigger_vblank(5); g_cpu.A = nes_read((nes_read16zp(0xF5) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_B7CB:;
    /* $B7CB: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B7DC; }
label_B7CD:;
    /* $B7CD: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x83; FLAG_NZ(g_cpu.A);
label_B7CF:;
    /* $B7CF: 8D */ maybe_trigger_vblank(4); nes_write(0x4000, g_cpu.A);
label_B7D2:;
    /* $B7D2: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x94; FLAG_NZ(g_cpu.A);
label_B7D4:;
    /* $B7D4: 8D */ maybe_trigger_vblank(4); nes_write(0x4001, g_cpu.A);
label_B7D7:;
    /* $B7D7: 8D */ maybe_trigger_vblank(4); nes_write(0x07CA, g_cpu.A);
label_B7DA:;
    /* $B7DA: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) {
    maybe_trigger_vblank(1);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_B7C5;
    }
label_B7DC:;
    /* $B7DC: 20 */ maybe_trigger_vblank(6); func_F8C5();
label_B7DF:;
    /* $B7DF: 8D */ maybe_trigger_vblank(4); nes_write(0x07B6, g_cpu.A);
label_B7E2:;
    /* $B7E2: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0xF1); FLAG_NZ(g_cpu.Y);
label_B7E4:;
    /* $B7E4: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(2); goto label_B81A; }
label_B7E6:;
    /* $B7E6: 8A */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.X; FLAG_NZ(g_cpu.A);
label_B7E7:;
    /* $B7E7: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x3E; FLAG_NZ(g_cpu.A);
label_B7E9:;
    /* $B7E9: 20 */ maybe_trigger_vblank(6); func_F38B();
label_B7EC:;
    /* $B7EC: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_B7F1; }
label_B7EE:;
    /* $B7EE: 20 */ maybe_trigger_vblank(6); func_F8D8();
label_B7F1:; /* NextWh */
    /* $B7F1: 8D */ maybe_trigger_vblank(4); nes_write(0x07B7, g_cpu.A);
label_B7F4:; /* ExitWh */
    /* $B7F4: 20 */ maybe_trigger_vblank(6); func_F381();
label_B7F7:;
    /* $B7F7: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xF1); FLAG_NZ(g_cpu.A);
label_B7F9:;
    /* $B7F9: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(2); goto label_B81A; }
label_B7FB:;
    /* $B7FB: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07B1); FLAG_NZ(g_cpu.A);
label_B7FE:;
    /* $B7FE: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x91; FLAG_NZ(g_cpu.A);
label_B800:;
    /* $B800: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B810; }
label_B802:;
    /* $B802: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x07B7); FLAG_NZ(g_cpu.Y);
label_B805:;
    /* $B805: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_B80A; }
label_B807:;
    /* $B807: CE */ maybe_trigger_vblank(6); { uint16_t a=0x07B7; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_B80A:;
    /* $B80A: 20 */ maybe_trigger_vblank(6); func_F8F4();
label_B80D:;
    /* $B80D: 8D */ maybe_trigger_vblank(4); nes_write(0x4000, g_cpu.A);
label_B810:;
    /* $B810: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07CA); FLAG_NZ(g_cpu.A);
label_B813:;
    /* $B813: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B817; }
label_B815:;
    /* $B815: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x7F; FLAG_NZ(g_cpu.A);
label_B817:;
    /* $B817: 8D */ maybe_trigger_vblank(4); nes_write(0x4001, g_cpu.A);
label_B81A:;
    /* $B81A: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xF9); FLAG_NZ(g_cpu.A);
label_B81C:;
    /* $B81C: CE */ maybe_trigger_vblank(6); { uint16_t a=0x07B9; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_B81F:;
    /* $B81F: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B86D; }
label_B821:;
    /* $B821: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0xF9); FLAG_NZ(g_cpu.Y);
label_B823:;
    /* $B823: E6 */ maybe_trigger_vblank(5); { uint16_t a=0xF9; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_B825:;
    /* $B825: B1 */ maybe_trigger_vblank(5); g_cpu.A = nes_read((nes_read16zp(0xF5) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_B827:;
    /* $B827: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_B86A; }
label_B829:;
    /* $B829: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) { maybe_trigger_vblank(1); goto label_B83E; }
label_B82B:;
    /* $B82B: 20 */ maybe_trigger_vblank(6); func_F8CB();
label_B82E:;
    /* $B82E: 8D */ maybe_trigger_vblank(4); nes_write(0x07B8, g_cpu.A);
label_B831:;
    /* $B831: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x1F; FLAG_NZ(g_cpu.A);
label_B833:;
    /* $B833: 8D */ maybe_trigger_vblank(4); nes_write(0x4008, g_cpu.A);
label_B836:;
    /* $B836: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0xF9); FLAG_NZ(g_cpu.Y);
label_B838:;
    /* $B838: E6 */ maybe_trigger_vblank(5); { uint16_t a=0xF9; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_B83A:;
    /* $B83A: B1 */ maybe_trigger_vblank(5); g_cpu.A = nes_read((nes_read16zp(0xF5) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_B83C:;
    /* $B83C: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_B86A; }
label_B83E:;
    /* $B83E: 20 */ maybe_trigger_vblank(6); func_F3AD();
label_B841:;
    /* $B841: AE */ maybe_trigger_vblank(4); g_cpu.X = nes_read(0x07B8); FLAG_NZ(g_cpu.X);
label_B844:;
    /* $B844: 8E */ maybe_trigger_vblank(4); nes_write(0x07B9, g_cpu.X);
label_B847:;
    /* $B847: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07B1); FLAG_NZ(g_cpu.A);
label_B84A:;
    /* $B84A: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x6E; FLAG_NZ(g_cpu.A);
label_B84C:;
    /* $B84C: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B854; }
label_B84E:;
    /* $B84E: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xF4); FLAG_NZ(g_cpu.A);
label_B850:; /* FlagpoleScoreDigits */
    /* $B850: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x0A; FLAG_NZ(g_cpu.A);
label_B852:;
    /* $B852: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_B86D; }
label_B854:;
    /* $B854: 8A */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.X; FLAG_NZ(g_cpu.A);
label_B855:; /* FlagpoleRoutine */
    /* $B855: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x12; g_cpu.C=(g_cpu.A>=0x12)?1:0; FLAG_NZ(r&0xFF); }
label_B857:;
    /* $B857: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_B868; }
label_B859:;
    /* $B859: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07B1); FLAG_NZ(g_cpu.A);
label_B85C:;
    /* $B85C: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x08; FLAG_NZ(g_cpu.A);
label_B85E:;
    /* $B85E: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_B864; }
label_B860:;
    /* $B860: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x0F; FLAG_NZ(g_cpu.A);
label_B862:;
    /* $B862: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B86A; }
label_B864:;
    /* $B864: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x1F; FLAG_NZ(g_cpu.A);
label_B866:;
    /* $B866: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B86A; }
label_B868:;
    /* $B868: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xFF; FLAG_NZ(g_cpu.A);
label_B86A:;
    /* $B86A: 8D */ maybe_trigger_vblank(4); nes_write(0x4008, g_cpu.A);
label_B86D:;
    /* $B86D: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xF4); FLAG_NZ(g_cpu.A);
label_B86F:;
    /* $B86F: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0xF3; FLAG_NZ(g_cpu.A);
label_B871:;
    /* $B871: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_B8C4; }
label_B873:;
    /* $B873: CE */ maybe_trigger_vblank(6); { uint16_t a=0x07BA; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_B876:;
    /* $B876: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B8C4; }
label_B878:;
    /* $B878: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x07B0); FLAG_NZ(g_cpu.Y);
label_B87B:;
    /* $B87B: EE */ maybe_trigger_vblank(6); { uint16_t a=0x07B0; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_B87E:;
    /* $B87E: B1 */ maybe_trigger_vblank(5); g_cpu.A = nes_read((nes_read16zp(0xF5) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_B880:;
    /* $B880: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B88A; }
label_B882:;
    /* $B882: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07C1); FLAG_NZ(g_cpu.A);
label_B885:;
    /* $B885: 8D */ maybe_trigger_vblank(4); nes_write(0x07B0, g_cpu.A);
label_B888:;
    /* $B888: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) {
    maybe_trigger_vblank(1);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_B878;
    }
label_B88A:;
    /* $B88A: 20 */ maybe_trigger_vblank(6); func_F8C5();
label_B88D:;
    /* $B88D: 8D */ maybe_trigger_vblank(4); nes_write(0x07BA, g_cpu.A);
label_B890:;
    /* $B890: 8A */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.X; FLAG_NZ(g_cpu.A);
label_B891:;
    /* $B891: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x3E; FLAG_NZ(g_cpu.A);
label_B893:;
    /* $B893: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_B8B9; }
label_B895:;
    /* $B895: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x30; g_cpu.C=(g_cpu.A>=0x30)?1:0; FLAG_NZ(r&0xFF); }
label_B897:;
    /* $B897: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_B8B1; }
label_B899:; /* GiveFPScr */
    /* $B899: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x20; g_cpu.C=(g_cpu.A>=0x20)?1:0; FLAG_NZ(r&0xFF); }
label_B89B:;
    /* $B89B: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_B8A9; }
label_B89D:;
    /* $B89D: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x10; FLAG_NZ(g_cpu.A);
label_B89F:;
    /* $B89F: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_B8B9; }
label_B8A1:;
    /* $B8A1: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x1C; FLAG_NZ(g_cpu.A);
label_B8A3:;
    /* $B8A3: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x03; FLAG_NZ(g_cpu.X);
label_B8A5:;
    /* $B8A5: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x18; FLAG_NZ(g_cpu.Y);
label_B8A7:;
    /* $B8A7: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B8BB; }
label_B8A9:;
    /* $B8A9: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x1C; FLAG_NZ(g_cpu.A);
label_B8AB:;
    /* $B8AB: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x0C; FLAG_NZ(g_cpu.X);
label_B8AD:;
    /* $B8AD: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x18; FLAG_NZ(g_cpu.Y);
label_B8AF:;
    /* $B8AF: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B8BB; }
label_B8B1:;
    /* $B8B1: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x1C; FLAG_NZ(g_cpu.A);
label_B8B3:;
    /* $B8B3: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x03; FLAG_NZ(g_cpu.X);
label_B8B5:; /* ExitFlagP */
    /* $B8B5: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x58; FLAG_NZ(g_cpu.Y);
label_B8B7:;
    /* $B8B7: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B8BB; }
label_B8B9:;
    /* $B8B9: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x10; FLAG_NZ(g_cpu.A);
label_B8BB:;
    /* $B8BB: 8D */ maybe_trigger_vblank(4); nes_write(0x400C, g_cpu.A);
label_B8BE:;
    /* $B8BE: 8E */ maybe_trigger_vblank(4); nes_write(0x400E, g_cpu.X);
label_B8C1:;
    /* $B8C1: 8C */ maybe_trigger_vblank(4); nes_write(0x400F, g_cpu.Y);
label_B8C4:;
    /* $B8C4: 60 */ maybe_trigger_vblank(6); 
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
    return;
}

void func_B970_b1(void) {
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_B970_b1");
#endif
label_B970:;
    /* $B970: 68 */ maybe_trigger_vblank(4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_B971:;
    /* $B971: 08 */ maybe_trigger_vblank(3); { uint8_t p = (g_cpu.N<<7)|(g_cpu.V<<6)|0x30|(g_cpu.D<<3)|(g_cpu.I<<2)|(g_cpu.Z<<1)|g_cpu.C;
  g_ram[0x100 + g_cpu.S] = p; g_cpu.S--; }
label_B972:;
    /* $B972: 51 */ maybe_trigger_vblank(5); g_cpu.A ^= nes_read((nes_read16zp(0xFE) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_B974:;
    /* $B974: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address_tail(0x1824, -1); return;
}

void func_B976_b1_body(int _entry) {
    switch (_entry) {
        case 1: goto label_B9A9;
        case 2: goto label_BB33;
        case 3: goto label_BB48;
        case 4: goto label_BFC6;
    }
label_B976:;
    /* $B976: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_B977:;
    /* $B977: 01 */ maybe_trigger_vblank(6); g_cpu.A |= nes_read(nes_read16zp((0xFA + g_cpu.X) & 0xFF)); FLAG_NZ(g_cpu.A);
label_B979:; /* VDrawLoop */
    /* $B979: 2D */ maybe_trigger_vblank(4); g_cpu.A &= nes_read(0xB81C); FLAG_NZ(g_cpu.A);
label_B97C:;
    /* $B97C: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_B97D:;
    /* $B97D: 49 */ maybe_trigger_vblank(2); g_cpu.A ^= 0xFA; FLAG_NZ(g_cpu.A);
label_B97F:;
    /* $B97F: 20 */ maybe_trigger_vblank(6); nes_dispatch_call(0x7012, -1);
label_B982:;
    /* $B982: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_B983:;
    /* $B983: 75 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0xFA + g_cpu.X) & 0xFF); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_B985:;
    /* $B985: 1B */ maybe_trigger_vblank(7); { uint16_t a=(0x4410 + g_cpu.Y) & 0xFFFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); g_cpu.A|=v; FLAG_NZ(g_cpu.A); }
label_B988:;
    /* $B988: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_B989:;
    /* $B989: 9D */ maybe_trigger_vblank(5); nes_write((0x11FA + g_cpu.X) & 0xFFFF, g_cpu.A);
label_B98C:;
    /* $B98C: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_B98D:;
    /* $B98D: 1C */ maybe_trigger_vblank(4); (void)nes_read((0xC218 + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_B990:;
    /* $B990: FA */ maybe_trigger_vblank(2); /* NOP */
label_B991:;
    /* $B991: 2D */ maybe_trigger_vblank(4); g_cpu.A &= nes_read(0x5810); FLAG_NZ(g_cpu.A);
label_B994:;
    /* $B994: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_B995:;
    /* $B995: DB */ maybe_trigger_vblank(7); { uint16_t a=(0x14FA + g_cpu.Y) & 0xFFFF; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); g_cpu.C=(g_cpu.A>=v)?1:0; FLAG_NZ((uint8_t)(g_cpu.A-v)); }
label_B998:;
    /* $B998: 0D */ maybe_trigger_vblank(4); g_cpu.A |= nes_read(0x183F); FLAG_NZ(g_cpu.A);
label_B99B:;
    /* $B99B: F9 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0x15FA + g_cpu.Y) & 0xFFFF); int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_B99E:;
    /* $B99E: 0D */ maybe_trigger_vblank(4); g_cpu.A |= nes_read(0x1821); FLAG_NZ(g_cpu.A);
label_B9A1:;
    /* $B9A1: 25 */ maybe_trigger_vblank(3); g_cpu.A &= nes_read(0xFB); FLAG_NZ(g_cpu.A);
label_B9A3:;
    /* $B9A3: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_B9A4:;
    /* $B9A4: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) { maybe_trigger_vblank(2); goto label_BA20; }
label_B9A6:;
    /* $B9A6: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_B9A7:;
    /* $B9A7: 4B */ maybe_trigger_vblank(2); g_cpu.A &= 0xFB; g_cpu.C=g_cpu.A&1; g_cpu.A>>=1; FLAG_NZ(g_cpu.A);
label_B9A9:;
    /* $B9A9: 19 */ maybe_trigger_vblank(4); g_cpu.A |= nes_read((0x540F + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_B9AC:;
    /* $B9AC: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_B9AD:;
    /* $B9AD: 74 */ maybe_trigger_vblank(4); (void)nes_read((0xFB + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_B9AF:;
    /* $B9AF: 1E */ maybe_trigger_vblank(7); { uint16_t a=(0x2B12 + g_cpu.X) & 0xFFFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_B9B2:;
    /* $B9B2: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_B9B3:;
    /* $B9B3: 72 */ maybe_trigger_vblank(2); /* ILLEGAL $72 — skip 1 */
label_B9B4:;
    /* $B9B4: FB */ maybe_trigger_vblank(7); { uint16_t a=(0x0F1E + g_cpu.Y) & 0xFFFF; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); int16_t r=g_cpu.A-v-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,v); g_cpu.A=r&0xFF; }
label_B9B7:; /* ExitVH */
    /* $B9B7: 2D */ maybe_trigger_vblank(4); g_cpu.A &= nes_read(0x2C84); FLAG_NZ(g_cpu.A);
label_B9BA:; /* CannonBitmasks */
    /* $B9BA: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x822C); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_B9BD:;
    /* $B9BD: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x2C); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_B9BF:;
    /* $B9BF: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x85); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_B9C1:;
    /* $B9C1: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x2C84); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_B9C4:;
    /* $B9C4: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x2A2A); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_B9C7:;
    /* $B9C7: 2A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_B9C8:;
    /* $B9C8: 82 */ maybe_trigger_vblank(2); /* NOP */
label_B9CA:;
    /* $B9CA: 2A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_B9CB:;
    /* $B9CB: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x85); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_B9CD:;
    /* $B9CD: 2A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_B9CE:;
    /* $B9CE: 84 */ maybe_trigger_vblank(3); nes_write(0x2A, g_cpu.Y);
label_B9D0:;
    /* $B9D0: 2A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_B9D1:;
    /* $B9D1: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xB9D1); return;
label_B9D2:;
    /* $B9D2: 1F */ maybe_trigger_vblank(7); { uint16_t a=(0x1F1F + g_cpu.X) & 0xFFFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); g_cpu.A|=v; FLAG_NZ(g_cpu.A); }
label_B9D5:;
    /* $B9D5: 98 */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.Y; FLAG_NZ(g_cpu.A);
label_B9D6:;
    /* $B9D6: 1F */ maybe_trigger_vblank(7); { uint16_t a=(0x981F + g_cpu.X) & 0xFFFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); g_cpu.A|=v; FLAG_NZ(g_cpu.A); }
label_B9D9:;
    /* $B9D9: 9E */ maybe_trigger_vblank(5); /* ILLEGAL $9E — skip 3 */
label_B9DC:;
    /* $B9DC: 1D */ maybe_trigger_vblank(4); g_cpu.A |= nes_read((0x1D1D + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_B9DF:;
    /* $B9DF: 94 */ maybe_trigger_vblank(4); nes_write((0x1D + g_cpu.X) & 0xFF, g_cpu.Y);
label_B9E1:;
    /* $B9E1: 1D */ maybe_trigger_vblank(4); g_cpu.A |= nes_read((0x9C94 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_B9E4:;
    /* $B9E4: 94 */ maybe_trigger_vblank(4); nes_write((0x1D + g_cpu.X) & 0xFF, g_cpu.Y);
label_B9E6:;
    /* $B9E6: 86 */ maybe_trigger_vblank(3); nes_write(0x18, g_cpu.X);
label_B9E8:;
    /* $B9E8: 85 */ maybe_trigger_vblank(3); nes_write(0x26, g_cpu.A);
label_B9EA:;
    /* $B9EA: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) { maybe_trigger_vblank(1); call_by_address(0xB970); return; }
label_B9EC:;
    /* $B9EC: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x26); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_B9EE:;
    /* $B9EE: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) {
    maybe_trigger_vblank(1);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_B976;
    }
label_B9F0:;
    /* $B9F0: 14 */ maybe_trigger_vblank(4); (void)nes_read((0x85 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_B9F2:;
    /* $B9F2: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_B9F3:;
    /* $B9F3: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x0484); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_B9F6:;
    /* $B9F6: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_B9F7:;
    /* $B9F7: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0xD021); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_B9FA:;
    /* $B9FA: C4 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0xD0); int r=g_cpu.Y-m; g_cpu.C=(g_cpu.Y>=m)?1:0; FLAG_NZ(r&0xFF); }
label_B9FC:;
    /* $B9FC: 31 */ maybe_trigger_vblank(5); g_cpu.A &= nes_read((nes_read16zp(0xD0) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_B9FE:;
    /* $B9FE: C4 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0xD0); int r=g_cpu.Y-m; g_cpu.C=(g_cpu.Y>=m)?1:0; FLAG_NZ(r&0xFF); }
label_BA00:;
    /* $BA00: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xBA00); return;
label_BA01:;
    /* $BA01: 85 */ maybe_trigger_vblank(3); nes_write(0x2C, g_cpu.A);
label_BA03:;
    /* $BA03: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_BA04:;
    /* $BA04: 1C */ maybe_trigger_vblank(4); (void)nes_read((0x2684 + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BA07:;
    /* $BA07: 2A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_BA08:;
    /* $BA08: 82 */ maybe_trigger_vblank(2); /* NOP */
label_BA0A:;
    /* $BA0A: 26 */ maybe_trigger_vblank(5); { uint16_t a=0x04; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BA0C:;
    /* $BA0C: 87 */ maybe_trigger_vblank(3); nes_write(0x22, g_cpu.A & g_cpu.X); /* SAX */
label_BA0E:;
    /* $BA0E: 34 */ maybe_trigger_vblank(4); (void)nes_read((0x3A + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BA10:;
    /* $BA10: 82 */ maybe_trigger_vblank(2); /* NOP */
label_BA12:;
    /* $BA12: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x36); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BA14:;
    /* $BA14: 84 */ maybe_trigger_vblank(3); nes_write(0x3A, g_cpu.Y);
label_BA16:;
    /* $BA16: 34 */ maybe_trigger_vblank(4); (void)nes_read((0x82 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BA18:;
    /* $BA18: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x8530); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_BA1B:;
    /* $BA1B: 2A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_BA1C:;
    /* $BA1C: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xBA1C); return;
label_BA1D:;
    /* $BA1D: 5D */ maybe_trigger_vblank(4); g_cpu.A ^= nes_read((0x4D55 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_BA20:;
    /* $BA20: 15 */ maybe_trigger_vblank(4); g_cpu.A |= nes_read((0x19 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_BA22:;
    /* $BA22: 96 */ maybe_trigger_vblank(4); nes_write((0x15 + g_cpu.Y) & 0xFF, g_cpu.X);
label_BA24:;
    /* $BA24: D5 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0xE3 + g_cpu.X) & 0xFF); int r=g_cpu.A-m; g_cpu.C=(g_cpu.A>=m)?1:0; FLAG_NZ(r&0xFF); }
label_BA26:;
    /* $BA26: EB */ maybe_trigger_vblank(2); { uint8_t m=0x2D; int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_BA28:;
    /* $BA28: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x2B); FLAG_NZ(g_cpu.X);
label_BA2A:;
    /* $BA2A: 27 */ maybe_trigger_vblank(5); { uint16_t a=0x9C; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); g_cpu.A&=v; FLAG_NZ(g_cpu.A); }
label_BA2C:;
    /* $BA2C: 9E */ maybe_trigger_vblank(5); /* ILLEGAL $9E — skip 3 */
label_BA2F:;
    /* $BA2F: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_BA30:; /* ExCannon */
    /* $BA30: 1C */ maybe_trigger_vblank(4); (void)nes_read((0x8414 + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BA33:; /* BulletBillHandler */
    /* $BA33: 1E */ maybe_trigger_vblank(7); { uint16_t a=(0x8222 + g_cpu.X) & 0xFFFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BA36:;
    /* $BA36: 20 */ maybe_trigger_vblank(6); nes_dispatch_call(0x041E, -1);
label_BA39:;
    /* $BA39: 87 */ maybe_trigger_vblank(3); nes_write(0x1C, g_cpu.A & g_cpu.X); /* SAX */
label_BA3B:;
    /* $BA3B: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x8234); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_BA3E:;
    /* $BA3E: 36 */ maybe_trigger_vblank(6); { uint16_t a=(0x04 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BA40:;
    /* $BA40: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) { maybe_trigger_vblank(1); call_by_address(0xBA76); return; }
label_BA42:;
    /* $BA42: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x2C); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BA44:;
    /* $BA44: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x26); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BA46:;
    /* $BA46: 2A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_BA47:;
    /* $BA47: 85 */ maybe_trigger_vblank(3); nes_write(0x22, g_cpu.A);
label_BA49:;
    /* $BA49: 84 */ maybe_trigger_vblank(3); nes_write(0x04, g_cpu.Y);
label_BA4B:;
    /* $BA4B: 82 */ maybe_trigger_vblank(2); /* NOP */
label_BA4D:; /* SetupBB */
    /* $BA4D: 38 */ maybe_trigger_vblank(2); g_cpu.C = 1;
label_BA4E:;
    /* $BA4E: 36 */ maybe_trigger_vblank(6); { uint16_t a=(0x32 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BA50:;
    /* $BA50: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x34); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BA52:;
    /* $BA52: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x24); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BA54:;
    /* $BA54: 26 */ maybe_trigger_vblank(5); { uint16_t a=0x2C; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BA56:;
    /* $BA56: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x26); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BA58:;
    /* $BA58: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x0030); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_BA5B:;
    /* $BA5B: 05 */ maybe_trigger_vblank(3); g_cpu.A |= nes_read(0xB4); FLAG_NZ(g_cpu.A);
label_BA5D:;
    /* $BA5D: B2 */ maybe_trigger_vblank(2); /* ILLEGAL $B2 — skip 1 */
label_BA5E:;
    /* $BA5E: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { maybe_trigger_vblank(1); call_by_address(0xBA8B); return; }
label_BA60:;
    /* $BA60: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x9C84); FLAG_NZ(g_cpu.Y);
label_BA63:;
    /* $BA63: 9E */ maybe_trigger_vblank(5); /* ILLEGAL $9E — skip 3 */
label_BA66:;
    /* $BA66: 94 */ maybe_trigger_vblank(4); nes_write((0x9C + g_cpu.X) & 0xFF, g_cpu.Y);
label_BA68:;
    /* $BA68: 9E */ maybe_trigger_vblank(5); /* ILLEGAL $9E — skip 3 */
label_BA6B:;
    /* $BA6B: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_BA6C:;
    /* $BA6C: 84 */ maybe_trigger_vblank(3); nes_write(0x2C, g_cpu.Y);
label_BA6E:;
    /* $BA6E: 85 */ maybe_trigger_vblank(3); nes_write(0x1E, g_cpu.A);
label_BA70:;
    /* $BA70: 82 */ maybe_trigger_vblank(2); /* NOP */
label_BA72:;
    /* $BA72: 84 */ maybe_trigger_vblank(3); nes_write(0x2C, g_cpu.Y);
label_BA74:;
    /* $BA74: 1E */ maybe_trigger_vblank(7); { uint16_t a=(0x0484 + g_cpu.X) & 0xFFFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BA77:;
    /* $BA77: 82 */ maybe_trigger_vblank(2); /* NOP */
label_BA79:;
    /* $BA79: 38 */ maybe_trigger_vblank(2); g_cpu.C = 1;
label_BA7A:;
    /* $BA7A: 36 */ maybe_trigger_vblank(6); { uint16_t a=(0x32 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BA7C:;
    /* $BA7C: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x34); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BA7E:;
    /* $BA7E: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x64); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BA80:;
    /* $BA80: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x64); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BA82:;
    /* $BA82: 86 */ maybe_trigger_vblank(3); nes_write(0x64, g_cpu.X);
label_BA84:;
    /* $BA84: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xBA84); return;
label_BA85:; /* KillBB */
    /* $BA85: 05 */ maybe_trigger_vblank(3); g_cpu.A |= nes_read(0xB4); FLAG_NZ(g_cpu.A);
label_BA87:;
    /* $BA87: B2 */ maybe_trigger_vblank(2); /* ILLEGAL $B2 — skip 1 */
label_BA88:;
    /* $BA88: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { maybe_trigger_vblank(1); call_by_address(0xBAB5); return; }
label_BA8A:;
    /* $BA8A: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x3784); FLAG_NZ(g_cpu.Y);
label_BA8D:;
    /* $BA8D: B6 */ maybe_trigger_vblank(4); g_cpu.X = nes_read((0xB6 + g_cpu.Y) & 0xFF); FLAG_NZ(g_cpu.X);
label_BA8F:;
    /* $BA8F: 45 */ maybe_trigger_vblank(3); g_cpu.A ^= nes_read(0x85); FLAG_NZ(g_cpu.A);
label_BA91:;
    /* $BA91: 14 */ maybe_trigger_vblank(4); (void)nes_read((0x1C + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BA93:;
    /* $BA93: 82 */ maybe_trigger_vblank(2); /* NOP */
label_BA95:;
    /* $BA95: 84 */ maybe_trigger_vblank(3); nes_write(0x2C, g_cpu.Y);
label_BA97:;
    /* $BA97: 4E */ maybe_trigger_vblank(6); { uint16_t a=0x4E82; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_BA9A:;
    /* $BA9A: 84 */ maybe_trigger_vblank(3); nes_write(0x4E, g_cpu.Y);
label_BA9C:;
    /* $BA9C: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_BA9D:;
    /* $BA9D: 84 */ maybe_trigger_vblank(3); nes_write(0x04, g_cpu.Y);
label_BA9F:;
    /* $BA9F: 85 */ maybe_trigger_vblank(3); nes_write(0x32, g_cpu.A);
label_BAA1:;
    /* $BAA1: 85 */ maybe_trigger_vblank(3); nes_write(0x30, g_cpu.A);
label_BAA3:;
    /* $BAA3: 86 */ maybe_trigger_vblank(3); nes_write(0x2C, g_cpu.X);
label_BAA5:;
    /* $BAA5: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x00); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BAA7:;
    /* $BAA7: 05 */ maybe_trigger_vblank(3); g_cpu.A |= nes_read(0xA4); FLAG_NZ(g_cpu.A);
label_BAA9:;
    /* $BAA9: 05 */ maybe_trigger_vblank(3); g_cpu.A |= nes_read(0x9E); FLAG_NZ(g_cpu.A);
label_BAAB:;
    /* $BAAB: 05 */ maybe_trigger_vblank(3); g_cpu.A |= nes_read(0x9D); FLAG_NZ(g_cpu.A);
label_BAAD:;
    /* $BAAD: 85 */ maybe_trigger_vblank(3); nes_write(0x84, g_cpu.A);
label_BAAF:;
    /* $BAAF: 14 */ maybe_trigger_vblank(4); (void)nes_read((0x85 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BAB1:;
    /* $BAB1: 24 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x28); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_BAB3:;
    /* $BAB3: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x2282); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_BAB6:;
    /* $BAB6: 84 */ maybe_trigger_vblank(3); nes_write(0x22, g_cpu.Y);
label_BAB8:;
    /* $BAB8: 14 */ maybe_trigger_vblank(4); (void)nes_read((0x21 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BABA:;
    /* $BABA: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) {
    maybe_trigger_vblank(1);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_BA80;
    }
label_BABC:;
    /* $BABC: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_BAEF; }
label_BABE:;
    /* $BABE: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) {
    maybe_trigger_vblank(1);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_BA84;
    }
label_BAC0:;
    /* $BAC0: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_BAC2; }
label_BAC2:;
    /* $BAC2: 82 */ maybe_trigger_vblank(2); /* NOP */
label_BAC4:;
    /* $BAC4: 84 */ maybe_trigger_vblank(3); nes_write(0x2C, g_cpu.Y);
label_BAC6:;
    /* $BAC6: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x2C82); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_BAC9:;
    /* $BAC9: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) { maybe_trigger_vblank(1); goto label_BACF; }
label_BACB:;
    /* $BACB: 34 */ maybe_trigger_vblank(4); (void)nes_read((0x2C + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BACD:;
    /* $BACD: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x26); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BACF:;
    /* $BACF: 86 */ maybe_trigger_vblank(3); nes_write(0x22, g_cpu.X);
label_BAD1:;
    /* $BAD1: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xBAD1); return;
label_BAD2:;
    /* $BAD2: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0x25); FLAG_NZ(g_cpu.Y);
label_BAD4:;
    /* $BAD4: 25 */ maybe_trigger_vblank(3); g_cpu.A &= nes_read(0xA4); FLAG_NZ(g_cpu.A);
label_BAD6:;
    /* $BAD6: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0xA2; FLAG_NZ(g_cpu.A);
label_BAD8:;
    /* $BAD8: 1D */ maybe_trigger_vblank(4); g_cpu.A |= nes_read((0x959C + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_BADB:;
    /* $BADB: 82 */ maybe_trigger_vblank(2); /* NOP */
label_BADD:;
    /* $BADD: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x2C04); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_BAE0:;
    /* $BAE0: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x2C); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BAE2:;
    /* $BAE2: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) { maybe_trigger_vblank(1); call_by_address(0xBA69); return; }
label_BAE4:;
    /* $BAE4: 34 */ maybe_trigger_vblank(4); (void)nes_read((0x04 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BAE6:;
    /* $BAE6: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x00); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BAE8:;
    /* $BAE8: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0x25); FLAG_NZ(g_cpu.Y);
label_BAEA:;
    /* $BAEA: 25 */ maybe_trigger_vblank(3); g_cpu.A &= nes_read(0xA4); FLAG_NZ(g_cpu.A);
label_BAEC:;
    /* $BAEC: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_BAED:;
    /* $BAED: 63 */ maybe_trigger_vblank(8); { uint16_t a=nes_read16zp((0x04 + g_cpu.X) & 0xFF); uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=v&1; v=((v>>1)|(c<<7))&0xFF; nes_write(a,v); uint16_t r=g_cpu.A+v+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,v); g_cpu.A=r&0xFF; }
label_BAEF:;
    /* $BAEF: 85 */ maybe_trigger_vblank(3); nes_write(0x0E, g_cpu.A);
label_BAF1:;
    /* $BAF1: 1A */ maybe_trigger_vblank(2); /* NOP */
label_BAF2:;
    /* $BAF2: 84 */ maybe_trigger_vblank(3); nes_write(0x24, g_cpu.Y);
label_BAF4:;
    /* $BAF4: 85 */ maybe_trigger_vblank(3); nes_write(0x22, g_cpu.A);
label_BAF6:;
    /* $BAF6: 14 */ maybe_trigger_vblank(4); (void)nes_read((0x84 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BAF8:;
    /* $BAF8: 0C */ maybe_trigger_vblank(4); (void)nes_read(0x3482); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BAFB:;
    /* $BAFB: 84 */ maybe_trigger_vblank(3); nes_write(0x34, g_cpu.Y);
label_BAFD:;
    /* $BAFD: 34 */ maybe_trigger_vblank(4); (void)nes_read((0x82 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BAFF:;
    /* $BAFF: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x3484); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_BB02:;
    /* $BB02: 86 */ maybe_trigger_vblank(3); nes_write(0x3A, g_cpu.X);
label_BB04:;
    /* $BB04: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x00); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BB06:;
    /* $BB06: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x21; FLAG_NZ(g_cpu.Y);
label_BB08:;
    /* $BB08: 21 */ maybe_trigger_vblank(6); g_cpu.A &= nes_read(nes_read16zp((0xA0 + g_cpu.X) & 0xFF)); FLAG_NZ(g_cpu.A);
label_BB0A:;
    /* $BB0A: 21 */ maybe_trigger_vblank(6); g_cpu.A &= nes_read(nes_read16zp((0x2B + g_cpu.X) & 0xFF)); FLAG_NZ(g_cpu.A);
label_BB0C:;
    /* $BB0C: 05 */ maybe_trigger_vblank(3); g_cpu.A |= nes_read(0xA3); FLAG_NZ(g_cpu.A);
label_BB0E:;
    /* $BB0E: 82 */ maybe_trigger_vblank(2); /* NOP */
label_BB10:;
    /* $BB10: 84 */ maybe_trigger_vblank(3); nes_write(0x18, g_cpu.Y);
label_BB12:;
    /* $BB12: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_BB13:;
    /* $BB13: 82 */ maybe_trigger_vblank(2); /* NOP */
label_BB15:;
    /* $BB15: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_BB16:;
    /* $BB16: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x86); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BB18:;
    /* $BB18: 3A */ maybe_trigger_vblank(2); /* NOP */
label_BB19:;
    /* $BB19: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_BB1A:;
    /* $BB1A: 31 */ maybe_trigger_vblank(5); g_cpu.A &= nes_read((nes_read16zp(0x90) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_BB1C:;
    /* $BB1C: 31 */ maybe_trigger_vblank(5); g_cpu.A &= nes_read((nes_read16zp(0x90) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_BB1E:;
    /* $BB1E: 31 */ maybe_trigger_vblank(5); g_cpu.A &= nes_read((nes_read16zp(0x71) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_BB20:;
    /* $BB20: 31 */ maybe_trigger_vblank(5); g_cpu.A &= nes_read((nes_read16zp(0x90) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_BB22:;
    /* $BB22: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) { maybe_trigger_vblank(2); call_by_address(0xBAB4); return; }
label_BB24:;
    /* $BB24: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xBB24); return;
label_BB25:;
    /* $BB25: 82 */ maybe_trigger_vblank(2); /* NOP */
label_BB27:;
    /* $BB27: 84 */ maybe_trigger_vblank(3); nes_write(0x2C, g_cpu.Y);
label_BB29:;
    /* $BB29: 85 */ maybe_trigger_vblank(3); nes_write(0x22, g_cpu.A);
label_BB2B:; /* RunHSubs */
    /* $BB2B: 84 */ maybe_trigger_vblank(3); nes_write(0x24, g_cpu.Y);
label_BB2D:;
    /* $BB2D: 82 */ maybe_trigger_vblank(2); /* NOP */
label_BB2F:;
    /* $BB2F: 36 */ maybe_trigger_vblank(6); { uint16_t a=(0x04 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BB31:;
    /* $BB31: 36 */ maybe_trigger_vblank(6); { uint16_t a=(0x86 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BB33:;
    /* $BB33: 26 */ maybe_trigger_vblank(5); { uint16_t a=0x00; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BB35:;
    /* $BB35: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x5D27); FLAG_NZ(g_cpu.Y);
label_BB38:; /* CoinBlock */
    /* $BB38: 1D */ maybe_trigger_vblank(4); g_cpu.A |= nes_read((0x2D9E + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_BB3B:;
    /* $BB3B: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x859F); FLAG_NZ(g_cpu.Y);
label_BB3E:;
    /* $BB3E: 14 */ maybe_trigger_vblank(4); (void)nes_read((0x82 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BB40:;
    /* $BB40: 20 */ maybe_trigger_vblank(6); nes_dispatch_call(0x2284, -1);
label_BB43:;
    /* $BB43: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x1E1E); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_BB46:;
    /* $BB46: 82 */ maybe_trigger_vblank(2); /* NOP */
label_BB48:;
    /* $BB48: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x041E); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_BB4B:;
    /* $BB4B: 87 */ maybe_trigger_vblank(3); nes_write(0x2A, g_cpu.A & g_cpu.X); /* SAX */
label_BB4D:;
    /* $BB4D: 40 */ maybe_trigger_vblank(6); /* RTI */ g_rti_source = 0xBB4D; g_rti_bank = 1; g_cpu.S++; { uint8_t p=g_ram[0x100+g_cpu.S]; g_cpu.N=(p>>7)&1; g_cpu.V=(p>>6)&1; g_cpu.D=(p>>3)&1; g_cpu.I=(p>>2)&1; g_cpu.Z=(p>>1)&1; g_cpu.C=p&1; }
    g_cpu.S++; { uint8_t _rti_lo = g_ram[0x100+g_cpu.S];
    g_cpu.S++; uint8_t _rti_hi = g_ram[0x100+g_cpu.S];
    g_rti_target = (_rti_hi << 8) | _rti_lo; }
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
    return;
label_BB4E:;
    /* $BB4E: 40 */ maybe_trigger_vblank(6); /* RTI */ g_rti_source = 0xBB4E; g_rti_bank = 1; g_cpu.S++; { uint8_t p=g_ram[0x100+g_cpu.S]; g_cpu.N=(p>>7)&1; g_cpu.V=(p>>6)&1; g_cpu.D=(p>>3)&1; g_cpu.I=(p>>2)&1; g_cpu.Z=(p>>1)&1; g_cpu.C=p&1; }
    g_cpu.S++; { uint8_t _rti_lo = g_ram[0x100+g_cpu.S];
    g_cpu.S++; uint8_t _rti_hi = g_ram[0x100+g_cpu.S];
    g_rti_target = (_rti_hi << 8) | _rti_lo; }
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
    return;
label_BB4F:;
    /* $BB4F: 40 */ maybe_trigger_vblank(6); /* RTI */ g_rti_source = 0xBB4F; g_rti_bank = 1; g_cpu.S++; { uint8_t p=g_ram[0x100+g_cpu.S]; g_cpu.N=(p>>7)&1; g_cpu.V=(p>>6)&1; g_cpu.D=(p>>3)&1; g_cpu.I=(p>>2)&1; g_cpu.Z=(p>>1)&1; g_cpu.C=p&1; }
    g_cpu.S++; { uint8_t _rti_lo = g_ram[0x100+g_cpu.S];
    g_cpu.S++; uint8_t _rti_hi = g_ram[0x100+g_cpu.S];
    g_rti_target = (_rti_hi << 8) | _rti_lo; }
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
    return;
label_BB50:;
    /* $BB50: 3A */ maybe_trigger_vblank(2); /* NOP */
label_BB51:; /* SetupJumpCoin */
    /* $BB51: 36 */ maybe_trigger_vblank(6); { uint16_t a=(0x82 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BB53:;
    /* $BB53: 34 */ maybe_trigger_vblank(4); (void)nes_read((0x2C + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BB55:;
    /* $BB55: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x26); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BB57:;
    /* $BB57: 86 */ maybe_trigger_vblank(3); nes_write(0x22, g_cpu.X);
label_BB59:;
    /* $BB59: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xBB59); return;
label_BB5A:;
    /* $BB5A: E3 */ maybe_trigger_vblank(8); { uint16_t a=nes_read16zp((0xF7 + g_cpu.X) & 0xFF); uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); int16_t r=g_cpu.A-v-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,v); g_cpu.A=r&0xFF; }
label_BB5C:;
    /* $BB5C: F7 */ maybe_trigger_vblank(6); { uint16_t a=(0xF7 + g_cpu.X) & 0xFF; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); int16_t r=g_cpu.A-v-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,v); g_cpu.A=r&0xFF; }
label_BB5E:;
    /* $BB5E: F5 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0xF1 + g_cpu.X) & 0xFF); int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_BB60:;
    /* $BB60: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x9E27); FLAG_NZ(g_cpu.Y);
label_BB63:;
    /* $BB63: 9D */ maybe_trigger_vblank(5); nes_write((0x1885 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_BB66:;
    /* $BB66: 82 */ maybe_trigger_vblank(2); /* NOP */
label_BB68:;
    /* $BB68: 84 */ maybe_trigger_vblank(3); nes_write(0x22, g_cpu.Y);
label_BB6A:;
    /* $BB6A: 2A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_BB6B:;
    /* $BB6B: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_BB6C:; /* JCoinC */
    /* $BB6C: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_BB6D:;
    /* $BB6D: 82 */ maybe_trigger_vblank(2); /* NOP */
label_BB6F:;
    /* $BB6F: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x0422); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_BB72:;
    /* $BB72: 86 */ maybe_trigger_vblank(3); nes_write(0x04, g_cpu.X);
label_BB74:;
    /* $BB74: 82 */ maybe_trigger_vblank(2); /* NOP */
label_BB76:;
    /* $BB76: 36 */ maybe_trigger_vblank(6); { uint16_t a=(0x04 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BB78:;
    /* $BB78: 36 */ maybe_trigger_vblank(6); { uint16_t a=(0x87 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BB7A:;
    /* $BB7A: 36 */ maybe_trigger_vblank(6); { uint16_t a=(0x34 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BB7C:;
    /* $BB7C: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) {
    maybe_trigger_vblank(1);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_BB04;
    }
label_BB7E:;
    /* $BB7E: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x0004); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_BB81:;
    /* $BB81: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xBB81); return;
label_BB82:;
    /* $BB82: 68 */ maybe_trigger_vblank(4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_BB83:;
    /* $BB83: 6A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=g_cpu.A&1; g_cpu.A=((g_cpu.A>>1)|(c<<7))&0xFF; FLAG_NZ(g_cpu.A); }
label_BB84:; /* FindEmptyMiscSlot */
    /* $BB84: 6C */ maybe_trigger_vblank(5); { uint16_t _jt = nes_read16_jmpbug(0xA245); nes_trace_indirect_jump(0xBB84, _jt); maybe_trigger_vblank(2); call_by_address_tail(_jt, -1); return; }
label_BFC6:;
    /* $BFC6: 95 */ maybe_trigger_vblank(4); nes_write((0x95 + g_cpu.X) & 0xFF, g_cpu.A);
label_BFC8:;
    /* $BFC8: 94 */ maybe_trigger_vblank(4); nes_write((0x93 + g_cpu.X) & 0xFF, g_cpu.Y);
label_BFCA:;
    /* $BFCA: 15 */ maybe_trigger_vblank(4); g_cpu.A |= nes_read((0x16 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_BFCC:;
    /* $BFCC: 16 */ maybe_trigger_vblank(6); { uint16_t a=(0x17 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BFCE:;
    /* $BFCE: 17 */ maybe_trigger_vblank(6); { uint16_t a=(0x18 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); g_cpu.A|=v; FLAG_NZ(g_cpu.A); }
label_BFD0:;
    /* $BFD0: 19 */ maybe_trigger_vblank(4); g_cpu.A |= nes_read((0x1A19 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_BFD3:;
    /* $BFD3: 1A */ maybe_trigger_vblank(2); /* NOP */
label_BFD4:;
    /* $BFD4: 1C */ maybe_trigger_vblank(4); (void)nes_read((0x1D1D + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BFD7:; /* ImposeGravity */
    /* $BFD7: 1E */ maybe_trigger_vblank(7); { uint16_t a=(0x1F1E + g_cpu.X) & 0xFFFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BFDA:;
    /* $BFDA: 1F */ maybe_trigger_vblank(7); { uint16_t a=(0x1F1F + g_cpu.X) & 0xFFFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); g_cpu.A|=v; FLAG_NZ(g_cpu.A); }
label_BFDD:;
    /* $BFDD: 1E */ maybe_trigger_vblank(7); { uint16_t a=(0x1C1D + g_cpu.X) & 0xFFFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BFE0:;
    /* $BFE0: 1E */ maybe_trigger_vblank(7); { uint16_t a=(0x1F1F + g_cpu.X) & 0xFFFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BFE3:;
    /* $BFE3: 1E */ maybe_trigger_vblank(7); { uint16_t a=(0x1C1D + g_cpu.X) & 0xFFFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BFE6:;
    /* $BFE6: 1A */ maybe_trigger_vblank(2); /* NOP */
label_BFE7:;
    /* $BFE7: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_BFE8:;
    /* $BFE8: 16 */ maybe_trigger_vblank(6); { uint16_t a=(0x14 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BFEA:;
    /* $BFEA: 15 */ maybe_trigger_vblank(4); g_cpu.A |= nes_read((0x16 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_BFEC:;
    /* $BFEC: 16 */ maybe_trigger_vblank(6); { uint16_t a=(0x17 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BFEE:;
    /* $BFEE: 17 */ maybe_trigger_vblank(6); { uint16_t a=(0x18 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); g_cpu.A|=v; FLAG_NZ(g_cpu.A); }
label_BFF0:;
    /* $BFF0: 19 */ maybe_trigger_vblank(4); g_cpu.A |= nes_read((0x1A19 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_BFF3:;
    /* $BFF3: 1A */ maybe_trigger_vblank(2); /* NOP */
label_BFF4:;
    /* $BFF4: 1C */ maybe_trigger_vblank(4); (void)nes_read((0x1D1D + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BFF7:;
    /* $BFF7: 1E */ maybe_trigger_vblank(7); { uint16_t a=(0x1F1E + g_cpu.X) & 0xFFFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BFFA:;
    /* $BFFA: 82 */ maybe_trigger_vblank(2); /* NOP */
label_BFFC:;
    /* $BFFC: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xBFFC); return;
label_BB87:; return;
label_BB89:; return;
label_BB8B:; return;
label_BB8D:; return;
label_BB90:; return;
label_BB92:; return;
label_BB94:; return;
label_BB96:; return;
label_BB98:; return;
label_BB9A:; return;
label_BB9C:; return;
label_BB9D:; return;
label_BB9F:; return;
label_BBA1:; return;
label_BBA3:; return;
label_BBA4:; return;
label_BBA6:; return;
label_BBA7:; return;
label_BBA8:; return;
label_BBAA:; return;
label_BBAC:; return;
label_BBAE:; return;
label_BBAF:; return;
label_BBB0:; return;
label_BBB1:; return;
label_BBB2:; return;
label_BBB3:; return;
label_BBB4:; return;
label_BBB6:; return;
label_BBB7:; return;
label_BBB8:; return;
label_BBBA:; return;
label_BBBC:; return;
label_BBBE:; return;
label_BBBF:; return;
label_BBC0:; return;
label_BBC1:; return;
label_BBC2:; return;
label_BBC3:; return;
label_BBC4:; return;
label_BBC6:; return;
label_BBC8:; return;
label_BBCA:; return;
label_BBCC:; return;
label_BBCD:; return;
label_BBD0:; return;
label_BBD1:; return;
label_BBD4:; return;
label_BBD6:; return;
label_BBD8:; return;
label_BBDA:; return;
label_BBDC:; return;
label_BBDD:; return;
label_BBE0:; return;
label_BBE1:; return;
label_BBE4:; return;
label_BBE6:; return;
label_BBE8:; return;
label_BBE9:; return;
label_BBEA:; return;
label_BBEC:; return;
label_BBEF:; return;
label_BBF0:; return;
label_BBF3:; return;
label_BBF4:; return;
label_BBF7:; return;
label_BBF8:; return;
label_BBF9:; return;
label_BBFA:; return;
label_BBFC:; return;
label_BBFF:; return;
label_BC00:; return;
label_BC03:; return;
label_BC04:; return;
label_BC07:; return;
label_BC09:; return;
label_BC10:; return;
label_BC13:; return;
label_BC15:; return;
label_BC17:; return;
label_BC1A:; return;
label_BC1C:; return;
label_BC1E:; return;
label_BC24:; return;
label_BC26:; return;
label_BC77:; return;
label_BC79:; return;
label_BC7C:; return;
label_BC7D:; return;
label_BC7E:; return;
label_BC80:; return;
label_BC82:; return;
label_BC84:; return;
label_BC86:; return;
label_BC88:; return;
label_BC8A:; return;
label_BC8C:; return;
label_BC8E:; return;
label_BC8F:; return;
label_BC91:; return;
label_BC93:; return;
label_BC94:; return;
label_BC95:; return;
label_BC96:; return;
label_BC97:; return;
label_BC99:; return;
label_BC9B:; return;
label_BC9C:; return;
label_BC9E:; return;
label_BC9F:; return;
label_BCA1:; return;
label_BCA3:; return;
label_BCA5:; return;
label_BCA7:; return;
label_BCA9:; return;
label_BCAB:; return;
label_BCAD:; return;
label_BCAF:; return;
label_BCB0:; return;
label_BCB2:; return;
label_BCB4:; return;
label_BCB6:; return;
label_BCB7:; return;
label_BCB9:; return;
label_BCBA:; return;
label_BCBC:; return;
label_BCBD:; return;
label_BCC0:; return;
label_BCC2:; return;
label_BCC5:; return;
label_BCC7:; return;
label_BCC9:; return;
label_BCCC:; return;
label_BCCE:; return;
label_BCD0:; return;
label_BCD1:; return;
label_BCD4:; return;
label_BCD6:; return;
label_BCD8:; return;
label_BCDA:; return;
label_BCDC:; return;
label_BCDE:; return;
label_BCE0:; return;
label_BCE2:; return;
label_BCE5:; return;
label_BCE7:; return;
label_BCEA:; return;
label_BCED:; return;
label_BCEF:; return;
label_BCF1:; return;
label_BCF4:; return;
label_BCF6:; return;
label_BCF9:; return;
label_BCFB:; return;
label_BCFD:; return;
label_BCFF:; return;
label_BD00:; return;
label_BD02:; return;
label_BD04:; return;
label_BD06:; return;
label_BD07:; return;
label_BD0A:; return;
label_BD0C:; return;
label_BD0E:; return;
label_BD10:; return;
label_BD13:; return;
label_BD16:; return;
label_BD18:; return;
label_BD1A:; return;
label_BD1C:; return;
label_BD1F:; return;
label_BD21:; return;
label_BD23:; return;
label_BD25:; return;
label_BD28:; return;
label_BD29:; return;
label_BD2A:; return;
label_BD2C:; return;
label_BD2E:; return;
label_BD31:; return;
label_BD32:; return;
label_BD33:; return;
label_BD35:; return;
label_BD37:; return;
label_BD38:; return;
label_BD3A:; return;
label_BD3C:; return;
label_BD3D:; return;
label_BD40:; return;
label_BD42:; return;
label_BD45:; return;
label_BD46:; return;
label_BD48:; return;
label_BD4A:; return;
label_BD4B:; return;
label_BD4D:; return;
label_BD50:; return;
label_BD52:; return;
label_BD54:; return;
label_BD57:; return;
label_BD59:; return;
label_BD5B:; return;
label_BD5C:; return;
label_BD5D:; return;
label_BD5F:; return;
label_BD61:; return;
label_BD62:; return;
label_BD64:; return;
label_BD66:; return;
label_BD67:; return;
label_BD69:; return;
label_BD6B:; return;
label_BD6D:; return;
label_BD70:; return;
label_BD72:; return;
label_BD73:; return;
label_BD75:; return;
label_BD77:; return;
label_BD79:; return;
label_BD7B:; return;
label_BD7D:; return;
label_BD80:; return;
label_BD82:; return;
label_BD84:; return;
label_BD87:; return;
label_BD89:; return;
label_BD8A:; return;
label_BD8C:; return;
label_BD8E:; return;
label_BD90:; return;
label_BD92:; return;
label_BD94:; return;
label_BD95:; return;
label_BD96:; return;
label_BD98:; return;
label_BD9A:; return;
label_BD9C:; return;
label_BD9E:; return;
label_BDA0:; return;
label_BDA2:; return;
label_BDA4:; return;
label_BDA6:; return;
label_BDA8:; return;
label_BDAA:; return;
label_BDAC:; return;
label_BDAE:; return;
label_BDAF:; return;
label_BDB1:; return;
label_BDB3:; return;
label_BDB5:; return;
label_BDB7:; return;
label_BDB9:; return;
label_BDBA:; return;
label_BDBC:; return;
label_BDBE:; return;
label_BDC0:; return;
label_BDC2:; return;
label_BDC3:; return;
label_BDC5:; return;
label_BDC6:; return;
label_BDC8:; return;
label_BDC9:; return;
label_BDCA:; return;
label_BDCB:; return;
label_BDCD:; return;
label_BDCF:; return;
label_BDD1:; return;
label_BDD3:; return;
label_BDD5:; return;
label_BDD7:; return;
label_BDD9:; return;
label_BDDC:; return;
label_BDDF:; return;
label_BDE1:; return;
label_BDE3:; return;
label_BDE6:; return;
label_BDE9:; return;
label_BDEB:; return;
label_BDED:; return;
label_BDEE:; return;
label_BDEF:; return;
label_BDF1:; return;
label_BDF4:; return;
label_BDF6:; return;
label_BDF7:; return;
label_BDF9:; return;
label_BDFB:; return;
label_BDFC:; return;
label_BDFF:; return;
label_BE00:; return;
label_BE02:; return;
label_BE05:; return;
label_BE08:; return;
label_BE0B:; return;
label_BE0C:; return;
label_BE0E:; return;
label_BE11:; return;
label_BE14:; return;
label_BE15:; return;
label_BE17:; return;
label_BE18:; return;
label_BE19:; return;
label_BE1A:; return;
label_BE1B:; return;
label_BE1C:; return;
label_BE1D:; return;
label_BE1E:; return;
label_BE1F:; return;
label_BE20:; return;
label_BE21:; return;
label_BE22:; return;
label_BE23:; return;
label_BE24:; return;
label_BE26:; return;
label_BE29:; return;
label_BE2C:; return;
label_BE2E:; return;
label_BE2F:; return;
label_BE31:; return;
label_BE32:; return;
label_BE35:; return;
label_BE37:; return;
label_BE39:; return;
label_BE3B:; return;
label_BE3D:; return;
label_BE3F:; return;
label_BE40:; return;
label_BE41:; return;
label_BE43:; return;
label_BE44:; return;
label_BE46:; return;
label_BE47:; return;
label_BE48:; return;
label_BE4A:; return;
label_BE4D:; return;
label_BE4F:; return;
label_BE51:; return;
label_BE53:; return;
label_BE54:; return;
label_BE57:; return;
label_BE5A:; return;
label_BE5C:; return;
label_BE5F:; return;
label_BE62:; return;
label_BE64:; return;
label_BE66:; return;
label_BE67:; return;
label_BE68:; return;
label_BE69:; return;
label_BE6A:; return;
label_BE6B:; return;
label_BE6C:; return;
label_BE6E:; return;
label_BE70:; return;
label_BE72:; return;
label_BE74:; return;
label_BE75:; return;
label_BE78:; return;
label_BE7B:; return;
label_BE7E:; return;
label_BE81:; return;
label_BE84:; return;
label_BE87:; return;
label_BE8A:; return;
label_BE8D:; return;
label_BE90:; return;
label_BE91:; return;
label_BE93:; return;
label_BE94:; return;
label_BE96:; return;
label_BE97:; return;
label_BE98:; return;
label_BE99:; return;
label_BE9B:; return;
label_BE9D:; return;
label_BE9F:; return;
label_BEA1:; return;
label_BEA3:; return;
label_BEA5:; return;
label_BEA7:; return;
label_BEA9:; return;
label_BEAB:; return;
label_BEAD:; return;
label_BEAF:; return;
label_BEB1:; return;
label_BEB3:; return;
label_BEB5:; return;
label_BEB7:; return;
label_BEB8:; return;
label_BEB9:; return;
label_BEBA:; return;
label_BEBB:; return;
label_BEBC:; return;
label_BEBD:; return;
label_BEBF:; return;
label_BEC0:; return;
label_BEC2:; return;
label_BEC4:; return;
label_BEC7:; return;
label_BEC9:; return;
label_BECB:; return;
label_BECE:; return;
label_BED0:; return;
label_BED1:; return;
label_BED3:; return;
label_BED4:; return;
label_BED7:; return;
label_BED8:; return;
label_BEDB:; return;
label_BEDC:; return;
label_BEDE:; return;
label_BEE0:; return;
label_BEE3:; return;
label_BEE6:; return;
label_BEE8:; return;
label_BEEA:; return;
label_BEEC:; return;
label_BEEE:; return;
label_BEF0:; return;
label_BEF1:; return;
label_BEF2:; return;
label_BEF5:; return;
label_BEF6:; return;
label_BEF9:; return;
label_BEFC:; return;
label_BEFE:; return;
label_BF01:; return;
label_BF02:; return;
label_BF03:; return;
label_BF06:; return;
label_BF07:; return;
label_BF09:; return;
label_BF0B:; return;
label_BF0E:; return;
label_BF0F:; return;
label_BF10:; return;
label_BF12:; return;
label_BF14:; return;
label_BF16:; return;
label_BF18:; return;
label_BF1A:; return;
label_BF1C:; return;
label_BF1E:; return;
label_BF20:; return;
label_BF22:; return;
label_BF24:; return;
label_BF26:; return;
label_BF27:; return;
label_BF2A:; return;
label_BF2B:; return;
label_BF2D:; return;
label_BF2F:; return;
label_BF31:; return;
label_BF34:; return;
label_BF35:; return;
label_BF37:; return;
label_BF39:; return;
label_BF3B:; return;
label_BF3E:; return;
label_BF3F:; return;
label_BF41:; return;
label_BF44:; return;
label_BF45:; return;
label_BF47:; return;
label_BF49:; return;
label_BF4C:; return;
label_BF4D:; return;
label_BF4F:; return;
label_BF51:; return;
label_BF53:; return;
label_BF56:; return;
label_BF57:; return;
label_BF58:; return;
label_BF59:; return;
label_BF5B:; return;
label_BF5D:; return;
label_BF5F:; return;
label_BF62:; return;
label_BF64:; return;
label_BF65:; return;
label_BF66:; return;
label_BF68:; return;
label_BF6A:; return;
label_BF6C:; return;
label_BF6F:; return;
label_BF70:; return;
label_BF72:; return;
label_BF73:; return;
label_BF74:; return;
label_BF76:; return;
label_BF78:; return;
label_BF7B:; return;
label_BF7C:; return;
label_BF7E:; return;
label_BF80:; return;
label_BF82:; return;
label_BF83:; return;
label_BF86:; return;
label_BF88:; return;
label_BF8A:; return;
label_BF8D:; return;
label_BF8E:; return;
label_BF8F:; return;
label_BF91:; return;
label_BF92:; return;
label_BF94:; return;
label_BF97:; return;
label_BF9A:; return;
label_BF9C:; return;
label_BF9E:; return;
label_BFA0:; return;
label_BFA2:; return;
label_BFA4:; return;
label_BFA5:; return;
label_BFA6:; return;
label_BFA8:; return;
label_BFAA:; return;
label_BFAC:; return;
label_BFAE:; return;
label_BFB0:; return;
label_BFB2:; return;
label_BFB4:; return;
label_BFB6:; return;
label_BFB8:; return;
label_BFBA:; return;
label_BFBC:; return;
label_BFBE:; return;
label_BFC0:; return;
label_BFC2:; return;
label_BFC4:; return;
label_BFFD:; return;
label_BFFF:; return;
label_C002:; return;
label_C004:; return;
label_C006:; return;
label_C008:; return;
label_C00B:; return;
label_C00D:; return;
label_C00F:; return;
label_C011:; return;
label_C013:; return;
label_C015:; return;
label_C018:; return;
label_C019:; return;
label_C01B:; return;
label_C01D:; return;
label_C01F:; return;
label_C020:; return;
label_C021:; return;
label_C023:; return;
label_C026:; return;
label_C027:; return;
label_C029:; return;
label_C02C:; return;
label_C02E:; return;
label_C030:; return;
label_C032:; return;
label_C034:; return;
label_C036:; return;
label_C039:; return;
label_C03B:; return;
label_C03D:; return;
label_C03F:; return;
label_C041:; return;
label_C043:; return;
label_C046:; return;
label_C047:; return;
label_C049:; return;
label_C04A:; return;
label_C04B:; return;
label_C04D:; return;
label_C04E:; return;
label_C050:; return;
label_C053:; return;
label_C056:; return;
label_C058:; return;
label_C05A:; return;
label_C05C:; return;
label_C05F:; return;
label_C060:; return;
label_C062:; return;
label_C063:; return;
label_C066:; return;
label_C068:; return;
label_C06A:; return;
label_C06B:; return;
label_C06D:; return;
label_C06F:; return;
label_C071:; return;
label_C073:; return;
label_C075:; return;
label_C077:; return;
label_C079:; return;
label_C07B:; return;
label_C07C:; return;
label_C07E:; return;
label_C080:; return;
label_C082:; return;
label_C084:; return;
label_C086:; return;
label_C087:; return;
label_C089:; return;
label_C08B:; return;
label_C08D:; return;
label_C090:; return;
label_C092:; return;
label_C095:; return;
label_C097:; return;
label_C099:; return;
label_C09C:; return;
label_C09F:; return;
label_C0A0:; return;
label_C0A2:; return;
label_C0A5:; return;
label_C0A8:; return;
label_C0A9:; return;
label_C0AB:; return;
label_C0AE:; return;
label_C0B1:; return;
label_C0B2:; return;
label_C0B4:; return;
label_C0B7:; return;
label_C0B9:; return;
label_C0BC:; return;
label_C0BF:; return;
label_C0C2:; return;
label_C0C5:; return;
label_C0C8:; return;
label_C0CB:; return;
label_C0CC:; return;
label_C0CF:; return;
label_C0D1:; return;
label_C0D4:; return;
label_C0D6:; return;
label_C0D8:; return;
label_C0D9:; return;
label_C0DB:; return;
label_C0DE:; return;
label_C0E1:; return;
label_C0E3:; return;
label_C0E6:; return;
label_C0E9:; return;
label_C0EB:; return;
label_C0ED:; return;
label_C0F0:; return;
label_C0F2:; return;
label_C0F4:; return;
label_C0F6:; return;
label_C0F8:; return;
label_C0FB:; return;
label_C0FD:; return;
label_C0FF:; return;
label_C102:; return;
label_C105:; return;
label_C108:; return;
label_C10A:; return;
label_C10C:; return;
label_C10F:; return;
label_C111:; return;
label_C113:; return;
label_C115:; return;
label_C118:; return;
label_C11A:; return;
label_C11C:; return;
label_C11F:; return;
label_C122:; return;
label_C124:; return;
label_C127:; return;
label_C12A:; return;
label_C12C:; return;
label_C12F:; return;
label_C132:; return;
label_C134:; return;
label_C136:; return;
label_C138:; return;
label_C13A:; return;
label_C13C:; return;
label_C13E:; return;
label_C141:; return;
label_C144:; return;
label_C147:; return;
label_C149:; return;
label_C14B:; return;
label_C14D:; return;
label_C150:; return;
label_C152:; return;
label_C154:; return;
label_C156:; return;
label_C158:; return;
label_C15A:; return;
label_C15B:; return;
label_C15D:; return;
label_C15F:; return;
label_C161:; return;
label_C163:; return;
label_C164:; return;
label_C167:; return;
label_C168:; return;
label_C16A:; return;
label_C16C:; return;
label_C16E:; return;
label_C171:; return;
label_C173:; return;
label_C175:; return;
label_C178:; return;
label_C179:; return;
label_C17B:; return;
label_C17C:; return;
label_C17E:; return;
label_C181:; return;
label_C183:; return;
label_C186:; return;
label_C189:; return;
label_C18A:; return;
label_C18C:; return;
label_C18E:; return;
label_C190:; return;
label_C192:; return;
label_C195:; return;
label_C197:; return;
label_C198:; return;
label_C19A:; return;
label_C19C:; return;
label_C19F:; return;
label_C1A2:; return;
label_C1A5:; return;
label_C1A8:; return;
label_C1AB:; return;
label_C1AE:; return;
label_C1B0:; return;
label_C1B2:; return;
label_C1B4:; return;
label_C1B6:; return;
label_C1B9:; return;
label_C1BB:; return;
label_C1BE:; return;
label_C1C0:; return;
label_C1C2:; return;
label_C1C4:; return;
label_C1C6:; return;
label_C1C8:; return;
label_C1CB:; return;
label_C1CD:; return;
label_C1CF:; return;
label_C1D1:; return;
label_C1D3:; return;
label_C1D5:; return;
label_C1D7:; return;
label_C1D9:; return;
label_C1DB:; return;
label_C1DC:; return;
label_C1DD:; return;
label_C1DE:; return;
label_C1DF:; return;
label_C1E1:; return;
label_C1E3:; return;
label_C1E5:; return;
label_C1E6:; return;
label_C1E8:; return;
label_C1EA:; return;
label_C1EC:; return;
label_C1EF:; return;
label_C1F1:; return;
label_C1F3:; return;
label_C1F5:; return;
label_C1F7:; return;
label_C1F9:; return;
label_C1FB:; return;
label_C1FD:; return;
label_C1FF:; return;
label_C201:; return;
label_C204:; return;
label_C206:; return;
label_C208:; return;
label_C20A:; return;
label_C20C:; return;
label_C20E:; return;
label_C211:; return;
label_C213:; return;
label_C215:; return;
label_C216:; return;
label_C219:; return;
label_C21B:; return;
label_C21E:; return;
label_C220:; return;
label_C222:; return;
label_C224:; return;
label_C226:; return;
label_C228:; return;
label_C22A:; return;
label_C22D:; return;
label_C22E:; return;
label_C231:; return;
label_C232:; return;
label_C233:; return;
label_C235:; return;
label_C236:; return;
label_C237:; return;
label_C238:; return;
label_C239:; return;
label_C23A:; return;
label_C23D:; return;
label_C23F:; return;
label_C240:; return;
label_C242:; return;
label_C245:; return;
label_C246:; return;
label_C248:; return;
label_C24A:; return;
label_C24D:; return;
label_C25E:; return;
label_C261:; return;
label_C264:; return;
label_C266:; return;
label_C269:; return;
label_C26B:; return;
label_C26C:; return;
label_C26E:; return;
label_C270:; return;
label_C272:; return;
label_C273:; return;
label_C275:; return;
label_C277:; return;
label_C279:; return;
label_C27B:; return;
label_C27E:; return;
label_C27F:; return;
label_C2F0:; return;
label_C2F1:; return;
label_C2F4:; return;
label_C2F7:; return;
label_C2F9:; return;
label_C2FB:; return;
label_C2FD:; return;
label_C2FE:; return;
label_C301:; return;
label_C302:; return;
label_C304:; return;
label_C307:; return;
label_C309:; return;
label_C30B:; return;
label_C30C:; return;
label_C30D:; return;
label_C30F:; return;
label_C311:; return;
label_C312:; return;
label_C314:; return;
label_C316:; return;
label_C319:; return;
label_C31B:; return;
label_C31E:; return;
label_C321:; return;
label_C323:; return;
label_C325:; return;
label_C326:; return;
label_C328:; return;
label_C32A:; return;
label_C32D:; return;
label_C32F:; return;
label_C332:; return;
label_C335:; return;
label_C338:; return;
label_C33A:; return;
label_C33D:; return;
label_C33F:; return;
label_C342:; return;
label_C344:; return;
label_C346:; return;
label_C348:; return;
label_C34A:; return;
label_C34C:; return;
label_C34E:; return;
label_C351:; return;
label_C353:; return;
label_C355:; return;
label_C356:; return;
label_C358:; return;
label_C35A:; return;
label_C35C:; return;
label_C35F:; return;
label_C361:; return;
label_C363:; return;
label_C365:; return;
label_C367:; return;
label_C36A:; return;
label_C36B:; return;
label_C36D:; return;
label_C36F:; return;
label_C371:; return;
label_C374:; return;
label_C375:; return;
label_C378:; return;
label_C37B:; return;
label_C37D:; return;
label_C37F:; return;
label_C381:; return;
label_C384:; return;
label_C385:; return;
label_C388:; return;
label_C38A:; return;
label_C38C:; return;
label_C38F:; return;
label_C392:; return;
label_C395:; return;
label_C398:; return;
label_C39A:; return;
label_C39B:; return;
label_C39C:; return;
label_C39F:; return;
label_C3A1:; return;
label_C3A3:; return;
label_C3A5:; return;
label_C3A8:; return;
label_C3AB:; return;
label_C3AD:; return;
label_C3AF:; return;
label_C3B2:; return;
label_C3B4:; return;
label_C3B7:; return;
label_C3B9:; return;
label_C3BB:; return;
label_C3BC:; return;
label_C3BE:; return;
label_C3C1:; return;
label_C3C4:; return;
label_C3C6:; return;
label_C3C8:; return;
label_C3CA:; return;
label_C3CC:; return;
label_C3CE:; return;
label_C3CF:; return;
label_C3D1:; return;
label_C3D3:; return;
label_C3D5:; return;
label_C3D7:; return;
label_C3D9:; return;
label_C3DB:; return;
label_C3DE:; return;
label_C3E0:; return;
label_C3E3:; return;
label_C3E5:; return;
label_C3E6:; return;
label_C3E8:; return;
label_C3EA:; return;
label_C3EC:; return;
label_C3EF:; return;
label_C3F1:; return;
label_C3F4:; return;
label_C3F6:; return;
label_C3F9:; return;
label_C3FB:; return;
label_C3FD:; return;
label_C3FF:; return;
label_C402:; return;
label_C403:; return;
label_C405:; return;
label_C407:; return;
label_C40A:; return;
label_C40C:; return;
label_C40D:; return;
label_C40F:; return;
label_C412:; return;
label_C414:; return;
label_C415:; return;
label_C416:; return;
label_C417:; return;
label_C418:; return;
label_C419:; return;
label_C41B:; return;
label_C41D:; return;
label_C420:; return;
label_C422:; return;
label_C424:; return;
label_C426:; return;
label_C427:; return;
label_C42A:; return;
label_C42C:; return;
label_C42E:; return;
label_C42F:; return;
label_C431:; return;
label_C432:; return;
label_C433:; return;
label_C434:; return;
label_C437:; return;
label_C439:; return;
label_C43B:; return;
label_C43D:; return;
label_C43F:; return;
label_C440:; return;
label_C442:; return;
label_C444:; return;
label_C446:; return;
label_C448:; return;
label_C44A:; return;
label_C44C:; return;
label_C44E:; return;
label_C44F:; return;
label_C450:; return;
label_C451:; return;
label_C452:; return;
label_C453:; return;
label_C454:; return;
label_C455:; return;
label_C456:; return;
label_C458:; return;
label_C459:; return;
label_C45C:; return;
label_C45E:; return;
label_C460:; return;
label_C462:; return;
label_C463:; return;
label_C465:; return;
label_C466:; return;
label_C469:; return;
label_C46C:; return;
label_C46F:; return;
label_C471:; return;
label_C473:; return;
label_C474:; return;
label_C476:; return;
label_C478:; return;
label_C47A:; return;
label_C47B:; return;
label_C47D:; return;
label_C47F:; return;
label_C481:; return;
label_C483:; return;
label_C485:; return;
label_C488:; return;
label_C48A:; return;
label_C48B:; return;
label_C48D:; return;
label_C48F:; return;
label_C491:; return;
label_C492:; return;
label_C494:; return;
label_C496:; return;
label_C498:; return;
label_C49B:; return;
label_C49E:; return;
label_C4A0:; return;
label_C4A3:; return;
label_C4A5:; return;
label_C4A6:; return;
label_C4A9:; return;
label_C4AC:; return;
label_C4AE:; return;
label_C4B0:; return;
label_C4B3:; return;
label_C4B5:; return;
label_C4B6:; return;
label_C4B9:; return;
label_C4BC:; return;
label_C4BE:; return;
label_C4C1:; return;
label_C4C3:; return;
label_C4C4:; return;
label_C4C6:; return;
label_C4C8:; return;
label_C4CA:; return;
label_C4CD:; return;
label_C4CF:; return;
label_C4D1:; return;
label_C4D3:; return;
label_C4D5:; return;
label_C4D7:; return;
label_C4D9:; return;
label_C4DB:; return;
label_C4DD:; return;
label_C4DF:; return;
label_C4E1:; return;
label_C4E3:; return;
label_C4E4:; return;
label_C4E5:; return;
label_C4E6:; return;
label_C4E8:; return;
label_C4EA:; return;
label_C4ED:; return;
label_C4EF:; return;
label_C4F1:; return;
label_C4F4:; return;
label_C4F6:; return;
label_C4F8:; return;
label_C4F9:; return;
label_C4FA:; return;
label_C4FC:; return;
label_C4FD:; return;
label_C500:; return;
label_C502:; return;
label_C504:; return;
label_C506:; return;
label_C508:; return;
label_C50A:; return;
label_C50C:; return;
label_C50D:; return;
label_C50F:; return;
label_C511:; return;
label_C513:; return;
label_C515:; return;
label_C516:; return;
label_C518:; return;
label_C51A:; return;
label_C51C:; return;
label_C51D:; return;
label_C51F:; return;
label_C521:; return;
label_C523:; return;
label_C524:; return;
label_C527:; return;
label_C529:; return;
label_C52B:; return;
label_C52D:; return;
label_C530:; return;
label_C532:; return;
label_C533:; return;
label_C536:; return;
label_C538:; return;
label_C53A:; return;
label_C53C:; return;
label_C53E:; return;
label_C540:; return;
label_C542:; return;
label_C544:; return;
label_C546:; return;
label_C548:; return;
label_C549:; return;
label_C54C:; return;
label_C54F:; return;
label_C551:; return;
label_C554:; return;
label_C557:; return;
label_C559:; return;
label_C55C:; return;
label_C55E:; return;
label_C561:; return;
label_C563:; return;
label_C565:; return;
label_C568:; return;
label_C56B:; return;
label_C56D:; return;
label_C570:; return;
label_C571:; return;
label_C574:; return;
label_C575:; return;
label_C577:; return;
label_C578:; return;
label_C57B:; return;
label_C57D:; return;
label_C580:; return;
label_C581:; return;
label_C583:; return;
label_C586:; return;
label_C588:; return;
label_C58B:; return;
label_C58D:; return;
label_C590:; return;
label_C592:; return;
label_C594:; return;
label_C597:; return;
label_C599:; return;
label_C59C:; return;
label_C59D:; return;
label_C59F:; return;
label_C5A1:; return;
label_C5A4:; return;
label_C5A7:; return;
label_C5A9:; return;
label_C5AB:; return;
label_C5AD:; return;
label_C5AF:; return;
label_C5B1:; return;
label_C5B4:; return;
label_C5B7:; return;
label_C5B9:; return;
label_C5BB:; return;
label_C5BE:; return;
label_C5BF:; return;
label_C5C1:; return;
label_C5C4:; return;
label_C5C6:; return;
label_C5C7:; return;
label_C5C9:; return;
label_C5CC:; return;
label_C5CF:; return;
label_C5D1:; return;
label_C5D4:; return;
label_C5D5:; return;
label_C5D8:; return;
label_C5DA:; return;
label_C5DD:; return;
label_C5DE:; return;
label_C5E0:; return;
label_C5E2:; return;
label_C5E5:; return;
label_C5E7:; return;
label_C5E9:; return;
label_C5EC:; return;
label_C5EF:; return;
label_C5F0:; return;
label_C5F2:; return;
label_C5F4:; return;
label_C5F7:; return;
label_C5F9:; return;
label_C5FC:; return;
label_C5FD:; return;
label_C5FF:; return;
label_C601:; return;
label_C604:; return;
label_C606:; return;
label_C609:; return;
label_C60A:; return;
label_C60D:; return;
label_C60F:; return;
label_C611:; return;
label_C613:; return;
label_C614:; return;
label_C617:; return;
label_C61A:; return;
label_C61C:; return;
label_C61F:; return;
label_C621:; return;
label_C624:; return;
label_C626:; return;
label_C628:; return;
label_C62A:; return;
label_C62B:; return;
label_C62E:; return;
label_C630:; return;
label_C631:; return;
label_C632:; return;
label_C634:; return;
label_C635:; return;
label_C636:; return;
label_C639:; return;
label_C63B:; return;
label_C63C:; return;
label_C63E:; return;
label_C641:; return;
label_C643:; return;
label_C646:; return;
label_C648:; return;
label_C64A:; return;
label_C64C:; return;
label_C64D:; return;
label_C650:; return;
label_C652:; return;
label_C654:; return;
label_C657:; return;
label_C658:; return;
label_C65A:; return;
label_C65B:; return;
label_C65E:; return;
label_C660:; return;
label_C662:; return;
label_C665:; return;
label_C666:; return;
label_C669:; return;
label_C66A:; return;
label_C66B:; return;
label_C66C:; return;
label_C66F:; return;
label_C671:; return;
label_C673:; return;
label_C675:; return;
label_C677:; return;
label_C67A:; return;
label_C67C:; return;
label_C67E:; return;
label_C680:; return;
label_C682:; return;
label_C683:; return;
label_C685:; return;
label_C687:; return;
label_C689:; return;
label_C68A:; return;
label_C68C:; return;
label_C68E:; return;
label_C690:; return;
label_C691:; return;
label_C693:; return;
label_C695:; return;
label_C697:; return;
label_C698:; return;
label_C69A:; return;
label_C69B:; return;
label_C69D:; return;
label_C6A0:; return;
label_C6A3:; return;
label_C6A5:; return;
label_C6A7:; return;
label_C6A9:; return;
label_C6AB:; return;
label_C6AC:; return;
label_C6AF:; return;
label_C6B1:; return;
label_C6B3:; return;
label_C6B4:; return;
label_C6B7:; return;
label_C6B9:; return;
label_C6BB:; return;
label_C6BC:; return;
label_C6BD:; return;
label_C6BF:; return;
label_C6C0:; return;
label_C6C3:; return;
label_C6C5:; return;
label_C6C8:; return;
label_C6CA:; return;
label_C6CC:; return;
label_C6CE:; return;
label_C6D1:; return;
label_C6D4:; return;
label_C6D6:; return;
label_C6D7:; return;
label_C6DA:; return;
label_C6DD:; return;
label_C6DF:; return;
label_C6E0:; return;
label_C6E1:; return;
label_C6E3:; return;
label_C6E6:; return;
label_C6E9:; return;
label_C6EC:; return;
label_C6EF:; return;
label_C6F2:; return;
label_C6F5:; return;
label_C6F7:; return;
label_C6FA:; return;
label_C6FD:; return;
label_C6FF:; return;
label_C700:; return;
label_C702:; return;
label_C704:; return;
label_C707:; return;
label_C709:; return;
label_C70C:; return;
label_C70E:; return;
label_C710:; return;
label_C711:; return;
label_C713:; return;
label_C715:; return;
label_C717:; return;
label_C719:; return;
label_C71B:; return;
label_C71D:; return;
label_C71E:; return;
label_C720:; return;
label_C721:; return;
label_C723:; return;
label_C725:; return;
label_C726:; return;
label_C728:; return;
label_C72B:; return;
label_C72D:; return;
label_C72F:; return;
label_C730:; return;
label_C732:; return;
label_C734:; return;
label_C736:; return;
label_C738:; return;
label_C73A:; return;
label_C73C:; return;
label_C73F:; return;
label_C741:; return;
label_C744:; return;
label_C746:; return;
label_C748:; return;
label_C749:; return;
label_C74A:; return;
label_C74C:; return;
label_C74D:; return;
label_C750:; return;
label_C752:; return;
label_C753:; return;
label_C755:; return;
label_C757:; return;
label_C759:; return;
label_C75B:; return;
label_C75D:; return;
label_C75F:; return;
label_C761:; return;
label_C763:; return;
label_C765:; return;
label_C767:; return;
label_C768:; return;
label_C76A:; return;
label_C76C:; return;
label_C76E:; return;
label_C770:; return;
label_C772:; return;
label_C774:; return;
label_C776:; return;
label_C778:; return;
label_C77A:; return;
label_C77C:; return;
label_C77F:; return;
label_C782:; return;
label_C784:; return;
label_C787:; return;
label_C789:; return;
label_C78B:; return;
label_C78C:; return;
label_C78E:; return;
label_C790:; return;
label_C792:; return;
label_C795:; return;
label_C796:; return;
label_C798:; return;
label_C79B:; return;
label_C79D:; return;
label_C7A0:; return;
label_C7A2:; return;
label_C7A5:; return;
label_C7A6:; return;
label_C7A8:; return;
label_C7BB:; return;
label_C7BD:; return;
label_C7BF:; return;
label_C7C1:; return;
label_C7C3:; return;
label_C7C6:; return;
label_C7C7:; return;
label_C7C9:; return;
label_C7CB:; return;
label_C7CE:; return;
label_C7D0:; return;
label_C7D1:; return;
label_C7D3:; return;
label_C7D5:; return;
label_C7D7:; return;
label_C7D9:; return;
label_C7DB:; return;
label_C7DE:; return;
label_C7DF:; return;
label_C7E1:; return;
label_C7E3:; return;
label_C7E6:; return;
label_C7E8:; return;
label_C7EA:; return;
label_C7ED:; return;
label_C7EF:; return;
label_C7F2:; return;
label_C7F4:; return;
label_C7F6:; return;
label_C7F7:; return;
label_C7F8:; return;
label_C7FB:; return;
label_C7FD:; return;
label_C7FF:; return;
label_C800:; return;
label_C803:; return;
label_C805:; return;
label_C808:; return;
label_C80B:; return;
label_C80D:; return;
label_C80F:; return;
label_C812:; return;
label_C814:; return;
label_C816:; return;
label_C818:; return;
label_C81A:; return;
label_C81B:; return;
label_C81D:; return;
label_C81F:; return;
label_C822:; return;
label_C823:; return;
label_C824:; return;
label_C826:; return;
label_C828:; return;
label_C82B:; return;
label_C82D:; return;
label_C830:; return;
label_C832:; return;
label_C834:; return;
label_C837:; return;
label_C839:; return;
label_C83B:; return;
label_C83E:; return;
label_C83F:; return;
label_C842:; return;
label_C845:; return;
label_C848:; return;
label_C84B:; return;
label_C84D:; return;
label_C850:; return;
label_C852:; return;
label_C854:; return;
label_C857:; return;
label_C859:; return;
label_C85C:; return;
label_C85E:; return;
label_C860:; return;
label_C862:; return;
label_C865:; return;
label_C867:; return;
label_C86A:; return;
label_C86B:; return;
label_C86C:; return;
label_C86F:; return;
label_C870:; return;
label_C873:; return;
label_C874:; return;
label_C877:; return;
label_C879:; return;
label_C87B:; return;
label_C87E:; return;
label_C880:; return;
label_C881:; return;
label_C882:; return;
label_C884:; return;
label_C886:; return;
label_C888:; return;
label_C88A:; return;
label_C88C:; return;
label_C88D:; return;
label_C88F:; return;
label_C8D6:; return;
label_C8D7:; return;
label_C8DA:; return;
label_C8DD:; return;
label_C8E0:; return;
label_C8E2:; return;
label_C8E5:; return;
label_C8E8:; return;
label_C8EB:; return;
label_C8EE:; return;
label_C8F1:; return;
label_C8F4:; return;
label_C8F7:; return;
label_C8FA:; return;
label_C8FD:; return;
label_C8FF:; return;
label_C902:; return;
label_C905:; return;
label_C907:; return;
label_C934:; return;
label_C935:; return;
label_C938:; return;
label_C93B:; return;
label_C93E:; return;
label_C941:; return;
label_C944:; return;
label_C947:; return;
label_C94A:; return;
label_C94D:; return;
label_C950:; return;
label_C953:; return;
label_C956:; return;
label_C959:; return;
label_C95C:; return;
label_C95F:; return;
label_C962:; return;
label_C965:; return;
label_C968:; return;
label_C96B:; return;
label_C96E:; return;
label_C971:; return;
label_C974:; return;
label_C976:; return;
label_C979:; return;
label_C97C:; return;
label_C97F:; return;
label_C982:; return;
label_C984:; return;
label_C985:; return;
label_C987:; return;
label_C998:; return;
label_C99A:; return;
label_C99C:; return;
label_C99E:; return;
label_C9A0:; return;
label_C9A3:; return;
label_C9A6:; return;
label_C9A9:; return;
label_C9AC:; return;
label_C9AF:; return;
label_C9B0:; return;
label_C9B3:; return;
label_C9B5:; return;
label_C9B8:; return;
label_C9BB:; return;
label_C9BD:; return;
label_C9C0:; return;
label_C9C2:; return;
label_C9C4:; return;
label_C9C7:; return;
label_C9C9:; return;
label_C9CB:; return;
label_C9CE:; return;
label_C9D0:; return;
label_C9D1:; return;
label_C9D2:; return;
label_C9D3:; return;
label_C9D4:; return;
label_C9D5:; return;
label_C9D6:; return;
label_C9D9:; return;
label_C9DC:; return;
label_C9DE:; return;
label_C9E1:; return;
label_C9E3:; return;
label_C9E5:; return;
label_C9E7:; return;
label_C9EA:; return;
label_C9EC:; return;
label_C9EE:; return;
label_C9F1:; return;
label_C9F3:; return;
label_C9F6:; return;
label_C9F9:; return;
label_C9FC:; return;
label_C9FF:; return;
label_CA01:; return;
label_CA03:; return;
label_CA05:; return;
label_CA07:; return;
label_CA0A:; return;
label_CA0D:; return;
label_CA12:; return;
label_CA14:; return;
label_CA16:; return;
label_CA18:; return;
label_CA1A:; return;
label_CA1C:; return;
label_CA1E:; return;
label_CA20:; return;
label_CA22:; return;
label_CA24:; return;
label_CA26:; return;
label_CA28:; return;
label_CA2A:; return;
label_CA2C:; return;
label_CA2E:; return;
label_CA31:; return;
label_CA33:; return;
label_CA35:; return;
label_CA37:; return;
label_CA39:; return;
label_CA3B:; return;
label_CA3D:; return;
label_CA3F:; return;
label_CA41:; return;
label_CA44:; return;
label_CA45:; return;
label_CA48:; return;
label_CA4A:; return;
label_CA4B:; return;
label_CA4E:; return;
label_CA51:; return;
label_CA54:; return;
label_CA56:; return;
label_CA58:; return;
label_CA5A:; return;
label_CA5C:; return;
label_CA5E:; return;
label_CA60:; return;
label_CA62:; return;
label_CA64:; return;
label_CA66:; return;
label_CA69:; return;
label_CA6B:; return;
label_CA6C:; return;
label_CA6F:; return;
label_CA71:; return;
label_CA73:; return;
label_CA75:; return;
label_CA77:; return;
label_CA79:; return;
label_CA7B:; return;
label_CA7D:; return;
label_CA7F:; return;
label_CA81:; return;
label_CA82:; return;
label_CA84:; return;
label_CA86:; return;
label_CA88:; return;
label_CA8A:; return;
label_CA8C:; return;
label_CA8E:; return;
label_CA90:; return;
label_CA92:; return;
label_CA94:; return;
label_CA96:; return;
label_CA98:; return;
label_CA9B:; return;
label_CA9D:; return;
label_CA9F:; return;
label_CAA1:; return;
label_CAA3:; return;
label_CAA5:; return;
label_CAA7:; return;
label_CAA9:; return;
label_CAAB:; return;
label_CAAD:; return;
label_CAAF:; return;
label_CAB2:; return;
label_CAB4:; return;
label_CAB6:; return;
label_CAB7:; return;
label_CAB9:; return;
label_CABA:; return;
label_CABB:; return;
label_CABC:; return;
label_CABF:; return;
label_CAC1:; return;
label_CAC4:; return;
label_CAC5:; return;
label_CAC7:; return;
label_CAC8:; return;
label_CACB:; return;
label_CACD:; return;
label_CACF:; return;
label_CAD1:; return;
label_CAD3:; return;
label_CAD4:; return;
label_CAD5:; return;
label_CAD7:; return;
label_CAD8:; return;
label_CADB:; return;
label_CADD:; return;
label_CADE:; return;
label_CADF:; return;
label_CAE2:; return;
label_CAE4:; return;
label_CAE5:; return;
label_CAE8:; return;
label_CAEB:; return;
label_CAED:; return;
label_CAEF:; return;
label_CAF1:; return;
label_CAF3:; return;
label_CAF5:; return;
label_CAF8:; return;
label_CAF9:; return;
label_CAFC:; return;
label_CAFF:; return;
label_CB01:; return;
label_CB04:; return;
label_CB06:; return;
label_CB09:; return;
label_CB0B:; return;
label_CB0E:; return;
label_CB10:; return;
label_CB12:; return;
label_CB14:; return;
label_CB16:; return;
label_CB18:; return;
label_CB19:; return;
label_CB1B:; return;
label_CB1D:; return;
label_CB1F:; return;
label_CB22:; return;
label_CB25:; return;
label_CB28:; return;
label_CB2B:; return;
label_CB2D:; return;
label_CB2F:; return;
label_CB31:; return;
label_CB33:; return;
label_CB35:; return;
}

void func_B976_b1(void) {
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_B976_b1");
#endif
    func_B976_b1_body(0);
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
}

void func_B9A9_b1(void) {
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_B9A9_b1");
#endif
    func_B976_b1_body(1);
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
}

void func_BB33_b1(void) {
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_BB33_b1");
#endif
    func_B976_b1_body(2);
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
}

void func_BB48_b1(void) {
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_BB48_b1");
#endif
    func_B976_b1_body(3);
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
}

void func_BFC6_b1(void) {
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_BFC6_b1");
#endif
    func_B976_b1_body(4);
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
}

void func_BD0C_b1_body(int _entry) {
    switch (_entry) {
        case 1: goto label_BD35;
        case 2: goto label_BD8C;
        case 3: goto label_BEDB;
    }
label_BD0C:;
    /* $BD0C: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) { maybe_trigger_vblank(1); call_by_address(0xBD3E); return; }
label_BD0E:;
    /* $BD0E: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) { maybe_trigger_vblank(2); call_by_address(0xBC90); return; }
label_BD10:;
    /* $BD10: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x1482); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_BD13:;
    /* $BD13: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x2662); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_BD16:;
    /* $BD16: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) { maybe_trigger_vblank(1); goto label_BD40; }
label_BD18:;
    /* $BD18: 80 */ maybe_trigger_vblank(2); /* NOP */
label_BD1A:; /* ChkBrick */
    /* $BD1A: 82 */ maybe_trigger_vblank(2); /* NOP */
label_BD1C:;
    /* $BD1C: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x2662); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_BD1F:;
    /* $BD1F: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) { maybe_trigger_vblank(1); call_by_address(0xBD49); return; }
label_BD21:;
    /* $BD21: 80 */ maybe_trigger_vblank(2); /* NOP */
label_BD23:;
    /* $BD23: 82 */ maybe_trigger_vblank(2); /* NOP */
label_BD25:;
    /* $BD25: 1E */ maybe_trigger_vblank(7); { uint16_t a=(0x185E + g_cpu.X) & 0xFFFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BD28:;
    /* $BD28: 60 */ maybe_trigger_vblank(6); 
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
    return;
label_BD29:;
    /* $BD29: 1A */ maybe_trigger_vblank(2); /* NOP */
label_BD2A:;
    /* $BD2A: 80 */ maybe_trigger_vblank(2); /* NOP */
label_BD2C:; /* StartBTmr */
    /* $BD2C: 82 */ maybe_trigger_vblank(2); /* NOP */
label_BD2E:;
    /* $BD2E: 1E */ maybe_trigger_vblank(7); { uint16_t a=(0x185E + g_cpu.X) & 0xFFFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BD31:;
    /* $BD31: 60 */ maybe_trigger_vblank(6); 
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
    return;
label_BD32:;
    /* $BD32: 1A */ maybe_trigger_vblank(2); /* NOP */
label_BD33:;
    /* $BD33: 86 */ maybe_trigger_vblank(3); nes_write(0x04, g_cpu.X);
label_BD35:;
    /* $BD35: 83 */ maybe_trigger_vblank(6); nes_write(nes_read16zp((0x1A + g_cpu.X) & 0xFF), g_cpu.A & g_cpu.X); /* SAX */
label_BD37:;
    /* $BD37: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_BD38:;
    /* $BD38: 16 */ maybe_trigger_vblank(6); { uint16_t a=(0x84 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BD3A:;
    /* $BD3A: 14 */ maybe_trigger_vblank(4); (void)nes_read((0x1A + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BD3C:;
    /* $BD3C: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_BD3D:;
    /* $BD3D: 0E */ maybe_trigger_vblank(6); { uint16_t a=0x160C; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BD40:; /* PutOldMT */
    /* $BD40: 83 */ maybe_trigger_vblank(6); nes_write(nes_read16zp((0x14 + g_cpu.X) & 0xFF), g_cpu.A & g_cpu.X); /* SAX */
label_BD42:;
    /* $BD42: 20 */ maybe_trigger_vblank(6); nes_dispatch_call(0x1C1E, -1);
label_BD45:;
    /* $BD45: 28 */ maybe_trigger_vblank(4); { g_cpu.S++; uint8_t p = g_ram[0x100 + g_cpu.S];
  g_cpu.N=(p>>7)&1; g_cpu.V=(p>>6)&1; g_cpu.D=(p>>3)&1;
  g_cpu.I=(p>>2)&1; g_cpu.Z=(p>>1)&1; g_cpu.C=p&1; }
label_BD46:;
    /* $BD46: 26 */ maybe_trigger_vblank(5); { uint16_t a=0x87; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BD48:;
    /* $BD48: 24 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x1A); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_BD4A:;
    /* $BD4A: 12 */ maybe_trigger_vblank(2); /* ILLEGAL $12 — skip 1 */
label_BD4B:;
    /* $BD4B: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) { maybe_trigger_vblank(1); goto label_BDAF; }
label_BD4D:;
    /* $BD4D: 0E */ maybe_trigger_vblank(6); { uint16_t a=0x0480; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BD50:;
    /* $BD50: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x00); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BD52:;
    /* $BD52: 82 */ maybe_trigger_vblank(2); /* NOP */
label_BD54:;
    /* $BD54: 1C */ maybe_trigger_vblank(4); (void)nes_read((0x2220 + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BD57:;
    /* $BD57: 26 */ maybe_trigger_vblank(5); { uint16_t a=0x28; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BD59:;
    /* $BD59: 81 */ maybe_trigger_vblank(6); nes_write(nes_read16zp((0x2A + g_cpu.X) & 0xFF), g_cpu.A);
label_BD5B:;
    /* $BD5B: 2A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_BD5C:;
    /* $BD5C: 2A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_BD5D:;
    /* $BD5D: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x2A); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BD5F:;
    /* $BD5F: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x83); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BD61:; /* SmallBP */
    /* $BD61: 2A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_BD62:; /* BigBP */
    /* $BD62: 82 */ maybe_trigger_vblank(2); /* NOP */
label_BD64:;
    /* $BD64: 86 */ maybe_trigger_vblank(3); nes_write(0x34, g_cpu.X);
label_BD66:;
    /* $BD66: 32 */ maybe_trigger_vblank(2); /* ILLEGAL $32 — skip 1 */
label_BD67:;
    /* $BD67: 34 */ maybe_trigger_vblank(4); (void)nes_read((0x81 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BD69:;
    /* $BD69: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x22); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BD6B:;
    /* $BD6B: 26 */ maybe_trigger_vblank(5); { uint16_t a=0x2A; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BD6D:;
    /* $BD6D: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x8630); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_BD70:;
    /* $BD70: 34 */ maybe_trigger_vblank(4); (void)nes_read((0x83 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BD72:;
    /* $BD72: 32 */ maybe_trigger_vblank(2); /* ILLEGAL $32 — skip 1 */
label_BD73:;
    /* $BD73: 82 */ maybe_trigger_vblank(2); /* NOP */
label_BD75:;
    /* $BD75: 84 */ maybe_trigger_vblank(3); nes_write(0x34, g_cpu.Y);
label_BD77:;
    /* $BD77: 85 */ maybe_trigger_vblank(3); nes_write(0x04, g_cpu.A);
label_BD79:;
    /* $BD79: 81 */ maybe_trigger_vblank(6); nes_write(nes_read16zp((0x22 + g_cpu.X) & 0xFF), g_cpu.A);
label_BD7B:; /* InvOBit */
    /* $BD7B: 86 */ maybe_trigger_vblank(3); nes_write(0x30, g_cpu.X);
label_BD7D:;
    /* $BD7D: 2E */ maybe_trigger_vblank(6); { uint16_t a=0x8130; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BD80:;
    /* $BD80: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x22); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BD82:;
    /* $BD82: 26 */ maybe_trigger_vblank(5); { uint16_t a=0x2A; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BD84:; /* InitBlock_XY_Pos */
    /* $BD84: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x862E); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_BD87:;
    /* $BD87: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) {
    maybe_trigger_vblank(1);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_BD0C;
    }
label_BD89:;
    /* $BD89: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_BD8A:;
    /* $BD8A: 82 */ maybe_trigger_vblank(2); /* NOP */
label_BD8C:;
    /* $BD8C: 84 */ maybe_trigger_vblank(3); nes_write(0x34, g_cpu.Y);
label_BD8E:;
    /* $BD8E: 85 */ maybe_trigger_vblank(3); nes_write(0x04, g_cpu.A);
label_BD90:;
    /* $BD90: 81 */ maybe_trigger_vblank(6); nes_write(nes_read16zp((0x22 + g_cpu.X) & 0xFF), g_cpu.A);
label_BD92:;
    /* $BD92: 86 */ maybe_trigger_vblank(3); nes_write(0x3A, g_cpu.X);
label_BD94:;
    /* $BD94: 3A */ maybe_trigger_vblank(2); /* NOP */
label_BD95:;
    /* $BD95: 3A */ maybe_trigger_vblank(2); /* NOP */
label_BD96:;
    /* $BD96: 82 */ maybe_trigger_vblank(2); /* NOP */
label_BD98:;
    /* $BD98: 81 */ maybe_trigger_vblank(6); nes_write(nes_read16zp((0x40 + g_cpu.X) & 0xFF), g_cpu.A);
label_BD9A:;
    /* $BD9A: 82 */ maybe_trigger_vblank(2); /* NOP */
label_BD9C:;
    /* $BD9C: 81 */ maybe_trigger_vblank(6); nes_write(nes_read16zp((0x3A + g_cpu.X) & 0xFF), g_cpu.A);
label_BD9E:;
    /* $BD9E: 86 */ maybe_trigger_vblank(3); nes_write(0x36, g_cpu.X);
label_BDA0:;
    /* $BDA0: 36 */ maybe_trigger_vblank(6); { uint16_t a=(0x36 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BDA2:;
    /* $BDA2: 82 */ maybe_trigger_vblank(2); /* NOP */
label_BDA4:;
    /* $BDA4: 81 */ maybe_trigger_vblank(6); nes_write(nes_read16zp((0x3A + g_cpu.X) & 0xFF), g_cpu.A);
label_BDA6:;
    /* $BDA6: 82 */ maybe_trigger_vblank(2); /* NOP */
label_BDA8:;
    /* $BDA8: 81 */ maybe_trigger_vblank(6); nes_write(nes_read16zp((0x36 + g_cpu.X) & 0xFF), g_cpu.A);
label_BDAA:;
    /* $BDAA: 86 */ maybe_trigger_vblank(3); nes_write(0x34, g_cpu.X);
label_BDAC:;
    /* $BDAC: 82 */ maybe_trigger_vblank(2); /* NOP */
label_BDAE:;
    /* $BDAE: 2A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_BDAF:;
    /* $BDAF: 36 */ maybe_trigger_vblank(6); { uint16_t a=(0x81 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BDB1:;
    /* $BDB1: 34 */ maybe_trigger_vblank(4); (void)nes_read((0x34 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BDB3:;
    /* $BDB3: 85 */ maybe_trigger_vblank(3); nes_write(0x34, g_cpu.A);
label_BDB5:;
    /* $BDB5: 81 */ maybe_trigger_vblank(6); nes_write(nes_read16zp((0x2A + g_cpu.X) & 0xFF), g_cpu.A);
label_BDB7:;
    /* $BDB7: 86 */ maybe_trigger_vblank(3); nes_write(0x2C, g_cpu.X);
label_BDB9:;
    /* $BDB9: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xBDB9); return;
label_BDBA:;
    /* $BDBA: 84 */ maybe_trigger_vblank(3); nes_write(0x90, g_cpu.Y);
label_BDBC:;
    /* $BDBC: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) {
    maybe_trigger_vblank(1);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_BD42;
    }
label_BDBE:;
    /* $BDBE: 50 */ maybe_trigger_vblank(2); if (!g_cpu.V) { maybe_trigger_vblank(2); call_by_address(0xBE10); return; }
label_BDC0:;
    /* $BDC0: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_BDC2; }
label_BDC2:;
    /* $BDC2: 98 */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.Y; FLAG_NZ(g_cpu.A);
label_BDC3:;
    /* $BDC3: 96 */ maybe_trigger_vblank(4); nes_write((0x94 + g_cpu.Y) & 0xFF, g_cpu.X);
label_BDC5:;
    /* $BDC5: 92 */ maybe_trigger_vblank(2); /* ILLEGAL $92 — skip 1 */
label_BDC6:;
    /* $BDC6: 94 */ maybe_trigger_vblank(4); nes_write((0x96 + g_cpu.X) & 0xFF, g_cpu.Y);
label_BDC8:;
    /* $BDC8: 58 */ maybe_trigger_vblank(2); g_cpu.I = 0;
label_BDC9:;
    /* $BDC9: 58 */ maybe_trigger_vblank(2); g_cpu.I = 0;
label_BDCA:;
    /* $BDCA: 58 */ maybe_trigger_vblank(2); g_cpu.I = 0;
label_BDCB:;
    /* $BDCB: 44 */ maybe_trigger_vblank(3); (void)nes_read(0x5C); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BDCD:;
    /* $BDCD: 44 */ maybe_trigger_vblank(3); (void)nes_read(0x9F); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BDCF:;
    /* $BDCF: A3 */ maybe_trigger_vblank(6); g_cpu.A = g_cpu.X = nes_read(nes_read16zp((0xA1 + g_cpu.X) & 0xFF)); FLAG_NZ(g_cpu.A);
label_BDD1:;
    /* $BDD1: A3 */ maybe_trigger_vblank(6); g_cpu.A = g_cpu.X = nes_read(nes_read16zp((0x85 + g_cpu.X) & 0xFF)); FLAG_NZ(g_cpu.A);
label_BDD3:;
    /* $BDD3: A3 */ maybe_trigger_vblank(6); g_cpu.A = g_cpu.X = nes_read(nes_read16zp((0xE0 + g_cpu.X) & 0xFF)); FLAG_NZ(g_cpu.A);
label_BDD5:; /* StarBlock */
    /* $BDD5: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x23); FLAG_NZ(g_cpu.X);
label_BDD7:;
    /* $BDD7: C4 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x9F); int r=g_cpu.Y-m; g_cpu.C=(g_cpu.Y>=m)?1:0; FLAG_NZ(r&0xFF); }
label_BDD9:;
    /* $BDD9: 9D */ maybe_trigger_vblank(5); nes_write((0x859F + g_cpu.X) & 0xFFFF, g_cpu.A);
label_BDDC:;
    /* $BDDC: 9F */ maybe_trigger_vblank(5); /* ILLEGAL $9F — skip 3 */
label_BDDF:; /* VineBlock */
    /* $BDDF: 23 */ maybe_trigger_vblank(8); { uint16_t a=nes_read16zp((0xC4 + g_cpu.X) & 0xFF); uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); g_cpu.A&=v; FLAG_NZ(g_cpu.A); }
label_BDE1:;
    /* $BDE1: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xB1 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_BDE3:;
    /* $BDE3: AF */ maybe_trigger_vblank(4); g_cpu.A = g_cpu.X = nes_read(0xB185); FLAG_NZ(g_cpu.A);
label_BDE6:;
    /* $BDE6: AF */ maybe_trigger_vblank(4); g_cpu.A = g_cpu.X = nes_read(0x85AD); FLAG_NZ(g_cpu.A);
label_BDE9:;
    /* $BDE9: 95 */ maybe_trigger_vblank(4); nes_write((0x9E + g_cpu.X) & 0xFF, g_cpu.A);
label_BDEB:;
    /* $BDEB: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0xAA; FLAG_NZ(g_cpu.X);
label_BDED:;
    /* $BDED: 6A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=g_cpu.A&1; g_cpu.A=((g_cpu.A>>1)|(c<<7))&0xFF; FLAG_NZ(g_cpu.A); }
label_BDEE:;
    /* $BDEE: 6A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=g_cpu.A&1; g_cpu.A=((g_cpu.A>>1)|(c<<7))&0xFF; FLAG_NZ(g_cpu.A); }
label_BDEF:;
    /* $BDEF: 6B */ maybe_trigger_vblank(2); { g_cpu.A &= 0x5E; uint8_t c=g_cpu.C; g_cpu.A=((g_cpu.A>>1)|(c<<7))&0xFF; FLAG_NZ(g_cpu.A); g_cpu.C=(g_cpu.A>>6)&1; g_cpu.V=(((g_cpu.A>>6)&1)^((g_cpu.A>>5)&1)); }
label_BDF1:;
    /* $BDF1: 9D */ maybe_trigger_vblank(5); nes_write((0x0484 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_BDF4:;
    /* $BDF4: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x82); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BDF6:; /* BlockBumpedChk */
    /* $BDF6: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_BDF7:;
    /* $BDF7: 86 */ maybe_trigger_vblank(3); nes_write(0x22, g_cpu.X);
label_BDF9:;
    /* $BDF9: 82 */ maybe_trigger_vblank(2); /* NOP */
label_BDFB:;
    /* $BDFB: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_BDFC:;
    /* $BDFC: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x2212); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_BDFF:;
    /* $BDFF: 2A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_BE00:;
    /* $BE00: 14 */ maybe_trigger_vblank(4); (void)nes_read((0x22 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BE02:; /* BrickShatter */
    /* $BE02: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x221C); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_BE05:;
    /* $BE05: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x2214); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_BE08:;
    /* $BE08: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x2212); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_BE0B:;
    /* $BE0B: 2A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_BE0C:;
    /* $BE0C: 14 */ maybe_trigger_vblank(4); (void)nes_read((0x22 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BE0E:;
    /* $BE0E: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x221C); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_BE11:;
    /* $BE11: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x2218); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_BE14:;
    /* $BE14: 2A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_BE15:;
    /* $BE15: 16 */ maybe_trigger_vblank(6); { uint16_t a=(0x20 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BE17:;
    /* $BE17: 28 */ maybe_trigger_vblank(4); { g_cpu.S++; uint8_t p = g_ram[0x100 + g_cpu.S];
  g_cpu.N=(p>>7)&1; g_cpu.V=(p>>6)&1; g_cpu.D=(p>>3)&1;
  g_cpu.I=(p>>2)&1; g_cpu.Z=(p>>1)&1; g_cpu.C=p&1; }
label_BE18:;
    /* $BE18: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_BE19:;
    /* $BE19: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_BE1A:;
    /* $BE1A: 2A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_BE1B:;
    /* $BE1B: 12 */ maybe_trigger_vblank(2); /* ILLEGAL $12 — skip 1 */
label_BE1C:;
    /* $BE1C: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_BE1D:;
    /* $BE1D: 2A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_BE1E:;
    /* $BE1E: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_BE1F:; /* CheckTopOfBlock */
    /* $BE1F: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_BE20:;
    /* $BE20: 2A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_BE21:;
    /* $BE21: 12 */ maybe_trigger_vblank(2); /* ILLEGAL $12 — skip 1 */
label_BE22:;
    /* $BE22: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_BE23:;
    /* $BE23: 2A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_BE24:;
    /* $BE24: 14 */ maybe_trigger_vblank(4); (void)nes_read((0x22 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BE26:;
    /* $BE26: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x220C); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_BE29:;
    /* $BE29: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x2214); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_BE2C:;
    /* $BE2C: 34 */ maybe_trigger_vblank(4); (void)nes_read((0x12 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BE2E:;
    /* $BE2E: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_BE2F:;
    /* $BE2F: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) { maybe_trigger_vblank(1); goto label_BE41; }
label_BE31:;
    /* $BE31: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_BE32:;
    /* $BE32: 2E */ maybe_trigger_vblank(6); { uint16_t a=0x2216; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BE35:;
    /* $BE35: 34 */ maybe_trigger_vblank(4); (void)nes_read((0x18 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BE37:;
    /* $BE37: 26 */ maybe_trigger_vblank(5); { uint16_t a=0x36; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BE39:;
    /* $BE39: 16 */ maybe_trigger_vblank(6); { uint16_t a=(0x26 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BE3B:;
    /* $BE3B: 36 */ maybe_trigger_vblank(6); { uint16_t a=(0x14 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BE3D:;
    /* $BE3D: 26 */ maybe_trigger_vblank(5); { uint16_t a=0x36; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BE3F:;
    /* $BE3F: 12 */ maybe_trigger_vblank(2); /* ILLEGAL $12 — skip 1 */
label_BE40:; /* TopEx */
    /* $BE40: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_BE41:; /* SpawnBrickChunks */
    /* $BE41: 36 */ maybe_trigger_vblank(6); { uint16_t a=(0x5C + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BE43:;
    /* $BE43: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_BE44:;
    /* $BE44: 34 */ maybe_trigger_vblank(4); (void)nes_read((0x0C + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BE46:;
    /* $BE46: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_BE47:;
    /* $BE47: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_BE48:;
    /* $BE48: 81 */ maybe_trigger_vblank(6); nes_write(nes_read16zp((0x1E + g_cpu.X) & 0xFF), g_cpu.A);
label_BE4A:;
    /* $BE4A: 1E */ maybe_trigger_vblank(7); { uint16_t a=(0x1E85 + g_cpu.X) & 0xFFFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BE4D:;
    /* $BE4D: 81 */ maybe_trigger_vblank(6); nes_write(nes_read16zp((0x12 + g_cpu.X) & 0xFF), g_cpu.A);
label_BE4F:;
    /* $BE4F: 86 */ maybe_trigger_vblank(3); nes_write(0x14, g_cpu.X);
label_BE51:;
    /* $BE51: 81 */ maybe_trigger_vblank(6); nes_write(nes_read16zp((0x2C + g_cpu.X) & 0xFF), g_cpu.A);
label_BE53:;
    /* $BE53: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_BE54:;
    /* $BE54: 1C */ maybe_trigger_vblank(4); (void)nes_read((0x222C + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BE57:;
    /* $BE57: 1C */ maybe_trigger_vblank(4); (void)nes_read((0x2C85 + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BE5A:;
    /* $BE5A: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x81); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BE5C:;
    /* $BE5C: 2E */ maybe_trigger_vblank(6); { uint16_t a=0x1E24; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BE5F:;
    /* $BE5F: 2E */ maybe_trigger_vblank(6); { uint16_t a=0x1E24; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BE62:;
    /* $BE62: 85 */ maybe_trigger_vblank(3); nes_write(0x2E, g_cpu.A);
label_BE64:;
    /* $BE64: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x81); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BE66:;
    /* $BE66: 32 */ maybe_trigger_vblank(2); /* ILLEGAL $32 — skip 1 */
label_BE67:;
    /* $BE67: 28 */ maybe_trigger_vblank(4); { g_cpu.S++; uint8_t p = g_ram[0x100 + g_cpu.S];
  g_cpu.N=(p>>7)&1; g_cpu.V=(p>>6)&1; g_cpu.D=(p>>3)&1;
  g_cpu.I=(p>>2)&1; g_cpu.Z=(p>>1)&1; g_cpu.C=p&1; }
label_BE68:;
    /* $BE68: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_BE69:;
    /* $BE69: 32 */ maybe_trigger_vblank(2); /* ILLEGAL $32 — skip 1 */
label_BE6A:;
    /* $BE6A: 28 */ maybe_trigger_vblank(4); { g_cpu.S++; uint8_t p = g_ram[0x100 + g_cpu.S];
  g_cpu.N=(p>>7)&1; g_cpu.V=(p>>6)&1; g_cpu.D=(p>>3)&1;
  g_cpu.I=(p>>2)&1; g_cpu.Z=(p>>1)&1; g_cpu.C=p&1; }
label_BE6B:;
    /* $BE6B: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_BE6C:;
    /* $BE6C: 85 */ maybe_trigger_vblank(3); nes_write(0x32, g_cpu.A);
label_BE6E:;
    /* $BE6E: 87 */ maybe_trigger_vblank(3); nes_write(0x36, g_cpu.A & g_cpu.X); /* SAX */
label_BE70:; /* BlockObjectsCore */
    /* $BE70: 36 */ maybe_trigger_vblank(6); { uint16_t a=(0x36 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BE72:;
    /* $BE72: 84 */ maybe_trigger_vblank(3); nes_write(0x3A, g_cpu.Y);
label_BE74:;
    /* $BE74: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xBE74); return;
label_BE75:;
    /* $BE75: 5C */ maybe_trigger_vblank(4); (void)nes_read((0x4C54 + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BE78:;
    /* $BE78: 5C */ maybe_trigger_vblank(4); (void)nes_read((0x4C54 + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BE7B:;
    /* $BE7B: 5C */ maybe_trigger_vblank(4); (void)nes_read((0x1C1C + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BE7E:;
    /* $BE7E: 5C */ maybe_trigger_vblank(4); (void)nes_read((0x5C5C + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BE81:;
    /* $BE81: 5C */ maybe_trigger_vblank(4); (void)nes_read((0x565E + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BE84:;
    /* $BE84: 4E */ maybe_trigger_vblank(6); { uint16_t a=0x565E; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_BE87:;
    /* $BE87: 4E */ maybe_trigger_vblank(6); { uint16_t a=0x1E5E; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_BE8A:;
    /* $BE8A: 1E */ maybe_trigger_vblank(7); { uint16_t a=(0x5E5E + g_cpu.X) & 0xFFFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BE8D:;
    /* $BE8D: 5E */ maybe_trigger_vblank(7); { uint16_t a=(0x625E + g_cpu.X) & 0xFFFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_BE90:;
    /* $BE90: 5A */ maybe_trigger_vblank(2); /* NOP */
label_BE91:;
    /* $BE91: 50 */ maybe_trigger_vblank(2); if (!g_cpu.V) { maybe_trigger_vblank(1); goto label_BEF5; }
label_BE93:;
    /* $BE93: 5A */ maybe_trigger_vblank(2); /* NOP */
label_BE94:;
    /* $BE94: 50 */ maybe_trigger_vblank(2); if (!g_cpu.V) { maybe_trigger_vblank(1); call_by_address(0xBEF8); return; }
label_BE96:;
    /* $BE96: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_BE97:;
    /* $BE97: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_BE98:;
    /* $BE98: 62 */ maybe_trigger_vblank(2); /* ILLEGAL $62 — skip 1 */
label_BE99:;
    /* $BE99: E7 */ maybe_trigger_vblank(5); { uint16_t a=0xE7; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); int16_t r=g_cpu.A-v-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,v); g_cpu.A=r&0xFF; }
label_BE9B:;
    /* $BE9B: E7 */ maybe_trigger_vblank(5); { uint16_t a=0x2B; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); int16_t r=g_cpu.A-v-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,v); g_cpu.A=r&0xFF; }
label_BE9D:;
    /* $BE9D: 86 */ maybe_trigger_vblank(3); nes_write(0x14, g_cpu.X);
label_BE9F:;
    /* $BE9F: 81 */ maybe_trigger_vblank(6); nes_write(nes_read16zp((0x14 + g_cpu.X) & 0xFF), g_cpu.A);
label_BEA1:;
    /* $BEA1: 80 */ maybe_trigger_vblank(2); /* NOP */
label_BEA3:;
    /* $BEA3: 14 */ maybe_trigger_vblank(4); (void)nes_read((0x81 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BEA5:;
    /* $BEA5: 14 */ maybe_trigger_vblank(4); (void)nes_read((0x14 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BEA7:;
    /* $BEA7: 14 */ maybe_trigger_vblank(4); (void)nes_read((0x14 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BEA9:;
    /* $BEA9: 86 */ maybe_trigger_vblank(3); nes_write(0x16, g_cpu.X);
label_BEAB:;
    /* $BEAB: 81 */ maybe_trigger_vblank(6); nes_write(nes_read16zp((0x16 + g_cpu.X) & 0xFF), g_cpu.A);
label_BEAD:;
    /* $BEAD: 80 */ maybe_trigger_vblank(2); /* NOP */
label_BEAF:;
    /* $BEAF: 16 */ maybe_trigger_vblank(6); { uint16_t a=(0x81 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BEB1:;
    /* $BEB1: 16 */ maybe_trigger_vblank(6); { uint16_t a=(0x16 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BEB3:; /* BouncingBlockHandler */
    /* $BEB3: 16 */ maybe_trigger_vblank(6); { uint16_t a=(0x16 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BEB5:;
    /* $BEB5: 81 */ maybe_trigger_vblank(6); nes_write(nes_read16zp((0x28 + g_cpu.X) & 0xFF), g_cpu.A);
label_BEB7:;
    /* $BEB7: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_BEB8:;
    /* $BEB8: 1A */ maybe_trigger_vblank(2); /* NOP */
label_BEB9:;
    /* $BEB9: 28 */ maybe_trigger_vblank(4); { g_cpu.S++; uint8_t p = g_ram[0x100 + g_cpu.S];
  g_cpu.N=(p>>7)&1; g_cpu.V=(p>>6)&1; g_cpu.D=(p>>3)&1;
  g_cpu.I=(p>>2)&1; g_cpu.Z=(p>>1)&1; g_cpu.C=p&1; }
label_BEBA:;
    /* $BEBA: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_BEBB:;
    /* $BEBB: 1A */ maybe_trigger_vblank(2); /* NOP */
label_BEBC:;
    /* $BEBC: 28 */ maybe_trigger_vblank(4); { g_cpu.S++; uint8_t p = g_ram[0x100 + g_cpu.S];
  g_cpu.N=(p>>7)&1; g_cpu.V=(p>>6)&1; g_cpu.D=(p>>3)&1;
  g_cpu.I=(p>>2)&1; g_cpu.Z=(p>>1)&1; g_cpu.C=p&1; }
label_BEBD:;
    /* $BEBD: 80 */ maybe_trigger_vblank(2); /* NOP */
label_BEBF:;
    /* $BEBF: 28 */ maybe_trigger_vblank(4); { g_cpu.S++; uint8_t p = g_ram[0x100 + g_cpu.S];
  g_cpu.N=(p>>7)&1; g_cpu.V=(p>>6)&1; g_cpu.D=(p>>3)&1;
  g_cpu.I=(p>>2)&1; g_cpu.Z=(p>>1)&1; g_cpu.C=p&1; }
label_BEC0:;
    /* $BEC0: 81 */ maybe_trigger_vblank(6); nes_write(nes_read16zp((0x28 + g_cpu.X) & 0xFF), g_cpu.A);
label_BEC2:;
    /* $BEC2: 87 */ maybe_trigger_vblank(3); nes_write(0x2C, g_cpu.A & g_cpu.X); /* SAX */
label_BEC4:;
    /* $BEC4: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x842C); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_BEC7:;
    /* $BEC7: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) { maybe_trigger_vblank(1); call_by_address(0xBE4C); return; }
label_BEC9:;
    /* $BEC9: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x84); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BECB:;
    /* $BECB: 0C */ maybe_trigger_vblank(4); (void)nes_read(0x6283); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BECE:;
    /* $BECE: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) {
    maybe_trigger_vblank(1);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_BE54;
    }
label_BED0:;
    /* $BED0: 12 */ maybe_trigger_vblank(2); /* ILLEGAL $12 — skip 1 */
label_BED1:; /* UpdSte */
    /* $BED1: 83 */ maybe_trigger_vblank(6); nes_write(nes_read16zp((0x1C + g_cpu.X) & 0xFF), g_cpu.A & g_cpu.X); /* SAX */
label_BED3:;
    /* $BED3: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_BED4:; /* BlockObjMT_Updater */
    /* $BED4: 1E */ maybe_trigger_vblank(7); { uint16_t a=(0x2622 + g_cpu.X) & 0xFFFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BED7:;
    /* $BED7: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_BED8:;
    /* $BED8: 1E */ maybe_trigger_vblank(7); { uint16_t a=(0x1C04 + g_cpu.X) & 0xFFFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BEDB:;
    /* $BEDB: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xBEDB); return;
label_BEDC:;
    /* $BEDC: E3 */ maybe_trigger_vblank(8); { uint16_t a=nes_read16zp((0xE1 + g_cpu.X) & 0xFF); uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); int16_t r=g_cpu.A-v-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,v); g_cpu.A=r&0xFF; }
label_BEDE:;
    /* $BEDE: E3 */ maybe_trigger_vblank(8); { uint16_t a=nes_read16zp((0x1D + g_cpu.X) & 0xFF); uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); int16_t r=g_cpu.A-v-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,v); g_cpu.A=r&0xFF; }
label_BEE0:;
    /* $BEE0: DE */ maybe_trigger_vblank(7); { uint16_t a=(0x23E0 + g_cpu.X) & 0xFFFF; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BEE3:;
    /* $BEE3: EC */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x7475); int r=g_cpu.X-m; g_cpu.C=(g_cpu.X>=m)?1:0; FLAG_NZ(r&0xFF); }
label_BEE6:;
    /* $BEE6: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) {
    maybe_trigger_vblank(1);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_BEDC;
    }
label_BEE8:;
    /* $BEE8: F6 */ maybe_trigger_vblank(6); { uint16_t a=(0xEA + g_cpu.X) & 0xFF; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BEEA:;
    /* $BEEA: 31 */ maybe_trigger_vblank(5); g_cpu.A &= nes_read((nes_read16zp(0x2D) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_BEEC:;
    /* $BEEC: 83 */ maybe_trigger_vblank(6); nes_write(nes_read16zp((0x12 + g_cpu.X) & 0xFF), g_cpu.A & g_cpu.X); /* SAX */
label_BEEE:;
    /* $BEEE: 14 */ maybe_trigger_vblank(4); (void)nes_read((0x04 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BEF0:;
    /* $BEF0: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_BEF1:;
    /* $BEF1: 1A */ maybe_trigger_vblank(2); /* NOP */
label_BEF2:;
    /* $BEF2: 1C */ maybe_trigger_vblank(4); (void)nes_read((0x2614 + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BEF5:;
    /* $BEF5: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_BEF6:;
    /* $BEF6: 1E */ maybe_trigger_vblank(7); { uint16_t a=(0x181C + g_cpu.X) & 0xFFFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BEF9:;
    /* $BEF9: 1E */ maybe_trigger_vblank(7); { uint16_t a=(0x0C22 + g_cpu.X) & 0xFFFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BEFC:;
    /* $BEFC: 14 */ maybe_trigger_vblank(4); (void)nes_read((0xFF + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BEFE:; /* NextBUpd */
    /* $BEFE: FF */ maybe_trigger_vblank(7); { uint16_t a=(0x00FF + g_cpu.X) & 0xFFFF; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); int16_t r=g_cpu.A-v-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,v); g_cpu.A=r&0xFF; }
label_BF01:;
    /* $BF01: 88 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y-1)&0xFF; FLAG_NZ(g_cpu.Y);
label_BF02:; /* MoveEnemyHorizontally */
    /* $BF02: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xBF02); return;
label_BF03:; return;
label_BF06:; return;
label_BF07:; return;
label_BF09:; return;
label_BF0B:; return;
label_BF0E:; return;
label_BF0F:; return;
label_BF10:; return;
label_BF12:; return;
label_BF14:; return;
label_BF16:; return;
label_BF18:; return;
label_BF1A:; return;
label_BF1C:; return;
label_BF1E:; return;
label_BF20:; return;
label_BF22:; return;
label_BF24:; return;
label_BF26:; return;
label_BF27:; return;
label_BF2A:; return;
label_BF2B:; return;
label_BF2D:; return;
label_BF2F:; return;
label_BF31:; return;
label_BF34:; return;
label_BF35:; return;
label_BF37:; return;
label_BF39:; return;
label_BF3B:; return;
label_BF3E:; return;
label_BF3F:; return;
label_BF41:; return;
label_BF44:; return;
label_BF45:; return;
label_BF47:; return;
label_BF49:; return;
label_BF4C:; return;
label_BF4D:; return;
label_BF4F:; return;
label_BF51:; return;
label_BF53:; return;
label_BF56:; return;
label_BF57:; return;
label_BF58:; return;
label_BF59:; return;
label_BF5B:; return;
label_BF5D:; return;
label_BF5F:; return;
label_BF62:; return;
label_BF64:; return;
label_BF65:; return;
label_BF66:; return;
label_BF68:; return;
label_BF6A:; return;
label_BF6C:; return;
label_BF6F:; return;
label_BF70:; return;
label_BF72:; return;
label_BF73:; return;
label_BF74:; return;
label_BF76:; return;
label_BF78:; return;
label_BF7B:; return;
label_BF7C:; return;
label_BF7E:; return;
label_BF80:; return;
label_BF82:; return;
label_BF83:; return;
label_BF86:; return;
label_BF88:; return;
label_BF8A:; return;
label_BF8D:; return;
label_BF8E:; return;
label_BF8F:; return;
label_BF91:; return;
label_BF92:; return;
label_BF94:; return;
label_BF97:; return;
label_BF9A:; return;
label_BF9C:; return;
label_BF9E:; return;
label_BFA0:; return;
label_BFA2:; return;
label_BFA4:; return;
label_BFA5:; return;
label_BFA6:; return;
label_BFA8:; return;
label_BFAA:; return;
label_BFAC:; return;
label_BFAE:; return;
label_BFB0:; return;
label_BFB2:; return;
label_BFB4:; return;
label_BFB6:; return;
label_BFB8:; return;
label_BFBA:; return;
label_BFBC:; return;
label_BFBE:; return;
label_BFC0:; return;
label_BFC2:; return;
label_BFC4:; return;
label_BFC6:; return;
label_BFC8:; return;
label_BFCA:; return;
label_BFCC:; return;
label_BFCE:; return;
label_BFD0:; return;
label_BFD3:; return;
label_BFD4:; return;
label_BFD7:; return;
label_BFDA:; return;
label_BFDD:; return;
label_BFE0:; return;
label_BFE3:; return;
label_BFE6:; return;
label_BFE7:; return;
label_BFE8:; return;
label_BFEA:; return;
label_BFEC:; return;
label_BFEE:; return;
label_BFF0:; return;
label_BFF3:; return;
label_BFF4:; return;
label_BFF7:; return;
label_BFFA:; return;
label_BFFC:; return;
label_BFFD:; return;
label_BFFF:; return;
label_C002:; return;
label_C004:; return;
label_C006:; return;
label_C008:; return;
label_C00B:; return;
label_C00D:; return;
label_C00F:; return;
label_C011:; return;
label_C013:; return;
label_C015:; return;
label_C018:; return;
label_C019:; return;
label_C01B:; return;
label_C01D:; return;
label_C01F:; return;
label_C020:; return;
label_C021:; return;
label_C023:; return;
label_C026:; return;
label_C027:; return;
label_C029:; return;
label_C02C:; return;
label_C02E:; return;
label_C030:; return;
label_C032:; return;
label_C034:; return;
label_C036:; return;
label_C039:; return;
label_C03B:; return;
label_C03D:; return;
label_C03F:; return;
label_C041:; return;
label_C043:; return;
label_C046:; return;
label_C047:; return;
label_C049:; return;
label_C04A:; return;
label_C04B:; return;
label_C04D:; return;
label_C04E:; return;
label_C050:; return;
label_C053:; return;
label_C056:; return;
label_C058:; return;
label_C05A:; return;
label_C05C:; return;
label_C05F:; return;
label_C060:; return;
label_C062:; return;
label_C063:; return;
label_C066:; return;
label_C068:; return;
label_C06A:; return;
label_C06B:; return;
label_C06D:; return;
label_C06F:; return;
label_C071:; return;
label_C073:; return;
label_C075:; return;
label_C077:; return;
label_C079:; return;
label_C07B:; return;
label_C07C:; return;
label_C07E:; return;
label_C080:; return;
label_C082:; return;
label_C084:; return;
label_C086:; return;
label_C087:; return;
label_C089:; return;
label_C08B:; return;
label_C08D:; return;
label_C090:; return;
label_C092:; return;
label_C095:; return;
label_C097:; return;
label_C099:; return;
label_C09C:; return;
label_C09F:; return;
label_C0A0:; return;
label_C0A2:; return;
label_C0A5:; return;
label_C0A8:; return;
label_C0A9:; return;
label_C0AB:; return;
label_C0AE:; return;
label_C0B1:; return;
label_C0B2:; return;
label_C0B4:; return;
label_C0B7:; return;
label_C0B9:; return;
label_C0BC:; return;
label_C0BF:; return;
label_C0C2:; return;
label_C0C5:; return;
label_C0C8:; return;
label_C0CB:; return;
label_C0CC:; return;
label_C0CF:; return;
label_C0D1:; return;
label_C0D4:; return;
label_C0D6:; return;
label_C0D8:; return;
label_C0D9:; return;
label_C0DB:; return;
label_C0DE:; return;
label_C0E1:; return;
label_C0E3:; return;
label_C0E6:; return;
label_C0E9:; return;
label_C0EB:; return;
label_C0ED:; return;
label_C0F0:; return;
label_C0F2:; return;
label_C0F4:; return;
label_C0F6:; return;
label_C0F8:; return;
label_C0FB:; return;
label_C0FD:; return;
label_C0FF:; return;
label_C102:; return;
label_C105:; return;
label_C108:; return;
label_C10A:; return;
label_C10C:; return;
label_C10F:; return;
label_C111:; return;
label_C113:; return;
label_C115:; return;
label_C118:; return;
label_C11A:; return;
label_C11C:; return;
label_C11F:; return;
label_C122:; return;
label_C124:; return;
label_C127:; return;
label_C12A:; return;
label_C12C:; return;
label_C12F:; return;
label_C132:; return;
label_C134:; return;
label_C136:; return;
label_C138:; return;
label_C13A:; return;
label_C13C:; return;
label_C13E:; return;
label_C141:; return;
label_C144:; return;
label_C147:; return;
label_C149:; return;
label_C14B:; return;
label_C14D:; return;
label_C150:; return;
label_C152:; return;
label_C154:; return;
label_C156:; return;
label_C158:; return;
label_C15A:; return;
label_C15B:; return;
label_C15D:; return;
label_C15F:; return;
label_C161:; return;
label_C163:; return;
label_C164:; return;
label_C167:; return;
label_C168:; return;
label_C16A:; return;
label_C16C:; return;
label_C16E:; return;
label_C171:; return;
label_C173:; return;
label_C175:; return;
label_C178:; return;
label_C179:; return;
label_C17B:; return;
label_C17C:; return;
label_C17E:; return;
label_C181:; return;
label_C183:; return;
label_C186:; return;
label_C189:; return;
label_C18A:; return;
label_C18C:; return;
label_C18E:; return;
label_C190:; return;
label_C192:; return;
label_C195:; return;
label_C197:; return;
label_C198:; return;
label_C19A:; return;
label_C19C:; return;
label_C19F:; return;
label_C1A2:; return;
label_C1A5:; return;
label_C1A8:; return;
label_C1AB:; return;
label_C1AE:; return;
label_C1B0:; return;
label_C1B2:; return;
label_C1B4:; return;
label_C1B6:; return;
label_C1B9:; return;
label_C1BB:; return;
label_C1BE:; return;
label_C1C0:; return;
label_C1C2:; return;
label_C1C4:; return;
label_C1C6:; return;
label_C1C8:; return;
label_C1CB:; return;
label_C1CD:; return;
label_C1CF:; return;
label_C1D1:; return;
label_C1D3:; return;
label_C1D5:; return;
label_C1D7:; return;
label_C1D9:; return;
label_C1DB:; return;
label_C1DC:; return;
label_C1DD:; return;
label_C1DE:; return;
label_C1DF:; return;
label_C1E1:; return;
label_C1E3:; return;
label_C1E5:; return;
label_C1E6:; return;
label_C1E8:; return;
label_C1EA:; return;
label_C1EC:; return;
label_C1EF:; return;
label_C1F1:; return;
label_C1F3:; return;
label_C1F5:; return;
label_C1F7:; return;
label_C1F9:; return;
label_C1FB:; return;
label_C1FD:; return;
label_C1FF:; return;
label_C201:; return;
label_C204:; return;
label_C206:; return;
label_C208:; return;
label_C20A:; return;
label_C20C:; return;
label_C20E:; return;
label_C211:; return;
label_C213:; return;
label_C215:; return;
label_C216:; return;
label_C219:; return;
label_C21B:; return;
label_C21E:; return;
label_C220:; return;
label_C222:; return;
label_C224:; return;
label_C226:; return;
label_C228:; return;
label_C22A:; return;
label_C22D:; return;
label_C22E:; return;
label_C231:; return;
label_C232:; return;
label_C233:; return;
label_C235:; return;
label_C236:; return;
label_C237:; return;
label_C238:; return;
label_C239:; return;
label_C23A:; return;
label_C23D:; return;
label_C23F:; return;
label_C240:; return;
label_C242:; return;
label_C245:; return;
label_C246:; return;
label_C248:; return;
label_C24A:; return;
label_C24D:; return;
label_C25E:; return;
label_C261:; return;
label_C264:; return;
label_C266:; return;
label_C269:; return;
label_C26B:; return;
label_C26C:; return;
label_C26E:; return;
label_C270:; return;
label_C272:; return;
label_C273:; return;
label_C275:; return;
label_C277:; return;
label_C279:; return;
label_C27B:; return;
label_C27E:; return;
label_C27F:; return;
label_C2F0:; return;
label_C2F1:; return;
label_C2F4:; return;
label_C2F7:; return;
label_C2F9:; return;
label_C2FB:; return;
label_C2FD:; return;
label_C2FE:; return;
label_C301:; return;
label_C302:; return;
label_C304:; return;
label_C307:; return;
label_C309:; return;
label_C30B:; return;
label_C30C:; return;
label_C30D:; return;
label_C30F:; return;
label_C311:; return;
label_C312:; return;
label_C314:; return;
label_C316:; return;
label_C319:; return;
label_C31B:; return;
label_C31E:; return;
label_C321:; return;
label_C323:; return;
label_C325:; return;
label_C326:; return;
label_C328:; return;
label_C32A:; return;
label_C32D:; return;
label_C32F:; return;
label_C332:; return;
label_C335:; return;
label_C338:; return;
label_C33A:; return;
label_C33D:; return;
label_C33F:; return;
label_C342:; return;
label_C344:; return;
label_C346:; return;
label_C348:; return;
label_C34A:; return;
label_C34C:; return;
label_C34E:; return;
label_C351:; return;
label_C353:; return;
label_C355:; return;
label_C356:; return;
label_C358:; return;
label_C35A:; return;
label_C35C:; return;
label_C35F:; return;
label_C361:; return;
label_C363:; return;
label_C365:; return;
label_C367:; return;
label_C36A:; return;
label_C36B:; return;
label_C36D:; return;
label_C36F:; return;
label_C371:; return;
label_C374:; return;
label_C375:; return;
label_C378:; return;
label_C37B:; return;
label_C37D:; return;
label_C37F:; return;
label_C381:; return;
label_C384:; return;
label_C385:; return;
label_C388:; return;
label_C38A:; return;
label_C38C:; return;
label_C38F:; return;
label_C392:; return;
label_C395:; return;
label_C398:; return;
label_C39A:; return;
label_C39B:; return;
label_C39C:; return;
label_C39F:; return;
label_C3A1:; return;
label_C3A3:; return;
label_C3A5:; return;
label_C3A8:; return;
label_C3AB:; return;
label_C3AD:; return;
label_C3AF:; return;
label_C3B2:; return;
label_C3B4:; return;
label_C3B7:; return;
label_C3B9:; return;
label_C3BB:; return;
label_C3BC:; return;
label_C3BE:; return;
label_C3C1:; return;
label_C3C4:; return;
label_C3C6:; return;
label_C3C8:; return;
label_C3CA:; return;
label_C3CC:; return;
label_C3CE:; return;
label_C3CF:; return;
label_C3D1:; return;
label_C3D3:; return;
label_C3D5:; return;
label_C3D7:; return;
label_C3D9:; return;
label_C3DB:; return;
label_C3DE:; return;
label_C3E0:; return;
label_C3E3:; return;
label_C3E5:; return;
label_C3E6:; return;
label_C3E8:; return;
label_C3EA:; return;
label_C3EC:; return;
label_C3EF:; return;
label_C3F1:; return;
label_C3F4:; return;
label_C3F6:; return;
label_C3F9:; return;
label_C3FB:; return;
label_C3FD:; return;
label_C3FF:; return;
label_C402:; return;
label_C403:; return;
label_C405:; return;
label_C407:; return;
label_C40A:; return;
label_C40C:; return;
label_C40D:; return;
label_C40F:; return;
label_C412:; return;
label_C414:; return;
label_C415:; return;
label_C416:; return;
label_C417:; return;
label_C418:; return;
label_C419:; return;
label_C41B:; return;
label_C41D:; return;
label_C420:; return;
label_C422:; return;
label_C424:; return;
label_C426:; return;
label_C427:; return;
label_C42A:; return;
label_C42C:; return;
label_C42E:; return;
label_C42F:; return;
label_C431:; return;
label_C432:; return;
label_C433:; return;
label_C434:; return;
label_C437:; return;
label_C439:; return;
label_C43B:; return;
label_C43D:; return;
label_C43F:; return;
label_C440:; return;
label_C442:; return;
label_C444:; return;
label_C446:; return;
label_C448:; return;
label_C44A:; return;
label_C44C:; return;
label_C44E:; return;
label_C44F:; return;
label_C450:; return;
label_C451:; return;
label_C452:; return;
label_C453:; return;
label_C454:; return;
label_C455:; return;
label_C456:; return;
label_C458:; return;
label_C459:; return;
label_C45C:; return;
label_C45E:; return;
label_C460:; return;
label_C462:; return;
label_C463:; return;
label_C465:; return;
label_C466:; return;
label_C469:; return;
label_C46C:; return;
label_C46F:; return;
label_C471:; return;
label_C473:; return;
label_C474:; return;
label_C476:; return;
label_C478:; return;
label_C47A:; return;
label_C47B:; return;
label_C47D:; return;
label_C47F:; return;
label_C481:; return;
label_C483:; return;
label_C485:; return;
label_C488:; return;
label_C48A:; return;
label_C48B:; return;
label_C48D:; return;
label_C48F:; return;
label_C491:; return;
label_C492:; return;
label_C494:; return;
label_C496:; return;
label_C498:; return;
label_C49B:; return;
label_C49E:; return;
label_C4A0:; return;
label_C4A3:; return;
label_C4A5:; return;
label_C4A6:; return;
label_C4A9:; return;
label_C4AC:; return;
label_C4AE:; return;
label_C4B0:; return;
label_C4B3:; return;
label_C4B5:; return;
label_C4B6:; return;
label_C4B9:; return;
label_C4BC:; return;
label_C4BE:; return;
label_C4C1:; return;
label_C4C3:; return;
label_C4C4:; return;
label_C4C6:; return;
label_C4C8:; return;
label_C4CA:; return;
label_C4CD:; return;
label_C4CF:; return;
label_C4D1:; return;
label_C4D3:; return;
label_C4D5:; return;
label_C4D7:; return;
label_C4D9:; return;
label_C4DB:; return;
label_C4DD:; return;
label_C4DF:; return;
label_C4E1:; return;
label_C4E3:; return;
label_C4E4:; return;
label_C4E5:; return;
label_C4E6:; return;
label_C4E8:; return;
label_C4EA:; return;
label_C4ED:; return;
label_C4EF:; return;
label_C4F1:; return;
label_C4F4:; return;
label_C4F6:; return;
label_C4F8:; return;
label_C4F9:; return;
label_C4FA:; return;
label_C4FC:; return;
label_C4FD:; return;
label_C500:; return;
label_C502:; return;
label_C504:; return;
label_C506:; return;
label_C508:; return;
label_C50A:; return;
label_C50C:; return;
label_C50D:; return;
label_C50F:; return;
label_C511:; return;
label_C513:; return;
label_C515:; return;
label_C516:; return;
label_C518:; return;
label_C51A:; return;
label_C51C:; return;
label_C51D:; return;
label_C51F:; return;
label_C521:; return;
label_C523:; return;
label_C524:; return;
label_C527:; return;
label_C529:; return;
label_C52B:; return;
label_C52D:; return;
label_C530:; return;
label_C532:; return;
label_C533:; return;
label_C536:; return;
label_C538:; return;
label_C53A:; return;
label_C53C:; return;
label_C53E:; return;
label_C540:; return;
label_C542:; return;
label_C544:; return;
label_C546:; return;
label_C548:; return;
label_C549:; return;
label_C54C:; return;
label_C54F:; return;
label_C551:; return;
label_C554:; return;
label_C557:; return;
label_C559:; return;
label_C55C:; return;
label_C55E:; return;
label_C561:; return;
label_C563:; return;
label_C565:; return;
label_C568:; return;
label_C56B:; return;
label_C56D:; return;
label_C570:; return;
label_C571:; return;
label_C574:; return;
label_C575:; return;
label_C577:; return;
label_C578:; return;
label_C57B:; return;
label_C57D:; return;
label_C580:; return;
label_C581:; return;
label_C583:; return;
label_C586:; return;
label_C588:; return;
label_C58B:; return;
label_C58D:; return;
label_C590:; return;
label_C592:; return;
label_C594:; return;
label_C597:; return;
label_C599:; return;
label_C59C:; return;
label_C59D:; return;
label_C59F:; return;
label_C5A1:; return;
label_C5A4:; return;
label_C5A7:; return;
label_C5A9:; return;
label_C5AB:; return;
label_C5AD:; return;
label_C5AF:; return;
label_C5B1:; return;
label_C5B4:; return;
label_C5B7:; return;
label_C5B9:; return;
label_C5BB:; return;
label_C5BE:; return;
label_C5BF:; return;
label_C5C1:; return;
label_C5C4:; return;
label_C5C6:; return;
label_C5C7:; return;
label_C5C9:; return;
label_C5CC:; return;
label_C5CF:; return;
label_C5D1:; return;
label_C5D4:; return;
label_C5D5:; return;
label_C5D8:; return;
label_C5DA:; return;
label_C5DD:; return;
label_C5DE:; return;
label_C5E0:; return;
label_C5E2:; return;
label_C5E5:; return;
label_C5E7:; return;
label_C5E9:; return;
label_C5EC:; return;
label_C5EF:; return;
label_C5F0:; return;
label_C5F2:; return;
label_C5F4:; return;
label_C5F7:; return;
label_C5F9:; return;
label_C5FC:; return;
label_C5FD:; return;
label_C5FF:; return;
label_C601:; return;
label_C604:; return;
label_C606:; return;
label_C609:; return;
label_C60A:; return;
label_C60D:; return;
label_C60F:; return;
label_C611:; return;
label_C613:; return;
label_C614:; return;
label_C617:; return;
label_C61A:; return;
label_C61C:; return;
label_C61F:; return;
label_C621:; return;
label_C624:; return;
label_C626:; return;
label_C628:; return;
label_C62A:; return;
label_C62B:; return;
label_C62E:; return;
label_C630:; return;
label_C631:; return;
label_C632:; return;
label_C634:; return;
label_C635:; return;
label_C636:; return;
label_C639:; return;
label_C63B:; return;
label_C63C:; return;
label_C63E:; return;
label_C641:; return;
label_C643:; return;
label_C646:; return;
label_C648:; return;
label_C64A:; return;
label_C64C:; return;
label_C64D:; return;
label_C650:; return;
label_C652:; return;
label_C654:; return;
label_C657:; return;
label_C658:; return;
label_C65A:; return;
label_C65B:; return;
label_C65E:; return;
label_C660:; return;
label_C662:; return;
label_C665:; return;
label_C666:; return;
label_C669:; return;
label_C66A:; return;
label_C66B:; return;
label_C66C:; return;
label_C66F:; return;
label_C671:; return;
label_C673:; return;
label_C675:; return;
label_C677:; return;
label_C67A:; return;
label_C67C:; return;
label_C67E:; return;
label_C680:; return;
label_C682:; return;
label_C683:; return;
label_C685:; return;
label_C687:; return;
label_C689:; return;
label_C68A:; return;
label_C68C:; return;
label_C68E:; return;
label_C690:; return;
label_C691:; return;
label_C693:; return;
label_C695:; return;
label_C697:; return;
label_C698:; return;
label_C69A:; return;
label_C69B:; return;
label_C69D:; return;
label_C6A0:; return;
label_C6A3:; return;
label_C6A5:; return;
label_C6A7:; return;
label_C6A9:; return;
label_C6AB:; return;
label_C6AC:; return;
label_C6AF:; return;
label_C6B1:; return;
label_C6B3:; return;
label_C6B4:; return;
label_C6B7:; return;
label_C6B9:; return;
label_C6BB:; return;
label_C6BC:; return;
label_C6BD:; return;
label_C6BF:; return;
label_C6C0:; return;
label_C6C3:; return;
label_C6C5:; return;
label_C6C8:; return;
label_C6CA:; return;
label_C6CC:; return;
label_C6CE:; return;
label_C6D1:; return;
label_C6D4:; return;
label_C6D6:; return;
label_C6D7:; return;
label_C6DA:; return;
label_C6DD:; return;
label_C6DF:; return;
label_C6E0:; return;
label_C6E1:; return;
label_C6E3:; return;
label_C6E6:; return;
label_C6E9:; return;
label_C6EC:; return;
label_C6EF:; return;
label_C6F2:; return;
label_C6F5:; return;
label_C6F7:; return;
label_C6FA:; return;
label_C6FD:; return;
label_C6FF:; return;
label_C700:; return;
label_C702:; return;
label_C704:; return;
label_C707:; return;
label_C709:; return;
label_C70C:; return;
label_C70E:; return;
label_C710:; return;
label_C711:; return;
label_C713:; return;
label_C715:; return;
label_C717:; return;
label_C719:; return;
label_C71B:; return;
label_C71D:; return;
label_C71E:; return;
label_C720:; return;
label_C721:; return;
label_C723:; return;
label_C725:; return;
label_C726:; return;
label_C728:; return;
label_C72B:; return;
label_C72D:; return;
label_C72F:; return;
label_C730:; return;
label_C732:; return;
label_C734:; return;
label_C736:; return;
label_C738:; return;
label_C73A:; return;
label_C73C:; return;
label_C73F:; return;
label_C741:; return;
label_C744:; return;
label_C746:; return;
label_C748:; return;
label_C749:; return;
label_C74A:; return;
label_C74C:; return;
label_C74D:; return;
label_C750:; return;
label_C752:; return;
label_C753:; return;
label_C755:; return;
label_C757:; return;
label_C759:; return;
label_C75B:; return;
label_C75D:; return;
label_C75F:; return;
label_C761:; return;
label_C763:; return;
label_C765:; return;
label_C767:; return;
label_C768:; return;
label_C76A:; return;
label_C76C:; return;
label_C76E:; return;
label_C770:; return;
label_C772:; return;
label_C774:; return;
label_C776:; return;
label_C778:; return;
label_C77A:; return;
label_C77C:; return;
label_C77F:; return;
label_C782:; return;
label_C784:; return;
label_C787:; return;
label_C789:; return;
label_C78B:; return;
label_C78C:; return;
label_C78E:; return;
label_C790:; return;
label_C792:; return;
label_C795:; return;
label_C796:; return;
label_C798:; return;
label_C79B:; return;
label_C79D:; return;
label_C7A0:; return;
label_C7A2:; return;
label_C7A5:; return;
label_C7A6:; return;
label_C7A8:; return;
label_C7BB:; return;
label_C7BD:; return;
label_C7BF:; return;
label_C7C1:; return;
label_C7C3:; return;
label_C7C6:; return;
label_C7C7:; return;
label_C7C9:; return;
label_C7CB:; return;
label_C7CE:; return;
label_C7D0:; return;
label_C7D1:; return;
label_C7D3:; return;
label_C7D5:; return;
label_C7D7:; return;
label_C7D9:; return;
label_C7DB:; return;
label_C7DE:; return;
label_C7DF:; return;
label_C7E1:; return;
label_C7E3:; return;
label_C7E6:; return;
label_C7E8:; return;
label_C7EA:; return;
label_C7ED:; return;
label_C7EF:; return;
label_C7F2:; return;
label_C7F4:; return;
label_C7F6:; return;
label_C7F7:; return;
label_C7F8:; return;
label_C7FB:; return;
label_C7FD:; return;
label_C7FF:; return;
label_C800:; return;
label_C803:; return;
label_C805:; return;
label_C808:; return;
label_C80B:; return;
label_C80D:; return;
label_C80F:; return;
label_C812:; return;
label_C814:; return;
label_C816:; return;
label_C818:; return;
label_C81A:; return;
label_C81B:; return;
label_C81D:; return;
label_C81F:; return;
label_C822:; return;
label_C823:; return;
label_C824:; return;
label_C826:; return;
label_C828:; return;
label_C82B:; return;
label_C82D:; return;
label_C830:; return;
label_C832:; return;
label_C834:; return;
label_C837:; return;
label_C839:; return;
label_C83B:; return;
label_C83E:; return;
label_C83F:; return;
label_C842:; return;
label_C845:; return;
label_C848:; return;
label_C84B:; return;
label_C84D:; return;
label_C850:; return;
label_C852:; return;
label_C854:; return;
label_C857:; return;
label_C859:; return;
label_C85C:; return;
label_C85E:; return;
label_C860:; return;
label_C862:; return;
label_C865:; return;
label_C867:; return;
label_C86A:; return;
label_C86B:; return;
label_C86C:; return;
label_C86F:; return;
label_C870:; return;
label_C873:; return;
label_C874:; return;
label_C877:; return;
label_C879:; return;
label_C87B:; return;
label_C87E:; return;
label_C880:; return;
label_C881:; return;
label_C882:; return;
label_C884:; return;
label_C886:; return;
label_C888:; return;
label_C88A:; return;
label_C88C:; return;
label_C88D:; return;
label_C88F:; return;
label_C8D6:; return;
label_C8D7:; return;
label_C8DA:; return;
label_C8DD:; return;
label_C8E0:; return;
label_C8E2:; return;
label_C8E5:; return;
label_C8E8:; return;
label_C8EB:; return;
label_C8EE:; return;
label_C8F1:; return;
label_C8F4:; return;
label_C8F7:; return;
label_C8FA:; return;
label_C8FD:; return;
label_C8FF:; return;
label_C902:; return;
label_C905:; return;
label_C907:; return;
label_C934:; return;
label_C935:; return;
label_C938:; return;
label_C93B:; return;
label_C93E:; return;
label_C941:; return;
label_C944:; return;
label_C947:; return;
label_C94A:; return;
label_C94D:; return;
label_C950:; return;
label_C953:; return;
label_C956:; return;
label_C959:; return;
label_C95C:; return;
label_C95F:; return;
label_C962:; return;
label_C965:; return;
label_C968:; return;
label_C96B:; return;
label_C96E:; return;
label_C971:; return;
label_C974:; return;
label_C976:; return;
label_C979:; return;
label_C97C:; return;
label_C97F:; return;
label_C982:; return;
label_C984:; return;
label_C985:; return;
label_C987:; return;
label_C998:; return;
label_C99A:; return;
label_C99C:; return;
label_C99E:; return;
label_C9A0:; return;
label_C9A3:; return;
label_C9A6:; return;
label_C9A9:; return;
label_C9AC:; return;
label_C9AF:; return;
label_C9B0:; return;
label_C9B3:; return;
label_C9B5:; return;
label_C9B8:; return;
label_C9BB:; return;
label_C9BD:; return;
label_C9C0:; return;
label_C9C2:; return;
label_C9C4:; return;
label_C9C7:; return;
label_C9C9:; return;
label_C9CB:; return;
label_C9CE:; return;
label_C9D0:; return;
label_C9D1:; return;
label_C9D2:; return;
label_C9D3:; return;
label_C9D4:; return;
label_C9D5:; return;
label_C9D6:; return;
label_C9D9:; return;
label_C9DC:; return;
label_C9DE:; return;
label_C9E1:; return;
label_C9E3:; return;
label_C9E5:; return;
label_C9E7:; return;
label_C9EA:; return;
label_C9EC:; return;
label_C9EE:; return;
label_C9F1:; return;
label_C9F3:; return;
label_C9F6:; return;
label_C9F9:; return;
label_C9FC:; return;
label_C9FF:; return;
label_CA01:; return;
label_CA03:; return;
label_CA05:; return;
label_CA07:; return;
label_CA0A:; return;
label_CA0D:; return;
label_CA12:; return;
label_CA14:; return;
label_CA16:; return;
label_CA18:; return;
label_CA1A:; return;
label_CA1C:; return;
label_CA1E:; return;
label_CA20:; return;
label_CA22:; return;
label_CA24:; return;
label_CA26:; return;
label_CA28:; return;
label_CA2A:; return;
label_CA2C:; return;
label_CA2E:; return;
label_CA31:; return;
label_CA33:; return;
label_CA35:; return;
label_CA37:; return;
label_CA39:; return;
label_CA3B:; return;
label_CA3D:; return;
label_CA3F:; return;
label_CA41:; return;
label_CA44:; return;
label_CA45:; return;
label_CA48:; return;
label_CA4A:; return;
label_CA4B:; return;
label_CA4E:; return;
label_CA51:; return;
label_CA54:; return;
label_CA56:; return;
label_CA58:; return;
label_CA5A:; return;
label_CA5C:; return;
label_CA5E:; return;
label_CA60:; return;
label_CA62:; return;
label_CA64:; return;
label_CA66:; return;
label_CA69:; return;
label_CA6B:; return;
label_CA6C:; return;
label_CA6F:; return;
label_CA71:; return;
label_CA73:; return;
label_CA75:; return;
label_CA77:; return;
label_CA79:; return;
label_CA7B:; return;
label_CA7D:; return;
label_CA7F:; return;
label_CA81:; return;
label_CA82:; return;
label_CA84:; return;
label_CA86:; return;
label_CA88:; return;
label_CA8A:; return;
label_CA8C:; return;
label_CA8E:; return;
label_CA90:; return;
label_CA92:; return;
label_CA94:; return;
label_CA96:; return;
label_CA98:; return;
label_CA9B:; return;
label_CA9D:; return;
label_CA9F:; return;
label_CAA1:; return;
label_CAA3:; return;
label_CAA5:; return;
label_CAA7:; return;
label_CAA9:; return;
label_CAAB:; return;
label_CAAD:; return;
label_CAAF:; return;
label_CAB2:; return;
label_CAB4:; return;
label_CAB6:; return;
label_CAB7:; return;
label_CAB9:; return;
label_CABA:; return;
label_CABB:; return;
label_CABC:; return;
label_CABF:; return;
label_CAC1:; return;
label_CAC4:; return;
label_CAC5:; return;
label_CAC7:; return;
label_CAC8:; return;
label_CACB:; return;
label_CACD:; return;
label_CACF:; return;
label_CAD1:; return;
label_CAD3:; return;
label_CAD4:; return;
label_CAD5:; return;
label_CAD7:; return;
label_CAD8:; return;
label_CADB:; return;
label_CADD:; return;
label_CADE:; return;
label_CADF:; return;
label_CAE2:; return;
label_CAE4:; return;
label_CAE5:; return;
label_CAE8:; return;
label_CAEB:; return;
label_CAED:; return;
label_CAEF:; return;
label_CAF1:; return;
label_CAF3:; return;
label_CAF5:; return;
label_CAF8:; return;
label_CAF9:; return;
label_CAFC:; return;
label_CAFF:; return;
label_CB01:; return;
label_CB04:; return;
label_CB06:; return;
label_CB09:; return;
label_CB0B:; return;
label_CB0E:; return;
label_CB10:; return;
label_CB12:; return;
label_CB14:; return;
label_CB16:; return;
label_CB18:; return;
label_CB19:; return;
label_CB1B:; return;
label_CB1D:; return;
label_CB1F:; return;
label_CB22:; return;
label_CB25:; return;
label_CB28:; return;
label_CB2B:; return;
label_CB2D:; return;
label_CB2F:; return;
label_CB31:; return;
label_CB33:; return;
label_CB35:; return;
label_CB37:; return;
label_CB39:; return;
label_CB3B:; return;
label_CB3D:; return;
label_CB3F:; return;
label_CB40:; return;
label_CB42:; return;
label_CB44:; return;
label_CB45:; return;
label_CB47:; return;
label_CB49:; return;
label_CB4B:; return;
label_CB4D:; return;
label_CB4F:; return;
label_CB51:; return;
label_CB53:; return;
label_CB54:; return;
label_CB56:; return;
label_CB58:; return;
label_CB5A:; return;
label_CB5C:; return;
label_CB5D:; return;
label_CB5F:; return;
label_CB60:; return;
label_CB61:; return;
label_CB63:; return;
label_CB65:; return;
label_CB66:; return;
label_CB68:; return;
label_CB69:; return;
label_CB6B:; return;
label_CB6D:; return;
label_CB6F:; return;
label_CB71:; return;
label_CB73:; return;
label_CB75:; return;
label_CB76:; return;
label_CB78:; return;
label_CB7A:; return;
label_CB7C:; return;
label_CB7E:; return;
label_CB81:; return;
label_CB83:; return;
label_CB84:; return;
label_CB86:; return;
label_CB87:; return;
label_CB8A:; return;
label_CB8D:; return;
label_CB8F:; return;
label_CB92:; return;
label_CB95:; return;
label_CB98:; return;
label_CB9A:; return;
label_CB9B:; return;
label_CB9C:; return;
label_CB9E:; return;
label_CBA0:; return;
label_CBA2:; return;
label_CBA4:; return;
label_CBA7:; return;
label_CBA9:; return;
label_CBAA:; return;
label_CBAC:; return;
label_CBAF:; return;
label_CBB1:; return;
label_CBB2:; return;
label_CBB5:; return;
label_CBB7:; return;
label_CBB9:; return;
label_CBBB:; return;
label_CBBD:; return;
label_CBBE:; return;
label_CBC0:; return;
label_CBC2:; return;
label_CBC3:; return;
label_CBC5:; return;
label_CBC7:; return;
label_CBC9:; return;
label_CBCB:; return;
label_CBCD:; return;
label_CBCE:; return;
label_CBD0:; return;
label_CBD1:; return;
label_CBD3:; return;
label_CBD5:; return;
label_CBD7:; return;
label_CBD9:; return;
label_CBDB:; return;
label_CBDC:; return;
label_CBDF:; return;
label_CBE1:; return;
label_CBE3:; return;
label_CBE5:; return;
label_CBE7:; return;
label_CBE9:; return;
label_CBEA:; return;
label_CBEC:; return;
label_CBED:; return;
label_CBEF:; return;
label_CBF0:; return;
label_CBF2:; return;
label_CBF5:; return;
label_CBF6:; return;
label_CBF8:; return;
label_CBFB:; return;
label_CBFD:; return;
label_CBFF:; return;
label_CC01:; return;
label_CC03:; return;
label_CC04:; return;
label_CC05:; return;
label_CC07:; return;
label_CC0A:; return;
label_CC0B:; return;
label_CC0D:; return;
label_CC10:; return;
label_CC12:; return;
label_CC14:; return;
label_CC16:; return;
label_CC18:; return;
label_CC1B:; return;
label_CC1C:; return;
label_CC1F:; return;
label_CC21:; return;
label_CC23:; return;
label_CC24:; return;
label_CC26:; return;
label_CC28:; return;
label_CC29:; return;
label_CC2B:; return;
label_CC2D:; return;
label_CC2F:; return;
label_CC31:; return;
label_CC33:; return;
label_CC35:; return;
label_CC36:; return;
label_CC38:; return;
label_CC3A:; return;
label_CC3C:; return;
label_CC3F:; return;
label_CC41:; return;
label_CC43:; return;
label_CC46:; return;
label_CC47:; return;
label_CC49:; return;
label_CC4B:; return;
label_CC4E:; return;
label_CC50:; return;
label_CC53:; return;
label_CC55:; return;
label_CC57:; return;
label_CC58:; return;
label_CC5A:; return;
label_CC5B:; return;
label_CC5E:; return;
label_CC60:; return;
label_CC63:; return;
label_CC64:; return;
label_CC66:; return;
label_CC69:; return;
label_CC6B:; return;
label_CC6D:; return;
label_CC6F:; return;
label_CC71:; return;
label_CC73:; return;
label_CC75:; return;
label_CC77:; return;
label_CC79:; return;
label_CC7B:; return;
label_CC7D:; return;
label_CC7F:; return;
label_CC81:; return;
label_CC83:; return;
label_CC86:; return;
label_CC87:; return;
label_CC89:; return;
label_CC8C:; return;
label_CC8E:; return;
label_CC90:; return;
label_CC92:; return;
label_CC94:; return;
label_CC96:; return;
label_CC99:; return;
label_CC9C:; return;
label_CC9D:; return;
label_CC9F:; return;
label_CCA2:; return;
label_CCA4:; return;
label_CCA6:; return;
label_CCA8:; return;
label_CCAA:; return;
label_CCAC:; return;
label_CCAE:; return;
label_CCB0:; return;
label_CCB2:; return;
label_CCB3:; return;
label_CCB6:; return;
label_CCB8:; return;
label_CCBA:; return;
label_CCBC:; return;
label_CCBD:; return;
label_CCBF:; return;
label_CCC1:; return;
label_CCC3:; return;
label_CCC4:; return;
label_CCC6:; return;
label_CCC7:; return;
label_CCC8:; return;
label_CCCA:; return;
label_CCCC:; return;
label_CCCE:; return;
label_CCD0:; return;
label_CCD1:; return;
label_CCD3:; return;
label_CCD5:; return;
label_CCD8:; return;
label_CCDA:; return;
label_CCDC:; return;
label_CCDF:; return;
label_CCE1:; return;
label_CCE2:; return;
label_CCE3:; return;
label_CCE5:; return;
label_CCE6:; return;
label_CCE8:; return;
label_CCEB:; return;
label_CCEC:; return;
label_CCEE:; return;
label_CCF0:; return;
label_CCF2:; return;
label_CCF4:; return;
label_CCF5:; return;
label_CCF7:; return;
label_CCFA:; return;
label_CCFD:; return;
label_CCFE:; return;
label_CD00:; return;
label_CD03:; return;
label_CD05:; return;
label_CD06:; return;
label_CD07:; return;
label_CD0A:; return;
label_CD0D:; return;
label_CD10:; return;
label_CD13:; return;
label_CD14:; return;
label_CD17:; return;
label_CD18:; return;
label_CD19:; return;
label_CD1C:; return;
label_CD1D:; return;
label_CD1E:; return;
label_CD1F:; return;
label_CD22:; return;
label_CD24:; return;
label_CD26:; return;
label_CD28:; return;
label_CD2A:; return;
label_CD2C:; return;
label_CD2D:; return;
label_CD2E:; return;
label_CD2F:; return;
label_CD31:; return;
label_CD34:; return;
label_CD36:; return;
label_CD37:; return;
label_CD39:; return;
label_CD3B:; return;
label_CD3C:; return;
label_CD3F:; return;
label_CD42:; return;
label_CD44:; return;
label_CD46:; return;
label_CD49:; return;
label_CD4B:; return;
label_CD4E:; return;
label_CD51:; return;
label_CD53:; return;
label_CD55:; return;
label_CD57:; return;
label_CD59:; return;
label_CD5B:; return;
label_CD5D:; return;
label_CD5F:; return;
label_CD61:; return;
label_CD63:; return;
label_CD65:; return;
label_CD66:; return;
label_CD68:; return;
label_CD6A:; return;
label_CD6C:; return;
label_CD6F:; return;
label_CD72:; return;
label_CD75:; return;
label_CD78:; return;
label_CD7B:; return;
label_CD7D:; return;
label_CD80:; return;
label_CD83:; return;
label_CD85:; return;
label_CD87:; return;
label_CD89:; return;
label_CD8C:; return;
label_CD8E:; return;
label_CD90:; return;
label_CD92:; return;
label_CD94:; return;
label_CD96:; return;
label_CD98:; return;
label_CD9A:; return;
label_CD9C:; return;
label_CD9E:; return;
label_CDA1:; return;
label_CDA4:; return;
label_CDA6:; return;
label_CDA8:; return;
label_CDAA:; return;
label_CDAD:; return;
label_CDB0:; return;
label_CDB2:; return;
label_CDB4:; return;
label_CDB6:; return;
label_CDB8:; return;
label_CDBA:; return;
label_CDBB:; return;
label_CDBD:; return;
label_CDBF:; return;
label_CDC1:; return;
label_CDC3:; return;
label_CDC5:; return;
label_CDC7:; return;
label_CDC9:; return;
label_CDCB:; return;
label_CDCC:; return;
label_CDCF:; return;
label_CDD2:; return;
label_CDD4:; return;
label_CDD7:; return;
label_CDD9:; return;
label_CDDC:; return;
label_CDDD:; return;
label_CDDF:; return;
label_CDE2:; return;
label_CDE3:; return;
label_CDE6:; return;
label_CDE8:; return;
label_CDEA:; return;
label_CDEC:; return;
label_CDEE:; return;
label_CDF1:; return;
label_CDF3:; return;
label_CDF5:; return;
label_CDF7:; return;
label_CDF9:; return;
label_CDFB:; return;
label_CDFD:; return;
label_CDFF:; return;
label_CE00:; return;
label_CE03:; return;
label_CE06:; return;
label_CE08:; return;
label_CE0B:; return;
label_CE0C:; return;
label_CE0D:; return;
label_CE10:; return;
label_CE13:; return;
label_CE15:; return;
label_CE17:; return;
label_CE19:; return;
label_CE1A:; return;
label_CE1C:; return;
label_CE1E:; return;
label_CE21:; return;
label_CE23:; return;
label_CE26:; return;
label_CE28:; return;
label_CE2A:; return;
label_CE2C:; return;
label_CE2D:; return;
label_CE2E:; return;
label_CE30:; return;
label_CE31:; return;
label_CE32:; return;
label_CE33:; return;
label_CE35:; return;
label_CE37:; return;
label_CE39:; return;
label_CE3A:; return;
label_CE3C:; return;
label_CE3E:; return;
label_CE40:; return;
label_CE42:; return;
label_CE44:; return;
label_CE46:; return;
label_CE49:; return;
label_CE4A:; return;
label_CE4C:; return;
label_CE4E:; return;
label_CE4F:; return;
label_CE51:; return;
label_CE53:; return;
label_CE55:; return;
label_CE56:; return;
label_CE58:; return;
label_CE5A:; return;
label_CE5C:; return;
label_CE5E:; return;
label_CE60:; return;
label_CE62:; return;
label_CE64:; return;
label_CE66:; return;
label_CE67:; return;
label_CE6A:; return;
label_CE6C:; return;
label_CE6F:; return;
label_CE71:; return;
label_CE73:; return;
label_CE75:; return;
label_CE77:; return;
label_CE78:; return;
label_CE7A:; return;
label_CE7C:; return;
label_CE7E:; return;
label_CE7F:; return;
label_CE82:; return;
}

void func_BD0C_b1(void) {
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_BD0C_b1");
#endif
    func_BD0C_b1_body(0);
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
}

void func_BD35_b1(void) {
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_BD35_b1");
#endif
    func_BD0C_b1_body(1);
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
}

void func_BD8C_b1(void) {
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_BD8C_b1");
#endif
    func_BD0C_b1_body(2);
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
}

void func_BEDB_b1(void) {
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_BEDB_b1");
#endif
    func_BD0C_b1_body(3);
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
}

void func_EF8C_body(int _entry) { /* PROfsLoop */
    switch (_entry) {
        case 1: goto label_EF97;
    }
label_EF8C:; /* PROfsLoop */
    /* $EF8C: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xF8; FLAG_NZ(g_cpu.A);
label_EF8E:;
    /* $EF8E: 46 */ maybe_trigger_vblank(5); { uint16_t a=0x00; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_EF90:;
    /* $EF90: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) { maybe_trigger_vblank(1); goto label_EF95; }
label_EF92:;
    /* $EF92: 20 */ maybe_trigger_vblank(6); func_E5C1();
label_EF95:; /* NPROffscr */
    /* $EF95: 98 */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.Y; FLAG_NZ(g_cpu.A);
label_EF96:;
    /* $EF96: 38 */ maybe_trigger_vblank(2); g_cpu.C = 1;
label_EF97:;
    /* $EF97: E9 */ maybe_trigger_vblank(2); { uint8_t m=0x08; int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_EF99:;
    /* $EF99: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_EF9A:;
    /* $EF9A: CA */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X-1)&0xFF; FLAG_NZ(g_cpu.X);
label_EF9B:;
    /* $EF9B: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) {
    maybe_trigger_vblank(1);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_EF8C;
    }
label_EF9D:;
    /* $EF9D: 60 */ maybe_trigger_vblank(6); 
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
    return;
}

void func_EF8C(void) { /* PROfsLoop */
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_EF8C");
#endif
    func_EF8C_body(0);
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
}

void func_EF97(void) {
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_EF97");
#endif
    func_EF8C_body(1);
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
}

void func_824E_b1(void) {
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_824E_b1");
#endif
label_824E:;
    /* $824E: 5B */ maybe_trigger_vblank(7); { uint16_t a=(0xACC2 + g_cpu.Y) & 0xFFFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); g_cpu.A^=v; FLAG_NZ(g_cpu.A); }
label_8251:;
    /* $8251: 39 */ maybe_trigger_vblank(4); g_cpu.A &= nes_read((0xB107 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_8254:;
    /* $8254: E9 */ maybe_trigger_vblank(2); { uint8_t m=0x29; int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_8256:;
    /* $8256: 0F */ maybe_trigger_vblank(6); { uint16_t a=0x0EC9; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); g_cpu.A|=v; FLAG_NZ(g_cpu.A); }
label_8259:;
    /* $8259: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_825E; }
label_825B:;
    /* $825B: EE */ maybe_trigger_vblank(6); { uint16_t a=0x0739; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_825E:;
    /* $825E: EE */ maybe_trigger_vblank(6); { uint16_t a=0x0739; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_8261:;
    /* $8261: EE */ maybe_trigger_vblank(6); { uint16_t a=0x0739; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_8264:;
    /* $8264: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_8266:;
    /* $8266: 8D */ maybe_trigger_vblank(4); nes_write(0x073B, g_cpu.A);
label_8269:;
    /* $8269: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x08); FLAG_NZ(g_cpu.X);
label_826B:;
    /* $826B: 60 */ maybe_trigger_vblank(6); 
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
    return;
}

void func_B3CD_b1(void) {
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_B3CD_b1");
#endif
label_B3CD:;
    /* $B3CD: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x26; FLAG_NZ(g_cpu.A);
label_B3CF:; /* ClimbingSub */
    /* $B3CF: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B3D3; }
label_B3D1:;
    /* $B3D1: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x18; FLAG_NZ(g_cpu.A);
label_B3D3:;
    /* $B3D3: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x82; FLAG_NZ(g_cpu.X);
label_B3D5:;
    /* $B3D5: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0xA7; FLAG_NZ(g_cpu.Y);
label_B3D7:;
    /* $B3D7: 20 */ maybe_trigger_vblank(6); func_F388();
label_B3DA:;
    /* $B3DA: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x28; FLAG_NZ(g_cpu.A);
label_B3DC:;
    /* $B3DC: 8D */ maybe_trigger_vblank(4); nes_write(0x07BB, g_cpu.A);
label_B3DF:;
    /* $B3DF: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07BB); FLAG_NZ(g_cpu.A);
label_B3E2:;
    /* $B3E2: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x25; g_cpu.C=(g_cpu.A>=0x25)?1:0; FLAG_NZ(r&0xFF); }
label_B3E4:;
    /* $B3E4: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B3EC; }
label_B3E6:;
    /* $B3E6: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x5F; FLAG_NZ(g_cpu.X);
label_B3E8:;
    /* $B3E8: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0xF6; FLAG_NZ(g_cpu.Y);
label_B3EA:;
    /* $B3EA: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B3F4; }
label_B3EC:;
    /* $B3EC: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x20; g_cpu.C=(g_cpu.A>=0x20)?1:0; FLAG_NZ(r&0xFF); }
label_B3EE:;
    /* $B3EE: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(2); goto label_B419; }
label_B3F0:;
    /* $B3F0: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x48; FLAG_NZ(g_cpu.X);
label_B3F2:;
    /* $B3F2: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0xBC; FLAG_NZ(g_cpu.Y);
label_B3F4:;
    /* $B3F4: 20 */ maybe_trigger_vblank(6); func_F381();
label_B3F7:;
    /* $B3F7: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(2); goto label_B419; }
label_B3F9:;
    /* $B3F9: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x05; FLAG_NZ(g_cpu.A);
label_B3FB:;
    /* $B3FB: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x99; FLAG_NZ(g_cpu.Y);
label_B3FD:;
    /* $B3FD: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(2); goto label_B403; }
label_B3FF:;
    /* $B3FF: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x0A; FLAG_NZ(g_cpu.A);
label_B401:;
    /* $B401: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x93; FLAG_NZ(g_cpu.Y);
label_B403:;
    /* $B403: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x9E; FLAG_NZ(g_cpu.X);
label_B405:;
    /* $B405: 8D */ maybe_trigger_vblank(4); nes_write(0x07BB, g_cpu.A);
label_B408:;
    /* $B408: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x0C; FLAG_NZ(g_cpu.A);
label_B40A:; /* CSetFDir */
    /* $B40A: 20 */ maybe_trigger_vblank(6); func_F388();
label_B40D:;
    /* $B40D: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07BB); FLAG_NZ(g_cpu.A);
label_B410:;
    /* $B410: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x06; g_cpu.C=(g_cpu.A>=0x06)?1:0; FLAG_NZ(r&0xFF); }
label_B412:;
    /* $B412: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B419; }
label_B414:;
    /* $B414: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xBB; FLAG_NZ(g_cpu.A);
label_B416:;
    /* $B416: 8D */ maybe_trigger_vblank(4); nes_write(0x4001, g_cpu.A);
label_B419:;
    /* $B419: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B47B; }
label_B41B:;
    /* $B41B: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0xFF); FLAG_NZ(g_cpu.Y);
label_B41D:;
    /* $B41D: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_B43F; }
label_B41F:; /* ExitCSub */
    /* $B41F: 84 */ maybe_trigger_vblank(3); nes_write(0xF1, g_cpu.Y);
label_B421:;
    /* $B421: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_B3CD;
    }
label_B423:;
    /* $B423: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_B425:;
    /* $B425: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_B3D1;
    }
label_B427:;
    /* $B427: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_B429:;
    /* $B429: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_B3FF;
    }
label_B42B:; /* FallMForceData */
    /* $B42B: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_B42D:;
    /* $B42D: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_B45B; }
label_B42F:;
    /* $B42F: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_B431:;
    /* $B431: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_B47D; }
label_B433:;
    /* $B433: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_B435:;
    /* $B435: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_B4B6; }
label_B437:;
    /* $B437: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_B439:; /* InitMForceData */
    /* $B439: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_B3F9;
    }
label_B43B:;
    /* $B43B: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_B43D:;
    /* $B43D: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { maybe_trigger_vblank(2); call_by_address(0xB3BF); return; }
label_B43F:;
    /* $B43F: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xF1); FLAG_NZ(g_cpu.A);
label_B441:;
    /* $B441: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_B45A; }
label_B443:; /* MaxRightXSpdData */
    /* $B443: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_B3DF;
    }
label_B445:;
    /* $B445: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B446:;
    /* $B446: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_B3DF;
    }
label_B448:;
    /* $B448: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B449:;
    /* $B449: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) {
    maybe_trigger_vblank(1);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_B40D;
    }
label_B44B:;
    /* $B44B: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B44C:;
    /* $B44C: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_B469; }
label_B44E:;
    /* $B44E: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B44F:;
    /* $B44F: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_B48D; }
label_B451:;
    /* $B451: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B452:;
    /* $B452: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_B4BB; }
label_B454:;
    /* $B454: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B455:;
    /* $B455: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) {
    maybe_trigger_vblank(1);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_B40D;
    }
label_B457:;
    /* $B457: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B458:;
    /* $B458: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_B4A2; }
label_B45A:;
    /* $B45A: 60 */
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
    return; /* branch-target RTS */
label_B45B:;
    /* $B45B: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x0E; FLAG_NZ(g_cpu.A);
label_B45D:;
    /* $B45D: 8D */ maybe_trigger_vblank(4); nes_write(0x07BB, g_cpu.A);
label_B460:;
    /* $B460: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x9C; FLAG_NZ(g_cpu.Y);
label_B462:;
    /* $B462: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x9E; FLAG_NZ(g_cpu.X);
label_B464:;
    /* $B464: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x26; FLAG_NZ(g_cpu.A);
label_B466:;
    /* $B466: 20 */ maybe_trigger_vblank(6); func_F388();
label_B469:;
    /* $B469: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x07BB); FLAG_NZ(g_cpu.Y);
label_B46C:;
    /* $B46C: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xF3B0 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_B46F:;
    /* $B46F: 8D */ maybe_trigger_vblank(4); nes_write(0x4000, g_cpu.A);
label_B472:;
    /* $B472: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x06; g_cpu.C=(g_cpu.Y>=0x06)?1:0; FLAG_NZ(r&0xFF); }
label_B474:;
    /* $B474: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B47B; }
label_B476:;
    /* $B476: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x9E; FLAG_NZ(g_cpu.A);
label_B478:;
    /* $B478: 8D */ maybe_trigger_vblank(4); nes_write(0x4002, g_cpu.A);
label_B47B:;
    /* $B47B: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B4A2; }
label_B47D:;
    /* $B47D: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x0E; FLAG_NZ(g_cpu.A);
label_B47F:;
    /* $B47F: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0xCB; FLAG_NZ(g_cpu.Y);
label_B481:;
    /* $B481: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x9F; FLAG_NZ(g_cpu.X);
label_B483:;
    /* $B483: 8D */ maybe_trigger_vblank(4); nes_write(0x07BB, g_cpu.A);
label_B486:;
    /* $B486: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x28; FLAG_NZ(g_cpu.A);
label_B488:; /* NoJump */
    /* $B488: 20 */ maybe_trigger_vblank(6); func_F388();
label_B48B:; /* ProcJumping */
    /* $B48B: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B4A2; }
label_B48D:;
    /* $B48D: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x07BB); FLAG_NZ(g_cpu.Y);
label_B490:;
    /* $B490: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x08; g_cpu.C=(g_cpu.Y>=0x08)?1:0; FLAG_NZ(r&0xFF); }
label_B492:;
    /* $B492: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B49D; }
label_B494:;
    /* $B494: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xA0; FLAG_NZ(g_cpu.A);
label_B496:;
    /* $B496: 8D */ maybe_trigger_vblank(4); nes_write(0x4002, g_cpu.A);
label_B499:;
    /* $B499: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x9F; FLAG_NZ(g_cpu.A);
label_B49B:;
    /* $B49B: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B49F; }
label_B49D:;
    /* $B49D: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x90; FLAG_NZ(g_cpu.A);
label_B49F:;
    /* $B49F: 8D */ maybe_trigger_vblank(4); nes_write(0x4000, g_cpu.A);
label_B4A2:;
    /* $B4A2: CE */ maybe_trigger_vblank(6); { uint16_t a=0x07BB; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_B4A5:;
    /* $B4A5: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B4B5; }
label_B4A7:;
    /* $B4A7: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x00; FLAG_NZ(g_cpu.X);
label_B4A9:;
    /* $B4A9: 86 */ maybe_trigger_vblank(3); nes_write(0xF1, g_cpu.X);
label_B4AB:;
    /* $B4AB: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x0E; FLAG_NZ(g_cpu.X);
label_B4AD:;
    /* $B4AD: 8E */ maybe_trigger_vblank(4); nes_write(0x4015, g_cpu.X);
label_B4B0:;
    /* $B4B0: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x0F; FLAG_NZ(g_cpu.X);
label_B4B2:;
    /* $B4B2: 8E */ maybe_trigger_vblank(4); nes_write(0x4015, g_cpu.X);
label_B4B5:;
    /* $B4B5: 60 */ maybe_trigger_vblank(6); 
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
    return;
label_B4B6:;
    /* $B4B6: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x2F; FLAG_NZ(g_cpu.A);
label_B4B8:;
    /* $B4B8: 8D */ maybe_trigger_vblank(4); nes_write(0x07BB, g_cpu.A);
label_B4BB:;
    /* $B4BB: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07BB); FLAG_NZ(g_cpu.A);
label_B4BE:;
    /* $B4BE: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B4BF:;
    /* $B4BF: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_B4D1; }
label_B4C1:;
    /* $B4C1: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B4C2:;
    /* $B4C2: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_B4D1; }
label_B4C4:;
    /* $B4C4: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x02; FLAG_NZ(g_cpu.A);
label_B4C6:;
    /* $B4C6: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_B4D1; }
label_B4C8:;
    /* $B4C8: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x91; FLAG_NZ(g_cpu.Y);
label_B4CA:;
    /* $B4CA: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x9A; FLAG_NZ(g_cpu.X);
label_B4CC:;
    /* $B4CC: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x44; FLAG_NZ(g_cpu.A);
label_B4CE:;
    /* $B4CE: 20 */ maybe_trigger_vblank(6); func_F388();
label_B4D1:;
    /* $B4D1: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); func_F4A2(); return;
}

void func_B3D1_b1(void) {
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_B3D1_b1");
#endif
label_B3D1:;
    /* $B3D1: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x18; FLAG_NZ(g_cpu.A);
label_B3D3:;
    /* $B3D3: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x82; FLAG_NZ(g_cpu.X);
label_B3D5:;
    /* $B3D5: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0xA7; FLAG_NZ(g_cpu.Y);
label_B3D7:;
    /* $B3D7: 20 */ maybe_trigger_vblank(6); func_F388();
label_B3DA:;
    /* $B3DA: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x28; FLAG_NZ(g_cpu.A);
label_B3DC:;
    /* $B3DC: 8D */ maybe_trigger_vblank(4); nes_write(0x07BB, g_cpu.A);
label_B3DF:;
    /* $B3DF: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07BB); FLAG_NZ(g_cpu.A);
label_B3E2:;
    /* $B3E2: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x25; g_cpu.C=(g_cpu.A>=0x25)?1:0; FLAG_NZ(r&0xFF); }
label_B3E4:;
    /* $B3E4: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B3EC; }
label_B3E6:;
    /* $B3E6: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x5F; FLAG_NZ(g_cpu.X);
label_B3E8:;
    /* $B3E8: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0xF6; FLAG_NZ(g_cpu.Y);
label_B3EA:;
    /* $B3EA: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B3F4; }
label_B3EC:;
    /* $B3EC: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x20; g_cpu.C=(g_cpu.A>=0x20)?1:0; FLAG_NZ(r&0xFF); }
label_B3EE:;
    /* $B3EE: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(2); goto label_B419; }
label_B3F0:;
    /* $B3F0: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x48; FLAG_NZ(g_cpu.X);
label_B3F2:;
    /* $B3F2: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0xBC; FLAG_NZ(g_cpu.Y);
label_B3F4:;
    /* $B3F4: 20 */ maybe_trigger_vblank(6); func_F381();
label_B3F7:;
    /* $B3F7: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(2); goto label_B419; }
label_B3F9:;
    /* $B3F9: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x05; FLAG_NZ(g_cpu.A);
label_B3FB:;
    /* $B3FB: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x99; FLAG_NZ(g_cpu.Y);
label_B3FD:;
    /* $B3FD: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(2); goto label_B403; }
label_B3FF:;
    /* $B3FF: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x0A; FLAG_NZ(g_cpu.A);
label_B401:;
    /* $B401: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x93; FLAG_NZ(g_cpu.Y);
label_B403:;
    /* $B403: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x9E; FLAG_NZ(g_cpu.X);
label_B405:;
    /* $B405: 8D */ maybe_trigger_vblank(4); nes_write(0x07BB, g_cpu.A);
label_B408:;
    /* $B408: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x0C; FLAG_NZ(g_cpu.A);
label_B40A:; /* CSetFDir */
    /* $B40A: 20 */ maybe_trigger_vblank(6); func_F388();
label_B40D:;
    /* $B40D: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07BB); FLAG_NZ(g_cpu.A);
label_B410:;
    /* $B410: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x06; g_cpu.C=(g_cpu.A>=0x06)?1:0; FLAG_NZ(r&0xFF); }
label_B412:;
    /* $B412: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B419; }
label_B414:;
    /* $B414: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xBB; FLAG_NZ(g_cpu.A);
label_B416:;
    /* $B416: 8D */ maybe_trigger_vblank(4); nes_write(0x4001, g_cpu.A);
label_B419:;
    /* $B419: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B47B; }
label_B41B:;
    /* $B41B: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0xFF); FLAG_NZ(g_cpu.Y);
label_B41D:;
    /* $B41D: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_B43F; }
label_B41F:; /* ExitCSub */
    /* $B41F: 84 */ maybe_trigger_vblank(3); nes_write(0xF1, g_cpu.Y);
label_B421:;
    /* $B421: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) { maybe_trigger_vblank(2); call_by_address(0xB3CD); return; }
label_B423:;
    /* $B423: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_B425:;
    /* $B425: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_B3D1;
    }
label_B427:;
    /* $B427: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_B429:;
    /* $B429: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_B3FF;
    }
label_B42B:; /* FallMForceData */
    /* $B42B: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_B42D:;
    /* $B42D: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_B45B; }
label_B42F:;
    /* $B42F: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_B431:;
    /* $B431: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_B47D; }
label_B433:;
    /* $B433: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_B435:;
    /* $B435: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_B4B6; }
label_B437:;
    /* $B437: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_B439:; /* InitMForceData */
    /* $B439: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_B3F9;
    }
label_B43B:;
    /* $B43B: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_B43D:;
    /* $B43D: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { maybe_trigger_vblank(2); call_by_address(0xB3BF); return; }
label_B43F:;
    /* $B43F: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xF1); FLAG_NZ(g_cpu.A);
label_B441:;
    /* $B441: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_B45A; }
label_B443:; /* MaxRightXSpdData */
    /* $B443: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_B3DF;
    }
label_B445:;
    /* $B445: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B446:;
    /* $B446: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_B3DF;
    }
label_B448:;
    /* $B448: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B449:;
    /* $B449: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) {
    maybe_trigger_vblank(1);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_B40D;
    }
label_B44B:;
    /* $B44B: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B44C:;
    /* $B44C: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_B469; }
label_B44E:;
    /* $B44E: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B44F:;
    /* $B44F: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_B48D; }
label_B451:;
    /* $B451: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B452:;
    /* $B452: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_B4BB; }
label_B454:;
    /* $B454: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B455:;
    /* $B455: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) {
    maybe_trigger_vblank(1);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_B40D;
    }
label_B457:;
    /* $B457: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B458:;
    /* $B458: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_B4A2; }
label_B45A:;
    /* $B45A: 60 */
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
    return; /* branch-target RTS */
label_B45B:;
    /* $B45B: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x0E; FLAG_NZ(g_cpu.A);
label_B45D:;
    /* $B45D: 8D */ maybe_trigger_vblank(4); nes_write(0x07BB, g_cpu.A);
label_B460:;
    /* $B460: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x9C; FLAG_NZ(g_cpu.Y);
label_B462:;
    /* $B462: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x9E; FLAG_NZ(g_cpu.X);
label_B464:;
    /* $B464: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x26; FLAG_NZ(g_cpu.A);
label_B466:;
    /* $B466: 20 */ maybe_trigger_vblank(6); func_F388();
label_B469:;
    /* $B469: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x07BB); FLAG_NZ(g_cpu.Y);
label_B46C:;
    /* $B46C: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xF3B0 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_B46F:;
    /* $B46F: 8D */ maybe_trigger_vblank(4); nes_write(0x4000, g_cpu.A);
label_B472:;
    /* $B472: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x06; g_cpu.C=(g_cpu.Y>=0x06)?1:0; FLAG_NZ(r&0xFF); }
label_B474:;
    /* $B474: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B47B; }
label_B476:;
    /* $B476: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x9E; FLAG_NZ(g_cpu.A);
label_B478:;
    /* $B478: 8D */ maybe_trigger_vblank(4); nes_write(0x4002, g_cpu.A);
label_B47B:;
    /* $B47B: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B4A2; }
label_B47D:;
    /* $B47D: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x0E; FLAG_NZ(g_cpu.A);
label_B47F:;
    /* $B47F: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0xCB; FLAG_NZ(g_cpu.Y);
label_B481:;
    /* $B481: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x9F; FLAG_NZ(g_cpu.X);
label_B483:;
    /* $B483: 8D */ maybe_trigger_vblank(4); nes_write(0x07BB, g_cpu.A);
label_B486:;
    /* $B486: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x28; FLAG_NZ(g_cpu.A);
label_B488:; /* NoJump */
    /* $B488: 20 */ maybe_trigger_vblank(6); func_F388();
label_B48B:; /* ProcJumping */
    /* $B48B: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B4A2; }
label_B48D:;
    /* $B48D: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x07BB); FLAG_NZ(g_cpu.Y);
label_B490:;
    /* $B490: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x08; g_cpu.C=(g_cpu.Y>=0x08)?1:0; FLAG_NZ(r&0xFF); }
label_B492:;
    /* $B492: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B49D; }
label_B494:;
    /* $B494: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xA0; FLAG_NZ(g_cpu.A);
label_B496:;
    /* $B496: 8D */ maybe_trigger_vblank(4); nes_write(0x4002, g_cpu.A);
label_B499:;
    /* $B499: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x9F; FLAG_NZ(g_cpu.A);
label_B49B:;
    /* $B49B: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B49F; }
label_B49D:;
    /* $B49D: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x90; FLAG_NZ(g_cpu.A);
label_B49F:;
    /* $B49F: 8D */ maybe_trigger_vblank(4); nes_write(0x4000, g_cpu.A);
label_B4A2:;
    /* $B4A2: CE */ maybe_trigger_vblank(6); { uint16_t a=0x07BB; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_B4A5:;
    /* $B4A5: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B4B5; }
label_B4A7:;
    /* $B4A7: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x00; FLAG_NZ(g_cpu.X);
label_B4A9:;
    /* $B4A9: 86 */ maybe_trigger_vblank(3); nes_write(0xF1, g_cpu.X);
label_B4AB:;
    /* $B4AB: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x0E; FLAG_NZ(g_cpu.X);
label_B4AD:;
    /* $B4AD: 8E */ maybe_trigger_vblank(4); nes_write(0x4015, g_cpu.X);
label_B4B0:;
    /* $B4B0: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x0F; FLAG_NZ(g_cpu.X);
label_B4B2:;
    /* $B4B2: 8E */ maybe_trigger_vblank(4); nes_write(0x4015, g_cpu.X);
label_B4B5:;
    /* $B4B5: 60 */ maybe_trigger_vblank(6); 
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
    return;
label_B4B6:;
    /* $B4B6: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x2F; FLAG_NZ(g_cpu.A);
label_B4B8:;
    /* $B4B8: 8D */ maybe_trigger_vblank(4); nes_write(0x07BB, g_cpu.A);
label_B4BB:;
    /* $B4BB: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07BB); FLAG_NZ(g_cpu.A);
label_B4BE:;
    /* $B4BE: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B4BF:;
    /* $B4BF: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_B4D1; }
label_B4C1:;
    /* $B4C1: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B4C2:;
    /* $B4C2: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_B4D1; }
label_B4C4:;
    /* $B4C4: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x02; FLAG_NZ(g_cpu.A);
label_B4C6:;
    /* $B4C6: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_B4D1; }
label_B4C8:;
    /* $B4C8: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x91; FLAG_NZ(g_cpu.Y);
label_B4CA:;
    /* $B4CA: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x9A; FLAG_NZ(g_cpu.X);
label_B4CC:;
    /* $B4CC: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x44; FLAG_NZ(g_cpu.A);
label_B4CE:;
    /* $B4CE: 20 */ maybe_trigger_vblank(6); func_F388();
label_B4D1:;
    /* $B4D1: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); func_F4A2(); return;
}

void func_B3FF_b1(void) {
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_B3FF_b1");
#endif
label_B3FF:;
    /* $B3FF: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x0A; FLAG_NZ(g_cpu.A);
label_B401:;
    /* $B401: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x93; FLAG_NZ(g_cpu.Y);
label_B403:;
    /* $B403: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x9E; FLAG_NZ(g_cpu.X);
label_B405:;
    /* $B405: 8D */ maybe_trigger_vblank(4); nes_write(0x07BB, g_cpu.A);
label_B408:;
    /* $B408: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x0C; FLAG_NZ(g_cpu.A);
label_B40A:; /* CSetFDir */
    /* $B40A: 20 */ maybe_trigger_vblank(6); func_F388();
label_B40D:;
    /* $B40D: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07BB); FLAG_NZ(g_cpu.A);
label_B410:;
    /* $B410: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x06; g_cpu.C=(g_cpu.A>=0x06)?1:0; FLAG_NZ(r&0xFF); }
label_B412:;
    /* $B412: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B419; }
label_B414:;
    /* $B414: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xBB; FLAG_NZ(g_cpu.A);
label_B416:;
    /* $B416: 8D */ maybe_trigger_vblank(4); nes_write(0x4001, g_cpu.A);
label_B419:;
    /* $B419: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B47B; }
label_B41B:;
    /* $B41B: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0xFF); FLAG_NZ(g_cpu.Y);
label_B41D:;
    /* $B41D: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_B43F; }
label_B41F:; /* ExitCSub */
    /* $B41F: 84 */ maybe_trigger_vblank(3); nes_write(0xF1, g_cpu.Y);
label_B421:;
    /* $B421: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) { maybe_trigger_vblank(2); call_by_address(0xB3CD); return; }
label_B423:;
    /* $B423: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_B425:;
    /* $B425: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { maybe_trigger_vblank(2); call_by_address(0xB3D1); return; }
label_B427:;
    /* $B427: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_B429:;
    /* $B429: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_B3FF;
    }
label_B42B:; /* FallMForceData */
    /* $B42B: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_B42D:;
    /* $B42D: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_B45B; }
label_B42F:;
    /* $B42F: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_B431:;
    /* $B431: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_B47D; }
label_B433:;
    /* $B433: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_B435:;
    /* $B435: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_B4B6; }
label_B437:;
    /* $B437: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_B439:; /* InitMForceData */
    /* $B439: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { maybe_trigger_vblank(2); call_by_address(0xB3F9); return; }
label_B43B:;
    /* $B43B: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_B43D:;
    /* $B43D: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { maybe_trigger_vblank(2); call_by_address(0xB3BF); return; }
label_B43F:;
    /* $B43F: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xF1); FLAG_NZ(g_cpu.A);
label_B441:;
    /* $B441: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_B45A; }
label_B443:; /* MaxRightXSpdData */
    /* $B443: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) { maybe_trigger_vblank(2); call_by_address(0xB3DF); return; }
label_B445:;
    /* $B445: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B446:;
    /* $B446: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { maybe_trigger_vblank(2); call_by_address(0xB3DF); return; }
label_B448:;
    /* $B448: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B449:;
    /* $B449: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) {
    maybe_trigger_vblank(1);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_B40D;
    }
label_B44B:;
    /* $B44B: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B44C:;
    /* $B44C: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_B469; }
label_B44E:;
    /* $B44E: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B44F:;
    /* $B44F: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_B48D; }
label_B451:;
    /* $B451: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B452:;
    /* $B452: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_B4BB; }
label_B454:;
    /* $B454: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B455:;
    /* $B455: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) {
    maybe_trigger_vblank(1);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_B40D;
    }
label_B457:;
    /* $B457: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B458:;
    /* $B458: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_B4A2; }
label_B45A:;
    /* $B45A: 60 */
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
    return; /* branch-target RTS */
label_B45B:;
    /* $B45B: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x0E; FLAG_NZ(g_cpu.A);
label_B45D:;
    /* $B45D: 8D */ maybe_trigger_vblank(4); nes_write(0x07BB, g_cpu.A);
label_B460:;
    /* $B460: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x9C; FLAG_NZ(g_cpu.Y);
label_B462:;
    /* $B462: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x9E; FLAG_NZ(g_cpu.X);
label_B464:;
    /* $B464: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x26; FLAG_NZ(g_cpu.A);
label_B466:;
    /* $B466: 20 */ maybe_trigger_vblank(6); func_F388();
label_B469:;
    /* $B469: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x07BB); FLAG_NZ(g_cpu.Y);
label_B46C:;
    /* $B46C: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xF3B0 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_B46F:;
    /* $B46F: 8D */ maybe_trigger_vblank(4); nes_write(0x4000, g_cpu.A);
label_B472:;
    /* $B472: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x06; g_cpu.C=(g_cpu.Y>=0x06)?1:0; FLAG_NZ(r&0xFF); }
label_B474:;
    /* $B474: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B47B; }
label_B476:;
    /* $B476: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x9E; FLAG_NZ(g_cpu.A);
label_B478:;
    /* $B478: 8D */ maybe_trigger_vblank(4); nes_write(0x4002, g_cpu.A);
label_B47B:;
    /* $B47B: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B4A2; }
label_B47D:;
    /* $B47D: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x0E; FLAG_NZ(g_cpu.A);
label_B47F:;
    /* $B47F: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0xCB; FLAG_NZ(g_cpu.Y);
label_B481:;
    /* $B481: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x9F; FLAG_NZ(g_cpu.X);
label_B483:;
    /* $B483: 8D */ maybe_trigger_vblank(4); nes_write(0x07BB, g_cpu.A);
label_B486:;
    /* $B486: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x28; FLAG_NZ(g_cpu.A);
label_B488:; /* NoJump */
    /* $B488: 20 */ maybe_trigger_vblank(6); func_F388();
label_B48B:; /* ProcJumping */
    /* $B48B: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B4A2; }
label_B48D:;
    /* $B48D: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x07BB); FLAG_NZ(g_cpu.Y);
label_B490:;
    /* $B490: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x08; g_cpu.C=(g_cpu.Y>=0x08)?1:0; FLAG_NZ(r&0xFF); }
label_B492:;
    /* $B492: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B49D; }
label_B494:;
    /* $B494: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xA0; FLAG_NZ(g_cpu.A);
label_B496:;
    /* $B496: 8D */ maybe_trigger_vblank(4); nes_write(0x4002, g_cpu.A);
label_B499:;
    /* $B499: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x9F; FLAG_NZ(g_cpu.A);
label_B49B:;
    /* $B49B: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B49F; }
label_B49D:;
    /* $B49D: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x90; FLAG_NZ(g_cpu.A);
label_B49F:;
    /* $B49F: 8D */ maybe_trigger_vblank(4); nes_write(0x4000, g_cpu.A);
label_B4A2:;
    /* $B4A2: CE */ maybe_trigger_vblank(6); { uint16_t a=0x07BB; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_B4A5:;
    /* $B4A5: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B4B5; }
label_B4A7:;
    /* $B4A7: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x00; FLAG_NZ(g_cpu.X);
label_B4A9:;
    /* $B4A9: 86 */ maybe_trigger_vblank(3); nes_write(0xF1, g_cpu.X);
label_B4AB:;
    /* $B4AB: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x0E; FLAG_NZ(g_cpu.X);
label_B4AD:;
    /* $B4AD: 8E */ maybe_trigger_vblank(4); nes_write(0x4015, g_cpu.X);
label_B4B0:;
    /* $B4B0: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x0F; FLAG_NZ(g_cpu.X);
label_B4B2:;
    /* $B4B2: 8E */ maybe_trigger_vblank(4); nes_write(0x4015, g_cpu.X);
label_B4B5:;
    /* $B4B5: 60 */ maybe_trigger_vblank(6); 
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
    return;
label_B4B6:;
    /* $B4B6: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x2F; FLAG_NZ(g_cpu.A);
label_B4B8:;
    /* $B4B8: 8D */ maybe_trigger_vblank(4); nes_write(0x07BB, g_cpu.A);
label_B4BB:;
    /* $B4BB: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07BB); FLAG_NZ(g_cpu.A);
label_B4BE:;
    /* $B4BE: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B4BF:;
    /* $B4BF: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_B4D1; }
label_B4C1:;
    /* $B4C1: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B4C2:;
    /* $B4C2: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_B4D1; }
label_B4C4:;
    /* $B4C4: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x02; FLAG_NZ(g_cpu.A);
label_B4C6:;
    /* $B4C6: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_B4D1; }
label_B4C8:;
    /* $B4C8: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x91; FLAG_NZ(g_cpu.Y);
label_B4CA:;
    /* $B4CA: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x9A; FLAG_NZ(g_cpu.X);
label_B4CC:;
    /* $B4CC: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x44; FLAG_NZ(g_cpu.A);
label_B4CE:;
    /* $B4CE: 20 */ maybe_trigger_vblank(6); func_F388();
label_B4D1:;
    /* $B4D1: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); func_F4A2(); return;
}

void func_B3F9_b1(void) {
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_B3F9_b1");
#endif
label_B3F9:;
    /* $B3F9: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x05; FLAG_NZ(g_cpu.A);
label_B3FB:;
    /* $B3FB: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x99; FLAG_NZ(g_cpu.Y);
label_B3FD:;
    /* $B3FD: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(2); goto label_B403; }
label_B3FF:;
    /* $B3FF: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x0A; FLAG_NZ(g_cpu.A);
label_B401:;
    /* $B401: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x93; FLAG_NZ(g_cpu.Y);
label_B403:;
    /* $B403: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x9E; FLAG_NZ(g_cpu.X);
label_B405:;
    /* $B405: 8D */ maybe_trigger_vblank(4); nes_write(0x07BB, g_cpu.A);
label_B408:;
    /* $B408: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x0C; FLAG_NZ(g_cpu.A);
label_B40A:; /* CSetFDir */
    /* $B40A: 20 */ maybe_trigger_vblank(6); func_F388();
label_B40D:;
    /* $B40D: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07BB); FLAG_NZ(g_cpu.A);
label_B410:;
    /* $B410: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x06; g_cpu.C=(g_cpu.A>=0x06)?1:0; FLAG_NZ(r&0xFF); }
label_B412:;
    /* $B412: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B419; }
label_B414:;
    /* $B414: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xBB; FLAG_NZ(g_cpu.A);
label_B416:;
    /* $B416: 8D */ maybe_trigger_vblank(4); nes_write(0x4001, g_cpu.A);
label_B419:;
    /* $B419: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B47B; }
label_B41B:;
    /* $B41B: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0xFF); FLAG_NZ(g_cpu.Y);
label_B41D:;
    /* $B41D: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_B43F; }
label_B41F:; /* ExitCSub */
    /* $B41F: 84 */ maybe_trigger_vblank(3); nes_write(0xF1, g_cpu.Y);
label_B421:;
    /* $B421: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) { maybe_trigger_vblank(2); call_by_address(0xB3CD); return; }
label_B423:;
    /* $B423: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_B425:;
    /* $B425: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { maybe_trigger_vblank(2); call_by_address(0xB3D1); return; }
label_B427:;
    /* $B427: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_B429:;
    /* $B429: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_B3FF;
    }
label_B42B:; /* FallMForceData */
    /* $B42B: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_B42D:;
    /* $B42D: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_B45B; }
label_B42F:;
    /* $B42F: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_B431:;
    /* $B431: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_B47D; }
label_B433:;
    /* $B433: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_B435:;
    /* $B435: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_B4B6; }
label_B437:;
    /* $B437: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_B439:; /* InitMForceData */
    /* $B439: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_B3F9;
    }
label_B43B:;
    /* $B43B: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_B43D:;
    /* $B43D: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { maybe_trigger_vblank(2); call_by_address(0xB3BF); return; }
label_B43F:;
    /* $B43F: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xF1); FLAG_NZ(g_cpu.A);
label_B441:;
    /* $B441: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_B45A; }
label_B443:; /* MaxRightXSpdData */
    /* $B443: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) { maybe_trigger_vblank(2); call_by_address(0xB3DF); return; }
label_B445:;
    /* $B445: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B446:;
    /* $B446: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { maybe_trigger_vblank(2); call_by_address(0xB3DF); return; }
label_B448:;
    /* $B448: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B449:;
    /* $B449: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) {
    maybe_trigger_vblank(1);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_B40D;
    }
label_B44B:;
    /* $B44B: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B44C:;
    /* $B44C: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_B469; }
label_B44E:;
    /* $B44E: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B44F:;
    /* $B44F: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_B48D; }
label_B451:;
    /* $B451: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B452:;
    /* $B452: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_B4BB; }
label_B454:;
    /* $B454: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B455:;
    /* $B455: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) {
    maybe_trigger_vblank(1);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_B40D;
    }
label_B457:;
    /* $B457: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B458:;
    /* $B458: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_B4A2; }
label_B45A:;
    /* $B45A: 60 */
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
    return; /* branch-target RTS */
label_B45B:;
    /* $B45B: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x0E; FLAG_NZ(g_cpu.A);
label_B45D:;
    /* $B45D: 8D */ maybe_trigger_vblank(4); nes_write(0x07BB, g_cpu.A);
label_B460:;
    /* $B460: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x9C; FLAG_NZ(g_cpu.Y);
label_B462:;
    /* $B462: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x9E; FLAG_NZ(g_cpu.X);
label_B464:;
    /* $B464: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x26; FLAG_NZ(g_cpu.A);
label_B466:;
    /* $B466: 20 */ maybe_trigger_vblank(6); func_F388();
label_B469:;
    /* $B469: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x07BB); FLAG_NZ(g_cpu.Y);
label_B46C:;
    /* $B46C: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xF3B0 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_B46F:;
    /* $B46F: 8D */ maybe_trigger_vblank(4); nes_write(0x4000, g_cpu.A);
label_B472:;
    /* $B472: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x06; g_cpu.C=(g_cpu.Y>=0x06)?1:0; FLAG_NZ(r&0xFF); }
label_B474:;
    /* $B474: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B47B; }
label_B476:;
    /* $B476: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x9E; FLAG_NZ(g_cpu.A);
label_B478:;
    /* $B478: 8D */ maybe_trigger_vblank(4); nes_write(0x4002, g_cpu.A);
label_B47B:;
    /* $B47B: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B4A2; }
label_B47D:;
    /* $B47D: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x0E; FLAG_NZ(g_cpu.A);
label_B47F:;
    /* $B47F: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0xCB; FLAG_NZ(g_cpu.Y);
label_B481:;
    /* $B481: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x9F; FLAG_NZ(g_cpu.X);
label_B483:;
    /* $B483: 8D */ maybe_trigger_vblank(4); nes_write(0x07BB, g_cpu.A);
label_B486:;
    /* $B486: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x28; FLAG_NZ(g_cpu.A);
label_B488:; /* NoJump */
    /* $B488: 20 */ maybe_trigger_vblank(6); func_F388();
label_B48B:; /* ProcJumping */
    /* $B48B: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B4A2; }
label_B48D:;
    /* $B48D: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x07BB); FLAG_NZ(g_cpu.Y);
label_B490:;
    /* $B490: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x08; g_cpu.C=(g_cpu.Y>=0x08)?1:0; FLAG_NZ(r&0xFF); }
label_B492:;
    /* $B492: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B49D; }
label_B494:;
    /* $B494: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xA0; FLAG_NZ(g_cpu.A);
label_B496:;
    /* $B496: 8D */ maybe_trigger_vblank(4); nes_write(0x4002, g_cpu.A);
label_B499:;
    /* $B499: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x9F; FLAG_NZ(g_cpu.A);
label_B49B:;
    /* $B49B: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B49F; }
label_B49D:;
    /* $B49D: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x90; FLAG_NZ(g_cpu.A);
label_B49F:;
    /* $B49F: 8D */ maybe_trigger_vblank(4); nes_write(0x4000, g_cpu.A);
label_B4A2:;
    /* $B4A2: CE */ maybe_trigger_vblank(6); { uint16_t a=0x07BB; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_B4A5:;
    /* $B4A5: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B4B5; }
label_B4A7:;
    /* $B4A7: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x00; FLAG_NZ(g_cpu.X);
label_B4A9:;
    /* $B4A9: 86 */ maybe_trigger_vblank(3); nes_write(0xF1, g_cpu.X);
label_B4AB:;
    /* $B4AB: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x0E; FLAG_NZ(g_cpu.X);
label_B4AD:;
    /* $B4AD: 8E */ maybe_trigger_vblank(4); nes_write(0x4015, g_cpu.X);
label_B4B0:;
    /* $B4B0: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x0F; FLAG_NZ(g_cpu.X);
label_B4B2:;
    /* $B4B2: 8E */ maybe_trigger_vblank(4); nes_write(0x4015, g_cpu.X);
label_B4B5:;
    /* $B4B5: 60 */ maybe_trigger_vblank(6); 
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
    return;
label_B4B6:;
    /* $B4B6: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x2F; FLAG_NZ(g_cpu.A);
label_B4B8:;
    /* $B4B8: 8D */ maybe_trigger_vblank(4); nes_write(0x07BB, g_cpu.A);
label_B4BB:;
    /* $B4BB: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07BB); FLAG_NZ(g_cpu.A);
label_B4BE:;
    /* $B4BE: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B4BF:;
    /* $B4BF: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_B4D1; }
label_B4C1:;
    /* $B4C1: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B4C2:;
    /* $B4C2: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_B4D1; }
label_B4C4:;
    /* $B4C4: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x02; FLAG_NZ(g_cpu.A);
label_B4C6:;
    /* $B4C6: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_B4D1; }
label_B4C8:;
    /* $B4C8: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x91; FLAG_NZ(g_cpu.Y);
label_B4CA:;
    /* $B4CA: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x9A; FLAG_NZ(g_cpu.X);
label_B4CC:;
    /* $B4CC: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x44; FLAG_NZ(g_cpu.A);
label_B4CE:;
    /* $B4CE: 20 */ maybe_trigger_vblank(6); func_F388();
label_B4D1:;
    /* $B4D1: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); func_F4A2(); return;
}

void func_BC90_b1_body(int _entry) {
    switch (_entry) {
        case 1: goto label_BC9E;
    }
label_BC90:;
    /* $BC90: 66 */ maybe_trigger_vblank(5); { uint16_t a=0xA6; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=v&1; v=((v>>1)|(c<<7))&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BC92:;
    /* $BC92: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_BC93:;
    /* $BC93: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_BC94:;
    /* $BC94: 68 */ maybe_trigger_vblank(4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_BC95:;
    /* $BC95: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_BC96:;
    /* $BC96: 6A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=g_cpu.A&1; g_cpu.A=((g_cpu.A>>1)|(c<<7))&0xFF; FLAG_NZ(g_cpu.A); }
label_BC97:;
    /* $BC97: 44 */ maybe_trigger_vblank(3); (void)nes_read(0x2B); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BC99:;
    /* $BC99: 81 */ maybe_trigger_vblank(6); nes_write(nes_read16zp((0x2A + g_cpu.X) & 0xFF), g_cpu.A);
label_BC9B:;
    /* $BC9B: 42 */ maybe_trigger_vblank(2); /* ILLEGAL $42 — skip 1 */
label_BC9C:;
    /* $BC9C: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x42); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BC9E:;
    /* $BC9E: 42 */ maybe_trigger_vblank(2); /* ILLEGAL $42 — skip 1 */
label_BC9F:;
    /* $BC9F: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x2C); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BCA1:;
    /* $BCA1: 64 */ maybe_trigger_vblank(3); (void)nes_read(0x04); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BCA3:;
    /* $BCA3: 64 */ maybe_trigger_vblank(3); (void)nes_read(0x64); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BCA5:;
    /* $BCA5: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x2E); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BCA7:;
    /* $BCA7: 46 */ maybe_trigger_vblank(5); { uint16_t a=0x04; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_BCA9:;
    /* $BCA9: 46 */ maybe_trigger_vblank(5); { uint16_t a=0x46; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_BCAB:;
    /* $BCAB: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x22); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BCAD:;
    /* $BCAD: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x84); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BCAF:;
    /* $BCAF: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_BCB0:;
    /* $BCB0: 87 */ maybe_trigger_vblank(3); nes_write(0x04, g_cpu.A & g_cpu.X); /* SAX */
label_BCB2:;
    /* $BCB2: 06 */ maybe_trigger_vblank(5); { uint16_t a=0x0C; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BCB4:;
    /* $BCB4: 14 */ maybe_trigger_vblank(4); (void)nes_read((0x1C + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BCB6:;
    /* $BCB6: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_BCB7:;
    /* $BCB7: 86 */ maybe_trigger_vblank(3); nes_write(0x2C, g_cpu.X);
label_BCB9:;
    /* $BCB9: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_BCBA:;
    /* $BCBA: 87 */ maybe_trigger_vblank(3); nes_write(0x04, g_cpu.A & g_cpu.X); /* SAX */
label_BCBC:;
    /* $BCBC: 60 */ maybe_trigger_vblank(6); 
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
    return;
}

void func_BC90_b1(void) {
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_BC90_b1");
#endif
    func_BC90_b1_body(0);
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
}

void func_BC9E_b1(void) {
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_BC9E_b1");
#endif
    func_BC90_b1_body(1);
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
}

