# Mossdeep opening — terrain and story implementation plan (Neo Emerald)

Status: **design specification, NOT yet an edited terrain map or verified ROM.**
Source anchor: `data/maps/MossdeepCity/map.json`; layout `data/layouts/MossdeepCity/map.bin` remains vanilla. The existing layout has 3,200 metatiles (80x40 at two bytes each). Ground walkability and collision **have not been verified** for proposed new geometry. All locations below marked **planned** are subject to map-editor validation.

## Creative objective

Make the first ten minutes of Neo Emerald unmistakably unlike Emerald: begin with Birch's prerecorded Ranger orientation, deploy at storm-threatened Mossdeep, choose one of three Ranger rescue partners, hear a distress call, learn to read the terrain, and save a stranded child and frightened Poochyena before the ferry leaves. End with a question: why was the evacuation siren late?

The player is a **local rookie Ranger** experiencing the first active rescue. Don't make them a silent spectator to an otherwise unstoppable scripted disaster. Early exploration should reveal the waterline, escape routes and distressed people. Flooding does not undo the rescue; lower Mossdeep remains damaged after the prologue.

## Existing map anchors — confirmed source coordinates

| Anchor | Map x,y | Role in redesign |
|---|---|---|
| Initial spawn | 28,17 | Beside Pokémon Center. New Game currently warps here |
| Pokémon Center door | 28,16 | Dry emergency triage / safe respawn (respawn fix on Claude's local branch; not yet integrated here) |
| Gym door | 38,9 | Upper-square landmark |
| Sailor | 38,12 | Check-in for ferry and missing passenger |
| Poké Mart door | 37,18 | Market terrace and search area entrance |
| Space Center door | 64,15 | High ground, visible emergency lights / communication relay |
| Existing youngster | 26,21 | Potential west-stair witness; not yet reassigned |
| Current shoreline district | primarily southern/lower part of layout | Planned waterline and debris; must inspect metatiles |

Note: these are **existing logical coordinates**, not certification that new docks, bridges, rails, or stairs already exist. The shipped Mossdeep layout has no dedicated rescue ferry dock or navigable flooded-market balconies.

## Planned terrain composition

### A — Ridge / emergency headquarters
Dry, elevated neighborhood around the Space Center. Tower beacon and temporary emergency command station. Safe vantage onto both flooded lower streets and the upper ferry terminal. Dispatch signal gets weaker as player descends.

### B — Upper terminal / Gym steps
Near the Gym and sailor. Evacuee queue, departure board and blocked gangway. This area teaches the player that the *ordinary* route to the terminal cannot be used. Anchor the mission objective here and make the remaining ferry physically visible. Two seats remain: the missing child and their family's Poochyena.

### C — Market terrace
Near the current Mart. Floodwater has reached the ground-floor shutters, but the storefront's *second floor* remains navigable. Add a little optional exploration: a shopkeeper can describe an old balcony shortcut; another citizen explains how to trace wet pawprints. Avoid making the first route an unmarked maze.

### D — Collapsed south access stairs
New geometry required. The player hears a metallic crack and can inspect the broken handrail. The damaged stairs explain why dispatch says to hold position; the player locates a parallel route on the market side. Crossing a changing waterline should never strand the player or their only partner.

### E — Balcony / tram platform / rescue ferry
New map/interior space required. A quick level-appropriate wild encounter blocks access to the child; Poochyena is scared, not an enemy. The player uses a safety tether, traverses the shopkeeper's apartment and upper balcony, and boards the remaining ferry via a temporary tram platform. The Ranger's reel and transmitter are damaged by saltwater; future upgrades have narrative justification.

## Prologue implementation beats

| Stage | Player action | Story event | Current status |
|---|---|---|---|
| 0 | Finish Birch's recorded welcome | New Ranger assigned | Intro text present; full opening untested |
| 1 | Spawn at Center, receive dispatch | Rising water; head count | Script present |
| 2 | Choose Poochyena / Spheal / Shroomish | Partner registered at level 5 | Choice wired to Mossdeep on phase-1-ranger-starters; untested |
| 3 | Speak to sailor near Gym | Two tickets left, child ran toward market | Source script present |
| 4 | Investigate market terrace | Wet pawprints; first warnings of blocked lower steps | Dialogue support planned first; geometry pending |
| 5 | Reach child and their Poochyena | Small first battle, then tether rescue | Not implemented |
| 6 | Cross upper balcony | Reel breaks, radio loses transmission | Not implemented |
| 7 | Ferry departs | Siren heard **after** water arrived; dated ticket/receipt | Not implemented |
| 8 | Arrive Rustboro coast | Rangers' testimony conflicts with dispatch log | Not implemented |

**Progress-state design:** `VAR_NEO_FERRY_DISPATCH` is currently used with values 1=new call, 2=select partner/report, 3=checked in. Extend only with explicit migration and recovery handling; never use global trainer flags as story gates. Do not add child-rescue completion state before a map and script can deliver that outcome.

## Terrain production procedure

1. Capture the current Mossdeep metatile/collision map in Porymap or an equivalent editor; **verify** pathfinding between spawn (28,17), sailor (38,12), and Mart (37,18).
2. Duplicate the layout into a prologue-specific Mossdeep variant, rather than destructively replacing vanilla geometry. Preserve the Space Center silhouette and recognizable landmarks.
3. Block and decorate **lower** access with broken stairs, cracked sidewalks and intermittent water tiles; build a walkable market terrace and controlled balcony bridge on **separate explicit elevations**.
4. Add a ferry terminal interior/exterior as separate maps with entry/exit warps. Keep a deterministic last-safe-position on both sides of every water transition.
5. Author a small flood state machine. Favor controlled scene transitions and map-layout changes over changing collision tiles beneath the player; update the waterline only when player position is known safe.
6. Playtest all three starters, first battle, movement, ferry departure, blackout/respawn, save/reload and walking back through exits before extending the next chapter.

## Opening dialogue tone

Birch's pre-recording should feel reassuring, optimistic, and dated. Dispatch should be clipped and operational. The sailor should sound frightened but focused. The shopkeeper should be practical, helping without being impressed by the player's Ranger status.

When the ferry pulls away:
- Child: "Why did the siren start after the water came?"
- An older crew member calls it an equipment fault. Their explanation feels rehearsed.
- The player's printed ferry receipt has a timestamp earlier than the *official* evacuation alert.

Don't explain Team Null, May's decisions or Birch's disappearance too early. Keep the mystery in a tangible, revisitable object (receipt), not just in a monologue.

## Design conflicts to reconcile

- Latest `CAMPAIGN_BLUEPRINT.md` adopts **fixed, authored Gym chapter order**; `design/story_pillars.md` still suggests open-order Gyms. Treat the newer campaign blueprint as current until explicitly changed.
- Claude reported a local, unpushed Mossdeep **respawn fix** on `neo-emerald/phase-1-opening`; this branch started from `phase-1-grimyena`, so its savepoint fix is **not included**.
- Starter choice is currently hooked to the existing Birch bag screen for stability; eventually redesign that UI as a Ranger partner assignment interface. Keep the starter source table centralized to avoid mismatches.
- Poochyena -> Mightyena -> Grimyena; Spheal -> Sealeo -> Walrein; Shroomish -> Breloom -> **unnamed future third stage**. New third-stage evolution is a design request only. Mega Breloom remains a separate project.
