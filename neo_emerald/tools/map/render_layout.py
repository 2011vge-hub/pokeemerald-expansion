"""Render an Emerald Mossdeep layout to PNG from the source tileset.
Usage: python3 neo_emerald/tools/map/render_layout.py <map.bin> <out.png> [--grid] [--mark x,y,label ...]
Requires Pillow (python3-pil); primary tileset General and secondary Mossdeep.
"""
import struct, sys, os
from PIL import Image, ImageDraw
ROOT=os.path.abspath(os.path.join(os.path.dirname(__file__),'../../..'))+'/'
W,H=80,40
PRIM,SEC=ROOT+'data/tilesets/primary/general/',ROOT+'data/tilesets/secondary/mossdeep/'

def pal(path):
    lines=open(path).read().split('\n')[3:19]
    return [tuple(int(v) for v in l.split()[:3]) for l in lines]

pals=[pal(PRIM+f'palettes/{i:02}.pal') for i in range(6)]+[pal(SEC+f'palettes/{i:02}.pal') for i in range(6,13)]+[[(0,0,0)]*16]*3

def tiles(path):
    im=Image.open(path);px=im.load();tw,th=im.size[0]//8,im.size[1]//8
    out=[]
    for ty in range(th):
        for tx in range(tw):
            out.append([[px[tx*8+x,ty*8+y]&15 for x in range(8)] for y in range(8)])
    return out

ptiles,stiles=tiles(PRIM+'tiles.png'),tiles(SEC+'tiles.png')

def metas(path):
    d=open(path,'rb').read()
    return [struct.unpack_from('<8H',d,i*16) for i in range(len(d)//16)]

pm,sm=metas(PRIM+'metatiles.bin'),metas(SEC+'metatiles.bin')

def tile(idx):
    if idx<512:return ptiles[idx] if idx<len(ptiles) else None
    idx-=512
    return stiles[idx] if idx<len(stiles) else None

cache={}
def meta_img(mid):
    if mid in cache:return cache[mid]
    m=pm[mid] if mid<512 else (sm[mid-512] if mid-512<len(sm) else None)
    im=Image.new('RGB',(16,16),(255,0,255))
    if m:
        px=im.load()
        for layer in range(2):
            for q in range(4):
                e=m[layer*4+q];t=tile(e&0x3ff)
                if t is None:continue
                hf,vf,p=e>>10&1,e>>11&1,e>>12
                for y in range(8):
                    for x in range(8):
                        c=t[7-y if vf else y][7-x if hf else x]
                        if layer and c==0:continue
                        px[(q&1)*8+x,(q>>1)*8+y]=pals[p][c]
    cache[mid]=im
    return im

def render(mapbin,out,grid=False,marks=()):
    d=open(mapbin,'rb').read()
    assert len(d)==W*H*2
    g=[struct.unpack_from('<H',d,2*i)[0] for i in range(W*H)]
    im=Image.new('RGB',(W*16,H*16))
    for y in range(H):
        for x in range(W):
            im.paste(meta_img(g[y*W+x]&0x3ff),(x*16,y*16))
    if grid:im=im.resize((W*32,H*32),Image.NEAREST)
    s=32 if grid else 16
    dr=ImageDraw.Draw(im)
    if grid:
        for x in range(0,W,5):
            dr.line([(x*s,0),(x*s,H*s)],fill=(255,255,0))
            dr.text((x*s+2,2),str(x),fill=(255,255,0))
        for y in range(0,H,5):
            dr.line([(0,y*s),(W*s,y*s)],fill=(255,255,0))
            dr.text((2,y*s+2),str(y),fill=(255,255,0))
    for x,y,label in marks:
        dr.rectangle([x*s,y*s,x*s+s-1,y*s+s-1],outline=(255,0,0),width=2)
        dr.text((x*s+2,y*s+s),label,fill=(255,0,0))
    im.save(out)

if __name__=='__main__':
    args=sys.argv[1:];marks=[]
    if '--mark' in args:
        i=args.index('--mark')
        for m in args[i+1:]:
            x,y,l=m.split(',');marks.append((int(x),int(y),l))
        args=args[:i]
    render(args[0],args[1],'--grid' in args,marks)
