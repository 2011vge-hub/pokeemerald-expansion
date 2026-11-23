#!/usr/bin/env python3
"""Build Neo Emerald Ranger player sprites from native Emerald overworld art.

Walking and running use checked-in original 144x32 (9-frame) Ranger pixel
sprites in native GBA 4bpp format, not the old Camper/Picnicker recolors.
Frames have orange cap and field vest, dark trousers, gloves, boots, and a
hip-mounted Ranger Styler, matching the user's uploaded visual references.
Other actions (surfing, fishing, cycling and battle backs) use provisional
existing pose geometry with Ranger recoloring until dedicated action art is
finished and Delta-tested.

The four original walking/running PNGs are committed source assets and are
validated but never repainted during builds. All 16-color indexes retain
compatible native GBA animation tables.
"""
import argparse
from pathlib import Path
from PIL import Image

ROOT=Path(__file__).resolve().parents[2]
ASSETS=ROOT/'graphics/object_events/pics/people'
PAL=ROOT/'graphics/object_events/palettes'
TRAINER=ROOT/'graphics/trainers'
OUT=ROOT/'neo_emerald/out'

# RANGER_PIXEL_ART_V1: palette shared across all original front/back/side
# Ranger pixel poses. Sprite pixel index 0 is transparent (GBA hardware).
# All sixteen source colors are intentionally fixed; never silently reindex
# the four checked-in player walking/running sheets back to NPC silhouettes.
RANGER_PALETTE=[
 (115,197,164),(255,215,184),(234,174,143),(166,105,95),
 (25,30,45),(52,59,91),(255,184,80),(238,125,52),
 (167,64,39),(29,43,70),(67,82,111),(23,35,60),
 (186,76,45),(10,19,36),(241,242,229),(255,209,104)
]
MALE=list(RANGER_PALETTE)
FEMALE=list(RANGER_PALETTE)

def validate_ranger_art(img, path, colors):
    """Refuse to overwrite the user's actual Ranger pixels during CI."""
    assert img.mode=='P' and img.size==(144,32), f"Invalid Ranger sheet: {path}"
    assert max(img.getdata()) <= 15, f"Must be GBA 4bpp indexed: {path}"
    assert img.getpalette()[:48] == [n for rgb in colors for n in rgb], (
        f"Palette mismatch in {path}: artwork is not using shared Ranger colors")
    assert sum(px in (6,7,8) for px in img.getdata()) >= 30, (
        f"Missing orange cap/vest colors in {path}")
    # 9 native 16x32 animation frames all have body pixels in the correct cell.
    for frame in range(9):
        assert img.crop((16*frame,0,16*(frame+1),32)).getbbox() is not None, (
            f"Empty movement frame {frame}: {path}")
    return img

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
            walk=path.name in ('walking.png','running.png')
            with Image.open(path) as raw:
                img=raw.copy()
            if walk:
                # This is original drawn pixel art checked into GitHub; do
                # not regenerate it from Brendan, May, Camper or Picnicker.
                img=validate_ranger_art(img,path,colors)
            else:
                # Temporary action set: old engine pose geometry recolored
                # to match the orange Ranger palette; true 16x32 custom
                # bike/surf/fishing/etc silhouettes remain on the art board.
                img=reindex(img,isfemale,False)
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
