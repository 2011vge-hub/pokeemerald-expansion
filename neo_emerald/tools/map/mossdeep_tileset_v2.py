"""Append-only Mossdeep City 2.0 metatile and Route 110 walkway importer.

Usage: python3 neo_emerald/tools/map/mossdeep_tileset_v2.py
- Existing vanilla IDs are preserved.
- Never writes into runtime door-animation slots 496..511.
- Copies only into verified blank and unreferenced 8x8 tile positions.
- Validates previously appended definitions and appends missing ones.
"""
import os, struct
from PIL import Image

ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), '../../..')) + '/'
TS = ROOT + 'data/tilesets/secondary/mossdeep/'
VANILLA_COUNT = 454
FIRST_ID = 512 + VANILLA_COUNT
DOOR_RESERVED = range(496, 512)

# (source tileset, source tile ID) -> Mossdeep tile ID
# Uses General palette 0 / 4, already shared by both tilesets.
IMPORT_TILES = {
    ('mauville', 574): 513, ('mauville', 575): 516, ('mauville', 590): 517,
    ('mauville', 681): 527, ('mauville', 682): 528, ('mauville', 697): 529,
    ('mauville', 698): 543, ('mauville', 762): 548, ('mauville', 763): 549,
}

# name, source metatile, edits {entry_index: (tile, palette, hflip, vflip)}
NEW_METATILES = [
    ('annex_roof_left_top', 928, {7: (661, 8, 0, 0)}),
    ('annex_roof_left_mid', 936, {5: (661, 8, 0, 0), 7: (661, 8, 0, 0)}),
    ('walkway_rail_north', ('mauville', 754), {}),
    ('walkway_deck_shaded', ('mauville', 758), {}),
    ('walkway_deck', ('mauville', 766), {}),
    ('walkway_rail_south', ('mauville', 774), {}),
    ('civic_roof_plain', 936, {4: (661, 8, 0, 0), 5: (661, 8, 0, 0), 6: (661, 8, 0, 0), 7: (661, 8, 0, 0)}),
    ('civic_roof_top', 936, {4: (523, 8, 0, 0), 5: (523, 8, 0, 0), 6: (661, 8, 0, 0), 7: (661, 8, 0, 0)}),
    ('walkway_deck_rail_west', ('mauville', 741), {}),
    ('walkway_deck_rail_east', ('mauville', 742), {}),
]
BEHAVIOR_OVERRIDE = {
    'walkway_rail_north': 0, 'walkway_deck_shaded': 0,
    'walkway_deck': 0, 'walkway_rail_south': 0,
    'walkway_deck_rail_west': 0, 'walkway_deck_rail_east': 0,
}


def read_u16(path):
    b = open(path, 'rb').read()
    return [struct.unpack_from('<H', b, 2 * i)[0] for i in range(len(b) // 2)]


def write_u16(path, vals):
    b = bytearray(2 * len(vals))
    for i, v in enumerate(vals):
        struct.pack_into('<H', b, 2 * i, v)
    open(path, 'wb').write(b)


def foreign(tileset, mid):
    d = ROOT + f'data/tilesets/secondary/{tileset}/'
    m, a = read_u16(d + 'metatiles.bin'), read_u16(d + 'metatile_attributes.bin')
    entries = []
    for e in m[(mid - 512) * 8:(mid - 512) * 8 + 8]:
        t = e & 0x3ff
        if t >= 512:
            assert (tileset, t) in IMPORT_TILES, f'{tileset} tile {t} used by {mid} not imported'
            t = IMPORT_TILES[(tileset, t)]
        assert e >> 12 < 6, f'{tileset} metatile {mid} uses a non-General palette'
        entries.append(t | (e & 0xfc00))
    return entries, a[mid - 512]


def import_tiles():
    path = TS + 'tiles.png'
    dst = Image.open(path)
    dpx = dst.load()
    changed = False
    for (tileset, src_id), dst_id in IMPORT_TILES.items():
        slot = dst_id - 512
        assert 0 < slot < 512 and slot not in DOOR_RESERVED, f'bad destination slot {slot}'
        src = Image.open(ROOT + f'data/tilesets/secondary/{tileset}/tiles.png').load()
        si = src_id - 512
        sx, sy = (si % 16) * 8, (si // 16) * 8
        dx, dy = (slot % 16) * 8, (slot // 16) * 8
        want = [src[sx + x, sy + y] & 15 for y in range(8) for x in range(8)]
        have = [dpx[dx + x, dy + y] & 15 for y in range(8) for x in range(8)]
        if have == want:
            continue
        assert not any(have), f'destination slot {slot} is not blank'
        for i, v in enumerate(want):
            dpx[dx + i % 8, dy + i // 8] = v
        changed = True
    if changed:
        dst.save(path, bits=4)
    return changed


def build(metas, attrs):
    out_m, out_a = [], []
    for name, base, edits in NEW_METATILES:
        if isinstance(base, tuple):
            entries, attr = foreign(*base)
            if name in BEHAVIOR_OVERRIDE:
                attr = (attr & 0xff00) | BEHAVIOR_OVERRIDE[name]
            out_m += entries
            out_a.append(attr)
            continue
        entries = list(metas[(base - 512) * 8:(base - 512) * 8 + 8])
        for idx, (tile, pal, hf, vf) in edits.items():
            entries[idx] = tile | hf << 10 | vf << 11 | pal << 12
        out_m += entries
        out_a.append(attrs[base - 512])
    return out_m, out_a


def ids():
    return {name: FIRST_ID + i for i, (name, _, _) in enumerate(NEW_METATILES)}


def main():
    if import_tiles():
        print(f'imported {len(IMPORT_TILES)} tiles into tiles.png')
    metas, attrs = read_u16(TS + 'metatiles.bin'), read_u16(TS + 'metatile_attributes.bin')
    count = len(attrs)
    assert len(metas) == count * 8, 'metatile and attribute count mismatch'
    new_m, new_a = build(metas, attrs)
    n = len(NEW_METATILES)
    assert VANILLA_COUNT + n <= 512, 'secondary metatile budget exceeded'
    if count == VANILLA_COUNT:
        write_u16(TS + 'metatiles.bin', metas + new_m)
        write_u16(TS + 'metatile_attributes.bin', attrs + new_a)
        print(f'appended {n} metatiles as IDs {FIRST_ID}-{FIRST_ID + n - 1}')
    else:
        have_m = metas[VANILLA_COUNT * 8:]
        have_a = attrs[VANILLA_COUNT:]
        assert new_m[:len(have_m)] == have_m and new_a[:len(have_a)] == have_a, \
            'appended metatiles differ; reconcile before re-running'
        if count == VANILLA_COUNT + n:
            print('already applied; nothing to do')
            return
        assert count < VANILLA_COUNT + n, 'tileset has more metatiles than this script'
        k = count - VANILLA_COUNT
        write_u16(TS + 'metatiles.bin', metas + new_m[k * 8:])
        write_u16(TS + 'metatile_attributes.bin', attrs + new_a[k:])
        print(f'appended {n-k} metatiles as IDs {FIRST_ID+k}-{FIRST_ID+n-1}')
    for i, (name, base, _) in enumerate(NEW_METATILES):
        print(f'  {FIRST_ID+i}: {name} (from {base})')


if __name__ == '__main__':
    main()
