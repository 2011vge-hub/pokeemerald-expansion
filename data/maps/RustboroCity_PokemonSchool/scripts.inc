RustboroCity_PokemonSchool_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, RustboroCity_PokemonSchool_NeoTransition
	.byte 0

RustboroCity_PokemonSchool_NeoTransition:
	setflag FLAG_HIDE_RUSTBORO_CITY_POKEMON_SCHOOL_SCOTT
	end

RustboroCity_PokemonSchool_EventScript_Blackboard::
	lockall
	msgbox RustboroCity_PokemonSchool_Text_BlackboardListsStatusChanges, MSGBOX_DEFAULT
	goto RustboroCity_PokemonSchool_EventScript_ChooseBlackboardTopic
	end

RustboroCity_PokemonSchool_EventScript_ChooseBlackboardTopic::
	message RustboroCity_PokemonSchool_Text_ReadWhichTopic
	waitmessage
	multichoicegrid 8, 1, MULTI_STATUS_INFO, 3, FALSE
	switch VAR_RESULT
	case 0, RustboroCity_PokemonSchool_EventScript_Poison
	case 1, RustboroCity_PokemonSchool_EventScript_Paralysis
	case 2, RustboroCity_PokemonSchool_EventScript_Sleep
	case 3, RustboroCity_PokemonSchool_EventScript_Burn
	case 4, RustboroCity_PokemonSchool_EventScript_Freeze
	case 5, RustboroCity_PokemonSchool_EventScript_ExitTopicSelect
	case MULTI_B_PRESSED, RustboroCity_PokemonSchool_EventScript_ExitTopicSelect
	end

RustboroCity_PokemonSchool_EventScript_Poison::
	msgbox RustboroCity_PokemonSchool_Text_ExplainPoison, MSGBOX_DEFAULT
	goto RustboroCity_PokemonSchool_EventScript_ChooseBlackboardTopic
	end

RustboroCity_PokemonSchool_EventScript_Paralysis::
	msgbox RustboroCity_PokemonSchool_Text_ExplainParalysis, MSGBOX_DEFAULT
	goto RustboroCity_PokemonSchool_EventScript_ChooseBlackboardTopic
	end

RustboroCity_PokemonSchool_EventScript_Sleep::
	msgbox RustboroCity_PokemonSchool_Text_ExplainSleep, MSGBOX_DEFAULT
	goto RustboroCity_PokemonSchool_EventScript_ChooseBlackboardTopic
	end

RustboroCity_PokemonSchool_EventScript_Burn::
	msgbox RustboroCity_PokemonSchool_Text_ExplainBurn, MSGBOX_DEFAULT
	goto RustboroCity_PokemonSchool_EventScript_ChooseBlackboardTopic
	end

RustboroCity_PokemonSchool_EventScript_Freeze::
	msgbox RustboroCity_PokemonSchool_Text_ExplainFreeze, MSGBOX_DEFAULT
	goto RustboroCity_PokemonSchool_EventScript_ChooseBlackboardTopic
	end

RustboroCity_PokemonSchool_EventScript_ExitTopicSelect::
	releaseall
	end

RustboroCity_PokemonSchool_EventScript_GameboyKid1::
	msgbox RustboroCity_PokemonSchool_Text_TradingRightNow, MSGBOX_NPC
	end

RustboroCity_PokemonSchool_EventScript_GameboyKid2::
	msgbox RustboroCity_PokemonSchool_Text_AlwaysWantedSeedot, MSGBOX_NPC
	end

RustboroCity_PokemonSchool_EventScript_RichBoy::
	msgbox RustboroCity_PokemonSchool_Text_PokemontCantUseManMadeItems, MSGBOX_NPC
	end

RustboroCity_PokemonSchool_EventScript_Lass::
	msgbox RustboroCity_PokemonSchool_Text_ConfusedPokemonAttacksItself, MSGBOX_NPC
	end

RustboroCity_PokemonSchool_EventScript_SchoolKidM::
	msgbox RustboroCity_PokemonSchool_Text_PokemonHealItselfWithBerry, MSGBOX_NPC
	end

RustboroCity_PokemonSchool_EventScript_StudentNotebook::
	msgbox RustboroCity_PokemonSchool_Text_StudentsNotes, MSGBOX_SIGN
	end

