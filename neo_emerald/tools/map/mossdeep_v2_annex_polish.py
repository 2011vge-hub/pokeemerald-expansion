"""One-shot polish for the Space Center annex placed at (46,10) by mossdeep_v2_upper.py.

- Replace the west roof edge at x=46, y=10-11 with newly appended metatiles
  966/967, removing unwanted helipad markings without changing old tile IDs.
- Column x=47, rows 13-16: swap the 'right of centre' wall pieces (conduit line
  and a glass-entrance sliver) for plain repeating wing wall.
- (48,17),(49,17): replace sand stub in front of facade with grass; no fake door.

Guarded: ALL 8 tiles must hold the expected metatile before writing.
Checks major routes and reachable sea tiles before saving. The mapping is
intended to run on the pre-polish annex only, not on an already-polished map.
"""
import os, sys
sys.path.insert(0, os.path.dirname(__file__))
import mossdeep_v2_upper as u

# (x,y): (expected metatile, replacement metatile, replacement collision)
EDITS = {
    (46,10): (928,966,1),
    (46,11): (936,967,1),
    (47,13): (955,953,1),
    (47,14): (734,731,1),
    (47,15): (742,739,1),
    (47,16): (750,747,1),
    (48,17): (296,1,0),
    (49,17): (298,1,0),
}

def main():
    g=u.load()
    for (x,y),(old,new,col) in EDITS.items():
        v=g[y*u.W+x]
        assert v&0x3ff==old, \
            f'({x},{y}) is metatile {v&0x3ff}; expected {old} (already polished or edited?)'
    for (x,y),(old,new,col) in EDITS.items():
        v=g[y*u.W+x]
        g[y*u.W+x]=new|(col<<10)|(v&0xf000)
    bad, sea=u.check_routes(g)
    assert not bad and not sea, f'polish breaks routes: {bad} sea={sea}'
    u.save(g)
    print(f'polished {len(EDITS)} tiles - all key routes reachable, zero reachable sea tiles')

if __name__=='__main__':
    main()
