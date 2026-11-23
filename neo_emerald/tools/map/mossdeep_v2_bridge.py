"""One-shot Mossdeep upper-market bridge to the rescue landing.

Rows 28..30, columns 35..43:
 north rail (968, collision); deck (969, walkable); south rail (971, collision).
Deck heights 3 west, 0 at x39 transition, 5 east. The transition is boxed in
by blocked rails so it cannot create an unintended path into open sea.

Guarded against re-running on already edited terrain.
"""
import os, sys
sys.path.insert(0, os.path.dirname(__file__))
import mossdeep_v2_upper as u
import mossdeep_tileset_v2 as ts

X0,X1=35,43
EXPECTED={
    28:[137,802,803,802,803,1,802,803,112],
    29:[366,796,797,796,797,796,797,137,112],
    30:[368,804,805,804,805,804,761,358,120],
}
SOUTH_STAIRS=[(32,27),(33,27),(32,28),(33,28)]


def deck_elevation(x):
    return 3 if x < 39 else (0 if x == 39 else 5)


def main():
    ids=ts.ids()
    north=ids['walkway_rail_north']
    deck=ids['walkway_deck_shaded']
    south=ids['walkway_rail_south']
    g=u.load()
    for y,expected in EXPECTED.items():
        row=[g[y*u.W+x]&0x3ff for x in range(X0,X1+1)]
        assert row==expected, f'row {y}: expected {expected}, have {row}; already edited?'
    for x in range(X0,X1+1):
        e=deck_elevation(x)
        g[28*u.W+x]=north|(1<<10)|(e<<12)
        g[29*u.W+x]=deck|(e<<12)
        g[30*u.W+x]=south|(1<<10)|(e<<12)
    bad,sea=u.check_routes(g)
    assert not bad and not sea, f'bridge breaks routes: {bad}, sea={sea}'
    blocked=list(g)
    for x,y in SOUTH_STAIRS:
        blocked[y*u.W+x]|=1<<10
    accessible=u.reachable(blocked)
    assert (33,29) in accessible and (44,29) in accessible, \
        'rescue landing cannot be reached via bridge after stair closure'
    u.save(g)
    print('bridge x35-43 y28-30 placed; rescue reachable with south stairs blocked')


if __name__=='__main__':
    main()