RustboroCity_PokemonSchool_EventScript_Teacher::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_QUICK_CLAW, RustboroCity_PokemonSchool_EventScript_GaveQuickClaw
	call_if_eq VAR_FACING, DIR_EAST, RustboroCity_PokemonSchool_EventScript_TeacherCheckOnStudentsEast
	call_if_eq VAR_FACING, DIR_WEST, RustboroCity_PokemonSchool_EventScript_TeacherCheckOnStudentsWest
	msgbox RustboroCity_PokemonSchool_Text_StudentsWhoDontStudyGetQuickClaw, MSGBOX_DEFAULT
	giveitem ITEM_QUICK_CLAW
	goto_if_eq VAR_RESULT, 0, Common_EventScript_ShowBagIsFull
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	setflag FLAG_RECEIVED_QUICK_CLAW
	release
	end

RustboroCity_PokemonSchool_EventScript_TeacherCheckOnStudentsEast::
	applymovement VAR_LAST_TALKED, RustboroCity_PokemonSchool_Movement_TeacherCheckOnStudentsEast
	waitmovement 0
	return

RustboroCity_PokemonSchool_EventScript_TeacherCheckOnStudentsWest::
	applymovement VAR_LAST_TALKED, RustboroCity_PokemonSchool_Movement_TeacherCheckOnStudentsWest
	waitmovement 0
	return

RustboroCity_PokemonSchool_EventScript_GaveQuickClaw::
	msgbox RustboroCity_PokemonSchool_Text_ExplainQuickClaw, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	release
	end

RustboroCity_PokemonSchool_Movement_TeacherCheckOnStudentsWest:
	walk_left
	walk_down
	walk_down
	walk_right
	walk_in_place_faster_down
	delay_16
	delay_16
	delay_16
	walk_down
	walk_in_place_faster_left
	delay_16
	delay_16
	walk_right
	delay_16
	delay_16
	delay_8
	walk_up
	walk_left
	walk_left
	walk_up
	walk_up
	walk_right
	step_end

RustboroCity_PokemonSchool_Movement_TeacherCheckOnStudentsEast:
	walk_right
	walk_right
	walk_down
	walk_down
	walk_left
	walk_left
	walk_in_place_faster_down
	delay_16
	delay_16
	delay_16
	walk_down
	walk_in_place_faster_left
	delay_16
	delay_16
	walk_right
	delay_16
	delay_16
	delay_8
	walk_up
	walk_right
	walk_up
	walk_up
	walk_left
	walk_left
	step_end

RustboroCity_PokemonSchool_EventScript_Scott::
	lock
	faceplayer
	goto_if_set FLAG_MET_SCOTT_AFTER_OBTAINING_STONE_BADGE, RustboroCity_PokemonSchool_EventScript_ScottWatchStudents
	goto_if_set FLAG_MET_SCOTT_RUSTBORO, RustboroCity_PokemonSchool_EventScript_ScottSpokeAlready
	goto_if_set FLAG_BADGE01_GET, RustboroCity_PokemonSchool_EventScript_ScottGreetHasBadge
	msgbox RustboroCity_PokemonSchool_Text_ScottMetAlreadyCut, MSGBOX_DEFAULT
	addvar VAR_SCOTT_STATE, 1
	setflag FLAG_MET_SCOTT_RUSTBORO
	release
	end

RustboroCity_PokemonSchool_EventScript_ScottSpokeAlready::
	goto_if_set FLAG_BADGE01_GET, RustboroCity_PokemonSchool_EventScript_ScottNoticeBadge
	msgbox RustboroCity_PokemonSchool_Text_StudentTalentLevelUnknown, MSGBOX_DEFAULT
	release
	end

RustboroCity_PokemonSchool_EventScript_ScottGreetHasBadge::
	msgbox RustboroCity_PokemonSchool_Text_ScottMetAlreadyStoneBadge, MSGBOX_DEFAULT
	goto RustboroCity_PokemonSchool_EventScript_MetScottAfterBadge
	end

RustboroCity_PokemonSchool_EventScript_ScottNoticeBadge::
	msgbox RustboroCity_PokemonSchool_Text_ScottStoneBadge, MSGBOX_DEFAULT
	goto RustboroCity_PokemonSchool_EventScript_MetScottAfterBadge
	end

RustboroCity_PokemonSchool_EventScript_MetScottAfterBadge::
	addvar VAR_SCOTT_STATE, 1
	setflag FLAG_MET_SCOTT_AFTER_OBTAINING_STONE_BADGE
	release
	end

