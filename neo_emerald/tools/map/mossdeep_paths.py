"""Walkability check for Mossdeep layouts (collision bits + engine elevation rules).
Usage: python3 neo_emerald/tools/map/mossdeep_paths.py data/layouts/MossdeepCity_Storm/map.bin
Ignores ledges, doors and other metatile behaviours. Starts from New Game spawn (28,17).
"""
import struct, collections, sys
W, H = 80, 40
d = open(sys.argv[1], 'rb').read()
assert len(d) == W * H * 2, f'Expected {W * H * 2} bytes, got {len(d)}'
g = [struct.unpack_from('<H', d, 2 * i)[0] for i in range(W * H)]
col = lambda x,y:(g[y*W+x]>>10)&3
elv = lambda x,y:g[y*W+x]>>12
def bfs(s):
    st=(s[0],s[1],elv(*s)); seen={st}; q=collections.deque([st])
    while q:
        x,y,ce=q.popleft()
        for dx,dy in ((1,0),(-1,0),(0,1),(0,-1)):
            nx,ny=x+dx,y+dy
            if not (0<=nx<W and 0<=ny<H) or col(nx,ny): continue
            e=elv(nx,ny)
            if not(e in (0,15) or ce in (0,15) or e==ce): continue
            ns=(nx,ny,ce if e==15 else e)
            if ns not in seen: seen.add(ns); q.append(ns)
    return {(a,b) for a,b,_ in seen}
r=bfs((28,17))
checks=[('Pokemon Center door front',(28,17)),('sailor neighbour',(38,13)),
 ('Mart door front',(37,19)),('Gym door front',(38,10)),('Space Center door front',(64,16)),
 ('child landing (talk spot)',(33,29)),('flooded SE shelf',(50,33)),
 ('item ball on shelf',(62,35)),('west shore below stairs 25,26',(25,26)),
 ('south shore 31,31',(31,31)),('relocated tutor 23,21',(23,21)),
 ('relocated black belt 34,26',(34,26))]
for n,p in checks:
    print(f'{n:32s}', 'reachable' if p in r else 'NOT reachable')
