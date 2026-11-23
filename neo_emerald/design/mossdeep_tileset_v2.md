# Mossdeep City 2.0 — tileset plan

Status: **13 Neo metatiles appended (966–978)**. Nine Route 110 walkway graphics plus nine new indexed street-art tiles installed in previously blank slots. Existing IDs preserved. Binary assets are source-created/validated, but the v3 build has not yet been tested on an emulator.

## Decision: extend `gTileset_Mossdeep`, don't fork it

- `src/field_door.c` binds Mossdeep's door animations to `gTileset_Mossdeep`; a new tileset would need door tables, a header in `src/data/tilesets/headers.h`, graphics and metatile includes, and anim callbacks — code risk before we have a build.
- Appending keeps every existing metatile ID. Vanilla `LAYOUT_MOSSDEEP_CITY` renders the same because every old ID remains unchanged. Routes 124-129 share this tileset and retain their existing IDs.
- Revisit a fork only if we run out of room or need a different tileset animation.

## Budget (secondary tileset, Emerald engine)

| Resource | Limit | Used | Free |
|---|---|---|---|
| Metatiles | 512 | **467 (454 vanilla + 13 Neo)** | **45** |
| 8x8 tile slots | 512 | Nine Route 110 imports + nine v3 street-art patterns added | Many slots remain blank; 496–511 are reserved for door animations |
| Palettes (slots 6-12) | 7 | 7, 8, 9, 10, 11 | 6 and 12 |
| Tile animation | — | none reported for Mossdeep | confirm in game |

Budget is a planning constraint, not a substitute for a successful ROM build. New structures should share tiles and metatiles where possible. Palette 6 is proposed for Ranger/modern steel, blue glass and orange; 12 for harbor/storm rust, steel, hazard yellow and dark water.

## Proposed art

| Feature | Existing graphics | Next action |
|---|---|---|
| Space Center expansion | Yes, dishes and module walls | Main Space Center retained; decorative annex removed in v3 |
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


## Neo metatile registry

| IDs | Source | Purpose |
|---|---|---|
| 966–967 | Existing Space Center roof | Observatory roof correction |
| 968–971 | Route 110 / Mauville art and General palettes | North rail, shaded deck, deck, south rail |
| 972–973 | Space Center plain roof | Ranger HQ civic tower |
| 974–975 | Route 110 / Mauville art | Quay platform side railing |
| 976 | New indexed stone paving art, tile 550, General palette 0 | Urban sidewalks and plazas |
| 977–978 | Eight new indexed top-layer 8×8 pixels (tile IDs 551, 559, 562, 564, 565–567, 575) | Two-stage 16×32 static lampposts, blocked collision when placed |

`data/tilesets/secondary/mossdeep/tiles.png` is an indexed PNG with nine imported 8×8 graphics patterns. The visual pattern mapping is verified against the source tiles; the binary differs from the collaborator's PNG only due to image re-encoding. Do not reapply the old patches.

### Street-art construction

Regenerate/verify the v3 additions with `python3 neo_emerald/tools/map/mossdeep_v3_street_art.py`. It refuses to overwrite nonblank graphics, uses General palette 0, and appends only after ID 975. Street-paving uses a blue-grey 8×8 repeating pattern; the streetlight uses a white/light-blue fixture and navy metallic pole. **Lights are decorative, not dynamic light emitters.** Always render and inspect in Porymap and test in a compiled ROM. The older annex correction IDs 966/967 remain allocated even though the annex was removed.
