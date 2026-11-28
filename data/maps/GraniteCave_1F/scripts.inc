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


@ Refuge survey: preserve the two existing persistent checks and guide incomplete visits.
GraniteCave_NeoSurvey:
	goto_if_set FLAG_NEO_C4_SURVEY, GraniteCave_NeoSurveyReminder
	goto_if_unset FLAG_NEO_C4_BRIEF, GraniteCave_NeoAwait
	goto_if_unset FLAG_NEO_C4_CREW_CHECKED, GraniteCave_NeoCrewMissing
	goto_if_unset FLAG_NEO_C4_READING_CHECKED, GraniteCave_NeoReadingMissing
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
	.string "HIKER: Thanks for checking both.\n"
	.string "The crew is safe for now.\p"
	.string "CAYTON wants to compare these\n"
	.string "tremors with his inland site.\p"
	.string "Take a copy of our report to HALE.$"
GraniteCave_NeoSurveyReminderText:
	.string "NEXT: BRINEY at the DEWFORD dock.\p"
	.string "Sail to SLATEPORT. Find STERN\n"
	.string "at his shipyard.$"
GraniteCave_NeoAwaitText:
	.string "HIKER: Speak to BRAWLY about\n"
	.string "the survey before you go deeper.$"

GraniteCave_NeoCrewMissing:
	goto_if_unset FLAG_NEO_C4_READING_CHECKED, GraniteCave_NeoRefugeDirections
	msgbox GraniteCave_NeoCrewMissingText, MSGBOX_DEFAULT
	release
	end
GraniteCave_NeoReadingMissing:
	msgbox GraniteCave_NeoReadingMissingText, MSGBOX_DEFAULT
	release
	end
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
GraniteCave_NeoWarden::
	msgbox GraniteCave_NeoRefugeDirectionsText, MSGBOX_NPC
	end
GraniteCave_NeoRefugeChild::
	msgbox GraniteCave_NeoChildText, MSGBOX_NPC
	end
GraniteCave_NeoChildText:
	.string "Grandpa used to dive for stone.\p"
	.string "Now he knocks on every bunk at\n"
	.string "lights-out. Even the empty ones.$"
GraniteCave_NeoRefugeDirectionsText:
	.string "Take the ladder by the crates.\p"
	.string "Check the bunk warden, then the\n"
	.string "gauge keeper east of the bunks.\p"
	.string "Bring both reports to the Hiker\n"
	.string "at the cave mouth.$"
GraniteCave_NeoCrewMissingText:
	.string "HIKER: I have the gauge readings.\n"
	.string "We still need the crew report.\p"
	.string "Take the ladder by the crates.\n"
	.string "Speak to the worker in the bunks.$"
GraniteCave_NeoReadingMissingText:
	.string "HIKER: The crew is accounted for.\n"
	.string "We still need the gauge readings.\p"
	.string "Take the ladder, then go east\n"
	.string "from the bunks to the survey room.$"
GraniteCave_NeoCrewText:
	.string "WORKER: Everyone is accounted\n"
	.string "for. Our supplies are dry.\p"
	.string "We'll stay clear of the lower\n"
	.string "caves until the survey is done.$"
GraniteCave_NeoReadingText:
	.string "SURVEYOR: The rock has shifted.\p"
	.string "CAYTON's inland team needs\n"
	.string "a copy of these readings.$"
GraniteCave_NeoSuppliesText:
	.string "Emergency shelter supplies.\n"
	.string "Water, blankets and ropes.$"
