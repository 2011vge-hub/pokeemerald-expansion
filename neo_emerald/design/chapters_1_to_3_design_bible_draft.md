> Historical working draft. Newer decisions in current_canon_2026_11_23.md supersede any conflicts.

# POKÉMON: NEO EMERALD
## Chapters 1–3: Opening Campaign — Design and Implementation Bible
**Design status:** Chapter 1 existing story preserved; Chapter 2 detailed specification; Chapter 3 proposed expansion, ready for review and implementation.
**Project type:** Pokémon Emerald (GBA) ROM hack / decompilation-based game. Setting: Hoenn, 25 years after Emerald/ORAS.
**Important:** This is a production design packet, NOT a patched ROM or proof of implemented scripts. Where an exact map coordinate or compiled engine constant is absent, symbolic IDs are used and must be resolved in the source tree.

---

## A. Canonical rules / continuity guardrails

1. **Chapter 1 Mossdeep rescue stays intact.** Do not overwrite the established Birch recording, Ari/June orientation, three Ranger starters, storm/flood, child-and-Poochyena rescue, collapsing stairs, compromised rescue rig, upper-floor shop escape, late-siren clue, or Hale debrief.
2. **Ranger starter selection:** Poochyena (Lv. 5, Fire Fang), Spheal (Lv. 5, Ice Beam), Shroomish (Lv. 5, Giga Drain). Lv. 5 is the starting level only. All grow normally through battle EXP and evolution. Existing progression and move compatibility must be verified in code.
3. **Opposite-gender rival:** male player -> **Nessa**; female player -> **Vern**. Both are Commander Hale's child. Same ambitions, dialogue, mission flags, teams, and narrative. Different name, battle/overworld graphics, and hair palette only (Vern blue; Nessa purple). Rival receives the advantageous unchosen starter: player Poochyena -> Spheal; player Spheal -> Shroomish; player Shroomish -> Poochyena. Advantage is chiefly strategic/long-term, not a promise of a type advantage in every move matchup.
4. **Enemy trainer names:** all ordinary grunts display **Neo Magma Grunt**, **Neo Aqua Grunt**, or **Team Null Grunt**. No personal names for grunts. Senior officers/leaders are distinct trainer classes if introduced later.
5. **Neo uniforms:** retain canonical Gen 3 Magma/Aqua base sprite silhouettes. Neo Magma uniform BLACK, M emblem RED. Neo Aqua uniform WHITE, A emblem BLUE. Clone sprite + palette assets rather than altering global/shared originals.
6. **Villain targets:** Neo Magma and Neo Aqua each pursue **Volcanion** for different reasons. Their leaders are descended from the original Archie/Maxie leadership (their children). Team Null has a separate Arceus objective. Do not reveal Team Null's full intent during Chapters 1–3.
7. **Weather trio:** Groudon, Kyogre, Rayquaza have an established late-game Elite Four/Champion roster role; do not contradict with a Chapter 1–3 capture event.
8. **Gyms:** Rustboro/Roxanne remains open early and is STEEL themed. Other low-tier Gyms may be accessed without forcing a strict fixed badge order. Gym dialogue and rosters respond to progress; Mossdeep's Gym remains progression-locked. Earliest Mossdeep prompt remains **“Now's not the time. I should check with the sailor nearby.”** before the sailor checkpoint, then gains story-sensitive variants.
9. **Ranger gear:** tools replace HM obstacles. Badges determine eligibility for Ranger promotion/equipment, but completing Ranger missions advances Ranger-specific standing. Upgrades require reporting to headquarters and are not silently granted just because a badge is earned.
10. **Ranger EXP vs Pokémon EXP:** track separately. Initial Mossdeep rescue already has a mission completion and Ranger XP (+100 in existing design). Ranger mission Pokémon EXP starts at +250 for Rank 1, +300 at Rank 2, then +50 per further rank (provisional Rank 3 350, Rank 4 400, Rank 5 450). Selected major story missions can give +1,000, but never apply all awards indiscriminately. Decide distribution in code (recommend bonded Ranger partner only, no fainted/released partner problems) and test balance.
11. **Briney:** about 104 years old, jokes about his age. His Peeko is and remains a **Wingull**, never a Pelipper.
12. **Story mystery:** Neo Aqua/Magma are not responsible for every disaster; they react to and exploit anomalies. Early traces of Team Null are subtle and unidentified. Avoid naming May as Null leader or deciding Birch/Norman's full fate before a later story lock.
13. **World state:** 25-year time skip. Mossdeep is a partly sinking, mostly paved metropolis (minimal intentional greenery). Main characters show Ranger outfits in all character views. Other setting facts already established include a retired Wattson, Wally running Petalburg Gym, Norman missing ~15 years, Birch's larger lab in Mauville, an overgrown abandoned Littleroot lab, and subterranean Dewford. Mention only where relevant to Chapters 1–3.

