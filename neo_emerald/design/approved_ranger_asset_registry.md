# Approved refined trainer portraits — 2026-11-26
User approved the new hatless full-body portrait reference `hatless_pixel_ranger_duo.png` (SHA-256 8526ae3090a42e815b535e0f8d4172b6b5ce5b2754878c3fb282b589e9f21c96). The derived 64x64, 16-entry indexed PNGs are stored with exact hashes and bytes in `neo_emerald/design/approved_hatless_ranger_portraits.json` on `neo-emerald/hatless-ranger-integration`, commit `c572cf19d87b9b4b0b8ae18a2e56e2f88c70f3b1`. Supersedes earlier front portrait candidates; preserve approved hatless overworld sprites separately. Runtime front/back palette reconciliation, battle-back artwork and emulator verification remain pending. Do not regenerate the visual identity.

---

# Superseding visual decision — 2026-11-26
The user explicitly approved the revised hatless male/female Ranger design with compact Brendan/May-style legs, navy hair, navy/orange uniforms and black boots. This supersedes the helmeted Option A visual approval below. Do NOT restore helmeted art or its pending walking sheet. The new 144x32 indexed walking candidates and installer are on neo-emerald/hatless-ranger-integration, build integration commit 7d8b5c9d184b1bea8b33e7f355058abb8f363585. See neo_emerald/tools/install_hatless_rangers.py for exact embedded PNG hashes. The runtime conversion, walking steps and temporary running reuse have not been tested in an emulator; other actions, naming portraits, rivals and battle backs remain unfinished. Reconcile with current gameplay branches before release.

---

# Canonical Ranger asset registry — 2026-11-25
Build 21 rejected. This registry locks approved stationary Option A only; no runtime installation. Source archive NeoEmerald-Ranger-approval.zip (library libfile_b46a175b51f881918cf78ec06afa5435). Locally authored pixel grids, orange shoulder yoke, black boots, navy fabric, wrist Styler. Native uniform references graphics/trainers/front_pics/pokemon_ranger_m.png and pokemon_ranger_f.png at c643dd8edf9b40bc8a2a8322be3fd48c611aa4c6; these are 64x64 battle portraits, not overworld sheets. Player geometry reference graphics/object_events/pics/people/{brendan,may}/walking.png at 22b2b010b8c11daf36262557d7de08fa65254672.
Approved archive paths and SHA256:
- A/female/north.png 5b2d746e0c98682cd2e61b43396c6a7ed7b3bacc345c2ad411ce25f0d93a0ca9
- A/female/south.png 464ba31e63217427a00273eef5fdd7142365d1c63c1516f60e1a446c61ed3c4f
- A/female/west.png 28222634dd9501f722eb8e6cf9444c52a5114e48d250b77a8cd31e282cd20b92
- A/male/north.png d5fcd84036c1d979438b28981ae80c35328761c4a58e41d45607045cb7103f27
- A/male/south.png 13b882ce4987f6c6df5cfedb8c71bdda292a00d7a2c5afeb363b40f3bce1bf22
- A/male/west.png f09abb413b32d9c346ca1119da03ea8d1ba7841b92fe03e70f3e4416e92fd9ea
16x32 indexed frames, 4-bit PNG, 16 palette entries, transparent index 0, baseline y30. East mirrors west. Palette RGB5: [(0,31,0),(3,3,5),(6,7,10),(9,11,16),(6,8,13),(10,13,18),(5,6,8),(19,8,6),(26,12,7),(31,17,9),(31,25,8),(26,16,12),(31,26,23),(17,10,9),(18,23,26),(28,30,29)].
Pending approval: NeoEmerald-Ranger-Walk-A.zip (libfile_db15532dd9d88191acc4876b87614614), 144x32 nine-frame sheets, idle S/N/W then step pairs S/N/W. female-walking.png SHA256 ff1889b647684553b824bba554c6e09a2c703dc81ac19880e4f5b625c92fc9a1; male-walking.png SHA256 f36bd9a5ace57e93290bf0474e79c23e6f693a704afd3473a19edd54aad9a170. Do not integrate without explicit approval. Running, cycling, surfing, fishing, field, naming, battle backs and rivals remain unapproved. Never substitute Build 21 sprites or regenerate approved pixels. Before installation verify exact approved source hashes, runtime palette/reflection mapping, frame tables, generator preservation and emulator screenshots. Registry is not proof of compiled assets. No ROM release until regression gates pass.
