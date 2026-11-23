"""Mossdeep City 2.0 reusable upper-city building kits (facades only).

Usage:
 python3 neo_emerald/tools/map/mossdeep_v2_buildings.py search KIT
 python3 neo_emerald/tools/map/mossdeep_v2_buildings.py apply

One-shot placement; keep doors, map events and all critical routes accessible.
"""
import json, os, sys
sys.path.insert(0, os.path.dirname(__file__))
import mossdeep_v2_upper as u
import mossdeep_tileset_v2 as ts

RIDGE,BALCONY,EAVE,BASE = [660,661,662,663],[656,657,658,659],[664,665,666,667],[672,673,674,675]
_ids=ts.ids()
_P,_T=_ids['civic_roof_plain'],_ids['civic_roof_top']
KITS={
 'apartment_3f':[RIDGE,BALCONY,BALCONY,EAVE,BASE],
 'apartment_4f':[RIDGE,BALCONY,BALCONY,BALCONY,EAVE,BASE],
 'ranger_hq':[[966,_T,932,_T,814],[967,_P,940,_P,822],[944,_P,948,_P,859],
              [952,954,733,955,957],[730,732,733,734,711],
              [738,740,741,742,719],[746,748,749,750,727]],
 'ranger_hq_tower':[[966,932,814],[967,940,822],[944,948,859],
                    [952,733,957],[730,733,711],[738,741,719],[746,749,727]]
}
DOOR_COLUMN={'apartment_3f':1,'apartment_4f':1,'ranger_hq':2,'ranger_hq_tower':1}
WALK_BEHIND_TOP={'apartment_3f':True,'apartment_4f':True,'ranger_hq':False,'ranger_hq_tower':False}
SPAWN=(28,17)


def protected_tiles():
    """Preserve spawn and tile in front of each door or north-facing sign."""
    m=json.load(open(u.MAP))
    doors=[(w['x'],w['y']) for w in m['warp_events']] + [
        (b['x'],b['y']) for b in m['bg_events']
        if b.get('player_facing_dir')=='BG_EVENT_PLAYER_FACING_NORTH'
    ]
    return {SPAWN}|{(x,y+1) for x,y in doors}


# House 4 gets a third storey while preserving its original base, door and warp.
RAISES=[('apartment_3f',17,16)]
# Earlier HQ was placed in the preceding commit; do not re-run it.
PLACEMENTS=[('apartment_3f',46,25)]


def collision(kit,row_index):
    return 0 if row_index==0 and WALK_BEHIND_TOP[kit] else 1


def footprint(kit,x0,y0):
    rows=KITS[kit]
    return [(x0+i,y0+j) for j in range(len(rows)) for i in range(len(rows[0]))]


def door(kit,x0,y0):
    return (x0+DOOR_COLUMN[kit],y0+len(KITS[kit])-1)


def site_ok(g,kit,x0,y0,events):
    fp=footprint(kit,x0,y0)
    if any(not(0<=x<u.W and 0<=y<u.H) for x,y in fp):
        return False
    elevations={g[y*u.W+x]>>12 for x,y in fp}
    if len(elevations)!=1 or elevations&{0,1,15}:
        return False
    if any((g[y*u.W+x]>>10)&3 for x,y in fp) or any(p in events for p in fp):
        return False
    if any(p in protected_tiles() for p in fp):
        return False
    dx,dy=door(kit,x0,y0)
    front=(dx,dy+1)
    return 0<=front[1]<u.H and not (g[front[1]*u.W+front[0]]>>10)&3 and front not in events


def place(g,kit,x0,y0):
    for j,row in enumerate(KITS[kit]):
        for i,mid in enumerate(row):
            t=(y0+j)*u.W+x0+i
            g[t]=mid | collision(kit,j)<<10 | (g[t]&0xf000)


def raise_ok(g,kit,x0,base_y,events):
    rows=KITS[kit]
    top=base_y-len(rows)+1
    have_base=[g[base_y*u.W+x0+i]&0x3ff for i in range(4)]
    if have_base!=BASE:
        return False
    old_top=base_y-3
    for y in range(top,old_top):
        for x in range(x0,x0+4):
            v=g[y*u.W+x]
            if (v>>10)&3 or (x,y) in events or (x,y) in protected_tiles() or v>>12 in (0,1,15):
                return False
    return True


def raise_house(g,kit,x0,base_y):
    rows=KITS[kit]
    top=base_y-len(rows)+1
    for j,row in enumerate(rows[:-1]):
        for i,mid in enumerate(row):
            t=(top+j)*u.W+x0+i
            g[t]=mid|collision(kit,j)<<10|(g[t]&0xf000)


def main():
    mode=sys.argv[1] if len(sys.argv)>1 else 'search'
    g=u.load();events=u.event_tiles()
    bad,sea=u.check_routes(g)
    assert not bad and not sea, f'baseline fails: {bad},sea={sea}'
    if mode=='search':
        kit=sys.argv[2]
        for y0 in range(u.H):
            for x0 in range(u.W):
                if site_ok(g,kit,x0,y0,events):
                    t=list(g);place(t,kit,x0,y0)
                    bad,sea=u.check_routes(t)
                    dx,dy=door(kit,x0,y0)
                    front=(dx,dy+1)
                    ok=not bad and not sea and front in u.reachable(t)
                    print((x0,y0),'OK' if ok else f'breaks {bad},sea={sea},front={front in u.reachable(t)}')
        return
    for kit,x0,base_y in RAISES:
        assert raise_ok(g,kit,x0,base_y,events), f'cannot raise house at {x0},{base_y}; already raised?'
        raise_house(g,kit,x0,base_y)
    for kit,x0,y0 in PLACEMENTS:
        assert site_ok(g,kit,x0,y0,events), f'site {x0},{y0} no longer suitable'
        place(g,kit,x0,y0)
    bad,sea=u.check_routes(g)
    assert not bad and not sea, f'placement breaks routes: {bad},sea={sea}'
    r=u.reachable(g)
    for kit,x0,y0 in PLACEMENTS:
        dx,dy=door(kit,x0,y0)
        assert (dx,dy+1) in r, 'HQ entrance approach not reachable'
    u.save(g)
    print('placed',PLACEMENTS)


if __name__=='__main__':
    main()
