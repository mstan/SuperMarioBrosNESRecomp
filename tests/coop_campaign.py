"""Native campaign boundary fixtures, loaded through the real area parser.

These enter each original area and exercise its real exit. They complement
terrain/collision tests; they do not claim to be full manual playthroughs.
"""
import argparse
import re
from pathlib import Path
from coop_runtime import State, Harness


def main():
    ap=argparse.ArgumentParser()
    ap.add_argument('--exe',required=True,type=Path)
    ap.add_argument('--rom',required=True,type=Path)
    ap.add_argument('--out',type=Path,default=Path('build-coop/campaign'))
    ap.add_argument('--level',default='all')
    ap.add_argument('--from-level',default='1-1')
    args=ap.parse_args();h=Harness(args.exe,args.rom,args.out);out=h.out
    root=Path(__file__).resolve().parents[1]
    symbols={name:int(addr,16) for addr,name in re.findall(r'^(\w+) (\w+) func$',(root/'symbols.sym').read_text(),re.M)}
    rom=args.rom.read_bytes()
    def byte(addr): return rom[16+(addr-0x8000)%32768]
    def table(name,index): return byte(symbols[name]+index)
    def exits(pointer):
        offset=table('AreaDataHOffsets',(pointer>>5)&3)+(pointer&31)
        address=table('AreaDataAddrLow',offset)+256*table('AreaDataAddrHigh',offset)+2
        page=0;result=[]
        while byte(address)!=0xfd:
            first,second=byte(address),byte(address+1);address+=2
            if second&0x80: page+=1
            elif first&15==13 and not second&0x40: page=second&31
            if first&15==13 and second&0x7f in (0x41,0x42):
                result.append(('axe' if second&0x7f==0x42 else 'flag',page*256+(first&0xf0),96 if second&0x7f==0x42 else 128))
            if first&15==15 and second&0x70==0x40:
                result.append(('pipe',page*256+(first&0xf0),(second&15)*16+16))
            if first&15<12 and second&0x7f==9:
                result.append(('pipe',page*256+(first&0xf0),(first&15)*16+32))
        return result
    h.run('boot','WAIT 1')
    for world in range(8):
        # Worlds with an underground/water -2 have a separate introductory
        # pipe area at AreaNumber 1. The real -2 level is AreaNumber 2.
        areas=[0,2,3,4] if world in (0,1,3,6) else [0,1,2,3]
        for level,area in enumerate(areas):
            name=f'{world+1}-{level+1}'
            if name<args.from_level: continue
            if args.level!='all' and args.level!=name: continue
            pointer=table('AreaAddrOffsets',table('WorldAddrOffsets',world)+area)
            destinations=exits(pointer)
            assert destinations,(name,'no native exit found')
            kind,x,y=destinations[-1]
            page=x//256
            fixture=State(out/'boot.sav')
            for addr,value in {0x75f:world,0x75c:level,0x760:area,0x750:pointer,0x772:0,
                               0x75b:page,0x752:0,0x757:1,0x769:1}.items(): fixture.ram[addr]=value
            entered=h.run(name+'-entry','WAIT_RAM8 000E 08\nWAIT 3',fixture=fixture)
            assert entered.data[entered.mod+7]==1,(name,'party never initialized')
            assert entered.ram[0x75f]==world and entered.ram[0x75c]==level,(name,'wrong area')
            # Position one survivor at the original exit collision, after the
            # native parser has built that area's tiles/enemies. P1 stays out;
            # surviving power states must persist through the transition.
            entered.actor(0)[2048]=2
            for p in (1,2,3):
                entered.actor(p)[0x756]=2 if p==2 else 1
                entered.actor(p)[0x754]=0
                entered.actor(p)[0x79f]=255
            lead=entered.actor(3)
            px=x-7 if kind=='flag' else x-4 if kind=='axe' else x-20
            lead[0x6d]=px//256;lead[0x86]=px%256
            lead[0xce]=y
            lead[0xb5]=1;lead[0x1d]=0 if kind=='pipe' else 2;lead[0x9f]=0;lead[0x57]=0
            lead[0x0e]=8
            body='HOLD RIGHT 4\nWAIT 60\nRELEASE RIGHT 4\nWAIT 900'
            if world<7 or kind!='axe': body+='\nWAIT_RAM8 000E 08\nWAIT 3'
            ended=h.run(name+'-exit',body,fixture=entered)
            if kind=='flag':
                assert ended.ram[0x75c]==level+1,(name,'flag did not advance level')
            elif kind=='axe' and world<7:
                assert ended.ram[0x75f]==world+1 and ended.ram[0x75c]==0,(name,'castle did not advance world')
            elif kind=='axe':
                assert ended.ram[0x770]==2 and ended.ram[0x772]>=3,(name,'final castle did not finish')
            else:
                assert ended.data[ended.mod+15]!=pointer,(name,'exit pipe did not change area')
                assert ended.actor(0)[2048]==2,(name,'exit pipe revived dead actor')
                # Underground/water exits return to an outdoor flagpole. Let
                # the native parser build its last screen, then finish there.
                outside=ended.data[ended.mod+15]
                _,flag_x,_=next(e for e in exits(outside) if e[0]=='flag')
                for addr,value in {0x750:outside,0x772:0,0x75b:flag_x//256,0x752:0,0x769:1}.items():ended.ram[addr]=value
                outside=h.run(name+'-outside','WAIT_RAM8 000E 08\nWAIT 3',fixture=ended)
                lead=outside.actor(3);lead[0x6d]=(flag_x-7)//256;lead[0x86]=(flag_x-7)%256
                lead[0xce]=128;lead[0xb5]=1;lead[0x1d]=2;lead[0x9f]=0;lead[0x57]=0;lead[0x0e]=8
                ended=h.run(name+'-outside-flag',body,fixture=outside)
                assert ended.ram[0x75c]==level+1,(name,'outdoor flag did not advance level')
            if kind in ('flag','pipe') or (kind=='axe' and world<7):
                assert ended.actor(0)[2048]==0 and ended.actor(0)[0x756]==0,(name,'dead actor did not revive small')
                assert [ended.actor(p)[0x756] for p in (1,2,3)]==[1,2,1],(name,'surviving powers changed')
            print(f'PASS: {name} native {kind} at {x}, party progression',flush=True)


if __name__=='__main__': main()
