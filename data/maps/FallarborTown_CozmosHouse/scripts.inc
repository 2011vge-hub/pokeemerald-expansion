FallarborTown_CozmosHouse_MapScripts::
	.byte 0

FallarborTown_CozmosHouse_EventScript_ProfCozmo::
	lock
	faceplayer
	goto_if_set FLAG_NEO_METEOR_REPORTED, Fallarbor_NeoSurveyClosed
	goto_if_unset FLAG_NEO_C4_REPORTED, Fallarbor_NeoSurveyWait
	goto_if_unset FLAG_BADGE02_GET, Fallarbor_NeoSurveyWait
	goto_if_set FLAG_NEO_METEOR_BRIEF, Fallarbor_NeoSurveyDirections
	msgbox Fallarbor_NeoSurveyOffer, MSGBOX_YESNO
	goto_if_ne VAR_RESULT, YES, Fallarbor_NeoSurveyLater
	setflag FLAG_NEO_METEOR_BRIEF
Fallarbor_NeoSurveyDirections:
	msgbox Fallarbor_NeoSurveyDirectionsText, MSGBOX_DEFAULT
	release
	end

FallarborTown_CozmosHouse_EventScript_PlayerHasMeteorite::
	call_if_unset FLAG_TEMP_2, FallarborTown_CozmosHouse_EventScript_NoticeMeteorite
	call_if_set FLAG_TEMP_2, FallarborTown_CozmosHouse_EventScript_AskForMeteorite
	goto_if_eq VAR_RESULT, NO, FallarborTown_CozmosHouse_EventScript_DeclineGiveMeteorite
	msgbox FallarborTown_CozmosHouse_Text_PleaseUseThisTM, MSGBOX_DEFAULT
	giveitem ITEM_TM_RETURN
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setvar VAR_0x8004, ITEM_METEORITE
	call Common_EventScript_PlayerHandedOverTheItem
	setflag FLAG_RECEIVED_TM_RETURN
	msgbox FallarborTown_CozmosHouse_Text_ReallyGoingToHelpMyResearch, MSGBOX_DEFAULT
	release
	end

FallarborTown_CozmosHouse_EventScript_NoticeMeteorite::
	msgbox FallarborTown_CozmosHouse_Text_MeteoriteWillNeverBeMineNow, MSGBOX_DEFAULT
	msgbox FallarborTown_CozmosHouse_Text_IsThatMeteoriteMayIHaveIt, MSGBOX_YESNO
	return

FallarborTown_CozmosHouse_EventScript_AskForMeteorite::
	msgbox FallarborTown_CozmosHouse_Text_MayIHaveMeteorite, MSGBOX_YESNO
	return

FallarborTown_CozmosHouse_EventScript_DeclineGiveMeteorite::
	setflag FLAG_TEMP_2
	msgbox FallarborTown_CozmosHouse_Text_CrushedWithDisappointment, MSGBOX_DEFAULT
	release
	end

FallarborTown_CozmosHouse_EventScript_GaveMeteorite::
	msgbox FallarborTown_CozmosHouse_Text_ReallyGoingToHelpMyResearch, MSGBOX_DEFAULT
	release
	end

FallarborTown_CozmosHouse_EventScript_CozmosWife::
	msgbox Fallarbor_NeoStationText, MSGBOX_NPC
	end

FallarborTown_CozmosHouse_EventScript_CozmoIsSad::
	msgbox FallarborTown_CozmosHouse_Text_FeelSorryForCozmo, MSGBOX_DEFAULT
	release
	end

FallarborTown_CozmosHouse_EventScript_CozmoIsHappy::
	msgbox FallarborTown_CozmosHouse_Text_CozmoIsSoHappy, MSGBOX_DEFAULT
	release
	end

