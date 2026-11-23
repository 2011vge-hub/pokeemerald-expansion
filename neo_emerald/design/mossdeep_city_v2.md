# Mossdeep City 2.0 — Storm-Era Urban Redesign
**Status:** City v3 enhancements in progress on `neo-emerald/mossdeep-city-v3-streets`. The annex has been removed and the rescue bridge has a southern walkable entrance. Earlier v2 features remain. Source and geometry checked; ROM build/emulator playtest still pending. Thunderstorm configured, not playtested.

## V3 terrain refinements (source level)

- **Bridge third entrance:** the south rail at **(43,30)** is now a walkable deck, joining the deck at (43,29) to the lower flooded-terrace approach at (43,31). Both sides retain their collision railings; the new side gate stays usable if the original south stairs become blocked.
- **Decorative Space Center annex removed:** restore the 5×7 area **x46–50, y10–16** directly from untouched vanilla terrain. It had **no interior, warp, events, or unique gameplay**, so the original main Space Center retains all working content. The two formerly sandy forecourt squares remain grass until the streetscape pass.
- Original Space Center and all key warp approaches, ferry connection, and child/Poochyena remain unchanged. 0 open-sea tiles reachable by source-level path check.
- Historical annex-creation scripts should **not** be rerun on v3.

## Implemented so far (v2)

| Change | Where | State |
|---|---|---|
| Space Center weather-observatory annex: 5x7 building assembled from the existing Space Center metatiles (dish roof, glass/steel wall, pillared base) | Ridge terrace west of the Space Center, top-left (46,10), footprint x 46-50, y 10-16 | Implemented as a **facade only** (no door, warp or interior). 35 tiles changed, collision copied from the source building, elevation kept at the terrace's 7 |
| Annex roof and forecourt polish: roof entries 966/967 without helipad marks at (46,10)/(46,11), plain wall at x47,y13–16, sand stub to grass at (48,17)/(49,17) | Same annex footprint, 8 tiles updated | Implemented in source; no new door, warp, or interior |
| Market-to-child bridge using Route 110 walkway art (metatiles 968–971) | x35–43, y28–30 | Source implemented; landing reachable even when south stairs are blocked |
| Ranger HQ civic tower, 3×7; sign, no usable interior | x32–34, y13–19 | Source implemented; avoids blocking main street |
| House 4 raised to three floors with existing door/warp retained | x17–20, y12–16 | Source implemented |
| Three-story evacuated apartment facade with sign, no usable interior | x46–49, y25–29 | Source implemented |
| East walkway leading from southeastern shelf to city boundary | row35, x64–79 | Source implemented and reachable |
| New linked waterfront district with quay and ferry terminal facade | 32×40 map `MossdeepCity_Waterfront` | Source implemented; no ferry, boat boarding, or NPCs yet |

Verified with `neo_emerald/tools/map/mossdeep_v2_upper.py` (re-applies only after checking the site and every route) and `mossdeep_paths.py`: spawn still reaches the Center, sailor, Mart, Gym, Space Center, child landing, Steven's house, House 2, all three ridge NPCs and the flooded shelf; 0 reachable sea tiles; `LAYOUT_MOSSDEEP_CITY` untouched.

Tileset plan and remaining tile budget: [mossdeep_tileset_v2.md](mossdeep_tileset_v2.md). Constraint found: a map can only use General + one secondary tileset (Mossdeep). Larger *modern* houses, Ranger HQ signage, walkways and a ferry terminal need new metatiles (tileset pass); with existing art only Space Center-style and vanilla-house pieces are available.

## Core visual direction
Mossdeep is a **25-years-later coastal technology capital**, built upward after repeated high-water emergencies, not a vanilla small island with ocean painted over the sidewalks. It remains recognizable through its Space Center ridge, Gym, Center and shoreline contours, but now reads as a layered settlement. **Modern upper city / forgotten lower city** is the contrast. The first ten minutes should reveal this through movement and landmarks, not expositional dialogue.

## Source and screenshot grounding
- Current source: `data/maps/MossdeepCity/map.json`, 80x40 `LAYOUT_MOSSDEEP_CITY_STORM`; `LAYOUT_MOSSDEEP_CITY` remains the vanilla backup.
- Current visible anchors: Center by (28,16) with spawn (28,17); sailor (38,12), Gym (38,9), Mart (37,18), Space Center (64,15).
- Claude's flood milestone 1 screenshots show most western/southern low coast replaced with ocean and the lower southeast shelf transformed into shallow floodwater, while the island's original one-story houses remain nearly unchanged.
- Child (33,30) and Poochyena (32,30) on the south landing (integrated); keep them, or a reachable equivalent landing.
- Do not mistake PNG concepts or screenshots for editable map tiles. Final in-game geometry is the Porymap layout + metatile/graphics assets.

## Weather
- **During the prologue:** real GBA `WEATHER_RAIN_THUNDERSTORM` visual overlay and sound, with intermittent lightning; not rain baked into static tiles.
- **After the rescue:** design a lighter state (rain/overcast), eventually controlled by story vars in a safe transition script; do not attempt dynamic swap until player positions and load/save paths are tested.
- Keep the floodwater as physical geometry regardless of weather. Changing sky effects must not magically reverse the years-long coastal loss.

