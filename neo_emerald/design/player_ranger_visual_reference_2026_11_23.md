# Ranger player sprite direction — November 23, 2026

**Reference supplied by the user:** Two images depict official-style orange / dark-navy Pokémon Ranger outfits. One image compares red-uniform Rangers and orange-uniform Rangers; the other shows a male and female Ranger in orange field equipment. Treat the **orange-and-black pair** as the preferred player outfit reference, with red as an optional higher-rank palette (not yet approved as a rank mechanic).

## Non-negotiable silhouette and outfit
- Male: orange field cap with dark emblem, orange vest/shoulder jacket, dark fitted top and navy cargo trousers, orange reinforced boots, black gloves, and hip-mounted capture stylus/coiled cord.
- Female: corresponding orange field cap, orange field vest over dark top, navy/dark shorts or trousers as the sprite resolution permits, tall orange boots, black gloves, and visible rescue/capture equipment.
- Recognizable **Ranger class**, never an unmodified Brendan or May costume. Pixel art should remain native GBA scale. Any hair recolor must preserve a clear cap, head silhouette and recognizable dark/blue hair.
- Apply coherent visual identity across the male/female overworld 9-frame walk, run, bike, surf, fishing, field moves, trainer battle backs, title/profile art, and any reflection/shadow palettes. Also create rival Nessa (purple hair) and Vern (blue hair) as distinct Ranger variants.
- **The supplied illustrations cannot be imported directly into a GBA ROM**; they are compositional and palette references for dedicated indexed 16-color, 16x32-pixel frame sheets.

## Implementation state and next QA
The current branch modifies `neo_emerald/tools/generate_ranger_sprites.py` to use **native Camper/Picnicker overworld geometry** for walking and running, recolored toward orange-and-dark uniform. This is a *prototype only*: base geometry has no custom detailed Ranger stylus, the cap emblem is not drawn, other animation modes still derive from older player art, and NPC gender/portrait assets are not final. Do not claim a full Ranger visual overhaul or that the new sprite passes Delta inspection.

Next: source/create original 16x32 Ranger walk/run sprites with front/back/side frames; add palette-matched run and gear animations; update all activity and trainer sprites; export before/after transparent pixel previews; do male/female gameplay tests. Keep all changes on development branches and preserve the existing save format.
