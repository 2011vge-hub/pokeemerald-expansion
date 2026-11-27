MossdeepCity_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MossdeepCity_OnTransition
	.byte 0

MossdeepCity_RangerCheckIn:
	lock
	faceplayer
	goto_if_ge VAR_NEO_FERRY_DISPATCH, 3, MossdeepCity_RangerCheckedIn
	msgbox MossdeepCity_Text_RangerTickets, MSGBOX_DEFAULT
	setvar VAR_NEO_FERRY_DISPATCH, 3
	release
	end

MossdeepCity_RangerCheckedIn:
	goto_if_ge VAR_NEO_FERRY_DISPATCH, 4, MossdeepCity_RangerAllAboard
	msgbox MossdeepCity_Text_RangerStillMissing, MSGBOX_DEFAULT
	release
	end

MossdeepCity_RangerAllAboard:
	msgbox MossdeepCity_Text_RangerAllAboard, MSGBOX_DEFAULT
	release
	end

MossdeepCity_Text_RangerAllAboard:
	.string "SAILOR: Head count's complete.\n"
	.string "Every ticket accounted for.\p"
	.string "You did good, Ranger. Real good.$"

MossdeepCity_Text_RangerStillMissing:
	.string "SAILOR: The kid and his POOCHYENA\n"
	.string "are still missing. Check the MART.\p"
	.string "Watch the lower stairs, Ranger.\n"
	.string "The water keeps climbing.$"

MossdeepCity_Text_RangerTickets:
	.string "SAILOR: Two tickets left, Ranger.\p"
	.string "That kid was right here a minute\n"
	.string "ago. Said his POOCHYENA was scared.\p"
	.string "Then I saw him running back toward\n"
	.string "the market.$"

MossdeepCity_OnTransition:
	setflag FLAG_HIDE_MOSSDEEP_CITY_TEAM_MAGMA
	call_if_set FLAG_SYS_WEATHER_CTRL, Common_EventScript_SetAbnormalWeather
	call MossdeepCity_EventScript_RangerRescueVisibility
	end

@ Sync whether the rescuees are visible on the landing each time Mossdeep loads.
MossdeepCity_EventScript_RangerRescueVisibility:
	setflag FLAG_NEO_HIDE_LANDING_RESCUEES
	goto_if_ge VAR_NEO_FERRY_DISPATCH, 4, MossdeepCity_EventScript_RangerRescueVisibilityDone
	clearflag FLAG_NEO_HIDE_LANDING_RESCUEES
MossdeepCity_EventScript_RangerRescueVisibilityDone:
	return

MossdeepCity_EventScript_PokefanF::
	msgbox MossdeepCity_NeoShelterText, MSGBOX_NPC
	end

MossdeepCity_EventScript_PokefanFMagmaGone::
	msgbox MossdeepCity_Text_SpaceCenterLaunchingRockets, MSGBOX_DEFAULT
	release
	end

MossdeepCity_EventScript_Sailor::
	goto_if_ge VAR_NEO_FERRY_DISPATCH, 2, MossdeepCity_RangerCheckIn
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_HM_DIVE, MossdeepCity_EventScript_SailorMagmaGone
	msgbox MossdeepCity_Text_MossdeepTargetedByMagma, MSGBOX_DEFAULT
	release
	end

MossdeepCity_EventScript_SailorMagmaGone::
	msgbox MossdeepCity_Text_FeelReliefOnLand, MSGBOX_DEFAULT
	release
	end

MossdeepCity_EventScript_NinjaBoy::
	goto_if_ge VAR_NEO_FERRY_DISPATCH, 3, MossdeepCity_RangerWestStairWitness
	msgbox MossdeepCity_Text_WailmerWatching, MSGBOX_NPC
	end

MossdeepCity_RangerWestStairWitness:
	msgbox MossdeepCity_Text_WestStairWitness, MSGBOX_NPC
	end

MossdeepCity_Text_WestStairWitness:
	.string "The lower stairs are soaked!\n"
	.string "I heard the railing buckle.\p"
	.string "Look for higher ground near\n"
	.string "the shops, Ranger.$"

MossdeepCity_EventScript_ExpertM::
	msgbox MossdeepCity_Text_LifeNeedsSeaToLive, MSGBOX_NPC
	end

