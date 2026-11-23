# Neo Emerald — Ranger Base new-game opening (v1)

Status: scripted into the development branch; compile and emulator QA required.

- A fresh save starts on the reception mat (7,8) in Mossdeep Ranger Base 1F.
- The first ON_FRAME at dispatch state 1 runs Ari's greeting, June's starter selection,
  the dispatch storm alarm and first assignment.
- The existing ChooseStarter / GetStarterPokemon / ScriptGiveMon path grants a
  **permanent level-5** Poochyena, Spheal or Shroomish. The state becomes 2
  before opening the selection UI, preventing the initial script repeating.
- The Ranger Base's other six staff, supplies, commander, entrance/exit warps,
  Mossdeep weather and the 3->4->5 rescue progression remain unchanged.
- Mossdeep's old exterior ON_FRAME starter event is removed so exiting the
  base does not replay it.
- Subsequent game loads should resume normally; this scene is new-game-only.
- The existing Rustboro chapter is not yet implemented as custom narrative.

## Playtest
1. Start a NEW GAME in mGBA/Delta; confirm first scene is inside Ranger Base 1F, not outside the Center.
2. Confirm Ari->June->three starter selection and correct level-5 Pokémon in party.
3. Exit/reenter Ranger Base repeatedly: no extra starters, no repeated introduction.
4. Save/reload inside, then walk outside: storm activates and HQ door works.
5. Complete the ferry rescue: state 3->4->5, only +1 Ranger mission and +100 XP.
6. Talk to June/Ari after the rescue; Commander Hale displays updated record.
7. Test both player genders and the authored Ranger uniform sprites; inspect any palette issues.
