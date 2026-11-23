#ifndef GUARD_CONSTANTS_NEO_RANGER_H
#define GUARD_CONSTANTS_NEO_RANGER_H

// Neo Emerald Ranger career framework.
// VAR_NEO_RANGER_RANK stores RANGER_RANK_*; missions and field XP use
// VAR_NEO_RANGER_MISSIONS and VAR_NEO_RANGER_XP.
// Badges are counted from FLAG_BADGE01_GET through FLAG_BADGE08_GET.
// Commander Hale promotes one rank at a time when all requirements are met.
// Mission credit is not yet wired into the ferry rescue.
// Example of a future completion script:
//   addvar VAR_NEO_RANGER_MISSIONS, 1
//   addvar VAR_NEO_RANGER_XP, 100

#define RANGER_RANK_ROOKIE   0
#define RANGER_RANK_RANGER   1
#define RANGER_RANK_SENIOR   2
#define RANGER_RANK_AREA     3
#define RANGER_RANK_TOP      4
#define RANGER_RANK_MAX      RANGER_RANK_TOP

#define RANGER_REQ_RANGER_MISSIONS   1
#define RANGER_REQ_RANGER_XP         100
#define RANGER_REQ_RANGER_BADGES     1

#define RANGER_REQ_SENIOR_MISSIONS   3
#define RANGER_REQ_SENIOR_XP         400
#define RANGER_REQ_SENIOR_BADGES     3

#define RANGER_REQ_AREA_MISSIONS     6
#define RANGER_REQ_AREA_XP           900
#define RANGER_REQ_AREA_BADGES       5

#define RANGER_REQ_TOP_MISSIONS      10
#define RANGER_REQ_TOP_XP            1600
#define RANGER_REQ_TOP_BADGES        8

#endif // GUARD_CONSTANTS_NEO_RANGER_H
