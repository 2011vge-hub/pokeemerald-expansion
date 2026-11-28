# C5 dispatch gate delta v1 — 2026-11-28
Narrative only. Source inspected at 6c5b4d19643ba48d42105b1d422fd80d8258217d; parent storyboard f0640f1160faee72cdccbcc476310a802938b272. Supplements, never replaces, C4–5 milestone v2 and continuity_2026_11_26.md; current release override wins. Stop at Badge 2.

## Verified source delta
- Shipyard 1F Dock already directs Ranger upstairs after FLAG_NEO_C4_SURVEY. Do not duplicate briefing.
- Shipyard 2F has NeoSlateport_Stern and NeoSlateport_Hale. Stern sets FLAG_NEO_C4_STERN_REVIEWED; Hale sets FLAG_NEO_C4_REPORTED and credits mission/XP/training once. Hale's repeat orders end "Await desert route clearance." No clearance grant in this script.
- 1F warp index 2 at (3,1) leads to 2F index 0; reciprocal 2F (3,1) returns to 1F index 2. Stern at (8,4), Hale (10,7), elevation 3; collision not verified.
- Route111 map actually registers sandstorm restriction triggers (despite @ Unused comments): southern row y61 x11–14 and western diagonal (12,44),(13,43),(14,42),(16,40),(17,39),(18,38), all elevation 3. Shared handler checks ITEM_GO_GOGGLES. VAR_TEMP_3 is transient; do not use as permanent clearance.
- Route111 connects south to Mauville and west to Routes112/113; no Relicrest connection or registered map found. No coordinate allocation proposed as fact.
- src/data/items.h contains ITEM_TM_ANCIENT_POWER entry; actual move mapping and obtainability still need verification. Do not substitute Rock Tomb.
- Nox approved art README at current head explicitly rejects earlier six blocky concept sheets and reserves her role/party/placement. Do not use Nox as Rill or Sable, reveal Null, or treat standing reference as runtime art.

## Missing scene C5.01–03: dispatch to corridor
Hale (after existing orders): "Your assignment is filed.\nHead north through MAUVILLE.\pThe survey marshal will show you\nthe safe route to RELICREST.$"
Mauville transit contact: "CAYTON's crew marked a safe path.\nFollow ROUTE 111 north.\pThe GYM is not part of your\nassignment today.$"
Marshal before Stern review: "The survey route is restricted.\nSpeak to CAPT. STERN in SLATEPORT.$"
Marshal after Stern but before Hale: "We need HALE's dispatch first.\nHe's upstairs at the shipyard.$"
Marshal eligible: "Your dispatch checks out.\nStay between the survey markers.\pReady to enter the safe route?$"
No: "I'll be here when you're ready.$"
Yes: "You're cleared for RELICREST.\nKeep to the marked passage.$"
Repeat: "Your clearance is still valid.\nFollow the markers either way.$"
Outside corridor: "That area isn't surveyed.\nReturn to the marked path.$"
Nessa: "Let's get those workers out first.\nThe badge can wait.$"
Vern: "The route is marked. Let's keep\nto the survey team's path.$"

## State and map contract
Eligibility = C4 survey AND Stern reviewed AND Hale reported. Do not infer dispatch from legacy C4_REPORTED alone. Proposed C5_DESERT_AUTHORIZED persistent milestone set only after eligible marshal confirmation; no numeric allocation. Old credited saves complete missing Stern review then receive orders without duplicate credit. Reentry after loss/blackout uses same clearance. Existing Go-Goggles behavior remains intact. A scoped physical corridor is required: do not simply bypass shared handler globally (VAR_TEMP_3 can suppress subsequent triggers). Environment team must provide walkable marked route and boundaries before coordinate assignment. Prefer reciprocal physical connection to proposed MAP_RELICREST_CITY; proposed survey office, excavation, restoration lab and Gym warps must be assigned by development after registry audit. Keep existing Route111 warp indices unchanged. No forced teleport or fabricated badge.

## C5.04–08 recovery dialogue delta
Cayton before rescue: "Check the surface gauge first.\nThen find my crew in the dig.$"
Worker safe, deeper reading missing: "We're clear of the collapse.\nCopy the lower gauge reading.$"
Sable encounter only after safe crew; explicit interaction, retry after defeat; no new trainer allocation without capacity audit. Reading remains available after victory and retreat.
Cayton after report: "The dig is safe again.\nThe fossil GYM can reopen.$"
Gym reception before report: "The GYM is closed for safety.\nReport to PROFESSOR CAYTON.$"
After loss: "Take your time to prepare.\nYour survey work is complete.$"
After badge with TM delivery pending: "Your RELIC BADGE is yours.\nMake room for your TM reward.$"
After both rewards: "You've earned your second badge.\nRest here before your next task.$"
Initial party locked: Shieldon/Amaura/Cranidos/Kabutops/Dracovish/Tyrunt Lv21–26; Relic Badge, Ancient Power TM. No Mega in first encounter. Badge and successful item delivery tracked separately; no repeat battle or reward farming. Preserve legacy trainer identifier if necessary.

## Acceptance / department handoff
Development: verify both shipyard stair directions and NPC adjacency, report idempotency, legacy save migration, eligibility truth table (none, survey only, Stern only with survey, all three), marshal decline/retry, all registered desert entry triggers, corridor exits and return after blackout; no Badge4/5 or later cargo/grid mission activation. Environment: marked safe corridor, physical city connection, signed office/dig/Gym, collision and elevation audit. Character art: use approved concepts only; no Nox in early public scenes. Field Log: replace "await clearance" with marshal destination only when route exists; after clearance name Relicrest survey office; after badge stop release milestone, allow revisits. Optional fossil identification remains optional and does not gate rescue. Retain C1–3 regression checks, source validation and compilation; no comprehensive playtest claimed here. No major lore decision required.
