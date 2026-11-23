"""One-shot record of how Neo Emerald Mossdeep flood milestone 1 was generated.
Run ONLY on a fresh COPY of original data/layouts/MossdeepCity/map.bin,
not on the already-flooded storm layout. Edits can then be polished in Porymap.
"""
import struct, sys, collections, re, os
W, H = 80, 40
path = sys.argv[1]
d = bytearray(open(path, 'rb').read())
assert len(d) == W * H * 2, f'Unexpected layout length: {len(d)}'
g = [struct.unpack_from('<H', d, 2*i)[0] for i in range(W*H)]
mt = lambda v: v & 0x3ff
pack = lambda m,col,elev: m | col << 10 | elev << 12
OCEAN = pack(368,0,1)
ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), '../../..')) + '/'
names = re.findall(r'^\s*(MB_\w+)', open(ROOT+'include/constants/metatile_behaviors.h').read(), re.M)
def attrs(p):
    b=open(ROOT+p,'rb').read()
    return [struct.unpack_from('<H',b,2*i)[0] for i in range(len(b)//2)]
pa=attrs('data/tilesets/primary/general/metatile_attributes.bin')
sa=attrs('data/tilesets/secondary/mossdeep/metatile_attributes.bin')
behavior=lambda m: names[(pa[m] if m<512 else sa[m-512])&0xff]
LANDING={(31,29),(32,29),(33,29),(34,29),(32,30),(33,30)}
changed=collections.Counter()
for y in range(H):
    for x in range(W):
        v=g[y*W+x]
        if (x,y) in LANDING: continue
        b=behavior(mt(v))
        walkable_shallow=b=='MB_SHALLOW_WATER' and (v>>10)&3 == 0
        if walkable_shallow or (b=='MB_OCEAN_WATER' and v!=OCEAN):
            g[y*W+x]=OCEAN
            changed['sea']+=1
seen=set()
for y in range(32,H):
    for x in range(40,67):
        v=g[y*W+x]
        if (v>>10)&3 == 0 and v>>12 == 5:
            g[y*W+x]=pack(414,0,5)
            seen.add((x,y))
            changed['shelf']+=1
for y in range(H):
    for x in range(W):
        v=g[y*W+x]
        if v>>12 == 0 and (v>>10)&3 == 0:
            for nx,ny in ((x+1,y),(x-1,y),(x,y+1),(x,y-1)):
                if 0<=nx<W and 0<=ny<H and g[ny*W+nx]==OCEAN:
                    g[ny*W+nx]=pack(368,1,1)
                    changed['stair_block']+=1
for i,v in enumerate(g):
    struct.pack_into('<H',d,2*i,v)
open(path,'wb').write(d)
print(dict(changed),'shelf bounds',min(x for x,_ in seen),max(x for x,_ in seen),min(y for _,y in seen),max(y for _,y in seen))
