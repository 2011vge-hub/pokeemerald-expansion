# Chapter 2 implementation checkpoint (2026-11-23)

**Branch:** `neo-emerald/ch2-woods-cutter-briney` (built atop the Rustboro University and Delta QA branches). **Status:** Source committed; compile and gameplay verification required.

The Nessa/Vern Rustboro contact was added in PR #2; this patch adds:

1. Existing Petalburg Woods Devon researcher rescue becomes the Neo Magma pressure-sensor interception. The existing early-game trainer is now a Magma grunt with Numel level 9. Completion sets a persistent mission flag.
2. A new Ranger rival object at (17,12) in Petalburg Woods demonstrates Cutter after the research battle. Both existing cut trees have shared persistent removal flag and are removed immediately in the scripted event. This is **a demonstration**, not a player HM or Rank 2 item.
3. Neo Aqua Grunt (Wingull 10, Carvanha 11) and a Devon supply worker near Route 104/Briney's cottage. The victory flag hides the grunt permanently; both NPCs have stage-specific text.
4. Briney's cottage dialogue acknowledges his age 104, Peeko remains Wingull, and the climate-data mystery. One-time evidence flag.
5. Rustboro campus Ranger liaison takes the report via Hale radio, grants one mission + 150 Ranger career XP + the normal rank-scaled partner training once, and informs player that **any one Gym badge** qualifies for Rank 2.

**Not implemented:** Full Chapter 3 badge promotion / Cutter hardware / Rusturf Tunnel, polished flight, fully distinct Neo-faction trainer class art, custom rival art and counter-starter battle, dynamic Gym scaling or team restructuring, physical oversized Rustboro campus exteriors. The two rival Cutter trees are an existing shortcut obstacle, not a freshly redesigned fallen-tree cutscene. Revisit prior Delta whiteout and dialogue bugs after build.

**Manual Delta test:** Fresh save → Birch/Ranger Mossdeep rescue → Hale flight → Rustboro Nessa/Vern intro → walk to Petalburg Woods and beat Neo Magma → locate rival in northwest Woods and watch permanent Cutter removal → defeat Neo Aqua near Briney's cottage on Route 104 → speak with Briney beside Peeko → return to university field student for Hale report → save/load and confirm no duplicate reward.
