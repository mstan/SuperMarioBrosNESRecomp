// semcomp/EnemyHandlers.cpp — bulk-ported routines (auto-generated).
#include "semcomp/EnemyHandlers.h"

#include "semcomp/GameState.h"
#include "semcomp/cpu_flags.h"

extern "C" {
#include "nes_runtime.h"
}

namespace smb::semcomp {

void EnemyHandlers::init_goomba() {
    (void)state_;
label_C2F1:; /* InitGoomba */
    /* $C2F1: 20 */ maybe_trigger_vblank(6); call_by_address(0xC30E);
label_C2F4:;
    /* $C2F4: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xC346); return;
}

void EnemyHandlers::init_hammer_bro() {
    (void)state_;
label_C328:; /* InitHammerBro */
    /* $C328: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_C32A:;
    /* $C32A: 9D */ maybe_trigger_vblank(5); nes_write((0x03A2 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_C32D:;
    /* $C32D: 95 */ maybe_trigger_vblank(4); nes_write((0x58 + g_cpu.X) & 0xFF, g_cpu.A);
label_C32F:;
    /* $C32F: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x06CC); FLAG_NZ(g_cpu.Y);
label_C332:;
    /* $C332: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xC326 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_C335:;
    /* $C335: 9D */ maybe_trigger_vblank(5); nes_write((0x0796 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_C338:;
    /* $C338: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x0B; FLAG_NZ(g_cpu.A);
label_C33A:;
    /* $C33A: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xC35C); return;
}

void EnemyHandlers::init_bullet_bill() {
    (void)state_;
label_C36B:; /* InitBulletBill */
    /* $C36B: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x02; FLAG_NZ(g_cpu.A);
label_C36D:;
    /* $C36D: 95 */ maybe_trigger_vblank(4); nes_write((0x46 + g_cpu.X) & 0xFF, g_cpu.A);
label_C36F:;
    /* $C36F: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x09; FLAG_NZ(g_cpu.A);
label_C371:;
    /* $C371: 9D */ maybe_trigger_vblank(5); nes_write((0x049A + g_cpu.X) & 0xFFFF, g_cpu.A);
label_C374:;
    /* $C374: 60 */ maybe_trigger_vblank(6);
    return;
}

void EnemyHandlers::init_cheep_cheep() {
    (void)state_;
label_C375:; /* InitCheepCheep */
    /* $C375: 20 */ maybe_trigger_vblank(6); call_by_address(0xC346);
label_C378:;
    /* $C378: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x07A7 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_C37B:;
    /* $C37B: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x10; FLAG_NZ(g_cpu.A);
label_C37D:;
    /* $C37D: 95 */ maybe_trigger_vblank(4); nes_write((0x58 + g_cpu.X) & 0xFF, g_cpu.A);
label_C37F:;
    /* $C37F: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xCF + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_C381:;
    /* $C381: 9D */ maybe_trigger_vblank(5); nes_write((0x0434 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_C384:;
    /* $C384: 60 */ maybe_trigger_vblank(6);
    return;
}

void EnemyHandlers::init_lakitu() {
    (void)state_;
label_C385:; /* InitLakitu */
    /* $C385: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x06CB); FLAG_NZ(g_cpu.A);
label_C388:;
    /* $C388: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_C395;
label_C38A:; /* SetupLakitu */
    /* $C38A: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_C38C:;
    /* $C38C: 8D */ maybe_trigger_vblank(4); nes_write(0x06D1, g_cpu.A);
label_C38F:;
    /* $C38F: 20 */ maybe_trigger_vblank(6); call_by_address(0xC33D);
label_C392:;
    /* $C392: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xC7D9); return;
label_C395:; /* KillLakitu */
    /* $C395: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xC998); return;
}

void EnemyHandlers::setup_lakitu() {
    (void)state_;
label_C38A:; /* SetupLakitu */
    /* $C38A: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_C38C:;
    /* $C38C: 8D */ maybe_trigger_vblank(4); nes_write(0x06D1, g_cpu.A);
label_C38F:;
    /* $C38F: 20 */ maybe_trigger_vblank(6); call_by_address(0xC33D);
label_C392:;
    /* $C392: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xC7D9); return;
}

void EnemyHandlers::init_short_firebar() {
    (void)state_;
label_C45C:; /* InitShortFirebar */
    /* $C45C: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_C45E:;
    /* $C45E: 95 */ maybe_trigger_vblank(4); nes_write((0x58 + g_cpu.X) & 0xFF, g_cpu.A);
label_C460:;
    /* $C460: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x16 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_C462:;
    /* $C462: 38 */ maybe_trigger_vblank(2); g_cpu.C = 1;
label_C463:;
    /* $C463: E9 */ maybe_trigger_vblank(2); { uint8_t m=0x1B; int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_C465:;
    /* $C465: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_C466:;
    /* $C466: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xC44F + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_C469:;
    /* $C469: 9D */ maybe_trigger_vblank(5); nes_write((0x0388 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_C46C:;
    /* $C46C: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xC454 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_C46F:;
    /* $C46F: 95 */ maybe_trigger_vblank(4); nes_write((0x34 + g_cpu.X) & 0xFF, g_cpu.A);
label_C471:;
    /* $C471: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xCF + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_C473:;
    /* $C473: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_C474:;
    /* $C474: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x04 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x04); g_cpu.A=r&0xFF; }
label_C476:;
    /* $C476: 95 */ maybe_trigger_vblank(4); nes_write((0xCF + g_cpu.X) & 0xFF, g_cpu.A);
label_C478:;
    /* $C478: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x87 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_C47A:;
    /* $C47A: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_C47B:;
    /* $C47B: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x04 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x04); g_cpu.A=r&0xFF; }
label_C47D:;
    /* $C47D: 95 */ maybe_trigger_vblank(4); nes_write((0x87 + g_cpu.X) & 0xFF, g_cpu.A);
label_C47F:;
    /* $C47F: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x6E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_C481:;
    /* $C481: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x00 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x00); g_cpu.A=r&0xFF; }
label_C483:;
    /* $C483: 95 */ maybe_trigger_vblank(4); nes_write((0x6E + g_cpu.X) & 0xFF, g_cpu.A);
label_C485:;
    /* $C485: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xC7D9); return;
}

void EnemyHandlers::move_defeated_enemy() {
    (void)state_;
label_CAE5:; /* MoveDefeatedEnemy */
    /* $CAE5: 20 */ maybe_trigger_vblank(6); call_by_address(0xBF63);
label_CAE8:;
    /* $CAE8: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xBF02); return;
}

void EnemyHandlers::move_jumping_enemy() {
    (void)state_;
label_CAF9:; /* MoveJumpingEnemy */
    /* $CAF9: 20 */ maybe_trigger_vblank(6); call_by_address(0xBF92);
label_CAFC:;
    /* $CAFC: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xBF02); return;
}

void EnemyHandlers::move_bloober() {
    (void)state_;
label_CB89:; /* MoveBloober */
    /* $CB89: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x1E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_CB8B:;
    /* $CB8B: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x20; FLAG_NZ(g_cpu.A);
label_CB8D:;
    /* $CB8D: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_CBDC;
label_CB8F:;
    /* $CB8F: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x06CC); FLAG_NZ(g_cpu.Y);
label_CB92:;
    /* $CB92: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x07A8 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_CB95:;
    /* $CB95: 39 */ maybe_trigger_vblank(4); g_cpu.A &= nes_read((0xCB87 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_CB98:;
    /* $CB98: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_CBAC;
label_CB9A:;
    /* $CB9A: 8A */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.X; FLAG_NZ(g_cpu.A);
label_CB9B:;
    /* $CB9B: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_CB9C:;
    /* $CB9C: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_CBA2;
label_CB9E:;
    /* $CB9E: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0x45); FLAG_NZ(g_cpu.Y);
label_CBA0:;
    /* $CBA0: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_CBAA;
label_CBA2:; /* FBLeft */
    /* $CBA2: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x02; FLAG_NZ(g_cpu.Y);
label_CBA4:;
    /* $CBA4: 20 */ maybe_trigger_vblank(6); call_by_address(0xE143);
label_CBA7:;
    /* $CBA7: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) goto label_CBAA;
label_CBA9:;
    /* $CBA9: 88 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y-1)&0xFF; FLAG_NZ(g_cpu.Y);
label_CBAA:; /* SBMDir */
    /* $CBAA: 94 */ maybe_trigger_vblank(4); nes_write((0x46 + g_cpu.X) & 0xFF, g_cpu.Y);
label_CBAC:; /* BlooberSwim */
    /* $CBAC: 20 */ maybe_trigger_vblank(6); call_by_address(0xCBDF);
label_CBAF:;
    /* $CBAF: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xCF + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_CBB1:;
    /* $CBB1: 38 */ maybe_trigger_vblank(2); g_cpu.C = 1;
label_CBB2:;
    /* $CBB2: FD */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0x0434 + g_cpu.X) & 0xFFFF); int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_CBB5:;
    /* $CBB5: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x20; g_cpu.C=(g_cpu.A>=0x20)?1:0; FLAG_NZ(r&0xFF); }
label_CBB7:;
    /* $CBB7: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_CBBB;
label_CBB9:;
    /* $CBB9: 95 */ maybe_trigger_vblank(4); nes_write((0xCF + g_cpu.X) & 0xFF, g_cpu.A);
label_CBBB:; /* SwimX */
    /* $CBBB: B4 */ maybe_trigger_vblank(4); g_cpu.Y = nes_read((0x46 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.Y);
label_CBBD:;
    /* $CBBD: 88 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y-1)&0xFF; FLAG_NZ(g_cpu.Y);
label_CBBE:;
    /* $CBBE: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_CBCE;
label_CBC0:;
    /* $CBC0: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x87 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_CBC2:;
    /* $CBC2: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_CBC3:;
    /* $CBC3: 75 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0x58 + g_cpu.X) & 0xFF); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_CBC5:;
    /* $CBC5: 95 */ maybe_trigger_vblank(4); nes_write((0x87 + g_cpu.X) & 0xFF, g_cpu.A);
label_CBC7:;
    /* $CBC7: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x6E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_CBC9:;
    /* $CBC9: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x00 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x00); g_cpu.A=r&0xFF; }
label_CBCB:;
    /* $CBCB: 95 */ maybe_trigger_vblank(4); nes_write((0x6E + g_cpu.X) & 0xFF, g_cpu.A);
label_CBCD:;
    /* $CBCD: 60 */ maybe_trigger_vblank(6);
    return;
label_CBCE:; /* LeftSwim */
    /* $CBCE: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x87 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_CBD0:;
    /* $CBD0: 38 */ maybe_trigger_vblank(2); g_cpu.C = 1;
label_CBD1:;
    /* $CBD1: F5 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0x58 + g_cpu.X) & 0xFF); int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_CBD3:;
    /* $CBD3: 95 */ maybe_trigger_vblank(4); nes_write((0x87 + g_cpu.X) & 0xFF, g_cpu.A);
label_CBD5:;
    /* $CBD5: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x6E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_CBD7:;
    /* $CBD7: E9 */ maybe_trigger_vblank(2); { uint8_t m=0x00; int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_CBD9:;
    /* $CBD9: 95 */ maybe_trigger_vblank(4); nes_write((0x6E + g_cpu.X) & 0xFF, g_cpu.A);
label_CBDB:;
    /* $CBDB: 60 */ maybe_trigger_vblank(6);
    return;
label_CBDC:; /* MoveDefeatedBloober */
    /* $CBDC: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xBF8C); return;
}

}  // namespace smb::semcomp