FallarborTown_CozmosHouse_Text_MeteoriteWillNeverBeMineNow:
	.string "PROF. COZMO: Oh…\n"
	.string "I never should have let myself be\l"
	.string "conned into telling TEAM MAGMA where\l"
	.string "you can find METEORITES…\p"
	.string "That METEORITE from METEOR FALLS…\n"
	.string "It's never going to be mine now…$"

FallarborTown_CozmosHouse_Text_IsThatMeteoriteMayIHaveIt:
	.string "Oh!\n"
	.string "Hah?\p"
	.string "That item…\p"
	.string "Could it be?\p"
	.string "Is it the METEORITE that TEAM MAGMA\n"
	.string "took from METEOR FALLS?\p"
	.string "Please, may I have it?\p"
	.string "I'm not asking for it for free.\n"
	.string "How about in exchange for this TM?$"

FallarborTown_CozmosHouse_Text_PleaseUseThisTM:
	.string "PROF. COZMO: This TM, it represents\n"
	.string "my feeling of gratitude.\l"
	.string "Please use it!$"

FallarborTown_CozmosHouse_Text_ReallyGoingToHelpMyResearch:
	.string "PROF. COZMO: Oh, I can't believe it.\n"
	.string "This is really, really great!\p"
	.string "This is really going to help my research!$"

FallarborTown_CozmosHouse_Text_CrushedWithDisappointment:
	.string "PROF. COZMO: Oh, but…\n"
	.string "I'm crushed with disappointment…$"

FallarborTown_CozmosHouse_Text_MayIHaveMeteorite:
	.string "PROF. COZMO: Please, may I have that\n"
	.string "METEORITE?\p"
	.string "I'm not asking for it for free.\n"
	.string "How about in exchange for this TM?$"

FallarborTown_CozmosHouse_Text_CozmoWentToMeteorFalls:
	.string "PROF. COZMO went off to METEOR FALLS\n"
	.string "on ROUTE 114 with some people from\l"
	.string "TEAM MAGMA.$"

FallarborTown_CozmosHouse_Text_FeelSorryForCozmo:
	.string "Poor PROF. COZMO…\n"
	.string "He's so depressed… I feel sorry for him.$"

FallarborTown_CozmosHouse_Text_CozmoIsSoHappy:
	.string "Look at PROF. COZMO…\n"
	.string "He's so happy! I think it's cute.$"


Fallarbor_NeoSurveyWait:
	msgbox Fallarbor_NeoSurveyWaitText, MSGBOX_DEFAULT
	release
	end
Fallarbor_NeoSurveyLater:
	msgbox Fallarbor_NeoSurveyLaterText, MSGBOX_DEFAULT
	release
	end
Fallarbor_NeoSurveyClosed:
	msgbox Fallarbor_NeoSurveyClosedText, MSGBOX_DEFAULT
	release
	end
Fallarbor_NeoSurveyOffer:
	.string "RESEARCH AIDE: FLINT's cave\n"
	.string "comparison reached COZMO.\p"
	.string "Will you help check his crew\n"
	.string "and their readings?$"
Fallarbor_NeoSurveyDirectionsText:
	.string "NEXT: ROUTE 114, METEOR FALLS.\p"
	.string "Speak to both surveyors.\n"
	.string "Then report to COZMO there.$"
Fallarbor_NeoSurveyWaitText:
	.string "RESEARCH AIDE: Our station\n"
	.string "supports the inland surveys.\p"
	.string "Finish DEWFORD's case and earn\n"
	.string "the RELIC BADGE first.$"
Fallarbor_NeoSurveyLaterText:
	.string "RESEARCH AIDE: Come back\n"
	.string "whenever you're ready.$"
Fallarbor_NeoSurveyClosedText:
	.string "RESEARCH AIDE: The crew is safe.\p"
	.string "COZMO sent the readings to\n"
	.string "FLANNERY in LAVARIDGE.$"
Fallarbor_NeoStationText:
	.string "This is our field research office.\p"
	.string "The old observatory records help\n"
	.string "us understand today's changes.$"
