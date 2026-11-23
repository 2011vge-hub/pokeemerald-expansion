# Neo Emerald: Ranger partner signature moves and gym access (prototype)

## Signature starter moves
- POOCHYENA: FIRE FANG
- SPHEAL: ICE BEAM
- SHROOMISH: GIGA DRAIN
Each Pokémon joins at **Level 5**, keeps its ordinary battle experience and evolution path, and is given its signature move once during recruitment. Signature moves are not ability changes and do not disable move learning.

## Mossdeep Gym story gate
The Mossdeep Gym is closed to newcomers during evacuation. A policeman is standing at (38,10), blocking the one-tile doorway directly before warp (38,9). This is an intentional overworld collision blocker rather than a warp redirect; the player must interact while facing the NPC. Its dialogue is the protagonist's internal thought:
- Before sailor check-in (states 1-2): "**Now's not the time. I should check with the sailor nearby.**"
- During sailor/rescue assignment (states 3-4): "The rescue isn't finished yet. I need to get back to the ferry."
- After evacuation (state 5), before Ranger promotion: "The storm's not over for MOSSDEEP. I should report to CMDR. HALE."
- After promotion: "No GYM challenge without clearance from COMMANDER HALE."

Clearance is a dedicated story flag FLAG_NEO_MOSSDEEP_GYM_ACCESS_GRANTED. It has no early unlock event yet. A future story beat must set it; then on map reload the blocker becomes hidden and native Gym warp/encounters are available. Since flags are saved, access is persistent. **Rustboro Gym remains unblocked.**

## QA
- Start new game, choose each starter and inspect level, move set, 4/4 move slots, and battle experience leveling.
- Try Mossdeep Gym at each mission state; guard blocks the door and says contextually relevant internal monologue.
- At future story flag unlock, the blocker must hide, and the native gym must be reachable.
- Enter Rustboro Gym as normal; do not add restrictions to early gyms.
