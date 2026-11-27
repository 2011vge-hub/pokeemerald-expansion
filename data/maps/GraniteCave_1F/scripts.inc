GraniteCave_1F_MapScripts::
	.byte 0

GraniteCave_1F_EventScript_Hiker::
	lock
	faceplayer
	goto_if_eq VAR_NEO_CH3_STEP, 9, GraniteCave_NeoSurvey
	goto_if_set FLAG_NEO_C1_FLIGHT_RUSTBORO, GraniteCave_NeoAwait
	goto_if_set FLAG_RECEIVED_HM_FLASH, GraniteCave_1F_EventScript_ReceivedFlash
	msgbox GraniteCave_1F_Text_GetsDarkAheadHereYouGo, MSGBOX_DEFAULT
	giveitem ITEM_HM_FLASH
	setflag FLAG_RECEIVED_HM_FLASH
	msgbox GraniteCave_1F_Text_ExplainFlash, MSGBOX_DEFAULT
	release
	end

GraniteCave_1F_EventScript_ReceivedFlash::
	msgbox GraniteCave_1F_Text_ExplainFlash, MSGBOX_DEFAULT
	release
	end

GraniteCave_1F_Text_GetsDarkAheadHereYouGo:
	.string "Hey, you.\n"
	.string "It gets awfully dark ahead.\l"
	.string "It'll be tough trying to explore.\p"
	.string "That guy who came by earlier…\n"
	.string "STEVEN, I think it was.\p"
	.string "He knew how to use FLASH, so he ought\n"
	.string "to be all right, but…\p"
	.string "Well, for us HIKERS, helping out those\n"
	.string "that we meet is our motto.\p"
	.string "Here you go, I'll pass this on to you.$"

GraniteCave_1F_Text_ExplainFlash:
	.string "Teach that hidden move FLASH to\n"
	.string "a POKéMON and use it.\p"
	.string "It lights up even the inky darkness\n"
	.string "of caves.\p"
	.string "But, to use it, you need the GYM BADGE\n"
	.string "from DEWFORD's POKéMON GYM.$"


@ Interim entrance-level survey. Expanded cave settlement/refuge assets remain pending.
GraniteCave_NeoSurvey:
	goto_if_set FLAG_NEO_C4_SURVEY, GraniteCave_NeoSurveyReminder
	goto_if_unset FLAG_NEO_C4_BRIEF, GraniteCave_NeoAwait
	goto_if_unset FLAG_NEO_C4_CREW_CHECKED, GraniteCave_NeoRefugeDirections
	goto_if_unset FLAG_NEO_C4_READING_CHECKED, GraniteCave_NeoRefugeDirections
	msgbox GraniteCave_NeoSurveyText, MSGBOX_DEFAULT
	setflag FLAG_NEO_C4_SURVEY
GraniteCave_NeoSurveyReminder:
	msgbox GraniteCave_NeoSurveyReminderText, MSGBOX_DEFAULT
	release
	end
GraniteCave_NeoAwait:
	msgbox GraniteCave_NeoAwaitText, MSGBOX_DEFAULT
	release
	end
GraniteCave_NeoSurveyText:
	.string "HIKER: Our crew is safe, but the\n"
	.string "rock survey has changed.\p"
	.string "FLINT asked us to compare these\n"
	.string "readings with his inland site.\p"
	.string "Here, copy the report for HALE.$"
GraniteCave_NeoSurveyReminderText:
	.string "NEXT: Speak to BRINEY at the\n"
	.string "DEWFORD dock, then return to\l"
	.string "HALE in RUSTBORO.$"
GraniteCave_NeoAwaitText:
	.string "HIKER: Speak to BRAWLY about\n"
	.string "the survey before you go deeper.$"

GraniteCave_NeoRefugeDirections:
	msgbox GraniteCave_NeoRefugeDirectionsText, MSGBOX_DEFAULT
	release
	end
GraniteCave_NeoRefugeCrew::
	lock
	faceplayer
	goto_if_unset FLAG_NEO_C4_BRIEF, GraniteCave_NeoAwait
	msgbox GraniteCave_NeoCrewText, MSGBOX_DEFAULT
	setflag FLAG_NEO_C4_CREW_CHECKED
	release
	end
GraniteCave_NeoRefugeSurveyor::
	lock
	faceplayer
	goto_if_unset FLAG_NEO_C4_BRIEF, GraniteCave_NeoAwait
	msgbox GraniteCave_NeoReadingText, MSGBOX_DEFAULT
	setflag FLAG_NEO_C4_READING_CHECKED
	release
	end
GraniteCave_NeoSupplies::
	msgbox GraniteCave_NeoSuppliesText, MSGBOX_SIGN
	end
GraniteCave_NeoRefugeDirectionsText:
	.string "HIKER: Check the two people\n"
	.string "at the shelter just west of here.\p"
	.string "Check the crew and the readings.\n"
	.string "Then come back to me.$"
GraniteCave_NeoCrewText:
	.string "WORKER: Everyone is accounted\n"
	.string "for. Our supplies are dry.\p"
	.string "We'll stay clear of the lower\n"
	.string "caves until the survey is done.$"
GraniteCave_NeoReadingText:
	.string "SURVEYOR: The rock has shifted.\p"
	.string "FLINT's inland team needs\n"
	.string "a copy of these readings.$"
GraniteCave_NeoSuppliesText:
	.string "Emergency shelter supplies.\n"
	.string "Water, blankets and ropes.$"