RustboroCity_PokemonSchool_EventScript_ScottWatchStudents::
	msgbox RustboroCity_PokemonSchool_Text_StudentTalentLevelUnknown, MSGBOX_DEFAULT
	release
	end

RustboroCity_PokemonSchool_Text_BlackboardListsStatusChanges:
	.string "RUSTBORO UNIVERSITY\p"
	.string "Battle Studies 101: status"
	.string "conditions and safety.$"

RustboroCity_PokemonSchool_Text_ReadWhichTopic:
	.string "Which topic do you want to read?$"

RustboroCity_PokemonSchool_Text_ExplainPoison:
	.string "If a POKéMON is poisoned, it will\n"
	.string "steadily lose HP.\p"
	.string "The effects of poison remain after\n"
	.string "a battle.\p"
	.string "A poisoned POKéMON's HP will drop\n"
	.string "while it is traveling.\p"
	.string "Heal a poisoning using an ANTIDOTE.$"

RustboroCity_PokemonSchool_Text_ExplainParalysis:
	.string "If a POKéMON becomes paralyzed,\n"
	.string "its SPEED drops.\p"
	.string "It may also not be able to move while\n"
	.string "it is in battle.\p"
	.string "Paralysis remains after battle.\n"
	.string "Cure it using a PARLYZ HEAL.$"

RustboroCity_PokemonSchool_Text_ExplainSleep:
	.string "If a POKéMON falls asleep, it will be\n"
	.string "unable to attack.\p"
	.string "A POKéMON may wake up on its own,\n"
	.string "but if a battle ends while it is\l"
	.string "sleeping, it will stay asleep.\p"
	.string "Wake it up using an AWAKENING.$"

RustboroCity_PokemonSchool_Text_ExplainBurn:
	.string "A burn reduces ATTACK power, and it\n"
	.string "steadily reduces the victim's HP.\p"
	.string "A burn lingers after battle.\n"
	.string "Cure a burn using a BURN HEAL.$"

RustboroCity_PokemonSchool_Text_ExplainFreeze:
	.string "If a POKéMON is frozen, it becomes\n"
	.string "completely helpless.\p"
	.string "It will remain frozen after battle.\n"
	.string "Thaw it out using an ICE HEAL.$"

RustboroCity_PokemonSchool_Text_StudentsWhoDontStudyGetQuickClaw:
	.string "Welcome to RUSTBORO\n"
	.string "UNIVERSITY! This is Field\n"
	.string "Studies 101.\p"
	.string "ROXANNE still teaches here\n"
	.string "between GYM challenges.\p"
	.string "Take this QUICK CLAW for\n"
	.string "your first field assignment.$"

RustboroCity_PokemonSchool_Text_ExplainQuickClaw:
	.string "The QUICK CLAW may let a\n"
	.string "POKéMON act first in battle.\p"
	.string "In the field, preparation\n"
	.string "matters as much as speed.$"

RustboroCity_PokemonSchool_Text_TradingRightNow:
	.string "We are comparing notes on\n"
	.string "last week's heavy storm.\p"
	.string "Our class tracks new\n"
	.string "POKéMON sightings.$"

RustboroCity_PokemonSchool_Text_AlwaysWantedSeedot:
	.string "My roommate is from GALAR!\p"
	.string "We compare native habitats\n"
	.string "for our ecology project.$"

RustboroCity_PokemonSchool_Text_PokemontCantUseManMadeItems:
	.string "My final project studies\n"
	.string "DEVON's RANGER equipment.\p"
	.string "Tools should protect people\n"
	.string "and POKéMON alike.$"

RustboroCity_PokemonSchool_Text_ConfusedPokemonAttacksItself:
	.string "Exams are coming up...\p"
	.string "My thesis is on POKéMON\n"
	.string "stress in extreme weather.$"

RustboroCity_PokemonSchool_Text_PokemonHealItselfWithBerry:
	.string "POKéMON can eat BERRIES,\n"
	.string "but RANGERS must be ready\n"
	.string "to help anyone in danger.$"

RustboroCity_PokemonSchool_Text_StudentsNotes:
	.string "FIELD STUDIES NOTES:\p"
	.string "1. Check risks before acting.\p"
	.string "2. Protect everyone nearby.\p"
	.string "3. Log unusual weather\n"
	.string "   at the RANGER office.\p"
	.string "4. Document every rescue.$"

