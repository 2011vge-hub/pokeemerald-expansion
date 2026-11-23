#!/usr/bin/env python3
"""Generate Neo Emerald's first-pass male and female Ranger uniform pixel sprites.

Reuses the game's proven Brendan/May animation frame geometry and animation
tables, but paints new dark-haired Ranger heads, teal/navy field uniforms,
silver-blue Ranger hair and rescue strap for the boy, and the girl's blue hair,
orange top and teal shorts, to match the already-approved full ID portraits.
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

def reindex(img, female=False, walk=False):
    """Match the existing large ID portraits, not Brendan/May's hat/bow colors.

    Male: silver-blue spiked hair, navy suit, diagonal orange rescue strap.
    Female: midnight-blue hair with teal streak, orange top, teal shorts.
    Keep every engine animation in its existing frame grid and 16-color palette.
    """
    assert img.mode == "P", "Expected indexed PNG (not RGB)"
    colors = FEMALE if female else MALE
    orig = img.copy()
    px = img.load()
    width, height = img.size
    for y in range(height):
        for x in range(width):
            k = orig.getpixel((x, y))
            if k > 15:
                raise ValueError(f"Unexpected palette index at ({x},{y}): {k}")
            if k == 0:
                continue
            yy, xx = y % 32, x % 16
            if walk and yy <= 22:
                if female:
                    # Original May ribbon and warm hair are now midnight-blue locks.
                    if yy <= 21 and k not in (1, 2, 3):
                        px[x, y] = ([6, 5, 7, 8][(x+y) % 4]
                                    if k not in (9, 14)
                                    else [9, 10][(x+y) % 2])
                    if yy <= 17 and k in (10, 11, 12, 13):
                        px[x, y] = 6
                else:
                    # Former white hat silhouette becomes silver-blue hair.
                    if yy <= 17 and k not in (1, 2, 3, 15):
                        if yy <= 14:
                            px[x, y] = 9 if (x+y) % 4 else 14
                        else:
                            px[x, y] = 5 if k in (5, 6, 7, 8) else 9
                        if yy in (12, 13, 14, 15) and xx in (9, 10):
                            px[x, y] = 10
            if walk and 22 <= yy <= 28:
                if not female:
                    if yy in (23, 24, 25, 26) and 5 <= xx <= 10 and k not in (1, 2, 3):
                        px[x, y] = 6 if (xx+yy) % 3 else 5
                    if yy in (23, 24, 25, 26) and xx == yy - 23 + 5 and k not in (1, 2, 3):
                        px[x, y] = 12
                    if yy == 26 and 5 <= xx <= 10 and k not in (1, 2, 3):
                        px[x, y] = 10
                else:
                    if yy in (23, 24, 25, 26) and 5 <= xx <= 10 and k not in (1, 2, 3):
                        px[x, y] = 13 if (xx+yy) % 4 else 12
                    if yy == 26 and 5 <= xx <= 10 and k not in (1, 2, 3):
                        px[x, y] = 10
                    if yy in (27, 28) and 5 <= xx <= 10 and k not in (1, 2, 3):
                        px[x, y] = 6 if xx % 3 else 5
            elif not walk:
                # Fishing, riding, surfing and battle backs inherit a matched
                # hair/uniform palette without changing fragile pose geometry.
                if k in (12, 13):
                    px[x, y] = 13 if female else 10
                if k in (9, 14) and yy < 18:
                    px[x, y] = 6 if female else 9
    if walk and height == 32 and width % 16 == 0:
        for frame in range(width//16):
            left = 16*frame
            accents = ([(7, 12, 9), (8, 12, 10), (8, 13, 10),
                        (10, 14, 10), (11, 17, 6)] if female else
                       [(7, 11, 9), (8, 10, 14), (9, 10, 9),
                        (10, 11, 10), (11, 12, 9)])
            for dx, dy, col in accents:
                if orig.getpixel((left+dx, dy)) != 0:
                    px[left+dx, dy] = col
    img.putpalette([c for rgb in colors for c in rgb] + [0]*(768-48))
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