---

## B. Timeline / player route / chapter boundaries

```
CHAPTER 1 — THE SINKING CITY
Birch recorded orientation -> Ari/June -> partner selection -> flood alarm ->
Mossdeep rescue -> Hale debrief -> Hale receives emergency-landing call ->
Ranger flight transport -> Rustboro arrival -> CHAPTER 2

CHAPTER 2 — THE FOREST AND THE FLOOD
Rustboro Ranger outpost / Nessa or Vern -> assigned southern supply corridor ->
Route 104 North -> Petalburg Woods / Neo Magma disturbance ->
South exit fallen-tree barrier (rival demonstrates Cutter) ->
Route 104 South / Briney's cottage / Neo Aqua vs evacuation supplies ->
return via cleared path to Rustboro -> Hale receives report ->
Hale orders player to earn 1 badge and report back -> CHAPTER 3

CHAPTER 3 — THE BROKEN SIGNAL
Any valid 1st badge (Roxanne likely, but not mandatory) ->
Hale / Rank 2 Ranger promotion / Cutter installed ->
Route 116 monitoring relay, fallen trees and unstable ground ->
Rusturf Tunnel rescue and suspicious interference ->
third-party signature found, identity withheld ->
report at Rustboro -> clearance for wider mainland missions -> CHAPTER 3 COMPLETE
```

### Global progression rules
- Chapter advances by **mission flags**, never by reaching an EXP or Pokémon-level ceiling.
- Player can challenge Rustboro Gym before finishing Chapter 2; if a badge is already owned when Hale asks, Chapter 3 qualification is immediately satisfied.
- Use **total badge count ≥ 1** for first promotion, not `FLAG_BADGE01_GET` only. Track `BADGES_OBTAINED` dynamically.
- If the player approaches Ranger routes out of order, alternate dialogue explains the situation; avoid impassable states.
- Gym team scaling follows badge count at battle initialization. Chapter story flags can enrich dialogue but do not make the player lose earned badges or equipment.
- All critical barriers cleared by an NPC remain cleared in save data (no softlocks on return trip).
- The Ranger Cutter is an approved field tool: does not require teaching HM Cut to a Pokémon.

---

## C. Chapter 1 — The Sinking City (preserve/append only)

### C1.01 — Birch's recorded greeting
Set in a private Ranger orientation space. Birch explains that Hoenn has changed dramatically over 25 years, strong Pokémon require badges and Ranger advancement often requires Gym qualifications; Ranger work and the League are compatible. Closing tone: keep gear intact, wits about you, have fun and return safely; end recording. Do not revert to standard Emerald truck/intro.

### C1.02 — Orientation / starter
Ari meets player in person; Dispatcher June assigns the first active task and offers exactly the three starter Pokémon. Partner starts at Lv. 5 and can grow normally. Ranger outfit/player overworld must be visible.

### C1.03 — Flood alarm and rescue
Preserve the established missing child, Poochyena retrieval, dangerous stairwell and failing rig; extraction through shopkeeper's upstairs apartment, late-siren mystery. Preserve the rescue-board/balcony return detail and the optional dry joke: “Front door's upstairs now.”

### C1.04 — Hale debrief and flight (NEW END-CAP, not a retcon)
Location: Mossdeep Ranger headquarters after all existing rescue flags complete.

**Commander Hale:**
> “Well done, Ranger. Considering the conditions out there, you've performed admirably.”
> “Hoenn needs people who can think on their feet. Today, you proved you're one of them.”

COMM DEVICE RINGS. Hale steps several tiles away. Text from his end only:
> “An emergency landing? Near Route 104?”
> “Mr. Briney's old cottage... Understood. Any casualties?”
> “Good. Keep them sheltered. I'll coordinate with Rustboro.”

Hale returns:
> “That vessel from the evacuation has made an emergency landing near Briney's old place.”
> “Everyone's accounted for, but they'll need support from the mainland.”
> “I'm sending you to Rustboro. You'll meet your field contact at the Ranger outpost.”
> “Fair warning—they're competitive. Very competitive.”
> “I'll fly you over. Come along.”

Fade out -> flight SFX/cutscene -> warp to Rustboro Ranger outpost exterior; fade in. Set `C1_DONE`, `HALE_FLIGHT_DONE`. Flight is story transport, not player-owned Fly HM.