RustboroCity_PokemonSchool_Text_ScottMetAlreadyCut:
	.string "Hello? Didn't we meet before?\n"
	.string "I think back in PETALBURG CITY.\p"
	.string "Let me introduce myself.\n"
	.string "My name's SCOTT.\p"
	.string "I've been traveling everywhere in\n"
	.string "search of outstanding TRAINERS.\p"
	.string "More specifically, I'm looking for\n"
	.string "POKéMON battle experts.\p"
	.string "So, what brings you to this SCHOOL?\n"
	.string "Are you a TRAINER, too?\p"
	.string "The first thing you should do is to\n"
	.string "have a POKéMON learn the move CUT.\p"
	.string "If I remember correctly, someone in\n"
	.string "this town has CUT.$"

RustboroCity_PokemonSchool_Text_StudentTalentLevelUnknown:
	.string "SCOTT: Hmm…\p"
	.string "The talent levels of the students here\n"
	.string "are unknown. The potential's there.$"

RustboroCity_PokemonSchool_Text_ScottStoneBadge:
	.string "SCOTT: Oh, what's that?\p"
	.string "It's a STONE BADGE, isn't it?\n"
	.string "That's pretty impressive, I'd say.\p"
	.string "But, you know, I would've loved to see\n"
	.string "you in battle.\p"
	.string "It's hard to tell what you're like as\n"
	.string "a TRAINER from a LEAGUE BADGE.$"

RustboroCity_PokemonSchool_Text_ScottMetAlreadyStoneBadge:
	.string "Hello? Didn't we meet before?\n"
	.string "I think back in PETALBURG CITY.\p"
	.string "Let me introduce myself.\n"
	.string "My name's SCOTT.\p"
	.string "I've been traveling everywhere in\n"
	.string "search of outstanding TRAINERS.\p"
	.string "More specifically, I'm looking for\n"
	.string "POKéMON battle experts.\p"
	.string "Oh, what's that?\n"
	.string "It's a STONE BADGE, isn't it?\p"
	.string "That's pretty impressive, I'd say, for\n"
	.string "a starting TRAINER like yourself.\p"
	.string "But, you know, I would've loved to see\n"
	.string "you in battle.\p"
	.string "It's hard to tell what you're like as\n"
	.string "a TRAINER from a LEAGUE BADGE.$"



@ Temporary on-wall lift terminal, preserving three existing blackboard topics.
@ A proper elevator metatile and bigger exterior will replace this frontage.
RustboroCity_PokemonSchool_EventScript_UniversityLift::
	lockall
	msgbox RustboroCity_PokemonSchool_Text_UniversityLiftPrompt, MSGBOX_YESNO
	goto_if_ne VAR_RESULT, YES, RustboroCity_PokemonSchool_EventScript_UniversityLiftDeclined
	closemessage
	fadescreen FADE_TO_BLACK
	warp MAP_RUSTBORO_CITY_UNIVERSITY_2F, 3, 3
	waitstate
	end

RustboroCity_PokemonSchool_EventScript_UniversityLiftDeclined:
	releaseall
	end

RustboroCity_PokemonSchool_Text_UniversityLiftPrompt:
	.string "RUSTBORO UNIVERSITY LIFT\n"
	.string "Upper lecture and research\n"
	.string "floors are now accessible.\p"
	.string "Go up to FLOOR TWO?$"

@ The attendant at (3,8) is approachable from the entrance; the sign is optional.
RustboroCity_PokemonSchool_EventScript_UniversityAttendant::
	lockall
	msgbox RustboroCity_PokemonSchool_Text_Attendant, MSGBOX_DEFAULT
	goto RustboroCity_PokemonSchool_EventScript_UniversityLift
	end

RustboroCity_PokemonSchool_Text_Attendant:
	.string "RUSTBORO UNIVERSITY\p"
	.string "1F: Reception and commons.\n"
	.string "2F: RANGER field sciences.\p"
	.string "3F: Climate Archive.\n"
	.string "4F: Faculty and ROXANNE.\p"
	.string "Use the stairs or ask me\n"
	.string "to take you to floor two.\p"
	.string "For missions, visit HALE's\n"
	.string "field office in the west flats.$"