MossdeepCity_EventScript_Girl::
	goto_if_ge VAR_NEO_FERRY_DISPATCH, 3, MossdeepCity_RangerMarketWitness
	msgbox MossdeepCity_Text_NiceIfWorldCoveredByFlowers, MSGBOX_NPC
	end

MossdeepCity_RangerMarketWitness:
	msgbox MossdeepCity_Text_MarketWitness, MSGBOX_NPC
	end

MossdeepCity_Text_MarketWitness:
	.string "A boy passed through here,\n"
	.string "calling for his POOCHYENA.\p"
	.string "The MART is still open, but\n"
	.string "the lower street is flooding.$"

MossdeepCity_EventScript_Woman::
	msgbox MossdeepCity_Text_SpecialSpaceCenterRock, MSGBOX_NPC
	end

MossdeepCity_EventScript_WhiteRock::
	msgbox MossdeepCity_Text_ItsAWhiteRock, MSGBOX_SIGN
	end

@ Former Gym is retired; its entrance now leads to Ranger Headquarters.
MossdeepCity_EventScript_CitySign::
	msgbox MossdeepCity_Text_CitySign, MSGBOX_SIGN
	end

MossdeepCity_EventScript_SpaceCenterSign::
	msgbox MossdeepCity_Text_SpaceCenterSign, MSGBOX_SIGN
	end

MossdeepCity_EventScript_VisitedMossdeep::
	setflag FLAG_VISITED_MOSSDEEP_CITY
	setvar VAR_TEMP_1, 1
	end

MossdeepCity_EventScript_TeamMagmaEnterSpaceCenter::
	lockall
	applymovement LOCALID_MOSSDEEP_MAXIE, MossdeepCity_Movement_MaxieGestureToSpaceCenter
	waitmovement 0
	applymovement LOCALID_MOSSDEEP_GRUNT_1, MossdeepCity_Movement_GruntFaceSpaceCenter
	applymovement LOCALID_MOSSDEEP_GRUNT_2, MossdeepCity_Movement_GruntFaceSpaceCenter
	applymovement LOCALID_MOSSDEEP_GRUNT_3, MossdeepCity_Movement_GruntFaceSpaceCenter
	applymovement LOCALID_MOSSDEEP_GRUNT_4, MossdeepCity_Movement_GruntFaceSpaceCenter
	waitmovement 0
	applymovement LOCALID_MOSSDEEP_MAXIE, MossdeepCity_Movement_MaxieEnterSpaceCenter
	applymovement LOCALID_MOSSDEEP_GRUNT_1, MossdeepCity_Movement_Grunt1EnterSpaceCenter
	applymovement LOCALID_MOSSDEEP_GRUNT_2, MossdeepCity_Movement_Grunt2EnterSpaceCenter
	applymovement LOCALID_MOSSDEEP_GRUNT_3, MossdeepCity_Movement_Grunt3EnterSpaceCenter
	applymovement LOCALID_MOSSDEEP_GRUNT_4, MossdeepCity_Movement_Grunt4EnterSpaceCenter
	waitmovement 0
	removeobject LOCALID_MOSSDEEP_MAXIE
	removeobject LOCALID_MOSSDEEP_GRUNT_1
	removeobject LOCALID_MOSSDEEP_GRUNT_2
	removeobject LOCALID_MOSSDEEP_GRUNT_3
	removeobject LOCALID_MOSSDEEP_GRUNT_4
	delay 30
	setvar VAR_MOSSDEEP_CITY_STATE, 2
	setflag FLAG_HIDE_MOSSDEEP_CITY_TEAM_MAGMA
	releaseall
	end

MossdeepCity_Movement_MaxieGestureToSpaceCenter:
	delay_16
	face_right
	delay_16
	delay_16
	delay_16
	delay_16
	face_left
	delay_16
	delay_16
	step_end

MossdeepCity_Movement_GruntFaceSpaceCenter:
	face_right
	delay_16
	delay_16
	delay_16
	step_end

