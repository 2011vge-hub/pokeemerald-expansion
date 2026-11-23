"""Mossdeep City v3: remove unused observatory annex, open a bridge side gate.

One-shot guarded operation applied to the v2 pre-streets layout.
- Removes only facade coordinates x46..50, y10..16 by copying original
  metatiles (and collision/elevation) from untouched Mossdeep backup.
- Opens the southern rescue-bridge rail at (43,30) with deck metatile 969
  on elevation 5, connecting to the southern terrace at (43,31).
- Preserves all event positions, doors/warps, weather, and all other map tiles.
- Uses engine-style elevation/collision reachability checks (not a ROM test).
"""
import os,sys,json
sys.path.insert(0,os.path.dirname(__file__))
import mossdeep_v2_upper as u

ANNEX=(46,50,10,16)
SIDE_ENTRANCE=(43,30)
EXPECTED_TOP_LEFT=966
EXPECTED_SIDE_RAIL=971
DECK=969
KEYS=dict(u.ROUTES,**{
    'bridge side gate':(43,30),
    'southern bridge approach':(43,31),
    'east waterfront seam':(79,35),
    'Ranger HQ approach':(33,20),
    'apartments':(47,30),
})


def check(g,block_south_stairs=False):
    sample=list(g)
    if block_south_stairs:
        for x,y in ((32,27),(33,27),(32,28),(33,28)):
            sample[y*u.W+x]|=1<<10
    r=u.reachable(sample)
    bad=[name for name,xy in KEYS.items() if xy not in r]
    assert not bad, f'blocked routes: {bad}'
    assert not any((sample[y*u.W+x]&1023)==368 for x,y in r), 'reachable open sea'
    return len(r)


def main():
    g=u.load()
    src=u.load(u.ROOT+'data/layouts/MossdeepCity/map.bin')
    assert g[10*u.W+46]&1023==EXPECTED_TOP_LEFT, 'annex already removed or edited'
    assert g[30*u.W+43]&1023==EXPECTED_SIDE_RAIL, 'side gate already edited'
    events=u.event_tiles()
    x0,x1,y0,y1=ANNEX
    assert not any((x,y) in events for y in range(y0,y1+1) for x in range(x0,x1+1)), \
        'active event inside proposed annex removal'
    for y in range(y0,y1+1):
        for x in range(x0,x1+1):
            i=y*u.W+x
            assert (g[i]>>12)==(src[i]>>12), 'unexpected elevation in annex'
            g[i]=src[i]
    approach=g[31*u.W+43]
    assert not (approach>>10)&3 and approach>>12==5, 'southern gate leads into blocked tile'
    g[30*u.W+43]=DECK|(5<<12)
    ordinary=check(g)
    stairs_closed=check(g,True)
    u.save(g)
    print('restored unused annex and added south bridge entrance',
          'reachable:',ordinary,'with stairs closed:',stairs_closed)


if __name__=='__main__':
    main()
