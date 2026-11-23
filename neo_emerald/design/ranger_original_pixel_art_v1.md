# Neo Emerald — Orange Ranger Player Art (original sprite milestone v1)

**Source:** `neo-emerald/player-ranger-sprite-v1`, based on Chapter 2 PR #5. User supplied reference images of male/female orange-capped Rangers in dark field uniforms.

## Implemented in the game source
Four NEW original indexed PNG sprites (not Brendan/May art, not Camper/Picnicker recolors), 144×32 pixels, 9 frames each:

- `graphics/object_events/pics/people/brendan/walking.png`
- `graphics/object_events/pics/people/brendan/running.png`
- `graphics/object_events/pics/people/may/walking.png`
- `graphics/object_events/pics/people/may/running.png`

Both use a deliberately shared 16-color GBA palette. They draw front, back, side and stepping poses. Each frame has an orange Ranger cap with insignia, orange vest, gloves, dark field attire, reinforced boots, and a stylized hip Ranger Styler. Female differs through dark-blue ponytail and shorter leg garments. The build no longer replaces these sprites with native Camper/Picnicker artwork and it validates all four original palettes before compiling.

## Still incomplete / needs playtest

- Cycling, surfing, fishing, field move, watering, decorating, underwater, reflection, player battle back and trainer portraits remain provisional re-colored player geometry. Do not call full animation parity complete.
- Animated Styler usage, polished hair, equipment cord, dedicated blue-/purple-haired Vern/Nessa and redesigned overworld overwrites of gender graphics still need a separate art pass.
- Test in-game walk/run directions against trainer portraits and trainer-class references to confirm scale, depth, collisions, outfit continuity and Delta compatibility. Compile success alone does not verify frames animate correctly.
- Keep source architecture and `master` unchanged. Use a fresh save for gameplay QA. 
