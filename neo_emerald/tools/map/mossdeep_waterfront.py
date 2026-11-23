"""Generate the MossdeepCity_Waterfront 32x40 map east of Mossdeep.

Walkway: west edge row35 x0-9, elevation5. Quay platform x10-24,
y33-38. Terminal facade x15-19,y26-32 (sign only; no warp or boat yet).
Sea everywhere else; all non-blocked quay tiles must be reachable.

Usage: python3 neo_emerald/tools/map/mossdeep_waterfront.py
Re-running regenerates original milestone map bytes; it will overwrite manual
Porymap edits, so use only before editing the generated layout.
"""
import collections,os,struct,sys
sys.path.insert(0,os.path.dirname(__file__))
import mossdeep_tileset_v2 as ts
import mossdeep_v2_buildings as b

ROOT=ts.ROOT
OUT=ROOT+'data/layouts/MossdeepCity_Waterfront/'
W,H=32,40
OCEAN=368|(1<<12)
WALK_ROW,ELEV=35,5
QUAY=(10,24,33,38)
TERMINAL=('ranger_hq',15,26)
TERMINAL_DOOR=(17,32)


def tile(mid,col,elev):
    return mid|(col<<10)|(elev<<12)


def generate():
    ids=ts.ids()
    g=[OCEAN]*(W*H)
    put=lambda x,y,v:g.__setitem__(y*W+x,v)
    for x in range(10):
        put(x,WALK_ROW,tile(ids['walkway_deck_shaded'],0,ELEV))
        put(x,WALK_ROW-1,tile(ids['walkway_rail_north'],1,ELEV))
        put(x,WALK_ROW+1,tile(ids['walkway_rail_south'],1,ELEV))
    x0,x1,y0,y1=QUAY
    for y in range(y0,y1+1):
        for x in range(x0,x1+1):
            mid=ids['walkway_deck']
            if x==x0 and y!=WALK_ROW:mid=ids['walkway_deck_rail_west']
            elif x==x1:mid=ids['walkway_deck_rail_east']
            put(x,y,tile(mid,0,ELEV))
    for x in range(x0,x1+1):
        put(x,y0-1,tile(ids['walkway_rail_north'],1,ELEV))
        put(x,y1+1,tile(ids['walkway_rail_south'],1,ELEV))
    kit,tx,ty=TERMINAL
    for j,row in enumerate(b.KITS[kit]):
        for i,mid in enumerate(row):
            put(tx+i,ty+j,tile(mid,1,ELEV))
    return g


def save(g):
    os.makedirs(OUT,exist_ok=True)
    d=bytearray(2*len(g))
    for i,v in enumerate(g):
        struct.pack_into('<H',d,2*i,v)
    open(OUT+'map.bin','wb').write(d)
    border=bytearray(8)
    for i in range(4):
        struct.pack_into('<H',border,2*i,OCEAN)
    open(OUT+'border.bin','wb').write(border)


def check(g):
    start=(0,WALK_ROW)
    seen={start};q=collections.deque([start])
    while q:
        x,y=q.popleft()
        for nx,ny in ((x+1,y),(x-1,y),(x,y+1),(x,y-1)):
            if 0<=nx<W and 0<=ny<H and (nx,ny) not in seen:
                v=g[ny*W+nx]
                if not ((v>>10)&3) and v>>12==ELEV:
                    seen.add((nx,ny));q.append((nx,ny))
    assert all(g[y*W+x]>>12 not in (0,15) for x,y in seen), 'unexpected transition'
    assert (TERMINAL_DOOR[0],TERMINAL_DOOR[1]+1) in seen, 'terminal entrance unreachable'
    walkable={(i%W,i//W) for i,v in enumerate(g) if not ((v>>10)&3) and v>>12==ELEV}
    assert walkable==seen, 'unreachable quay pocket'
    return len(seen)


if __name__=='__main__':
    g=generate()
    n=check(g)
    save(g)
    print(f'wrote {OUT}map.bin ({W}x{H}), {n} reachable walkable tiles')
