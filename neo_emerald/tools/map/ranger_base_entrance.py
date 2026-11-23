"""One-shot: open the Ranger HQ glass door into the new Ranger Base.

Original door metatile 749 remains unchanged; elevation becomes 0 as with
the other Mossdeep door warps. Map warp 10 points to Ranger Base 1F warp 0;
the HQ sign is moved to the adjacent wall at (32,19). Guarded against
repeated application.
"""
import json,os,sys
sys.path.insert(0,os.path.dirname(__file__))
import mossdeep_v2_upper as u

DOOR=(33,19)
SIGN_FROM=(33,19)
SIGN_TO=(32,19)
DEST="MAP_MOSSDEEP_CITY_RANGER_BASE_1F"


def main():
    g=u.load()
    idx=DOOR[1]*u.W+DOOR[0]
    v=g[idx]
    assert v&0x3ff==749 and (v>>10)&3==1, \
        'HQ door is not the original Space Center glass-door metatile'
    m=json.load(open(u.MAP))
    assert len(m['warp_events'])==10 and not any(w['dest_map']==DEST for w in m['warp_events']), \
        'HQ warp already exists or original warp set changed'
    signs=[e for e in m['bg_events'] if e['script']=="MossdeepCity_EventScript_RangerHQSign"]
    assert len(signs)==1 and (signs[0]['x'],signs[0]['y'])==SIGN_FROM
    g[idx]=v&0x0fff
    m['warp_events'].append({'x':33,'y':19,'elevation':0,'dest_map':DEST,'dest_warp_id':'0'})
    signs[0]['x'],signs[0]['y']=SIGN_TO
    bad,sea=u.check_routes(g)
    assert not bad and not sea,f'routes broken: {bad}, sea={sea}'
    r=u.reachable(g)
    assert (33,20) in r and (32,20) in r, 'door/sign approach blocked'
    u.save(g)
    with open(u.MAP,'w') as f:
        json.dump(m,f,indent=2,ensure_ascii=False)
        f.write('\n')
    print('Mossdeep warp 10 connects HQ door to Ranger Base 1F; sign moved')


if __name__=='__main__':
    main()
