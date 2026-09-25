"""Additional native team lifecycle, pause and environment fixtures."""
import argparse
from pathlib import Path
from coop_runtime import State,Harness


def main():
    ap=argparse.ArgumentParser()
    ap.add_argument('--exe',type=Path,required=True)
    ap.add_argument('--rom',type=Path,required=True)
    ap.add_argument('--out',type=Path,default=Path('build-coop/rules'))
    a=ap.parse_args();h=Harness(a.exe,a.rom,a.out);out=h.out
    boot=h.run('boot','WAIT 1')
    fresh=lambda:State(out/'boot.sav')
    fixture=fresh();fixture.actor(0)[2048]=2
    p4=h.run('p4-no-pause','HOLD START 4\nWAIT 4\nRELEASE START 4',fixture=fixture)
    assert not p4.ram[0x776]&1,'P4 paused game'
    p1=h.run('dead-p1-pause','HOLD START\nWAIT 4\nRELEASE START\nWAIT 60',fixture=fixture)
    assert p1.ram[0x776]&1,'dead P1 could not pause'
    resumed=h.run('dead-p1-resume','HOLD START\nWAIT 4\nRELEASE START\nWAIT 4',fixture=p1)
    assert not resumed.ram[0x776]&1
    print('PASS: P1 pause authority after death',flush=True)

    # 1-1's native checkpoint is page 5. Only P4 has reached it.
    fixture=fresh();fixture.actor(3)[0x6d]=5;fixture.actor(3)[0x86]=40
    fixture.ram[0x71a]=4;fixture.ram[0x71b]=5
    fixture.ram[0x71c]=128;fixture.ram[0x71d]=127
    for p in range(3):fixture.actor(p)[0x6d]=4;fixture.actor(p)[0x86]=160
    checkpoint=h.run('p4-checkpoint','WAIT 3',fixture=fixture)
    assert checkpoint.data[checkpoint.mod+14]==5,'P4 did not establish checkpoint'
    for p in range(4):checkpoint.actor(p)[2048]=2
    retry=h.run('checkpoint-retry','WAIT 340',fixture=checkpoint)
    assert retry.ram[0x71a]==5 and retry.ram[0x75a]==1
    print('PASS: any living player establishes native checkpoint, team retry uses it',flush=True)

    # One 1-up serves the team once, even with everyone in contact.
    fixture=fresh()
    for p in range(4):fixture.actor(p)[0x86]=40
    for addr,value in {0x14:1,0x1b:0x2e,0x23:0x80,0x73:0,0x8c:40,0xbb:1,0xd4:176,0x39:3}.items():fixture.ram[addr]=value
    oneup=h.run('team-oneup','WAIT 8',fixture=fixture)
    assert oneup.ram[0x75a]==3,'1-up was duplicated or not shared'
    fixture=fresh()
    for p in range(3):fixture.actor(p)[0x86]=160
    fixture.actor(3)[0x86]=40
    for addr,value in {0x14:1,0x1b:0x2e,0x23:0x80,0x73:0,0x8c:40,0xbb:1,0xd4:176,0x39:2}.items():fixture.ram[addr]=value
    star=h.run('private-star','WAIT 8',fixture=fixture)
    assert star.actor(3)[0x79f]>0 and all(star.actor(p)[0x79f]==0 for p in range(3))
    print('PASS: shared single 1-up and individual star',flush=True)

    # Any nearby living actor, including P4, keeps a piranha in its pipe.
    fixture=fresh();fixture.actor(3)[0x86]=120;fixture.actor(3)[0xce]=48
    for addr,value in {0x0f:1,0x16:0x0d,0x1e:0,0x6e:0,0x87:120,0xb6:1,0xcf:160,
                       0x58:1,0xa0:0,0x417:128,0x434:160,0x78a:0,0x49a:9}.items():fixture.ram[addr]=value
    near=h.run('piranha-p4-near','WAIT 12',fixture=fixture)
    assert near.ram[0xcf]==160,'plant rose through nearby P4'
    fixture.actor(3)[0x86]=200
    far=h.run('piranha-all-far','WAIT 12',fixture=fixture)
    assert far.ram[0xcf]<160,'plant never rose when party moved away'
    print('PASS: piranha proximity includes every living player',flush=True)

    fixture=fresh();fixture.actor(3)[0x86]=112
    for addr,value in {0x0f:1,0x16:0x1b,0x1e:0,0x6e:0,0x87:120,0xb6:1,0xcf:200}.items():fixture.ram[addr]=value
    firebar=h.run('p4-firebar','WAIT 5',fixture=fixture)
    assert firebar.actor(3)[2048]!=0 and all(firebar.actor(p)[2048]==0 for p in range(3)), 'firebar used another actor sprite position'
    print('PASS: native firebar hits P4 at P4 position only',flush=True)

    fixture=fresh();fixture.actor(3)[0x86]=112
    for addr,value in {0x2a:0x81,0x64:16,0x7a:0,0x93:116,0xac:0,0xc2:1,0xdb:192,0x4a2:7,0x6be:0}.items():fixture.ram[addr]=value
    hammer=h.run('p4-hammer','WAIT 5',fixture=fixture)
    assert hammer.actor(3)[2048]!=0 and all(hammer.actor(p)[2048]==0 for p in range(3)), 'native hammer missed P4'
    fixture.actor(2)[0x86]=112
    contest=h.run('hammer-contest','WAIT 5',fixture=fixture)
    assert contest.actor(2)[2048]!=0 and contest.actor(3)[2048]==0,'hammer contested contact ignored port priority'
    print('PASS: native hammer contact and port priority',flush=True)

    fixture=fresh();fixture.ram[0x74e]=0
    fixture.ram[0x71a]=1;fixture.ram[0x71b]=1
    for p in range(4):fixture.actor(p)[0x6d]=1;fixture.actor(p)[0xce]=100
    fixture.actor(3)[0x86]=120
    fixture.ram[0x46b]=1;fixture.ram[0x471]=100;fixture.ram[0x477]=80
    whirlpool=h.run('private-whirlpool','WAIT 12',fixture=fixture)
    assert whirlpool.actor(3)[0x47d]==1 and all(whirlpool.actor(p)[0x47d]==0 for p in range(3)), 'whirlpool state leaked between actors'
    assert whirlpool.x(3)>fixture.x(3),'native whirlpool did not pull P4 toward center'
    print('PASS: native whirlpool pulls and flags only affected actor',flush=True)

    fixture=fresh();fixture.actor(0)[2048]=2
    fixture.ram[0x743]=1;fixture.ram[0x750]=0x25
    fixture.actor(3)[0xb5]=4;fixture.actor(3)[0xce]=16
    cloud=h.run('p4-cloud-fall','WAIT 4',fixture=fixture)
    assert cloud.data[cloud.mod+10]==1 and cloud.data[cloud.mod+9]==3,'cloud fall did not select P4 exit'
    returned=h.run('cloud-no-revival','WAIT 250\nWAIT_RAM8 000E 08\nWAIT 3',fixture=cloud)
    assert returned.actor(0)[2048]==2 and returned.actor(3)[2048]==0,'cloud return changed party life state'
    print('PASS: native cloud fall exit and no bonus-room revival',flush=True)

    fixture=fresh();fixture.actor(0)[2048]=2;fixture.ram[0x750]=0x2b
    for row in range(13):fixture.ram[0x500+row*16+5]=0x26
    lead=fixture.actor(3);lead[0x86]=73;lead[0xce]=32;lead[0x1d]=3;lead[0x33]=1
    vine=h.run('p4-vine','HOLD UP 4\nWAIT 14',fixture=fixture)
    assert vine.data[vine.mod+10]==1 and vine.data[vine.mod+9]==3,'vine did not select P4 exit'
    cloud_room=h.run('vine-no-revival','WAIT 250\nWAIT_RAM8 000E 08\nWAIT 3',fixture=vine)
    assert cloud_room.data[cloud_room.mod+15]==0x2b and cloud_room.actor(0)[2048]==2,'vine failed to enter cloud bonus with dead teammate out'
    print('PASS: native vine climb entry and no bonus-room revival',flush=True)

    fixture=fresh()
    for p in range(4):fixture.actor(p)[0x86]=80;fixture.actor(p)[0xce]=144;fixture.actor(p)[0x1d]=2;fixture.actor(p)[0x9f]=1
    fixture.ram[0x595]=0x67
    for addr,value in {0x0f:1,0x16:0x32,0x1e:0,0x6e:0,0x87:80,0xb6:1,0xcf:176,0x58:176}.items():fixture.ram[addr]=value
    spring=h.run('spring-owner','WAIT 5',fixture=fixture)
    assert spring.actor(0)[0x70e]>0 and all(spring.actor(p)[0x70e]==0 for p in (1,2,3)), 'spring animation had multiple owners'
    bounced=h.run('spring-bounce','HOLD A\nWAIT 20',fixture=spring)
    assert bounced.actor(0)[0xce]<120 and all(bounced.actor(p)[0xce]>=144 for p in (1,2,3)), 'spring did not launch just its owner'
    print('PASS: contested spring has one owner and native bounce',flush=True)

    fixture=fresh();fixture.ram[0x75f]=3
    fixture.ram[0x71a]=4;fixture.ram[0x71b]=4;fixture.ram[0x725]=5;fixture.ram[0x726]=0;fixture.ram[0x745]=1
    for p in range(4):fixture.actor(p)[0x6d]=4
    fixture.actor(3)[0x86]=120;fixture.actor(3)[0xce]=64;fixture.actor(3)[0x1d]=0
    fixture.ram[0x547]=0x54;fixture.ram[0x548]=0x54
    maze=h.run('p4-maze-route','WAIT 3',fixture=fixture)
    assert maze.ram[0x745]==0 and maze.ram[0x71a]==4,'maze ignored correctly positioned P4'
    fixture.actor(3)[0xce]=176
    loop=h.run('party-maze-loop','WAIT 3',fixture=fixture)
    assert loop.ram[0x71a]==0 and all(loop.actor(p)[0x6d]==0 for p in range(4)), 'maze loop failed to move whole party once'
    print('PASS: any living player can satisfy castle maze; shared loopback occurs once',flush=True)

    fixture=fresh();fixture.ram[0x75a]=0
    for p in range(4):fixture.actor(p)[2048]=2
    over=h.run('game-over','WAIT 180',fixture=fixture)
    assert over.ram[0x770]==3,'last team attempt did not reach game over'
    new=h.run('new-game','WAIT 650\nHOLD START\nWAIT 6\nRELEASE START\nWAIT_RAM8 000E 08\nWAIT 30',fixture=over)
    assert new.ram[0x75a]==2 and all(new.actor(p)[2048]==0 and new.actor(p)[0x756]==0 for p in range(4))
    print('PASS: last team attempt, game over and clean new game',flush=True)


if __name__=='__main__': main()