## Proposed districts (use more than one linked map when the starter slice outgrows 80x40)

### 1. Ranger Commons / elevated upper street
Around the current Center and Mart. Replace some tiny houses with modern brick/glass 2–3-story buildings; create an emergency triage tent, Ranger signage, powered street lamps, rooftop cable lines, barriers and an upper pedestrian bridge. During the prologue, evacuees move through here. Make the player begin within two seconds of visible urgency.

### 2. Space Center Ridge / new technology campus
Preserve the rocket and iconic mountain cliff footprint. Expand into the visible **space-and-weather observatory** with communications arrays, solar/wind support, satellite dishes, active emergency weather radar and Ranger dispatch relay. A later chapter can explore interior labs and archives. The ridge must feel larger, not just more decorated.

### 3. Gym terrace / upper ferry concourse
Around the sailor and Gym. Build a physically visible ferry operation: queue, screening desk, departure board, emergency floodlights, railing, and access stairs. The evacuation boat can be on a *separate dock map* linked by stairs or a boarding warp, so we don't sacrifice the upper-city walking routes.

### 4. Market / old town
Around the current Mart. Split into upper dry shops and lower submerged ground floors, with raised walkways, shop signs and the neighbor's balcony. The player's first rescue puzzle routes through the surviving upper stories; reserve one healing checkpoint and a clearly reversible escape path.

### 5. South landing / lost neighborhood
Keep the child and Poochyena on the last dry ledge beneath the south stairs. Create a scenic view of a flooded residential block, trees half-submerged, storm debris and broken electrical infrastructure. Build an **actual traversable rescue path** before cutscene embellishments.

### 6. Harbor / ferry escape
A separate waterfront map with boat sprite or scripted tiles, boarding ramp and evacuees. After boarding, the player hears the delayed siren; give a dated ferry receipt as a tangible mystery clue. Build this after the child path and recovery tests.

## Visual priorities by implementation phase
1. **Low-risk decorative pass on storm copy:** replace several one-story homes with taller facades (when compatible tiles exist), add modern street furniture, emergency signage, warning barricades and weathered flooded edges. Do not move doors or warps yet.
2. **Tileset pass:** custom Mossdeep secondary tileset for rooftop/bridge railings, modern neon/space research signage, reinforced piers, shuttered submerged storefronts and broken stairs. Respect per-tileset GBA metatile capacity, 4bpp palettes and animation constraints.
3. **Navigation pass:** new dry second-floor walkway; map elevations and collision verified; ensure Center, sailor, Mart, Gym, Space Center, child and any replacement paths are reachable from a fresh save.
4. **Ferry & rescue:** add terminal maps and mission state; validate losing a battle, saving/reloading, returning from interiors and going back through all exits.
5. **Post-prologue:** alternate repaired/rainy state and a way to revisit the flooded market with upgraded Ranger equipment; no silent save migrations.

## Non-negotiable playtest acceptance
- From (28,17) with Poochyena, Spheal **or Shroomish**, check in at the sailor and reach the child/Poochyena. No required hidden moves or Surf.
- No player walkable path onto open sea or into a softlock; transitions from elevation-0 stairs are particularly dangerous.
- Every permanent connection/warp and key story NPC exists on nonblocked reachable tiles.
- Rain and thunder visually animate in mGBA and Delta without crashing, freezing input or endlessly looping a cutscene.
- Original `LAYOUT_MOSSDEEP_CITY` data remain untouched, and **master remains unchanged**.
- The branch builds a `.gba` before claiming any map work 'playable.'

## Handoff to collaborator
Flood milestone 1 was integrated from an exactly reproduced binary patch; the shared branch's `MossdeepCity_Storm/map.bin` matches Claude's byte-for-byte. v2 work continues on `neo-emerald/mossdeep-city-v2`, one verified terrain change per commit. Never merge to master.

## Weather and map transition test (not yet completed)

Mossdeep and the connected waterfront are configured with `WEATHER_RAIN_THUNDERSTORM`. The engine provides this weather type, but **no compiled .gba has verified it** on this branch.

1. Start **New Game** in mGBA, finish Birch's briefing and spawn in Mossdeep.
2. Check visible falling rain, occasional lightning and thunder, player input, and menu/message interactions during flashes.
3. Traverse the east walkway to the ferry waterfront and back. Confirm the weather persists and camera/map connections do not glitch.
4. Repeat in Delta on iPhone, save/reload, test blackout/respawn and all three Ranger partners.
5. Test approaching the child through the new bridge while treating southern stairs as blocked.

## Source-integrity notes

The first six milestone map and metatile binaries were reconstructed and their Git blob IDs matched Claude's patch targets exactly, including the 32×40 waterfront. The Mossdeep `tiles.png` bridge-art import is **pixel-equivalent** to the script's nine-tile import, but was re-encoded into a valid indexed PNG and therefore has a different Git blob ID than Claude's original patch. The current checker uses map collision/elevation approximations: it does not replace in-emulator QA.

The secondary Mossdeep tileset now contains **464/512 metatiles**, leaving **48 free** (454 vanilla + 10 Neo). The previously supplied 466/46 count was a two-metatile arithmetic error. Nine formerly blank 8×8 art slots are now occupied by imported walkway art; slots 496–511 are reserved for runtime door animations.
