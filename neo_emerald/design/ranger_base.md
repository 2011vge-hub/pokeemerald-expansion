# Mossdeep Ranger Base

Status: implemented in source on `neo-emerald/mossdeep-city-v3-streets`;
**not compiled or tested in mGBA/Delta yet**. See source-check limitations below.

## Location and maps

- HQ tower beside the Pokémon Center and Mart, x32–34, y13–19.
- Glass door (33,19) is Mossdeep warp **10** -> `MAP_MOSSDEEP_CITY_RANGER_BASE_1F`, warp 0.
- The glass-door metatile 749 is unchanged (only elevation normalized for a door warp).
- The building sign moved from the door to the wall (32,19).
- Existing Mossdeep warps 0–9 and pre-existing indoor map/layout IDs are unchanged.
- `MAP_MOSSDEEP_CITY_RANGER_BASE_1F` and `_2F` were appended to Mossdeep's indoor map group, with two new layouts.
- Each floor is 16×10, General + Facility tilesets; its furniture reuses Space Center interiors. Generator: `neo_emerald/tools/map/ranger_base.py`. Do not rerun after manual Porymap edits.

## Staffing and functions

| Role | Name | Floor | In-source function | Limit |
|---|---|---|---|---|
| Commander | Hale | 2F (7,6) | Checks mission count, field XP and badges; promotes one rank at a time | No mission reward scripts yet |
| Dispatch | June | 1F (3,4) | Briefs player on sailor check-in and missing child | Future missions need additional states |
| Medic | Tala | 1F (13,6) | `special HealPlayerParty`, healing fanfare | Must test in emulator |
| Quartermaster | Brant | 1F (3,7) | Issues 3 Potions once using a persistent flag; handles full bag | Later gear upgrades dialogue-only |
| Technician | Remy | 2F (13,7) | Describes field repairs and Senior-rank upgrades | Dialogue-only |
| Rookie | Ari | 1F (9,5) | Introduces base and future field partnership | Dialogue-only |

Staff presently use existing overworld sprites (woman, camper, nurse, hiker, older expert and scientist), **not custom Ranger uniforms**.

## Rooms

- **1F**: Dispatch desk, reception, mission board, healing station, supply lockers, entrance and stairs.
- **2F**: Storm-monitor consoles, communications desks, commander and upgrade bench.
- Monitoring and communication desks use readable sign scripts. The alert log notes the public siren was still pending after the surge was detected.

## Rank framework

Five ranks: Rookie (0), Ranger (1), Senior (2), Area (3), Top (4).
The commander's requirements to **reach** each rank are:

| Rank | Missions | Field XP | Gym badges |
|---|---:|---:|---:|
| Ranger | 1 | 100 | 1 |
| Senior | 3 | 400 | 3 |
| Area | 6 | 900 | 5 |
| Top | 10 | 1600 | 8 |

Persistent counters: `VAR_NEO_RANGER_RANK` (0x40FC), `VAR_NEO_RANGER_MISSIONS` (0x40FD), `VAR_NEO_RANGER_XP` (0x40FE); the kit-claimed flag is `FLAG_NEO_RANGER_KIT_ISSUED` (0x20).
**No mission completion currently increases mission count or field XP**, so promotions cannot yet be earned. The ferry rescue is the appropriate first milestone to credit.
The badge count reads `FLAG_BADGE01_GET` through `FLAG_BADGE08_GET`.

## Opening

After the Ranger partner selection, dispatch mentions the base as an optional stop. The sailor and the missing child remain the immediate rescue objective, with no forced base visit. Dialogue in the base responds to dispatch states 2 and 3.

## Test in a built ROM

1. Start a new game, enter HQ at (33,19), confirm door animation, 1F landing and return exit at (33,20).
2. Climb to 2F and return; verify all stair warp indices.
3. Speak to six staff before/after sailor check-in.
4. Damage Pokémon, heal at Tala, confirm fanfare and party HP.
5. Brant gives exactly three Potions once, even after saving/reloading; test with full bag.
6. Hale shows 1 mission / 100 XP / 1 badge for next promotion and initially reports zero progress.
7. Read mission board, command consoles and HQ sign; save and reload within 1F or 2F.

All floor tiles and the HQ-door tile were reconstructed to the exact Git blob checksums in Claude's original patches. Reachability checks use collision/elevation approximations and do **not** prove actual warp animation, runtime scripts, saving or graphics are bug-free.