**Chapter 1 ending journal:** “Report to the Ranger outpost in Rustboro City.”

---

## D. Chapter 2 — The Forest and the Flood

### C2.01 — Arrival: Rustboro Ranger outpost
Map: Rustboro City, small Ranger office/outpost in or near a repurposed municipal/Devon annex. Staff should be generic Ranger personnel, not additional named characters unless already established. One healing station; one bulletin board; save/recovery access.

Rival appears in the same spot regardless of gender. `RIVAL_NAME` automatically displays Nessa for male player and Vern for female player. Use same common text.

**Rival:**
> “So you're the rookie Dad's been talking about?”
> “I heard you handled a rescue in Mossdeep. Not bad for your first day.”
> “I'm {RIVAL_NAME}. Future greatest Ranger in Hoenn. Maybe the world.”
> “We've been assigned to the same supply corridor. Don't slow me down, okay?”

**Ranger dispatcher / bulletin board:**
> “Assignment 002: assess storm damage south of Rustboro, secure the path through Petalburg Woods, and deliver relief supplies to the evacuation crew near Briney's cottage.”

Player receives `MISSION_SUPPLY_CORRIDOR`, an objective marker, and supplies as a **quest item** (no item capacity trap). Rival accompanies by staged appearances rather than a continuous follower AI in the first implementation.

### C2.02 — Route 104 North / Woods entry
- Signs of damage: displaced debris, broken fencing, submerged patches.
- Optional wild encounters; no mandatory levels reset.
- Brief tutorial: Ranger Journal mission statuses, battle EXP vs Ranger mission bonus EXP.
- Two optional civilian dialogue beats: “Even the ground feels warm after the rain” and “It shouldn't be raining this hard this far inland.”

### C2.03 — Neo Magma at Petalburg Woods
On first approach, two **Neo Magma Grunts** operate a soil-temperature sensor beside an injured root system and a patch of steaming mud. They are collecting **temperature signatures** believed useful in locating Volcanion. In Chapter 2, the player is not told its species name.

**Neo Magma Grunt:**
> “Keep the probe steady. If the temperature spikes again, we'll finally have a direction.”

**Second Neo Magma Grunt:**
> “We aren't flooding the forests. We're measuring what's happening underneath them.”

**Rival:**
> “That equipment is making the roots steam. Turn it off before somebody gets hurt!”

**Neo Magma Grunt:**
> “Stay out of Neo Magma's work, Ranger. You have no idea what we're preventing.”

BATTLE A -> BATTLE B. Two separate grunt trainer names remain generic; battle index IDs are internal only. After defeat they shut down or abandon the probe. No named officer introduced here. Player collects `HEAT_PROBE_READOUT`, not an actual Pokémon encounter.

**Rival:**
> “They're talking like they're protecting the forest while burning it.”
> “I'll forward this reading to the outpost. We've still got supplies to deliver.”

Mission completion component: `WOODLAND_PROBE_DISABLED`. Optional rescue: free a displaced Shroomish or Zigzagoon; EXP reward for optional mission can be handled separately, not duplicated on re-entry.

### C2.04 — South exit: Cutter demonstration
At the southern Woods exit to Route 104 South, a storm-felled tree blocks the corridor. On first entry, rival moves into position and demonstrates the cutter equipped on their Ranger gauntlet. The rival has already earned the required qualification from an earlier badge (not a claimed extra badge earned during the prologue).

**Rival:**
> “Of course. The last stretch is blocked.”
> “Watch this: Ranger Cutter module.”
> “[Gauntlet activates; slice effect; fallen tree vanishes.]”
> “Field gear isn't free. You earn the certification by advancing as a Ranger—and badges are part of that.”
> “Get your first badge and report to headquarters. They'll authorize your upgrade.”
> “Now hurry. Those people are still waiting for us.”

Set `WOODS_TREE_CLEARED` permanently. The same saved flag controls collision removal and visual state. If player bypasses via another route, a fallback trigger clears it safely when visiting with rival or revisiting after assignment. IMPORTANT: do not require player's own Cutter to reach Briney in Chapter 2.

### C2.05 — Route 104 South / Briney's cottage
Evacuation vessel rests offshore; temporary relief supplies are stacked near the old cottage. **Neo Aqua Grunts** are searching the ship's emergency marine/atmospheric log for **pressure and steam anomaly data** related to Volcanion. They are compromising relief distribution, not simply cartoonishly stealing food. Evacuees are sheltered and accounted for; don't undo Chapter 1's rescue success.

**Neo Aqua Grunt:**
> “The ocean went wild before any warning came. The ship recorded something valuable.”

