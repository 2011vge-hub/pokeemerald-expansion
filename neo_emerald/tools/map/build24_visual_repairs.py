#!/usr/bin/env python3
"""Build 24 playtest repairs. Keep original geometry and save IDs."""
import json
import struct
from pathlib import Path
from collections import deque
from PIL import Image

ROOT = Path(__file__).resolve().parents[3]

def read_words(path):
    raw = path.read_bytes()
    return list(struct.unpack("<" + "H"*(len(raw)//2), raw))

def write_words(path, words):
    path.write_bytes(struct.pack("<" + "H"*len(words), *words))

# University: original facade overlays draw on BG1 (NORMAL). Covered
# metatiles draw their upper artwork behind the player on BG2. Only change
# the ground-level facade; retain all behavior bits including the door.
rust = ROOT/"data/tilesets/secondary/rustboro/metatile_attributes.bin"
attrs = read_words(rust)
for mid in range(0x37a, 0x381):
    i = mid-512
    assert attrs[i] in (0,0x69,0x1000,0x1069), (mid,attrs[i])
    attrs[i] = (attrs[i]&0x0fff)|0x1000
assert attrs[0x37d-512]&0x0fff == 0x69
write_words(rust, attrs)

# Male battle-back: change only contiguous white/light-gray headwear
# regions in the upper part of each 64x64 frame. Dark navy/black existing
# palette entries are reused so no body or transparent colors are changed.
back = ROOT/"graphics/trainers/back_pics/brendan.png"
with Image.open(back) as img:
    img.load()
    assert img.mode == "P" and img.size == (64,256)
    palette = img.getpalette()
    assert tuple(palette[9*3:9*3+3]) == (222,230,238)
    assert tuple(palette[14*3:14*3+3]) == (255,255,255)
    assert tuple(palette[13*3:13*3+3]) == (45,58,89)
    pixels = img.load()
    changed = 0
    for frame in range(4):
        top = frame*64
        light = {(x,y) for y in range(top,top+40) for x in range(64)
                 if pixels[x,y] in (9,14)}
        while light:
            seed=light.pop()
            component={seed}
            queue=deque([seed])
            while queue:
                x,y=queue.popleft()
                for pos in ((x-1,y),(x+1,y),(x,y-1),(x,y+1)):
                    if pos in light:
                        light.remove(pos)
                        component.add(pos)
                        queue.append(pos)
            if len(component)<6 or min(y for x,y in component)>=top+32:
                continue
            for x,y in component:
                pixels[x,y]=13 if pixels[x,y]==14 else 8
                changed+=1
    if changed:
        kwargs={"bits":4}
        if "transparency" in img.info:
            kwargs["transparency"]=img.info["transparency"]
        img.save(back,**kwargs)
    print("Male Ranger battle-back dark hair pixels changed:",changed)

# Remove the former Gym, preserving all unrelated map and warp indices.
mp=ROOT/"data/layouts/MossdeepCity_Storm/map.bin"
data=read_words(mp)
assert len(data)==80*40
city=json.loads((ROOT/"data/maps/MossdeepCity/map.json").read_text())
assert city["warp_events"][1]["dest_map"]=="MAP_MOSSDEEP_CITY_WEATHER_STATION"
assert (city["warp_events"][1]["x"],city["warp_events"][1]["y"])==(33,19)
old=[
    [426,427,427,427,427,428],
    [434,435,435,435,435,436],
    [440,441,442,435,443,444],
    [448,449,450,453,451,452],
    [456,457,458,461,459,460],
]
previous_kit=[
    [966,932,932,932,932,814],
    [944,948,948,948,948,859],
    [952,954,733,733,955,957],
    [738,740,740,741,742,719],
    [746,748,748,749,750,727],
]
current=[[data[(5+y)*80+35+x]&1023 for x in range(6)] for y in range(5)]
assert current in (old,previous_kit,[[1]*6 for _ in range(5)]), "Unexpected Gym footprint; protect newer art"
for y in range(5):
    for x in range(6):
        data[(5+y)*80+35+x]=1|((4 if y==0 else 5)<<12)
# Remove the physical GYM sign, not just its text.
assert data[9*80+34]&1023 in (305,1)
data[9*80+34]=1|(5<<12)
# Open the existing inland tower's native glass door into the weather station.
assert data[19*80+33]&1023==749
data[19*80+33]&=0x0fff
assert data[20*80+33]>>12==5 and not (data[20*80+33]>>10)&3
write_words(mp,data)

# The waterfront already uses the original HQ terminal facade. Open its
# native glass door; preserve the docks, ferry, boarding path and map ID.
wp=ROOT/"data/layouts/MossdeepCity_Waterfront/map.bin"
q=read_words(wp)
assert len(q)==32*40
assert q[32*32+17]&1023==749, "Unexpected waterfront door tile"
q[32*32+17]&=0x0fff
assert q[33*32+17]>>12==5 and not (q[33*32+17]>>10)&3
write_words(wp,q)
print("Former Gym and sign removed; inland weather station and waterfront HQ doors opened.")
print("University ground-level layering corrected; runtime inspection required.")
