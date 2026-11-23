"""Mossdeep City v3 indexed 8x8 sidewalk and streetlight tiles.

Add custom graphics only into nine pre-verified blank/unreferenced secondary
tile slots. Append three metatiles (976 pavement, 977/978 light pole sections)
without changing existing tiles or palette data. The artwork uses shared
General palette 0; streetlamps are static and do not actually cast light.

Usage: python3 neo_emerald/tools/map/mossdeep_v3_street_art.py

Idempotent: previously installed identical art/metatiles are verified, not
rewritten. Requires Pillow; standard PNG index semantics are preserved.
"""
import os
import struct
from PIL import Image

ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), '../../..')) + '/'
TS = ROOT + 'data/tilesets/secondary/mossdeep/'
GRAPHIC_IDS = [550, 551, 559, 562, 564, 565, 566, 567, 575]
FIRST_METATILE = 976
BASE_COUNT = 464
DOOR_RESERVED = set(range(1008, 1024))


def pave_pattern():
    return [4 if x == 0 or y == 0 else
            5 if x == 7 or y == 7 else
            3 if (x + y) % 7 == 0 else 2
            for y in range(8) for x in range(8)]


def lamp_patterns():
    grid = [[0] * 16 for _ in range(32)]

    def rect(x0, y0, x1, y1, palette_index):
        for y in range(y0, y1 + 1):
            for x in range(x0, x1 + 1):
                grid[y][x] = palette_index

    rect(7, 0, 8, 1, 7)
    rect(5, 2, 10, 2, 7)
    rect(4, 3, 11, 4, 7)
    rect(5, 4, 10, 6, 2)
    rect(6, 5, 9, 5, 1)
    rect(5, 7, 10, 7, 7)
    rect(7, 8, 8, 25, 6)
    rect(7, 11, 7, 24, 5)
    rect(8, 13, 8, 24, 7)
    rect(6, 26, 9, 27, 5)
    rect(5, 28, 10, 28, 6)
    rect(4, 29, 11, 30, 7)
    rect(5, 29, 10, 29, 5)

    return [[grid[cell_y * 8 + y][cell_x * 8 + x]
             for y in range(8) for x in range(8)]
            for cell_y in range(4) for cell_x in range(2)]


def read_u16(path):
    b = open(path, 'rb').read()
    return list(struct.unpack('<' + 'H' * (len(b) // 2), b))


def write_u16(path, values):
    with open(path, 'wb') as f:
        f.write(struct.pack('<' + 'H' * len(values), *values))


def install_art():
    path = TS + 'tiles.png'
    im = Image.open(path)
    assert im.size == (128, 256) and im.mode == 'P', \
        'requires 128x256 indexed Mossdeep sheet'
    pixels = im.load()
    patterns = [pave_pattern()] + lamp_patterns()
    assert len(patterns) == len(GRAPHIC_IDS) == 9
    already, missing = 0, 0
    for tile_id, pattern in zip(GRAPHIC_IDS, patterns):
        assert tile_id not in DOOR_RESERVED and 512 <= tile_id < 1008
        slot = tile_id - 512
        tx, ty = (slot % 16) * 8, (slot // 16) * 8
        found = [pixels[tx + x, ty + y] & 15
                 for y in range(8) for x in range(8)]
        if found == pattern:
            already += 1
            continue
        assert not any(found), f'tile {tile_id} is no longer blank'
        for index, value in enumerate(pattern):
            pixels[tx + index % 8, ty + index // 8] = value
        missing += 1
    if missing:
        im.save(path, bits=4)
    print('street artwork verified:', already, 'existing;', missing, 'installed')


def install_metatiles():
    path = TS + 'metatiles.bin'
    attr_path = TS + 'metatile_attributes.bin'
    m, a = read_u16(path), read_u16(attr_path)
    assert len(m) == 8 * len(a), 'metatiles/attributes not aligned'
    pavement = [550, 550, 550, 550, 0, 0, 0, 0]
    lamp_top = [550, 550, 550, 550, 551, 559, 562, 564]
    lamp_bottom = [550, 550, 550, 550, 565, 566, 567, 575]
    expected = pavement + lamp_top + lamp_bottom
    if len(a) == BASE_COUNT:
        write_u16(path, m + expected)
        write_u16(attr_path, a + [0, 0, 0])
        print('appended metatiles 976 pavement, 977 upper lamp, 978 lower lamp')
    else:
        assert len(a) == BASE_COUNT + 3 and m[BASE_COUNT * 8:] == expected \
            and a[BASE_COUNT:] == [0, 0, 0], \
            'existing v3 metatiles differ; refusing overwrite'
        print('metatiles 976-978 already installed')


if __name__ == '__main__':
    install_art()
    install_metatiles()