**Other Neo Aqua Grunt:**
> “Give us the navigation log, and nobody has to get in our way.”

**Rival:**
> “You're threatening evacuees over a notebook? That's enough.”

BATTLE C -> BATTLE D; no distinct grunt names. After victory, grunts withdraw with incomplete information. Rival retrieves a damaged page marked with unusual readings; player delivers quest supplies to Briney, then aid workers.

**Mr. Briney:**
> “HOHO! Another young Ranger! They keep tellin' me I'm too old to sail!”
> “A hundred and four years I've been kickin' around. A little rain won't finish me!”
> “Ain't that right, Peeko?”
> “Peeeeko!”
> “See? Me Wingull's got more sense than half the sailors out there!”

Peeko sprite MUST be Wingull; neither NPC dialogue nor in-battle composition may substitute Pelipper.

**Rival:**
> “First Neo Magma measuring heat, now Neo Aqua hunting pressure records.”
> “What exactly are they both looking for?”

Set `C2_AQUA_REPELLED`, `RELIEF_DELIVERED`, `SHIP_LOG_FRAGMENT_FOUND`; award mission completion exactly once, +250 Pokémon EXP at Rank 1 to designated bonded partner (pending engine design) and Ranger XP distinct from this reward. Avoid duplicate item/reward if revisited.

### C2.06 — Return to Rustboro and qualification briefing
Upon report, Commander Hale is temporarily present at Rustboro's Ranger outpost after handling the emergency air transport. In future he can return to Mossdeep, with radio reports filling gaps. No contradictory teleporting between maps.

**Commander Hale:**
> “I've reviewed both reports. Neo Magma in the woods. Neo Aqua at the landing site.”
> “They aren't working together, but they may be following the same disturbance.”
> “You handled the assignment well. It's time to talk about promotions.”
> “Ranger equipment isn't based on bravery alone. We certify people who prove they can manage stronger Pokémon.”
> “Earn one Gym badge, then return to headquarters. Once your field evaluation is confirmed, we'll authorize Rank 2 and your Cutter module.”

If player already has ≥1 badge, swap last line:
> “You've already earned a Gym badge? Excellent. Your qualification is satisfied. Report to the quartermaster for Rank 2 certification.”

**Chapter 2 ending journal:** “Earn one badge and report to the Rustboro Ranger outpost for promotion.” (Or “Report for Rank 2 certification” if eligible.)

### Chapter 2 battles — first-pass balancing
| Internal event ID | Displayed trainer class | Party | Story requirement |
| --- | --- | --- | --- |
| NM_WOODS_A | Neo Magma Grunt | Numel Lv. 8 | mandatory |
| NM_WOODS_B | Neo Magma Grunt | Slugma Lv. 9 | mandatory |
| NA_BRINEY_A | Neo Aqua Grunt | Wingull Lv. 9 | mandatory |
| NA_BRINEY_B | Neo Aqua Grunt | Carvanha Lv. 10; Lotad Lv. 8 | mandatory |

These are **draft party configurations**, not an existing ROM trainer table. Tune to the actual EXP gained by starters and available wild Pokémon. Use normal trainer battle format; no random grind requirements.

### First rival battle (optional side encounter)
After the first Route 104 mission, near the Rustboro practice yard, rival offers a **repeatable-dialogue but one-time reward** friendly battle. Declining does not block Chapter 3; battle remains available until accepted. Opposite starter as specified, Lv. 11; Taillow Lv. 10. If chosen, no Ranger mission reward from this sparring battle. Script outcome should acknowledge win/loss without changing the plot.

---

## E. Chapter 3 — The Broken Signal (proposed complete chapter)

### C3 design intent
Chapter 3 turns Ranger gear from exposition into playable exploration, connects Rustboro's industrial research to the broader Hoenn mystery, and gives the player a genuinely useful field command. **Route 116 / Rusturf Tunnel** is the natural local map arc. It has no early Volcanion/Arceus reveal.

### C3.01 — Badge checkpoint / Roxanne
Core condition: total badges ≥1, not specifically Roxanne's badge. Rustboro's early Steel-type Gym is the obvious introductory option and stays challengeable early. Its dialogue changes with story stage; for example:

- Before Ch2 report: “Rangers and Trainers are both welcome here. When you're ready, come test your team.”
- During one-badge objective: “Commander Hale sent you? Then let's see whether you can protect yourself—and your partners.”
- After promotion: “Your new equipment won't win battles for you. Your judgment will.”

