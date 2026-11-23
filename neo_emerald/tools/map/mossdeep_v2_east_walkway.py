"""Mossdeep City 2.0 east quay from flooded south-east shelf to waterfront.

One-shot extension row 35, x64..79 at elevation 5; rails only over the ocean
where the adjacent tile is open sea. The new waterfront map continues the
walkway on the next connected map.
"""
import os,sys
sys.path.insert(0,os.path.dirname(__file__))
import mossdeep_v2_upper as u
import mossdeep_tileset_v2 as ts

ROW,X0,X1,ELEV=35,64,79,5
OCEAN=368

def main():
    ids=ts.ids();g=u.load()
    before=[g[ROW*u.W+x]&0x3ff for x in range(X0,X1+1)]
    assert before[0]!=ids['walkway_deck_shaded'] and before[1:]==[OCEAN]*(X1-X0), \
        f'row {ROW} changed or already extended: {before}'
    for x in range(X0,X1+1):
        g[ROW*u.W+x]=ids['walkway_deck_shaded']|(ELEV<<12)
        for y,rail in ((ROW-1,ids['walkway_rail_north']),(ROW+1,ids['walkway_rail_south'])):
            if g[y*u.W+x]&0x3ff==OCEAN:
                g[y*u.W+x]=rail|(1<<10)|(ELEV<<12)
    bad,sea=u.check_routes(g)
    assert not bad and not sea, f'walkway invalid: {bad},sea={sea}'
    assert (X1,ROW) in u.reachable(g), 'east edge unreachable'
    u.save(g)
    print('walkway placed row35, x64..79; endpoint reachable')


if __name__=='__main__':
    main()
