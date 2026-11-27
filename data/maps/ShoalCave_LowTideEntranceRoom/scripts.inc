ShoalCave_LowTideEntranceRoom_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, ShoalCave_LowTideEntranceRoom_OnTransition
	.byte 0

ShoalCave_LowTideEntranceRoom_OnTransition:
	special UpdateShoalTideFlag
	goto_if_set FLAG_SYS_SHOAL_TIDE, ShoalCave_LowTideEntranceRoom_EventScript_SetHighTide
	goto ShoalCave_LowTideEntranceRoom_EventScript_SetLowTide

ShoalCave_LowTideEntranceRoom_EventScript_SetHighTide::
	setmaplayoutindex LAYOUT_SHOAL_CAVE_HIGH_TIDE_ENTRANCE_ROOM
	end

ShoalCave_LowTideEntranceRoom_EventScript_SetLowTide::
	setmaplayoutindex LAYOUT_SHOAL_CAVE_LOW_TIDE_ENTRANCE_ROOM
	end

ShoalCave_LowTideEntranceRoom_EventScript_ShellBellExpert::
	lock
	faceplayer
	goto_if_unset FLAG_BADGE05_GET, ShoalCave_NeoCraft
	msgbox ShoalCave_NeoOfferText, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, ShoalCave_NeoRecord
ShoalCave_NeoCraft:
	dotimebasedevents
	call_if_set FLAG_SYS_SHOAL_ITEM, ShoalCave_LowTideEntranceRoom_EventScript_ResetShoalItems
	checkitem ITEM_SHOAL_SALT, 4
	goto_if_eq VAR_RESULT, FALSE, ShoalCave_LowTideEntranceRoom_EventScript_NotEnoughShoalSaltOrShells
	checkitem ITEM_SHOAL_SHELL, 4
	goto_if_eq VAR_RESULT, FALSE, ShoalCave_LowTideEntranceRoom_EventScript_NotEnoughShoalSaltOrShells
	msgbox ShoalCave_LowTideEntranceRoom_Text_WouldYouLikeShellBell, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, ShoalCave_LowTideEntranceRoom_EventScript_DeclineShellBell
	checkitemspace ITEM_SHELL_BELL
	call_if_eq VAR_RESULT, FALSE, ShoalCave_LowTideEntranceRoom_EventScript_CheckSpaceWillBeFreed
	goto_if_eq VAR_RESULT, 2, ShoalCave_LowTideEntranceRoom_EventScript_NoRoomForShellBell
	msgbox ShoalCave_LowTideEntranceRoom_Text_MakeShellBellRightAway, MSGBOX_DEFAULT
	removeitem ITEM_SHOAL_SALT, 4
	removeitem ITEM_SHOAL_SHELL, 4
	giveitem ITEM_SHELL_BELL
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull  @ Never FALSE, we already made sure there will be room in the bag.
	msgbox ShoalCave_LowTideEntranceRoom_Text_ExplainShellBell, MSGBOX_DEFAULT
	setflag FLAG_TEMP_2  @ Not read. Perhaps meant to stop him from re-explaining the Shell Bell if multiple are received in one sitting.
	release
	end

@ If the bag is full, check if a slot will be freed when 4 Shoal Salt or Shells are given
ShoalCave_LowTideEntranceRoom_EventScript_CheckSpaceWillBeFreed::
	checkitem ITEM_SHOAL_SALT, 5
	goto_if_eq VAR_RESULT, TRUE, ShoalCave_LowTideEntranceRoom_EventScript_CheckSpaceWillBeFreedShells
	return

ShoalCave_LowTideEntranceRoom_EventScript_CheckSpaceWillBeFreedShells::
	checkitem ITEM_SHOAL_SHELL, 5
	goto_if_eq VAR_RESULT, TRUE, ShoalCave_LowTideEntranceRoom_EventScript_NoSpaceWillBeFreed
	return

ShoalCave_LowTideEntranceRoom_EventScript_NoSpaceWillBeFreed::
	setvar VAR_RESULT, 2
	return