**Proposed Rustboro Steel roster, 0 badges:** Aron Lv. 12; Magnemite Lv. 14. Signature long-term ace line: Aron -> Lairon -> Aggron -> **Mega Aggron** at high-tier scaling only. Don't deploy Mega Aggron in an early 0-badge battle. Badge name can remain Stone Badge despite Roxanne's updated specialization. Higher-tier team definitions belong in the Gym scaling document; avoid forcing the entire game into a strict gym order.

If player got first badge elsewhere, Rustboro remains available and Chapter 3 can proceed. Update rival dialogue accordingly: “You didn't even start here? Guess I shouldn't be surprised.”

### C3.02 — Rank 2 promotion / Cutter upgrade
Location: Rustboro Ranger outpost; Hale + unnamed quartermaster. Preconditions: `RELIEF_DELIVERED && C2_REPORT_DONE && BADGE_COUNT>=1`. One-time transaction:
- Ranger rank goes from 1 Rookie to 2 Ranger.
- Install `GEAR_CUTTER_R2` on player's Ranger gauntlet; set tool tutorial seen.
- Increase standard mission Pokémon EXP to +300 from this point forward (not retroactively); Ranger XP tracked separately.
- Unlock Ranger assignment `RELAY_ROUTE_116`.

**Commander Hale:**
> “One badge. Field evaluation complete. Congratulations—you're cleared for Rank 2 Ranger duty.”
> “The quartermaster has authorized your first independent gear upgrade.”
> “Remember: your badge establishes the qualification. Your missions prove how you use it.”

**Quartermaster:**
> “Ranger Cutter installed. It can clear approved vegetation and certain fallen obstacles.”
> “It won't cut rock, steel, or living trees without authorization. Your gear has limits.”

The last line provides in-world reasons Cutter doesn't replace all navigation tools. When used on scenery, prompt “Use Ranger Cutter?” with a short gauntlet animation, not HM dialogue. Re-use existing Cut obstacle system where possible, with a `GEAR_CUTTER_R2` check replacing the HM+badge check on selected Neo Emerald maps.

### C3.03 — Assignment 003: Route 116 relay
A weather/seismic monitoring relay on Route 116 stopped reporting at the same time as the Mossdeep storm. Devon-associated engineers ask Rangers to check for stranded personnel and restore power. Starting point Rustboro outpost; route goes east to Route 116, then toward Rusturf Tunnel.

**Bulletin board:**
> “Assignment 003: restore the Route 116 field relay, account for the technicians, and investigate a signal disruption near Rusturf Tunnel.”

**Rival:**
> “That relay was supposed to confirm the readings we found near Briney's place.”
> “Guess we're not the only ones chasing answers.”

### C3.04 — Player's first independent Cutter use
A minor fallen branch blocks the sanctioned Route 116 inspection trail. Player must use their own upgraded gauntlet; success clears one persistent obstacle and shows a “RANGER CUTTER” field animation. Avoid globally converting all trees if it will break original maps; start with selected flagged obstacles. No Pokémon must know Cut.

### C3.05 — Missing technicians / tunnel rescue
A technician and local traveler are trapped beyond a shifting rock pile inside Rusturf Tunnel. Player cannot simply Cut stone; the mission objective is to reach an alternate passage, talk to the survivors, and use a rescue rope/portable signal beacon supplied by the outpost. A second Ranger team (offscreen, no new named NPC) handles heavy clearance after player calls for help. Player finds a broken relay power coupling showing **heat and pressure readings spiking simultaneously**.

**Technician:**
> “The relay went wild. Heat underground, pressure in the air—both at once.”
> “Then another signal cut through ours. Not static. Something deliberate.”

Rival helps evacuate survivors through the safe passage. The story rewards rescue work over defeating every Pokémon.

### C3.06 — Neo Magma interference
An otherwise unnamed **Neo Magma Grunt** was attempting to recover geothermal data from the ruined relay. The grunt isn't necessarily the saboteur.

**Neo Magma Grunt:**
> “That relay picked up a power signature no one in Hoenn can explain.”
> “We've been chasing it for weeks. A Ranger wouldn't understand.”

Battle. After defeat:
> “Believe what you want. We didn't cut your signal. Someone beat us here.”

This is the chapter's first **explicit hint** that the known factions are not causing all disruptions. Do not show Volcanion onscreen or state its name yet. Rival logs the remark.

### C3.07 — A third signature (Team Null foreshadowing)
Player investigates a diagnostic terminal recovered from relay wreckage. Three historical channels: public Ranger telemetry, Neo Magma geothermal probing, Neo Aqua marine logging; a **fourth unregistered code** briefly appears in the corrupted relay data. It is not labeled “Team Null” in player UI.

