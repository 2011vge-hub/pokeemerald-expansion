# Neo Emerald — Ranger partner mission EXP

Ranger career XP and Pokémon training EXP are separate currencies.

## Ordinary rank-scaled training
| Ranger rank | Pokémon EXP credit per ordinary mission |
|---|---:|
| Rookie (internal 0) | 250 |
| Ranger (1) | 300 |
| Senior (2) | 350 |
| Area (3) | 400 |
| Top (4) | 450 |

Top rank plateaus at 450. Major story rewards use 1,000 EXP, independent of rank, via the same special with VAR_0x8004 = 1.

The first Mossdeep rescue credits +1 Ranger mission and +100 Ranger career XP. Separately it queues +250 **Pokémon EXP** when completed at Rookie rank.

### Why queued instead of directly changing Pokémon levels
Neo Emerald saves the selected partner's original 32-bit personality ID on recruitment, alongside a 16-bit training EXP queue. That identity survives level-ups, evolutions and party rearrangement. The queue is **not granted to a lookalike Pokémon** caught later. It remains in the player's save if the partner is deposited in a PC; it is applied when that exact partner is back in the active party and next gains EXP from an eligible battle. The amount enters Emerald Expansion's ordinary battle EXP controller after its standard multipliers and before the hard level-cap logic. That lets Emerald display level-up animation, learn moves, and handle evolution correctly.

Only the matching partner receives the bonus. It cannot be repeatedly farmed: the boarding scene pays only in state 4; it changes to state 5 before credit, and each bonus consumed in battle is removed from the saved pending bank. Amounts too large for the current level cap remain pending until an eligible future battle. The stored credit is capped at 65,535 EXP for safety.

**Starter is NOT level locked to 5.** It begins at level 5 and gains all normal battle EXP. The bonus stacks on top of its next qualifying battle EXP.

## Playtest checklist
- Start new game, choose each of the three starters and inspect signature move.
- Fight a normal battle before rescue; confirm normal EXP gain and level-ups.
- Complete rescue at Rookie rank: mission +1 / Ranger XP +100; +250 Pokémon EXP reserved.
- Fight another battle with the same starter: see normal battle EXP **plus** 250, normal level-up/moves.
- Repeat with another Pokémon in front of team: reserved bonus is held until original starter gains eligible battle EXP.
- Move original starter to PC, catch another of same species: the new Pokémon must NOT receive credit.
- Save/reload before battle and confirm the training credit persists.
- Future rank changes use 300/350/400/450 per ordinary mission; major event flag uses 1,000.
- Test when at hard level cap: excess queued bonus must survive.