ShoalCave_LowTideEntranceRoom_EventScript_NoRoomForShellBell::
	msgbox ShoalCave_LowTideEntranceRoom_Text_NoSpaceInYourBag, MSGBOX_DEFAULT
	release
	end

ShoalCave_LowTideEntranceRoom_EventScript_NotEnoughShoalSaltOrShells::
	checkitem ITEM_SHOAL_SALT
	goto_if_eq VAR_RESULT, TRUE, ShoalCave_LowTideEntranceRoom_EventScript_HasSomeShoalSaltOrShell
	checkitem ITEM_SHOAL_SHELL
	goto_if_eq VAR_RESULT, TRUE, ShoalCave_LowTideEntranceRoom_EventScript_HasSomeShoalSaltOrShell
	msgbox ShoalCave_LowTideEntranceRoom_Text_AreYouPlanningOnGoingInThere, MSGBOX_DEFAULT
	release
	end

ShoalCave_LowTideEntranceRoom_EventScript_HasSomeShoalSaltOrShell::
	msgbox ShoalCave_LowTideEntranceRoom_Text_BringMe4ShoalSaltAndShells, MSGBOX_DEFAULT
	release
	end

ShoalCave_LowTideEntranceRoom_EventScript_DeclineShellBell::
	msgbox ShoalCave_LowTideEntranceRoom_Text_WantedToMakeShellBell, MSGBOX_DEFAULT
	release
	end

ShoalCave_LowTideEntranceRoom_EventScript_ResetShoalItems::
	clearflag FLAG_RECEIVED_SHOAL_SALT_1
	clearflag FLAG_RECEIVED_SHOAL_SALT_2
	clearflag FLAG_RECEIVED_SHOAL_SALT_3
	clearflag FLAG_RECEIVED_SHOAL_SALT_4
	clearflag FLAG_RECEIVED_SHOAL_SHELL_1
	clearflag FLAG_RECEIVED_SHOAL_SHELL_2
	clearflag FLAG_RECEIVED_SHOAL_SHELL_3
	clearflag FLAG_RECEIVED_SHOAL_SHELL_4
	clearflag FLAG_SYS_SHOAL_ITEM
	return

ShoalCave_NeoRecord:
	goto_if_set FLAG_NEO_SHOAL_REPORTED, ShoalCave_NeoReported
	goto_if_set FLAG_SYS_SHOAL_TIDE, ShoalCave_NeoHigh
	setflag FLAG_NEO_SHOAL_LOW_RECORDED
	msgbox ShoalCave_NeoLowText, MSGBOX_DEFAULT
	goto ShoalCave_NeoCheck
ShoalCave_NeoHigh:
	setflag FLAG_NEO_SHOAL_HIGH_RECORDED
	msgbox ShoalCave_NeoHighText, MSGBOX_DEFAULT
ShoalCave_NeoCheck:
	goto_if_unset FLAG_NEO_SHOAL_LOW_RECORDED, ShoalCave_NeoReturn
	goto_if_unset FLAG_NEO_SHOAL_HIGH_RECORDED, ShoalCave_NeoReturn
	setflag FLAG_NEO_SHOAL_REPORTED
	call NeoOffice_MissionCredit
ShoalCave_NeoReported:
	msgbox ShoalCave_NeoReportedText, MSGBOX_DEFAULT
	release
	end
ShoalCave_NeoReturn:
	msgbox ShoalCave_NeoReturnText, MSGBOX_DEFAULT
	release
	end
ShoalCave_NeoOfferText:
	.string "GLACIA studies our changing ice.\p"
	.string "Would you record this tide\n"
	.string "for her research?$"
ShoalCave_NeoLowText:
	.string "Low tide reading recorded.\n"
	.string "The ice edge has retreated.$"
ShoalCave_NeoHighText:
	.string "High tide reading recorded.\n"
	.string "The water reaches new marks.$"
ShoalCave_NeoReturnText:
	.string "Come back at the opposite tide.\p"
	.string "This survey can wait. You don't\n"
	.string "need it for your main assignment.$"
ShoalCave_NeoReportedText:
	.string "Both tide records are complete.\p"
	.string "I'll send them to GLACIA.\n"
	.string "Thank you for your help.$"