RustboroCity_PokemonSchool_EventScript_RioluResearcher::
	lock
	faceplayer
	goto_if_set FLAG_NEO_RECEIVED_RIOLU_EGG, NeoRioluEgg_Received
	msgbox NeoRioluEgg_Offer, MSGBOX_YESNO
	goto_if_ne VAR_RESULT, YES, NeoRioluEgg_Declined
	getpartysize
	goto_if_eq VAR_RESULT, PARTY_SIZE, NeoRioluEgg_NoRoom
	giveegg SPECIES_RIOLU
	goto_if_ne VAR_RESULT, MON_GIVEN_TO_PARTY, NeoRioluEgg_Failed
	setflag FLAG_NEO_RECEIVED_RIOLU_EGG
	playfanfare MUS_OBTAIN_ITEM
	msgbox NeoRioluEgg_Obtained, MSGBOX_DEFAULT
	waitfanfare
	msgbox NeoRioluEgg_Care, MSGBOX_DEFAULT
	release
	end
NeoRioluEgg_Received:
	msgbox NeoRioluEgg_ReceivedText, MSGBOX_DEFAULT
	release
	end
NeoRioluEgg_Declined:
	msgbox NeoRioluEgg_DeclinedText, MSGBOX_DEFAULT
	release
	end
NeoRioluEgg_NoRoom:
	msgbox NeoRioluEgg_NoRoomText, MSGBOX_DEFAULT
	release
	end
NeoRioluEgg_Failed:
	msgbox NeoRioluEgg_NoRoomText, MSGBOX_DEFAULT
	release
	end
NeoRioluEgg_Offer:
	.string "I'm studying the bonds between\n"
	.string "RANGERS and their partners.\p"
	.string "Our SINNOH colleagues entrusted\n"
	.string "us with this POKéMON EGG.\p"
	.string "Would you care for it?$"
NeoRioluEgg_Obtained:
	.string "{PLAYER} received an EGG!$"
NeoRioluEgg_Care:
	.string "It needs warmth and time.\p"
	.string "Walk with it on your missions.\n"
	.string "You'll make a wonderful partner.$"
NeoRioluEgg_ReceivedText:
	.string "How is your partner doing?\p"
	.string "Trust is earned through care,\n"
	.string "not just through battles.$"
NeoRioluEgg_DeclinedText:
	.string "Of course! Come back if you'd\n"
	.string "like to care for it later.$"
NeoRioluEgg_NoRoomText:
	.string "Make room in your party first.\n"
	.string "I'll keep the EGG safe for you.$"

@ Public exhibition only. Temporary adult NPC until the approved May art is installed.
RustboroCity_PokemonSchool_EventScript_NeoMayExhibition::
	lock
	faceplayer
	goto_if_unset FLAG_BADGE01_GET, NeoMayExhibition_NoBadge
	goto_if_defeated TRAINER_NEO_MAY_EXHIBITION, NeoMayExhibition_Won
	msgbox NeoMayExhibition_Offer, MSGBOX_YESNO
	goto_if_ne VAR_RESULT, YES, NeoMayExhibition_Decline
	trainerbattle_no_intro TRAINER_NEO_MAY_EXHIBITION, NeoMayExhibition_Defeat
NeoMayExhibition_Won:
	msgbox NeoMayExhibition_After, MSGBOX_DEFAULT
	release
	end
NeoMayExhibition_NoBadge:
	msgbox NeoMayExhibition_Introduction, MSGBOX_DEFAULT
	release
	end
NeoMayExhibition_Decline:
	msgbox NeoMayExhibition_Later, MSGBOX_DEFAULT
	release
	end
NeoMayExhibition_Introduction:
	.string "MAY: Hello! I'm a visiting\n"
	.string "CONTEST COORDINATOR.\p"
	.string "Earn your first BADGE, then\n"
	.string "we can have a friendly match.$"
NeoMayExhibition_Offer:
	.string "MAY: Ready for a friendly\n"
	.string "exhibition battle?\p"
	.string "Let's show what our partners\n"
	.string "can do together!$"
NeoMayExhibition_Defeat:
	.string "Wonderful teamwork!$"
NeoMayExhibition_After:
	.string "MAY: Your partners trust you.\p"
	.string "Keep that bond, wherever your\n"
	.string "RANGER duties take you.$"
NeoMayExhibition_Later:
	.string "No rush! Come back whenever\n"
	.string "you're ready.$"
