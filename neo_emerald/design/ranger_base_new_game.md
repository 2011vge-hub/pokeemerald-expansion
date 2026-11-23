# Neo Emerald — Orientation Recording and Animated Reception (v2)

**Nov 22, 2026 Delta feedback:** The first playable prototype placed the Ranger at the lobby entrance but delivered anonymous dialogue while the cast remained at desks; small overworld sprites also differed from the already-approved larger ID portraits.

## Revised cinematic
1. Birch still appears in the standard trainer creation orientation. On a **new game**, the player now spawns in a quiet video orientation room using the Ranger Base's Facility art. The private display shows the tail end of Birch's recorded Ranger briefing and signs off "End recording."
2. The scene automatically transfers into the real Ranger Base 1F reception, with the player on the lower reception mat (7,8).
3. Ari physically approaches from reception (9,5) via (9,6),(9,7),(8,7), faces the player, and speaks.
4. Dispatcher June walks from (3,4) via (3,5),(3,6),(4,6),(5,6),(6,6), faces the recruit and explains partner registration.
5. Poochyena, Spheal or Shroomish is granted by the **existing** native ChooseStarter / ScriptGiveMon path. VAR_NEO_FERRY_DISPATCH becomes 2 before selection so the on-frame event never repeats.
6. A radio alert triggers mission 001. The player can visit Medic, Quartermaster and Commander Hale before exiting into Mossdeep's thunderstorm.
7. After rescue, original mission state 5, +1 mission, +100 Ranger XP, HQ dialogue and ferry visibility remain unchanged.

## Portrait fidelity
Keep the large boy/girl ID portraits. New overworld v2 sprite generator recolors/redraws indexed 16-color walking and running frames to **match those approved portraits**: male silver-blue hair, teal accent, navy field suit with orange diagonal rescue strap; female midnight blue hair/teal stripe, orange top and teal shorts. Other field action sheets and battle backs get the corresponding 16-color palette. Pixel-art polish, additional handmade animations and independent design assets remain future tasks.

## QA
- Choose boy/girl in **New Game**. Verify ID portrait matches small walking model.
- Watch prerecorded Birch scene in the *separate* orientation room; on completion it transfers to reception.
- Watch **both Ari and June physically walk up** before speaking.
- Choose one starter and ensure it persists after save/reload and no duplicate partner on reentry.
- Leave headquarters; rescue the boy and Poochyena; receive one-time XP; return to staff.
- Test walking and running animations in all directions, as well as riding, surfing and trainer back art.
- Existing saves will bypass the new-game recording; start fresh for this test.
