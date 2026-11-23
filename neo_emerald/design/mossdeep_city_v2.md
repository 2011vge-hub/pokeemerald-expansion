# Mossdeep City 2.0 — Storm-Era Urban Redesign
**Status:** design/production brief, not implemented terrain. The existing prologue weather has been switched to `WEATHER_RAIN_THUNDERSTORM` on the working branch; needs GBA build/playtest. Claude's flood milestone 1 is local/unpushed and has not been integrated here as a binary terrain change.

## Core visual direction
Mossdeep is a **25-years-later coastal technology capital**, built upward after repeated high-water emergencies, not a vanilla small island with ocean painted over the sidewalks. It remains recognizable through its Space Center ridge, Gym, Center and shoreline contours, but now reads as a layered settlement. **Modern upper city / forgotten lower city** is the contrast. The first ten minutes should reveal this through movement and landmarks, not expositional dialogue.

## Source and screenshot grounding
- Current source: `data/maps/MossdeepCity/map.json`, 80x40 `LAYOUT_MOSSDEEP_CITY_STORM`; `LAYOUT_MOSSDEEP_CITY` remains the vanilla backup.
- Current visible anchors: Center by (28,16) with spawn (28,17); sailor (38,12), Gym (38,9), Mart (37,18), Space Center (64,15).
- Claude's flood milestone 1 screenshots show most western/southern low coast replaced with ocean and the lower southeast shelf transformed into shallow floodwater, while the island's original one-story houses remain nearly unchanged.
- Claude's *unmerged* child/Poochyena placements: child (33,30), Poochyena (32,30); maintain these, or preserve reachable equivalent landing when revising architecture.
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
Claude's two-commit `mossdeep-flood-m1.patch` was pasted into chat, but the **actual binary patch file was not attached** here. The `map.bin` change is a Git binary delta and cannot be faithfully reconstructed by treating its human-readable diff as normal text. To integrate exactly Claude's terrain, provide the original `.patch` file or push Claude's branch; don't hand-copy or regenerate a visually similar binary without checking for differences and preserving collision data.

Use the current shared branch, rebase Claude's patch onto the latest commit and validate the one-line weather change doesn't conflict. Prefer a new `neo-emerald/mossdeep-city-v2` branch before major map remodeling.