MossdeepCity_Movement_MaxieEnterSpaceCenter:
	walk_down
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MossdeepCity_Movement_Grunt1EnterSpaceCenter:
	delay_16
	delay_8
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MossdeepCity_Movement_Grunt2EnterSpaceCenter:
	delay_16
	delay_8
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MossdeepCity_Movement_Grunt3EnterSpaceCenter:
	delay_16
	delay_8
	walk_down
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MossdeepCity_Movement_Grunt4EnterSpaceCenter:
	delay_16
	delay_8
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MossdeepCity_EventScript_Man::
	lock
	faceplayer
	msgbox MossdeepCity_Text_SurfExhilarating, MSGBOX_DEFAULT
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

MossdeepCity_EventScript_KingsRockBoy::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_KINGS_ROCK, MossdeepCity_EventScript_ReceivedKingsRock
	msgbox MossdeepCity_Text_WantKingsRockStevenGaveMe, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MossdeepCity_EventScript_DeclineKingsRock
	msgbox MossdeepCity_Text_YouCanKeepIt, MSGBOX_DEFAULT
	giveitem ITEM_KINGS_ROCK
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_KINGS_ROCK
	release
	end

MossdeepCity_EventScript_ReceivedKingsRock::
	msgbox MossdeepCity_Text_StevensHouseOverThere, MSGBOX_DEFAULT
	release
	end

MossdeepCity_EventScript_DeclineKingsRock::
	msgbox MossdeepCity_Text_WhatToDoWithWeirdRock, MSGBOX_DEFAULT
	release
	end

MossdeepCity_EventScript_BlackBelt::
	msgbox MossdeepCity_Text_SootopolisNewGymLeader, MSGBOX_NPC
	end

MossdeepCity_EventScript_Scott::
	lock
	faceplayer
	msgbox MossdeepCity_Text_ScottSomethingWrongWithTown, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_FACING, DIR_NORTH, MossdeepCity_EventScript_ScottExitNorth
	call_if_eq VAR_FACING, DIR_EAST, MossdeepCity_EventScript_ScottExitEast
	addvar VAR_SCOTT_STATE, 1
	removeobject LOCALID_MOSSDEEP_SCOTT
	release
	end

MossdeepCity_EventScript_ScottExitNorth::
	applymovement LOCALID_PLAYER, MossdeepCity_Movement_PlayerWatchScottExit
	applymovement LOCALID_MOSSDEEP_SCOTT, MossdeepCity_Movement_ScottExitNorth
	waitmovement 0
	return

MossdeepCity_EventScript_ScottExitEast::
	applymovement LOCALID_PLAYER, MossdeepCity_Movement_PlayerWatchScottExit
	applymovement LOCALID_MOSSDEEP_SCOTT, MossdeepCity_Movement_ScottExitEast
	waitmovement 0
	return

MossdeepCity_Movement_PlayerWatchScottExit:
	delay_16
	delay_16
	walk_in_place_faster_left
	step_end

MossdeepCity_Movement_ScottExitNorth:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

MossdeepCity_Movement_ScottExitEast:
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

MossdeepCity_Text_WantKingsRockStevenGaveMe:
	.string "I got this from STEVEN, but I don't\n"
	.string "know what it's good for.\p"
	.string "I think it's called KING'S ROCK.\n"
	.string "Do you want it?$"

MossdeepCity_Text_YouCanKeepIt:
	.string "Why would you want it?\n"
	.string "You're weird.\p"
	.string "You can keep it, but keep it a secret\n"
	.string "from STEVEN.$"

MossdeepCity_Text_StevensHouseOverThere:
	.string "STEVEN's house is right over there!$"

MossdeepCity_Text_WhatToDoWithWeirdRock:
	.string "Yeah, you think so, too! What are you\n"
	.string "supposed to do with some weird rock?$"

MossdeepCity_Text_WailmerWatching:
	.string "Around MOSSDEEP, you can see wild\n"
	.string "WAILMER.\p"
	.string "It's called, uh…\n"
	.string "What was it now…\p"
	.string "WAI, WAI, WAI…\p"
	.string "WAILMER watching!$"

MossdeepCity_Text_SpaceCenterReceivedLetter:
	.string "The island's SPACE CENTER has been\n"
	.string "launching huge rockets.\p"
	.string "There's been some kind of an uproar\n"
	.string "over a letter they received recently.$"

