# Mossdeep City 2.0 — tileset plan

Status: pipeline proven with 2 appended metatiles (966-967, annex roof). No new pixel art yet. The new metatiles and attributes match Claude's supplied binary patch byte-for-byte. Nothing here is "playable" until a ROM is built and tested in mGBA/Delta.

## Decision: extend `gTileset_Mossdeep`, don't fork it

- `src/field_door.c` binds Mossdeep's door animations to `gTileset_Mossdeep`; a new tileset would need door tables, a header in `src/data/tilesets/headers.h`, graphics and metatile includes, and anim callbacks — code risk before we have a build.
- Appending keeps every existing metatile ID. Vanilla `LAYOUT_MOSSDEEP_CITY` renders the same because every old ID remains unchanged. Routes 124-129 share this tileset and retain their existing IDs.
- Revisit a fork only if we run out of room or need a different tileset animation.

## Budget (secondary tileset, Emerald engine)

| Resource | Limit | Used | Free |
|---|---|---|---|
| Metatiles | 512 | 456 (454 vanilla + 2 Neo) | 56 |
| 8x8 tile slots | 512 | 254 referenced (Claude's inventory) | 258 unreferenced/blank slots |
| Palettes (slots 6-12) | 7 | 7, 8, 9, 10, 11 | 6 and 12 |
| Tile animation | — | none reported for Mossdeep | confirm in game |

Budget is a planning constraint, not a substitute for a successful ROM build. New structures should share tiles and metatiles where possible. Palette 6 is proposed for Ranger/modern steel, blue glass and orange; 12 for harbor/storm rust, steel, hazard yellow and dark water.

## Proposed art

| Feature | Existing graphics | Next action |
|---|---|---|
| Space Center expansion | Yes, dishes and module walls | Kitbash: first annex and roof correction |
| Taller modern buildings | Partial | Add repeating wall rows; dedicated glass/steel pieces later |
| Ranger headquarters | Insufficient | New facade, signage and doorway, preserve door behavior |
| Elevated walkways | Insufficient | First prototype on separate test map; validate elevation/collision |
| Ferry terminal | Insufficient | Separate harbor map and limited Mossdeep entrance |
| Damaged stairs / flooded stores | Partial | New broken-stair and shutter art |

## Workflow

1. Design indexed, 16-color tiles with correct palette assignment in Aseprite/Pixelorama/Porymap.
2. Append new tile graphics only in verified free slots; preserve existing slots.
3. Append new metatiles and attributes in `neo_emerald/tools/map/mossdeep_tileset_v2.py` or Porymap Tileset Editor, never overwrite existing IDs.
4. Place tiles on `LAYOUT_MOSSDEEP_CITY_STORM`, confirm collision/elevation, and render.
5. Run `mossdeep_paths.py`, build, and playtest in mGBA/Delta.
6. Commit one tested feature at a time; preserve original Mossdeep layout.

## Appended metatiles registry

| ID | Name | Built from | Usage |
|---|---|---|---|
| 966 | annex_roof_left_top | 928 with helipad marking removed (tile 661) | observatory annex x46,y10 |
| 967 | annex_roof_left_mid | 936 with helipad marking removed (tile 661) | observatory annex x46,y11 |
