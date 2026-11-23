"""City v3 street and lighting pass: guarded one-shot map painter.

Paints a small stone urban core around Ranger Commons and the ridge campus,
replaces two grouped trees with open plaza tiles, and installs six static
16x32 lampposts. Uses only new metatiles 976-978. Everything outside the
listed rectangles and tree clusters remains untouched.

Run only on v3 access-and-annex terrain BEFORE this street pass; do not rerun.
Artwork source: mossdeep_v3_street_art.py.
"""
import os,sys
sys.path.insert(0,os.path.dirname(__file__))
import mossdeep_v2_upper as u

PAVE=976
LAMP_TOP,LAMP_BOTTOM=977,978
ALLOWED={1,4,280,281,282,288,289,290,296,297,298}
DISTRICTS={
    'campus':(46,50,10,16,7),
    'rangerCommons':(25,34,18,23,5),
    'market':(35,42,17,22,5),
    'bridgeSquare':(43,51,27,31,5),
}
EXPECTED_PAVING={'campus':35,'rangerCommons':47,'market':18,'bridgeSquare':21}
TREE_CLUSTERS=[(22,14),(21,19)]
LAMPS=[(22,14),(21,19),(46,10),(50,10),(31,21),(44,27)]
CRITICAL={
    'spawn':(28,17),'sailor':(38,13),'mart':(37,19),
    'gym':(38,10),'Space Center':(64,16),'child':(33,29),
    'bridge side entrance':(43,30),'bridge southern approach':(43,31),
    'Ranger HQ front':(33,20),'evacuated apartment':(47,30),
    'waterfront link':(79,35),'Steven house':(49,7),
    'House 2':(67,26),
}


def safe(g,blocked_stairs=False):
    t=list(g)
    if blocked_stairs:
        for x,y in ((32,27),(33,27),(32,28),(33,28)):
            t[y*u.W+x]|=1<<10
    r=u.reachable(t)
    missing=[name for name,point in CRITICAL.items() if point not in r]
    assert not missing, 'unreachable: '+repr(missing)
    assert not any((t[y*u.W+x]&1023)==368 for x,y in r), 'reachable sea tile'
    return len(r)


def main():
    g=u.load()
    assert (g[30*u.W+43]&1023)==969, 'requires v3 bridge entrance'
    assert (g[10*u.W+46]&1023)==1, 'requires annex removal'
    events=u.event_tiles()
    counts={}
    for name,(x0,x1,y0,y1,elevation) in DISTRICTS.items():
        painted=0
        for y in range(y0,y1+1):
            for x in range(x0,x1+1):
                i=y*u.W+x
                v=g[i]
                if (v>>12)==elevation and not ((v>>10)&3) and (v&1023) in ALLOWED:
                    g[i]=PAVE | elevation<<12
                    painted+=1
        counts[name]=painted
    assert counts==EXPECTED_PAVING, f'unexpected terrain: {counts}'
    for x0,y0 in TREE_CLUSTERS:
        for j,row in enumerate(((794,795),(802,803))):
            for i,expected in enumerate(row):
                x,y=x0+i,y0+j
                v=g[y*u.W+x]
                assert v&1023==expected, f'tree ({x},{y}) has changed'
                assert (x,y) not in events, 'tree overlaps event'
                g[y*u.W+x]=PAVE|(5<<12)
    for x,y in LAMPS:
        top,bottom=(y*u.W+x),((y+1)*u.W+x)
        a,b=g[top],g[bottom]
        assert all((v&1023)==PAVE and not ((v>>10)&3) for v in (a,b)),\
            f'lamp at ({x},{y}) requires pavement below both parts'
        assert a>>12==b>>12, f'lamp elevation split at ({x},{y})'
        assert not ((x,y) in events or (x,y+1) in events), f'lamp overlaps event ({x},{y})'
        elev=a>>12
        g[top]=LAMP_TOP|(1<<10)|(elev<<12)
        g[bottom]=LAMP_BOTTOM|(1<<10)|(elev<<12)
    count=safe(g)
    closed=safe(g,True)
    u.save(g)
    print('paved',counts,'trees removed',TREE_CLUSTERS,'lamps',LAMPS,
          'reachable',count,'stairs-closed',closed)


if __name__=='__main__':
    main()
