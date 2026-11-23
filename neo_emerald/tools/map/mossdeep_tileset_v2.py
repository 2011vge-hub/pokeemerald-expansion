"""Mossdeep City 2.0 tileset additions, appended to gTileset_Mossdeep.

Why append instead of a new tileset: door animations (src/field_door.c) and the
tileset header are bound to gTileset_Mossdeep, so a separate tileset would need
code changes. Appending leaves every existing metatile ID unchanged, so vanilla
Mossdeep, Routes 124-129 and the backup layout render exactly as before.

Budget (secondary tileset): 512 metatiles (454 vanilla), 512 tiles (258 unreferenced
blank slots, no Mossdeep tile animation), palette slots 6 and 12 unused.

usage: python3 neo_emerald/tools/map/mossdeep_tileset_v2.py  # append / verify
Idempotent: re-running checks that the appended metatiles match and changes nothing.
"""
import os, struct

ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), '../../..')) + '/'
TS = ROOT + 'data/tilesets/secondary/mossdeep/'
VANILLA_COUNT = 454
FIRST_ID = 512 + VANILLA_COUNT  # 966

# Each new metatile: (name, base metatile ID, {entry index: (tile, palette, hflip, vflip)})
# Entries 0-3 = bottom layer TL,TR,BL,BR; 4-7 = top layer TL,TR,BL,BR.
NEW_METATILES = [
    ('annex_roof_left_top', 928, {7: (661, 8, 0, 0)}),
    ('annex_roof_left_mid', 936, {5: (661, 8, 0, 0), 7: (661, 8, 0, 0)}),
]


def read_u16(path):
    b = open(path, 'rb').read()
    return [struct.unpack_from('<H', b, 2 * i)[0] for i in range(len(b) // 2)]


def write_u16(path, vals):
    b = bytearray(2 * len(vals))
    for i, v in enumerate(vals):
        struct.pack_into('<H', b, 2 * i, v)
    open(path, 'wb').write(b)


def build(metas, attrs):
    out_m, out_a = [], []
    for name, base, edits in NEW_METATILES:
        entries = list(metas[(base - 512) * 8:(base - 512) * 8 + 8])
        for idx, (tile, pal, hf, vf) in edits.items():
            entries[idx] = tile | hf << 10 | vf << 11 | pal << 12
        out_m += entries
        out_a.append(attrs[base - 512])
    return out_m, out_a


def main():
    metas, attrs = read_u16(TS + 'metatiles.bin'), read_u16(TS + 'metatile_attributes.bin')
    count = len(attrs)
    assert len(metas) == count * 8
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
        assert have_m[:len(new_m)] == new_m and have_a[:len(new_a)] == new_a, \
            'appended metatiles differ from this script; reconcile before re-running'
        if count == VANILLA_COUNT + n:
            print('already applied; nothing to do')
            return
        raise SystemExit(f'tileset has {count - VANILLA_COUNT} added metatiles but script defines {n}; '
                         'append the new definitions in order')
    for i, (name, base, _) in enumerate(NEW_METATILES):
        print(f'  {FIRST_ID + i}: {name} (from {base})')


if __name__ == '__main__':
    main()
