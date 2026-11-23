# Neo Emerald Chapters 1–3: Test Scenarios

These are expected tests for a FUTURE compiled ROM. They are not evidence that the scripts are present in a current build.

| ID | Test scenario | Expected behavior |
|---|---|---|
| T01 | New game male | Ranger player; Nessa selected; Birch recording remains |
| T02 | New game female | Ranger player; Vern selected; same story scripts |
| T03 | Poochyena picked | Lv5 Fire Fang; rival Spheal; normal EXP leveling |
| T04 | Spheal picked | Lv5 Ice Beam; rival Shroomish; normal EXP leveling |
| T05 | Shroomish picked | Lv5 Giga Drain; rival Poochyena; normal EXP leveling |
| T06 | Walk to Mossdeep Gym before sailor | “Now's not the time. I should check with the sailor nearby.” |
| T07 | Finish missing-child rescue | Existing rescue ending retained; Hale debrief then call |
| T08 | Hale accepts call | Emergency landing reported near Briney's cottage |
| T09 | Flight to Rustboro | Arrives at Ranger outpost; no pre-story teleport |
| T10 | Neo Magma Grunt battle | Black uniform/red M, class generic; trainer encounter one time |
| T11 | Woods south exit | Rival demonstrates Cutter once; tree stays cleared |
| T12 | Re-enter Woods after saving | Forest path passable without player's Cutter |
| T13 | Neo Aqua Grunt battle | White uniform/blue A, class generic; trainer encounter one time |
| T14 | Speak to Briney | 104 joke; Peeko Wingull sprite |
| T15 | Deliver supplies twice | Mission EXP rewarded once; no duplication |
| T16 | Report with zero badges | Hale orders one Gym badge; no Cutter yet |
| T17 | Obtain badge then report | Rank 2 promotion, Cutter installed once |
| T18 | Badge obtained before Chapter2 report | Hale recognizes existing badge and certifies without extra battle |
| T19 | First badge from non-Rustboro Gym | Badge count accepted; early gym circuit remains flexible |
| T20 | Route116 branch | Player Cutter works without Pokémon knowing HM Cut |
| T21 | Route116 branch with no Cutter | Mission appropriately unavailable; access to healing safe |
| T22 | Tunnel rescue | Rescue can finish, no extra HMs required; survivors safe |
| T23 | Relay log | Unidentified fourth signal; no Arceus/Volcanion reveal |
| T24 | Return to Hale | Wider assignments unlocked; state persists |
| T25 | Optional rival spar decline | Doesn't block any chapter progression |
| T26 | Gender×starter×badge sequence | All six main gender/starter paths × early/late badge variations |
| T27 | Save/load after every cutscene | No duplicate NPC, softlock, mission reward, or level reset |
| T28 | Delta iPhone boot | Valid GBA loads, correct opening; emulator validation logged |