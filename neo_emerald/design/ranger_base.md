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
| Commander | Hale | 2F (7,6) | Checks mission count, field XP and badges; promotes one rank at a time | First ferry rescue now credits +1 mission/100 XP in source; a badge is still required to promote |
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
The **ferry rescue** is now scripted to award +1 completed Ranger mission and +100 Ranger XP (`NEO_MISSION_FERRY_RESCUE_XP`) once when the waterfront boarding scene completes. Commander Hale can evaluate promotion afterward; the first **RANGER** promotion still requires one Gym Badge. The static guard `neo_emerald/tools/check_rescue_once.py` is called by `build.sh`. This verifies script structure, not runtime behavior.
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


## Mossdeep ferry rescue: source implementation, not playtested

| State | Meaning | Source |
|---|---|---|
| 1 | Initial dispatch call pending | New game |
| 2 | Ranger partner selected; check in with the sailor | Mossdeep opening |
| 3 | Sailor check-in done, child rescue available | Mossdeep sailor |
| 4 | Boy and Poochyena escorted to the quay; boarding pending | Child dialogue at southern landing, scripted warp |
| 5 | Boarding completed; mission and XP credited | Waterfront on-frame scene |

Visibility: `FLAG_NEO_HIDE_LANDING_RESCUEES` hides the pair on the landing at state 4 and later; `FLAG_NEO_HIDE_QUAY_RESCUEES` shows them only at state 4 on the quay. Both flags are synchronized by their maps' ON_TRANSITION scripts.

At state 3, speaking to the boy calms his Poochyena and fades the party to the waterfront. At state 4, the boy asks why the siren sounded late; the ferry crew offers an evasive answer. The pair walks toward the ferry, the mission reaches state 5, and **one mission and 100 field XP** are awarded before the completion message. Re-entry at state 5 should not replay the reward.

Still planned: a walking escort/follower, first battle, tether mechanic, animated ferry sailing, and dated ticket evidence. A docked SS Tidal sprite is now placed on the quay (26,37, sea elevation 1) while the rescue is pending; it disappears during boarding and remains hidden after state 5. The rescue warp now lands at (19,37) so the ship is on-screen during the scene. This is a prototype use of the original Emerald ship artwork.

### Additional emulator tests

1. Check in with sailor and find the boy using either the south stairs or elevated bridge.
2. Talk to him; verify the fade to the waterfront and both rescuees spawning.
3. Verify the movement, dialogue, sound and mission completion message without freezing.
4. Return to Mossdeep. Neither child nor Poochyena should remain at the landing.
5. Revisit waterfront; confirm no duplicate dialogue or extra +1 mission/+100 XP.
6. Speak to Commander Hale: record should show one mission and 100 XP, but promotion requires one Gym Badge.
7. Save/reload on Mossdeep and waterfront, confirming visibility, mission credit and rescue completion persist.
8. Test entry and scene playback in both mGBA and Delta.

The static guard checks that only the boarding scene adds mission/XP and that it sets state 5 before paying. It does not establish a compiled game or a completed emulator test.

## Delta playtest feedback: November 22, 2026

Delta screenshots confirmed working storm/weather and dialogue but revealed characters drawing *behind* the new elevated decks. The Route 110 imported walkway metatiles (969, 970, 974, 975) inherited layer type NORMAL (0): their upper art painted BG1, obscuring Ranger/player sprites. Their layer attribute now uses COVERED (1, encoded 0x1000), which moves deck artwork behind overworld sprites on BG2. Guardrails (968/971) remain solid, foreground-capable tiles.

The waterfront map now includes an existing 96x40 S.S. Tidal overworld ship sprite at (26,37), hidden permanently after state 5. The boarding destination is (19,37) to frame the boat, child, and crew together. Ferry disappears during a brief black-screen transition; no physical sailing animation or ferry interior has been added. Existing missions, XP and starter logic are unchanged.

**Test in a newly built ROM:** walk across both city bridges and the waterfront deck with your character fully visible above planks; confirm the ferry is visible before rescue completion, the child + Poochyena board without clipping/softlock, ship vanishes after boarding, +1 mission / +100 XP is awarded once, and saved state 5 never brings the ferry back. A fresh new game is required to see the pre-boarding ship if your existing save has already completed the rescue.
