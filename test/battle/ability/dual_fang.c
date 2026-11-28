#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Dual Fang repeats eligible biting moves half the time")
{
    PASSES_RANDOMLY(1, 2, RNG_HITS);
    GIVEN {
        ASSUME(IsBitingMove(MOVE_BITE));
        ASSUME(GetMoveStrikeCount(MOVE_BITE) < 2);
        PLAYER(SPECIES_GRIMYENA) { Level(20); Ability(ABILITY_DUAL_FANG); }
        OPPONENT(SPECIES_WOBBUFFET) { Level(100); }
    } WHEN {
        TURN { MOVE(player, MOVE_BITE); }
    } SCENE {
        HP_BAR(opponent);
        HP_BAR(opponent);
        MESSAGE("The Pokémon was hit 2 times!");
    }
}

SINGLE_BATTLE_TEST("Dual Fang does not repeat non-biting moves")
{
    GIVEN {
        ASSUME(!IsBitingMove(MOVE_SCRATCH));
        ASSUME(GetMoveStrikeCount(MOVE_SCRATCH) < 2);
        PLAYER(SPECIES_GRIMYENA) { Level(20); Ability(ABILITY_DUAL_FANG); }
        OPPONENT(SPECIES_WOBBUFFET) { Level(100); }
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH); }
    } SCENE {
        HP_BAR(opponent);
        NOT MESSAGE("The Pokémon was hit 2 times!");
    }
}
