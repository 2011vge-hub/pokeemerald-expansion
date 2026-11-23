#!/usr/bin/env python3
"""Guard imported walkway render layers and the temporary evacuation ferry."""
import json, pathlib, struct
ROOT=pathlib.Path(__file__).resolve().parents[2]
attrs=(ROOT/'data/tilesets/secondary/mossdeep/metatile_attributes.bin').read_bytes()
assert len(attrs)%2==0
def attr(mid):
    return struct.unpack_from('<H',attrs,2*(mid-512))[0]
for mid in (969,970,974,975):
    assert attr(mid)&0xf000==0x1000, f'walkway deck {mid} must use COVERED (BG2) layer'
for mid in (968,971):
    assert attr(mid)&0xf000==0, f'rail {mid} should stay NORMAL (BG1)'
m=json.loads((ROOT/'data/maps/MossdeepCity_Waterfront/map.json').read_text())
ferries=[x for x in m['object_events'] if x['local_id']=='LOCALID_WATERFRONT_FERRY']
assert len(ferries)==1
f=ferries[0]
assert f['graphics_id']=='OBJ_EVENT_GFX_SS_TIDAL' and f['flag']=='FLAG_NEO_HIDE_DEPARTED_FERRY'
assert (f['x'],f['y'],f['elevation'])==(26,37,1)
w=(ROOT/'data/maps/MossdeepCity_Waterfront/scripts.inc').read_text()
s=(ROOT/'data/maps/MossdeepCity/scripts.inc').read_text()
assert 'warp MAP_MOSSDEEP_CITY_SHOP_LOFT, 4, 6' in s
loft=(ROOT/'data/maps/MossdeepCity_ShopLoft/scripts.inc').read_text()
assert 'warp MAP_MOSSDEEP_CITY_WATERFRONT, 19, 37' in loft
assert 'removeobject LOCALID_WATERFRONT_FERRY' in w
assert w.count('setflag FLAG_NEO_HIDE_DEPARTED_FERRY')==2
assert 'goto_if_ge VAR_NEO_FERRY_DISPATCH, 5, MossdeepCity_Waterfront_FerryVisibilityDone' in w
assert w.index('removeobject LOCALID_WATERFRONT_FERRY') < w.index('setvar VAR_NEO_FERRY_DISPATCH, 5')
print('Ferry visual check OK: walkable decks behind player; ferry present until departure')