**Terminal:**
> “UPLINK INTERRUPTED.”
> “SOURCE: UNKNOWN.”
> “ACCESS KEY: [UNREADABLE]”
> “TRANSMISSION ORIGIN: NOT FOUND.”

**Rival:**
> “That's not Neo Magma's equipment.”
> “And the Aqua log doesn't match it either.”
> “Someone else is listening.”

Keep Arceus entirely offscreen. Team Null's specific motives are for later chapters. A glyph/signal motif can be fixed later; do not prematurely add world-rewriting exposition to chapter 3.

### C3.08 — Return report and chapter close
The recovered data is archived at Rustboro Ranger outpost. Hale observes that both Neo teams appear to have been **following** the same disturbances rather than initiating all of them.

**Commander Hale:**
> “The people you brought out of the tunnel are safe. That's what matters most.”
> “But this third signal worries me. No civilian transmitter should have access to that relay.”
> “I've sent the logs for further analysis. For now, you've earned permission to accept wider mainland assignments.”
> “And Ranger? Keep a copy of what you found. Something about these reports isn't adding up.”

**Rival:**
> “You're getting better at this.”
> “Don't get comfortable. I'm still going to be the greatest Ranger Hoenn's ever seen.”
> “But... I'm glad we were both there.”

Set `C3_DONE`, open next regional assignment board, optional later travel branches. End chapter with a single short glitch/static visual in the Ranger device, without name-dropping Arceus.

### Chapter 3 battles — first-pass balancing
| Internal event ID | Displayed trainer class | Party | Requirement |
| --- | --- | --- | --- |
| NM_RELAY_A | Neo Magma Grunt | Numel Lv. 13; Baltoy Lv. 12 | mandatory |
| WILD_TUNNEL | Wild Pokémon | normal Rusturf Tunnel encounter table | optional |

**Second rival battle:** near outpost after reporting, optional but narratively timely: advantageous starter Lv. 16; Taillow Lv. 14; Electrike Lv. 15. Offer battle through reusable NPC prompt; no duplicated story flag or reward. Scale all rival parties by story checkpoint and adjust to actual badge scaling/test results.

### Side assignments to make Chapter 3 feel substantial
1. **Lost Equipment:** retrieve a technician's misplaced sensor from Route 116; Ranger mission (Rank 2) grants +300 designated partner Pokémon EXP and Ranger XP; claim-once flag.
2. **Forest Follow-up:** optional return to Petalburg Woods; animal habitat no longer steaming, but unusual residue remains. Grants journal evidence, modest items, no repeated +250 mission payout.
3. **Briney's Favor:** deliver replacement supplies to Route 104; Peeko Wingull cameo and age joke variant. A ferry ride can become available later without invalidating Chapter 1's emergency landing.

---

## F. Enemy organizations and assets

### Neo Magma
- Origin: successors led by Maxie's child; identities withheld early.
- Thesis: dangerous changes to the land demand intervention. They believe a rare source of geothermal power could stabilize territory. Secret target: Volcanion.
- Grunts: use original Team Magma trainer/overworld sprite base, cloned into unique Neo identifiers. Uniform black, **M red**. Preserve skin/hair/outline; don't recolor the entire palette indiscriminately.
- Early Pokémon pool: Numel, Slugma, Baltoy, Poochyena. Assign by ecological logic, not rigid type exclusivity.
- Voice: focused, convinced of necessity, occasionally defensive. Grunts do not have personal names.

### Neo Aqua
- Origin: successors led by Archie's child; identities withheld early.
- Thesis: ocean/rain equilibrium has shifted, and harnessing the missing steam/water signature may prevent a broader disaster. Secret target: Volcanion.
- Grunts: original Team Aqua base cloned. Uniform white, **A blue**; avoid eliminating outlines on a light uniform—retain navy/gray outlines, perhaps subtle pale-cyan shadow where the original had blue shading.
- Early Pokémon pool: Wingull, Carvanha, Lotad, Tentacool.
- Voice: maritime jargon, precise and assertive. Grunts do not have personal names.

### Team Null
- **Ultimate target:** Arceus. Separate from Volcanion rivalry and late-game weather trio roster.
- No named agents or battles required in Chapters 1–3. Only unknown signal/evidence begins to hint a third network.
- Preserve Birch/Norman/May mysteries as unresolved, avoiding premature canon lock of secret leadership.

