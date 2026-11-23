#!/usr/bin/env python3
"""Generate Neo Emerald's first-pass male and female Ranger uniform pixel sprites.

Reuses the game's proven Brendan/May animation frame geometry and animation
tables, but paints new dark-haired Ranger heads, teal/navy field uniforms,
reception-quality shoulder badges, belt highlights, and the female ponytail.
This is a functional v1 art pass rather than finished hand-drawn animation art.

Edits indexed PNGs and their JASC-PAL files in the build workspace so the
underlying engine graphics IDs, palettes and sprite tables stay compatible.
Source originals in Git are not changed by this script's CI invocation.
"""
import argparse
from pathlib import Path
from PIL import Image

ROOT=Path(__file__).resolve().parents[2]
ASSETS=ROOT/'graphics/object_events/pics/people'
PAL=ROOT/'graphics/object_events/palettes'
TRAINER=ROOT/'graphics/trainers'
OUT=ROOT/'neo_emerald/out'

# 4bpp-compatible shared identity, 16 entries including the transparency key.
# Skin stays natural; deep navy silhouette, teal jacket, gray reflective panel,
# gold identification, and a warm orange rescue tab.
MALE=[
(115,197,164),(255,213,180),(245,184,147),(204,133,105),
(110,66,62),(49,86,121),(35,64,97),(22,43,73),
(14,29,50),(191,210,213),(42,163,150),(21,112,112),
(246,181,75),(205,97,57),(239,245,240),(10,18,31)
]
FEMALE=[
(115,197,164),(255,222,205),(232,177,153),(194,121,102),
(107,53,50),(57,91,116),(39,64,100),(27,47,76),
(19,31,55),(192,208,219),(44,169,153),(26,111,109),
(247,178,75),(210,97,53),(241,242,238),(11,20,34)
]

def paltext(colors):
    assert len(colors)==16
    return 'JASC-PAL\n0100\n16\n'+''.join('%d %d %d\n'%c for c in colors)

def save_palette(path,colors):
    if not path.exists():
        raise FileNotFoundError(path)
    path.write_text(paltext(colors))

def reindex(img,female=False,walk=False):
    assert img.mode=='P', 'Expected indexed PNG; artwork must stay 4bpp-compatible'
    cols=FEMALE if female else MALE
    original=img.copy()
    pixels=img.load()
    width,height=img.size
    for y in range(height):
        for x in range(width):
            idx=pixels[x,y]
            if idx>15:
                raise ValueError('PNG color outside 16-color GBA palette')
            if idx==0: continue
            # Original warm/red clothing becomes a dark/teal rescue jacket.
            if idx==12: pixels[x,y]=10
            elif idx==13: pixels[x,y]=11
            # Replace signature Brendan/May white hats and May bow with hair.
            # On 16x32 walking/running frames, source head lies at y=10..18.
            # Only recolor the high head portion, preserve white eyes/gear below.
            if walk and y%32<=16 and idx in (9,14):
                pixels[x,y]=4 if female else 7
    if walk and height==32 and width%16==0:
        for frame in range(width//16):
            left=16*frame
            # Badge and two seam highlights: draw only on existing opaque torso.
            for px,py,color in [(7,24,9),(8,24,12),(9,24,9),(7,26,7),
                                (8,26,7),(9,26,7),(5,23,10),(11,23,10)]:
                if original.getpixel((left+px,py))!=0:
                    pixels[left+px,py]=color
            if female:
                # A tied-back auburn ponytail makes the silhouette distinct.
                # Add only against visible head outlines; avoid standalone pixels.
                if original.getpixel((left+11,17))!=0:
                    for px,py in [(12,17),(13,18),(12,19)]:
                        if 0<=px<16 and original.getpixel((left+max(px-1,0),py))!=0:
                            pixels[left+px,py]=4
    img.putpalette([v for c in cols for v in c]+[0]*(768-48))
    return img

def apply():
    OUT.mkdir(parents=True,exist_ok=True)
    views=[]
    for gender,colors in [('brendan',MALE),('may',FEMALE)]:
        isfemale=(gender=='may')
        sheets=list((ASSETS/gender).glob('*.png'))
        expected={'walking.png','running.png','surfing.png','fishing.png',
                  'acro_bike.png','mach_bike.png','field_move.png',
                  'underwater.png','decorating.png','watering.png'}
        assert expected.issubset({p.name for p in sheets}),f'Missing {gender} graphics'
        for path in sheets:
            with Image.open(path) as raw:
                img=raw.copy()
            walk=path.name in ('walking.png','running.png')
            img=reindex(img,isfemale,walk)
            img.save(path, optimize=True, bits=4)
            if path.name=='walking.png':
                views.append(img.convert('RGBA').resize((img.width*5,img.height*5),Image.Resampling.NEAREST))
        save_palette(PAL/(gender+'.pal'),colors)
        # Reflection palette uses washed-out, cool blues but the same index map.
        reflected=[((r*2+80)//3,(g*2+115)//3,(b*2+160)//3) for r,g,b in colors]
        reflected[0]=(148,230,230)
        save_palette(PAL/(gender+'_reflection.pal'),reflected)
        # Battle backs: match the same uniform palette and tint the existing pose.
        bpath=TRAINER/'back_pics'/(gender+'.png')
        with Image.open(bpath) as raw:
            b=raw.copy()
        b=reindex(b,isfemale,False)
        b.save(bpath, optimize=True, bits=4)
        save_palette(TRAINER/'palettes'/(gender+'.pal'),colors)
        print(f'Generated {gender} Ranger uniform: {len(sheets)} action sheets, battle back, palettes')
    if views:
        preview=Image.new('RGBA',(max(v.width for v in views),sum(v.height for v in views)),(10,22,37,255))
        y=0
        for v in views:
            preview.alpha_composite(v,(0,y));y+=v.height
        preview.save(OUT/'NeoEmerald_RangerSpritePreview.png')
        print('Wrote',OUT/'NeoEmerald_RangerSpritePreview.png')

if __name__=='__main__':
    apply()
