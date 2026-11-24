RustboroCity_Flat1_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, NeoOffice_SetRival
	.byte 0

NeoOffice_SetRival:
	call Common_EventScript_SetupRivalGfxId
	end

NeoOffice_Rival::
	lock
	faceplayer
	checkplayergender
	bufferstring STR_VAR_1, NeoOffice_Nessa
	goto_if_eq VAR_RESULT, MALE, NeoOffice_Greet
	bufferstring STR_VAR_1, NeoOffice_Vern
NeoOffice_Greet:
	goto_if_ne VAR_NEO_ASSIGNMENT, 1, NeoOffice_RivalRepeat
	msgbox NeoOffice_Welcome, MSGBOX_DEFAULT
	setvar VAR_NEO_ASSIGNMENT, 2
NeoOffice_RivalRepeat:
	goto_if_ge VAR_NEO_ASSIGNMENT, 3, NeoOffice_RivalLater
	msgbox NeoOffice_Woods, MSGBOX_DEFAULT
	goto_if_set FLAG_NEO_RIVAL_SPARRED, NeoOffice_EndSpar
	msgbox NeoOffice_Offer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, NeoOffice_EndSpar
	checkplayergender
	goto_if_eq VAR_RESULT, FEMALE, NeoOffice_VernBattle
	goto NeoOffice_NessaBattle
NeoOffice_RivalLater:
	msgbox NeoOffice_Later, MSGBOX_DEFAULT
NeoOffice_EndSpar:
	release
	end

NeoOffice_Hale::
	lock
	faceplayer
	goto_if_lt VAR_NEO_ASSIGNMENT, 5, NeoOffice_Early
	goto_if_eq VAR_NEO_ASSIGNMENT, 9, NeoOffice_Complete
	goto_if_eq VAR_NEO_ASSIGNMENT, 10, NeoOffice_Early
	goto_if_eq VAR_NEO_ASSIGNMENT, 8, NeoOffice_Report
	goto_if_ge VAR_NEO_ASSIGNMENT, 6, NeoOffice_Tunnel
	call MossdeepCity_RangerBase_2F_EventScript_CountBadges
	goto_if_eq VAR_0x8004, 0, NeoOffice_Badge
	goto_if_ge VAR_NEO_RANGER_RANK, RANGER_RANK_RANGER, NeoOffice_Install
	setvar VAR_NEO_RANGER_RANK, RANGER_RANK_RANGER
NeoOffice_Install:
	setvar VAR_NEO_ASSIGNMENT, 6
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
	clearflag FLAG_HIDE_ROUTE_116_DEVON_EMPLOYEE
	setvar VAR_NEO_ASSIGNMENT, 9
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

NeoOffice_Nessa:
	.string "NESSA$"

NeoOffice_Vern:
	.string "VERN$"

NeoOffice_Welcome:
	.string "{STR_VAR_1}: Dad said you'd come.\p"
	.string "That's my bunk under the chart.\n"
	.string "We gave our rooms to the evacuees.$"

NeoOffice_Woods:
	.string "{STR_VAR_1}: Meet me in the woods\n"
	.string "south of campus. Check the gauges.$"

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
	.string "The field study board is open.$"

NeoOffice_NessaBattle:
	switch VAR_STARTER_MON
	case 0, NeoSpar_NessaSpheal
	case 1, NeoSpar_NessaShroomish
	case 2, NeoSpar_NessaPoochyena
	goto NeoOffice_EndSpar
NeoSpar_NessaSpheal:
	trainerbattle_no_intro TRAINER_NEO_NESSA_SPHEAL, NeoOffice_SparLoss
	setflag FLAG_NEO_RIVAL_SPARRED
	goto NeoOffice_EndSpar
NeoSpar_NessaShroomish:
	trainerbattle_no_intro TRAINER_NEO_NESSA_SHROOMISH, NeoOffice_SparLoss
	setflag FLAG_NEO_RIVAL_SPARRED
	goto NeoOffice_EndSpar
NeoSpar_NessaPoochyena:
	trainerbattle_no_intro TRAINER_NEO_NESSA_POOCHYENA, NeoOffice_SparLoss
	setflag FLAG_NEO_RIVAL_SPARRED
	goto NeoOffice_EndSpar

NeoOffice_VernBattle:
	switch VAR_STARTER_MON
	case 0, NeoSpar_VernSpheal
	case 1, NeoSpar_VernShroomish
	case 2, NeoSpar_VernPoochyena
	goto NeoOffice_EndSpar
NeoSpar_VernSpheal:
	trainerbattle_no_intro TRAINER_NEO_VERN_SPHEAL, NeoOffice_SparLoss
	setflag FLAG_NEO_RIVAL_SPARRED
	goto NeoOffice_EndSpar
NeoSpar_VernShroomish:
	trainerbattle_no_intro TRAINER_NEO_VERN_SHROOMISH, NeoOffice_SparLoss
	setflag FLAG_NEO_RIVAL_SPARRED
	goto NeoOffice_EndSpar
NeoSpar_VernPoochyena:
	trainerbattle_no_intro TRAINER_NEO_VERN_POOCHYENA, NeoOffice_SparLoss
	setflag FLAG_NEO_RIVAL_SPARRED
	goto NeoOffice_EndSpar

NeoOffice_SparLoss:
	.string "Now I know who has my back.$"
NeoOffice_Offer:
	.string "One practice round before we go?$"
NeoOffice_Later:
	.string "Check in with Dad. His desk has\n"
	.string "the latest assignment.$"

NeoBoard::
	lock
	goto_if_ne VAR_NEO_ASSIGNMENT, 9, NeoBoardClosed
	msgbox NeoBoardOpen, MSGBOX_DEFAULT
	release
	end
NeoBoardClosed:
	msgbox NeoBoardPending, MSGBOX_DEFAULT
	release
	end
NeoBoardOpen:
	.string "OPEN FIELD STUDIES\n"
	.string "Equipment inventory: Route 116\p"
	.string "Canopy inspection: Petalburg Woods\n"
	.string "Emergency blankets: Route 104$"
NeoBoardPending:
	.string "Regional assignments await clearance.$"

NeoStudyFiled:
	.string "Field report already on file.$"