### Sprite / game asset specification
1. Rival battle art: duplicate `graphics/trainers/front_pics/pokemon_ranger_m.png` and `pokemon_ranger_f.png` into Vern/Nessa-specific filenames, recolor hair blue/purple while retaining Ranger costume shading. Do not alter base global trainer classes.
2. Rival overworld: original Emerald Ranger overworld may reuse Camper/Picnicker rather than fully distinct outfits; create **new** overworld Ranger sprite sheets if necessary, using existing Emerald 16×32-style proportions, matched to battle art. Editing only hair color on Camper/Picnicker may not give the target uniform, so inspect source graphics before selecting final base.
3. Neo grunts: duplicate existing aqua/magma front/back and overworld art; palette-specific recolor; ensure individual male/female sprite variants if present. Keep all battle text at grunt class.
4. Volcanion: user-supplied 256×256 sprite sheet can be processed later. It is not a playable encounter through Chapter 3; retain source artwork unchanged, use GBA-appropriate conversion/palettes when creature is introduced.
5. Every sprite conversion needs original-scale check, transparency index validation, no invisible hair/skin pixels, no unintended shared-palette changes, battle animation/frame tests, and emulator screenshots.

---

## G. Ranger equipment & badge logic

### Rank model — early game
| Ranger rank | Player title | Badge minimum | Example unlock | Routine mission partner EXP |
| --- | --- | --- | --- | --- |
| Rank 1 | Rookie | 0 | Journal, starter gear, emergency response | +250 |
| Rank 2 | Ranger | 1 | Ranger Cutter | +300 |
| Rank 3 | Senior Ranger | TBD later | Future module | +350 |
| Rank 4 | Area Ranger | TBD later | Future module | +400 |
| Rank 5 | High Ranger | TBD later | Future module | +450 |

Badge minimum alone does not create a promotion: field evaluation and headquarters interaction also required. Don't grant Rank 2 twice, or rerun upgrade animation on load. Major-story +1,000 partner EXP rewards are separate, individually flagged, and never recur on re-entering a map. No automatic level lock. Badge acquisition triggers next report eligibility, not instantaneous movement item grant.

### Journal objectives / completion notifications
- C1 objective: “Assist Mossdeep evacuation.” -> “Report to Hale.” -> “Travel to Rustboro.”
- C2 objective: “Meet your Ranger contact.” -> “Secure the woods route.” -> “Inspect Neo Magma equipment.” -> “Reach the emergency landing.” -> “Stop Neo Aqua.” -> “Deliver supplies.” -> “Report to Hale.”
- C3 objective: “Earn your first badge.” -> “Report for Rank 2 certification.” -> “Restore the Route 116 relay.” -> “Rescue trapped technicians.” -> “Recover interference log.” -> “Report to Hale.”
- Mission board always reads from state flags, not just story chapter index.

### No-softlock requirements
- Rescue completed? Hale's flight occurs once, with a safe return/fast travel later if needed.
- Rival's chapter 2 Cutter demonstration permanently removes tree collision; Chapter 2 can be finished without player's Cutter.
- Chapter 3 Cutter module is only required for **new approved obstacles**; side routes remain accessible, and the player can still reach medical/PC facilities.
- Badge order flexible: use `GetBadgeCount()` equivalent, not a fixed Stone Badge requirement.
- Starter or Pokémon faints, boxes, or evolves: Ranger gear must continue working (not attached to starter species or moves).
- Item capacity full: mission objects are key item/flag, not standard free inventory items.
- Grunt battles once defeated cannot produce repeated EXP or mission payouts through map reloads.
- Warp connections verified with mGBA and Delta once built; save/reload in every chapter.

---

## H. Event/flag table (symbolic implementation contract)

