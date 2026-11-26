# Professor Roxanne — approved 25-years-later design

User approved character sheet on 2026-11-26. Native-size derivative replacements installed directly in existing Roxanne paths. University 4F and Rustboro Gym both reference OBJ_EVENT_GFX_ROXANNE. Battle front uses gTrainerFrontPic_LeaderRoxanne and its embedded palette.

- Overworld: 48×32 indexed PNG, three 16×32 directional frames (down/up/left, right mirrored by engine); original stationary frame table preserved. Shared NPC_1 palette unchanged; limited colors approximate concept. SHA-256 a68d159e46a82802f431765d18dab6cc97612631252de45d0a39226cd2d8f5be.
- Trainer front: 64×64 indexed PNG, 16 colors, transparency index 0. SHA-256 0e5e38e840e16f4276da46ca887011655847e463b6b2b83f53190bf5721680e5.
- Dialogue portrait engine, walking animation, Gym roster and map changes are outside this commit. Runtime verification pending. Preserve player Ranger artwork.
