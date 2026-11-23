"""Generate Mossdeep's two 16x10 Ranger Base floors from vanilla Space Center maps.

General + Facility tilesets. Uses proven source walls, staircases and
entrance mats, but rearranges furniture into dispatch, reception,
medical and command areas. Each NPC, warp and sign must be reachable.

Usage: python3 neo_emerald/tools/map/ranger_base.py
NOTE: Re-running overwrites any later Porymap manual changes to these floors.
"""
import collections,json,os,struct

ROOT=os.path.abspath(os.path.join(os.path.dirname(__file__),'../../..'))+'/'
W,H=16,10
FLOOR,FLOOR_EDGE=752,753
FLOOR_ELEV=3


def load(name):
    d=open(ROOT+f'data/layouts/{name}/map.bin','rb').read()
    assert len(d)==W*H*2
    return [struct.unpack_from('<H',d,2*i)[0] for i in range(W*H)]


def tile(mid,col,elev):
    return mid | col<<10 | elev<<12


def clear(g,rows):
    for y in rows:
        for x in range(1,W):
            g[y*W+x]=tile(FLOOR,0,FLOOR_ELEV)
        g[y*W]=tile(FLOOR_EDGE,0,FLOOR_ELEV)


def put(g,x,y,mid,col=1,elev=0):
    g[y*W+x]=tile(mid,col,elev)


NPCS_1F={
    'dispatch':(3,4),'rookie':(9,5),'medic':(13,6),'quartermaster':(3,7)
}
SIGNS_1F=[(11,5),(12,5),(11,4),(12,4)]
WARPS_1F=[(7,9),(8,9),(13,1)]

NPCS_2F={'commander':(7,6),'technician':(13,7)}
SIGNS_2F=[(2,3),(3,3),(4,3),(5,3),(6,3),(8,7),(9,7)]
WARPS_2F=[(13,1)]


def ground_floor():
    g=load('MossdeepCity_SpaceCenter_1F')
    clear(g,range(3,9))
    for x in range(1,W):
        if x not in (7,8):
            g[9*W+x]=tile(FLOOR,0,FLOOR_ELEV)
    for x,y,mid,col,elev in [
        (1,4,867,0,3),(2,4,868,0,3),(1,5,875,1,0),(2,5,876,1,0),
        (6,5,849,1,0),(7,5,850,1,0),(8,5,851,1,0),
        (11,4,872,1,0),(12,4,873,1,0),(11,5,880,1,0),(12,5,881,1,0),
        (14,5,993,1,0),(14,6,1000,1,0),
        (1,7,783,1,0),(1,8,791,1,0),(2,7,799,1,0),(2,8,807,1,0),
        (4,8,821,1,0),(5,8,575,1,0),
    ]:
        put(g,x,y,mid,col,elev)
    return g


def second_floor():
    g=load('MossdeepCity_SpaceCenter_2F')
    clear(g,[3,6,7,8,9])
    for x,mid in zip(range(2,7),(560,561,612,656,657)):
        put(g,x,3,mid)
    for x,y,mid,col,elev in [
        (8,7,867,0,3),(9,7,868,0,3),(8,8,875,1,0),(9,8,876,1,0),
        (4,7,867,0,3),(5,7,868,0,3),(4,8,875,1,0),(5,8,876,1,0),
        (14,7,872,1,0),(15,7,873,1,0),(14,8,880,1,0),(15,8,881,1,0),
        (12,9,821,1,0),(13,9,609,1,0),
    ]:
        put(g,x,y,mid,col,elev)
    return g


def reachable(g,start):
    col=lambda x,y:(g[y*W+x]>>10)&3
    el=lambda x,y:g[y*W+x]>>12
    q=collections.deque([(start[0],start[1],el(*start))])
    seen=set(q)
    while q:
        x,y,e=q.popleft()
        for nx,ny in ((x+1,y),(x-1,y),(x,y+1),(x,y-1)):
            if not(0<=nx<W and 0<=ny<H) or col(nx,ny):
                continue
            new=el(nx,ny)
            if not(new in (0,15) or e in (0,15) or e==new):
                continue
            state=(nx,ny,e if new==15 else new)
            if state not in seen:
                seen.add(state);q.append(state)
    return {(x,y) for x,y,_ in seen}


def check(g,start,npcs,signs,warps,label):
    r=reachable(g,start)
    adj=lambda p:any((p[0]+dx,p[1]+dy) in r for dx,dy in
                     ((1,0),(-1,0),(0,1),(0,-1)))
    for name,p in npcs.items():
        v=g[p[1]*W+p[0]]
        assert not (v>>10)&3 and adj(p),f'{label}: NPC {name} is inaccessible'
    for p in signs:
        assert adj(p),f'{label}: sign {p} cannot be read'
    for p in warps:
        assert p in r or adj(p),f'{label}: warp {p} is inaccessible'
    blocked=list(g)
    for p in npcs.values():
        blocked[p[1]*W+p[0]]|=1<<10
    r2=reachable(blocked,start)
    for p in warps:
        assert p in r2 or any((p[0]+dx,p[1]+dy) in r2 for dx,dy in
                              ((1,0),(-1,0),(0,1),(0,-1))), \
            f'{label}: an NPC blocks warp {p}'
    return len(r2)


def save(g,name):
    out=ROOT+f'data/layouts/{name}/'
    os.makedirs(out,exist_ok=True)
    with open(out+'map.bin','wb') as f:
        for v in g:
            f.write(struct.pack('<H',v))
    with open(ROOT+'data/layouts/MossdeepCity_SpaceCenter_1F/border.bin','rb') as f:
        border=f.read()
    with open(out+'border.bin','wb') as f:
        f.write(border)


if __name__=='__main__':
    first,second=ground_floor(),second_floor()
    n1=check(first,(7,8),NPCS_1F,SIGNS_1F,WARPS_1F,'1F')
    n2=check(second,(13,2),NPCS_2F,SIGNS_2F,WARPS_2F,'2F')
    save(first,'MossdeepCity_RangerBase_1F')
    save(second,'MossdeepCity_RangerBase_2F')
    print(f'Ranger Base generated: 1F {n1} walkable, 2F {n2}; all critical events reachable')