MossdeepCity_Text_SpaceCenterLaunchingRockets:
	.string "The island's SPACE CENTER has been\n"
	.string "launching huge rockets.$"

MossdeepCity_Text_MossdeepTargetedByMagma:
	.string "I heard from a SAILOR buddy that\n"
	.string "TEAM AQUA set up shop in LILYCOVE.\p"
	.string "I also heard that someone came along\n"
	.string "and wiped the floor with them!\p"
	.string "But MOSSDEEP here's been targeted\n"
	.string "by that TEAM MAGMA.\p"
	.string "If you want to know what they're up to,\n"
	.string "go visit the SPACE CENTER.$"

MossdeepCity_Text_FeelReliefOnLand:
	.string "I'm a SAILOR, so the sea's obviously\n"
	.string "more important to me.\p"
	.string "But you know? When I get back on land\n"
	.string "after a long voyage, I do feel relief!$"

MossdeepCity_Text_NiceIfWorldCoveredByFlowers:
	.string "Wouldn't it be nice?\p"
	.string "If the whole world was covered in\n"
	.string "plants and flowers like this island?$"

MossdeepCity_Text_LifeNeedsSeaToLive:
	.string "All life needs the sea to live, even\n"
	.string "though it makes its home on the land.\p"
	.string "Life, having run its course, becomes\n"
	.string "soil and returns to the land.\p"
	.string "And the sea is always connected to\n"
	.string "the land.\p"
	.string "Yes, like the very shoreline here.$"

MossdeepCity_Text_SurfExhilarating:
	.string "A voyage on a ship is fine.\p"
	.string "But crossing the sea with POKéMON\n"
	.string "using SURF…\p"
	.string "Now that's an exhilarating trip!\n"
	.string "Wouldn't you agree, youngster?$"

MossdeepCity_Text_SpecialSpaceCenterRock:
	.string "This rock has a special meaning to\n"
	.string "the people at the SPACE CENTER.\p"
	.string "They put it here as their wish for\n"
	.string "their rockets to fly safely.\p"
	.string "When you make a wish, what do you use?\n"
	.string "Do you wish upon a star?\p"
	.string "I use a wish tag to make it happen.\n"
	.string "That's what I do.$"

MossdeepCity_Text_ItsAWhiteRock:
	.string "It's a white rock.$"

MossdeepCity_Text_CitySign:
	.string "MOSSDEEP CITY\n"
	.string "“Our slogan: Cherish POKéMON!”$"

MossdeepCity_Text_SpaceCenterSign:
	.string "MOSSDEEP SPACE CENTER\n"
	.string "“The closest place to space.”$"

MossdeepCity_Text_ScottSomethingWrongWithTown:
	.string "SCOTT: {PLAYER}{KUN}, feeling good?\n"
	.string "I'm doing great!\p"
	.string "I heard the RANGERS are helping\n"
	.string "with the storm, so I decided to\l"
	.string "take a look-see for myself.\p"
	.string "But there's something wrong about\n"
	.string "this town.\p"
	.string "People are going on about a warning\n"
	.string "letter and the SPACE CENTER…\p"
	.string "I don't think it concerns me in any\n"
	.string "way, though.$"

MossdeepCity_Text_SootopolisNewGymLeader:
	.string "Ahh… It feels great letting the waves\n"
	.string "wash over my feet…\p"
	.string "Speaking of the waves, you know that\n"
	.string "island city SOOTOPOLIS?\p"
	.string "I think the GYM there had a new\n"
	.string "LEADER come in.\p"
	.string "People tell me the new LEADER once\n"
	.string "mentored WALLACE.$"


@ First rescue is gated on checking in with the sailor (state 3).
@ Calm the boy's Poochyena, then escort both to the waterfront (state 4).
@ The waterfront boarding event pays mission/XP credit once at state 5.
MossdeepCity_EventScript_RangerChild::
	lock
	faceplayer
	goto_if_eq VAR_NEO_FERRY_DISPATCH, 3, MossdeepCity_RangerChildRescue
	msgbox MossdeepCity_Text_RangerChildEarly, MSGBOX_DEFAULT
	release
	end