| Flag / state | Trigger | Result |
| --- | --- | --- |
| `FLAG_NEO_C1_RESCUE_DONE` | Existing Mossdeep rescue completion | Hale debrief eligible |
| `FLAG_NEO_C1_HALE_CALL` | Hale communication cutscene | Emergency landing acknowledged |
| `FLAG_NEO_C1_FLIGHT_RUSTBORO` | Flight cutscene completed | Rustboro spawn; chapter 2 active |
| `FLAG_NEO_C2_RIVAL_MET` | Rustboro first rival contact | Mission002 offered |
| `FLAG_NEO_C2_WOODS_MAGMA_DEFEATED` | Both Magma grunts beaten | Soil-probe clue; route clear trigger |
| `FLAG_NEO_C2_TREE_CLEARED` | Rival Cutter cutscene | Persistently remove south exit tree |
| `FLAG_NEO_C2_AQUA_DEFEATED` | Both Aqua grunts beaten | Supplies protected |
| `FLAG_NEO_C2_SUPPLIES_DELIVERED` | Briney relief delivery | Mission002 completion eligible |
| `FLAG_NEO_C2_REPORT_DONE` | Hale debrief | First-badge objective, chapter 3 entry |
| `FLAG_NEO_RANK2_CERTIFIED` | `C2_REPORT_DONE && badge_count>=1` | Promote Rank 2, Cutter granted, one-time |
| `FLAG_NEO_C3_CUTTER_TUTORIAL` | First tool use Route116 | Barrier removed, tutorial complete |
| `FLAG_NEO_C3_TECHNICIANS_RESCUED` | Rusturf Tunnel rescue | Safety mission component complete |
| `FLAG_NEO_C3_RELAY_LOG_FOUND` | Diagnostic console inspection | Third signal evidence acquired |
| `FLAG_NEO_C3_MAGMA_DEFEATED` | Magma relay grunt defeated | Scene dialogue unlock |
| `FLAG_NEO_C3_REPORT_DONE` | Hale final report | Next chapter board unlocked |
| `FLAG_NEO_MISSION002_REWARD` | Claim Chapter2 reward | Prevent repeat reward |
| `FLAG_NEO_MISSION003_REWARD` | Claim Chapter3 reward | Prevent repeat reward |

Use existing script event flags for trainer defeat where supported; flags above are logical placeholders, not exact compiled identifiers. Add one concise chapter state variable if needed, but rely on fine-grained flags for recoverability.

---

## I. Test matrix / definition of done

### Prologue preservation
- Birch recording (not vanilla Birch startup) on new save.
- Male/female Ranger player sprites render properly in overworld, menu, battle/back sprite.
- Only Poochyena, Spheal, Shroomish starters; Lv 5 and expected moves.
- Natural battle experience increases starter level without cap.
- Mossdeep city terrain, rescue NPCs, sirens, balcony and escape are intact.
- Mossdeep Gym blocked with correct context-sensitive dialogue; early line matches exactly.
- Hale receives call and flies player to Rustboro **after** rescue completion, not before.

### Chapter 2
- Correct Nessa/Vern based on player gender; same dialogue/mission content.
- Opposite starter mapping across all three selections (six combinations including player genders).
- Both Magma and Aqua grunts show correct generic names and colors; no unexpected global sprite recolor.
- Petalburg Woods two battles occur once; probe clue is obtainable.
- South exit Cutter demonstration occurs once, tree remains gone on reload.
- Route104 South remains reachable without player's Cutter; Briney is 104/Peeko Wingull.
- Aqua defeat, supplies delivery and report function in both gender variants.
- First badge can be earned before or after C2 report without breaking eligibility.

### Chapter 3
- Roxanne first badge works; another first badge works identically.
- Rank2 promotion only when all requirements met, grants Cutter once.
- Cutter prompt/animation removes only eligible map objects.
- Rusturf Tunnel quest can be completed without requiring an unintroduced HM.
- Relay third-signal trace found; no visible Arceus or Volcanion encounter.
- Optional rival battles may be declined; one-time rewards if any do not duplicate.
- Chapter3 clearance opens next mission board; save/reload doesn't reset scene or trap player.

### Build validation
- All sprite files fit engine frame/palette constraints.
- Scripts compile; no duplicate constants or undefined maps, NPC IDs, specials, messages.
- New game and migrated save both considered (if save compatibility is supported).
- Boot/run in mGBA; then test GBA file in Delta on iPhone.
- Entire sequence playable with player male and female, each starter, and both early/late badge paths.

---

## J. Explicit non-goals through Chapter 3

- No playable Volcanion capture, no Arceus confrontation.
- No weather trio capture or storyline overriding Elite Four/Champion placements.
- No early Team Null leader identity reveal; no fabricated named grunts.
- No mandatory full follower AI, voice acting, or new ocean map system required for first playable chapter build.
- No claim that the written spec itself changes the GBA game. Source integration and ROM validation remain necessary.

## K. Production implementation sequence

1. Establish actual Neo Emerald source checkout/branch and verify build with current ROM baseline; archive test build hash.
2. Preserve/fix Chapter1 original intro, rescue and story state first (regression test).
3. Import rival battle + overworld recolor assets under new IDs; shared name string.
4. Import Neo Aqua/Neo Magma grunt palette clones and trainer names.
5. Implement Chapter1 Hale call/flight.
6. Script Chapter2 outpost, Woods, tree demo, Route104 South, Briney, Hale report.
7. Add one-badge certification and Cutter field handler.
8. Script Chapter3 Route116/Rusturf Tunnel relay event and evidence.
9. Add dynamic Ranger mission journal, rewards, and tests.
10. Run emulator tests and fix bugs before calling a ROM build playable.