# Neo Emerald — Male/Female Ranger sprite pass v1

Development build: `neo_emerald/tools/generate_ranger_sprites.py` runs before ROM compilation and generates 16-color indexed art, the corresponding object-event and reflection palettes, and battle backs on the GitHub runner.

**Male:** dark hair, deep navy pants/field boots, teal field jacket, orange-gold rescue badge.
**Female:** auburn hair with ponytail detail, matched navy/teal utility uniform and Ranger identifier.
The original engine player sprite IDs, animation table addresses, and gender selection remain unchanged. All ten field-action sheets, including running, fishing, surf, watering and both bicycles, receive the new palette; walking/running have additional pixel-level uniform details.

**Important:** This is a first-pass functional sprite implementation, not the final fully custom hand-drawn animation sheet. It uses Brendan/May pose frames to guarantee complete animation coverage. A dedicated original silhouette and complete pixel-art polish remain future work.

### Technical
- Use Pillow (`python3-pil` on Ubuntu).
- GBA 4bpp images retain their indexed color format and 16-color limit.
- `graphics/object_events/palettes/{brendan,may}.pal` and reflection palettes regenerate with the art; corresponding battle backs and trainer palettes are updated.
- The generator modifies image files only in the CI build workspace. It is deterministic and never commits altered upstream art to the branch.
- Preview artifact: `neo_emerald/out/NeoEmerald_RangerSpritePreview.png`.

### QA
- Start a NEW GAME separately as each gender. Verify uniform, movement, face directions and running.
- Check battle back and cards, then later cycling/surfing/fishing and reflections.
- Review for source pose remnants, transparent pixel artifacts and mismatched art; adjust next art pass based on playtest.