MossdeepCity_RangerChildRescue:
	lockall
	applymovement LOCALID_MOSSDEEP_RANGER_CHILD, Common_Movement_FacePlayer
	applymovement LOCALID_MOSSDEEP_RANGER_POOCHYENA, Common_Movement_FacePlayer
	waitmovement 0
	msgbox MossdeepCity_Text_RangerChildFound, MSGBOX_DEFAULT
	msgbox MossdeepCity_Text_RangerCalmPoochyena, MSGBOX_DEFAULT
	playmoncry SPECIES_POOCHYENA, CRY_MODE_NORMAL
	waitmoncry
	msgbox MossdeepCity_Text_RangerPoochyenaCalmed, MSGBOX_DEFAULT
	msgbox MossdeepCity_Text_RangerEscort, MSGBOX_DEFAULT
	closemessage
	setvar VAR_NEO_FERRY_DISPATCH, 4
	fadescreen FADE_TO_BLACK
	setflag FLAG_NEO_HIDE_LANDING_RESCUEES
	warp MAP_MOSSDEEP_CITY_WATERFRONT, 19, 37
	waitstate
	releaseall
	end

MossdeepCity_EventScript_RangerPoochyena::
	lock
	faceplayer
	playmoncry SPECIES_POOCHYENA, CRY_MODE_NORMAL
	msgbox MossdeepCity_Text_RangerPoochyena, MSGBOX_DEFAULT
	waitmoncry
	release
	end

MossdeepCity_Text_RangerChildEarly:
	.string "The water came up so fast!\p"
	.string "My POOCHYENA won't leave the\n"
	.string "steps. I'm not going without him!$"

MossdeepCity_Text_RangerChildFound:
	.string "You're a RANGER? The sailor sent you?\p"
	.string "POOCHYENA's too scared to climb.\n"
	.string "Please don't let the ferry leave!$"

MossdeepCity_Text_RangerPoochyena:
	.string "POOCHYENA is shaking.\n"
	.string "It won't take its eyes off the water.$"

MossdeepCity_Text_RangerCalmPoochyena:
	.string "{PLAYER} kneels down slowly and\n"
	.string "holds out a steady hand.\p"
	.string "Your partner stays close and calm.$"

MossdeepCity_Text_RangerPoochyenaCalmed:
	.string "POOCHYENA stopped shaking!\p"
	.string "BOY: He trusts you! Okay, I'm\n"
	.string "ready. Let's go!$"

MossdeepCity_Text_RangerEscort:
	.string "You lead the boy and POOCHYENA\n"
	.string "up the stairs, past the rising\l"
	.string "water, to the ferry quay...$"

@ Ranger Headquarters at the former Gym footprint.
MossdeepCity_EventScript_RangerHQSign::
	msgbox MossdeepCity_Text_RangerHQSign, MSGBOX_SIGN
	end

MossdeepCity_Text_RangerHQSign:
	.string "MOSSDEEP RANGER HQ\p"
	.string "1F: Dispatch and medical aid.\n"
	.string "2F: Commander HALE.$"

MossdeepCity_EventScript_EvacuatedApartment::
	msgbox MossdeepCity_Text_EvacuatedApartment, MSGBOX_SIGN
	end

MossdeepCity_Text_EvacuatedApartment:
	.string "The door is locked.\p"
	.string "A note: EVACUATED - ALL RESIDENTS\n"
	.string "ACCOUNTED FOR. -MOSSDEEP RANGERS$"

MossdeepCity_NeoRecoveryWorker::
	msgbox MossdeepCity_NeoRecoveryWorkerText, MSGBOX_NPC
	end
MossdeepCity_NeoRecoveryWorkerText:
	.string "We're checking the upper roads.\p"
	.string "Keep the rescue routes clear\n"
	.string "for the RANGERS.$"

MossdeepCity_NeoShelterText:
	.string "The RANGERS are keeping\n"
	.string "families safe in the shelter.\p"
	.string "I hope the lower streets\n"
	.string "can be rebuilt soon.$"

MossdeepCity_NeoReliefCrate::
	msgbox MossdeepCity_NeoReliefCrateText, MSGBOX_SIGN
	end
MossdeepCity_NeoReliefCrateText:
	.string "RANGER relief supplies.\n"
	.string "Dry blankets and first aid.$"
