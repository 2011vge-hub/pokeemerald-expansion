RustboroCity_Flat1_1F_MapScripts::
	.byte 0

RustboroCity_Flat1_1F_EventScript_Man::
	msgbox RustboroCity_Flat1_1F_Text_EveryPokemonHasAbility, MSGBOX_NPC
	end

RustboroCity_Flat1_1F_EventScript_Woman::
	msgbox RustboroCity_Flat1_1F_Text_PokemonStrange, MSGBOX_NPC
	end

RustboroCity_Flat1_1F_Text_EveryPokemonHasAbility:
	.string "Every POKéMON has a special ability\n"
	.string "that it can use.$"

RustboroCity_Flat1_1F_Text_PokemonStrange:
	.string "POKéMON are such strange creatures.$"


NeoOffice_Hale::
	lock
	faceplayer
	goto_if_unset FLAG_NEO_C2_DEBRIEF_DONE, NeoOffice_Early
	goto_if_eq VAR_NEO_CH3_STEP, 9, NeoOffice_Complete
	goto_if_eq VAR_NEO_CH3_STEP, 8, NeoOffice_Report
	goto_if_ge VAR_NEO_CH3_STEP, 6, NeoOffice_Tunnel
	call MossdeepCity_RangerBase_2F_EventScript_CountBadges
	goto_if_eq VAR_0x8004, 0, NeoOffice_Badge
	goto_if_ge VAR_NEO_RANGER_RANK, RANGER_RANK_RANGER, NeoOffice_Install
	setvar VAR_NEO_RANGER_RANK, RANGER_RANK_RANGER
NeoOffice_Install:
	setvar VAR_NEO_CH3_STEP, 6
	msgbox NeoOffice_Certified, MSGBOX_DEFAULT
NeoOffice_Tunnel:
	msgbox NeoOffice_Inspect, MSGBOX_DEFAULT
	release
	end
NeoOffice_Badge:
	msgbox NeoOffice_OneBadge, MSGBOX_DEFAULT
	release
	end
NeoOffice_Early:
	msgbox NeoOffice_Notice, MSGBOX_DEFAULT
	release
	end
NeoOffice_Report:
	setvar VAR_NEO_CH3_STEP, 9
	call NeoOffice_MissionCredit
	msgbox NeoOffice_Log, MSGBOX_DEFAULT
NeoOffice_Complete:
	msgbox NeoOffice_Board, MSGBOX_DEFAULT
	release
	end
NeoOffice_MissionCredit:
	addvar VAR_NEO_RANGER_MISSIONS, 1
	addvar VAR_NEO_RANGER_XP, 100
	setvar VAR_0x8004, 0
	special NeoRangerCreditMissionTraining
	return

NeoOffice_Certified:
	.string "HALE: Briney's report just came in.\n"
	.string "Rusturf missed its check-in.\p"
	.string "Two techs went in before dawn.\n"
	.string "Their names are still on my board.\p"
	.string "You've earned Rank 2, Ranger.\n"
	.string "Hold still. There. Cutter's live.$"

NeoOffice_Inspect:
	.string "Take Route 116 east to Rusturf.\n"
	.string "Cut the branch by the berries.\p"
	.string "Find both technicians.\n"
	.string "Radio me when they're safe.$"

NeoOffice_OneBadge:
	.string "HALE: Briney's report is here.\n"
	.string "Two tunnel techs missed roll call.\p"
	.string "I've got a crew on the radio.\n"
	.string "Bring any Gym badge for Rank 2.\p"
	.string "Then I can issue you a Cutter.$"

NeoOffice_Notice:
	.string "HALE: Follow the supply run from\n"
	.string "the woods to the Route 104 cottage.$"

NeoOffice_Log:
	.string "HALE: Both techs called home.\n"
	.string "I can take their names down now.\p"
	.string "Let's hear what you brought back.\p"
	.string "That's our crew. That's Devon.\n"
	.string "Hear that third call?\p"
	.string "It came before the relay cut out.\n"
	.string "I'll keep the original. Good work.$"

NeoOffice_Board:
	.string "Rusturf rescue complete.\n"
	.string "Both technicians are home safe.$"

