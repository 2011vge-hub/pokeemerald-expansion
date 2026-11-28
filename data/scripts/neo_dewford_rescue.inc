DewfordUnderground_Worker::
	lock
	faceplayer
	goto_if_unset FLAG_NEO_C4_BRIEF, DewfordUnderground_NoBrief
	msgbox DewfordUnderground_WorkerText, MSGBOX_DEFAULT
	setflag FLAG_NEO_C4_WORKER_SAFE
	release
	end
DewfordUnderground_WorkerText:
	.string "The supports gave way, RANGER.\pI'm safe now. I'll head back\nwhen it's clear.$"

DewfordUnderground_Courier::
	lock
	faceplayer
	goto_if_unset FLAG_NEO_C4_BRIEF, DewfordUnderground_NoBrief
	msgbox DewfordUnderground_CourierText, MSGBOX_DEFAULT
	setflag FLAG_NEO_C4_COURIER_SAFE
	release
	end
DewfordUnderground_CourierText:
	.string "The lower passage flooded!\pI'm all right. Tell the warden\nthat you've found me.$"

DewfordUnderground_Assistant::
	lock
	faceplayer
	goto_if_unset FLAG_NEO_C4_BRIEF, DewfordUnderground_NoBrief
	goto_if_defeated TRAINER_GRUNT_UNUSED, DewfordUnderground_AssistantSafe
	goto DewfordUnderground_AssistantWait
DewfordUnderground_AssistantSafe:
	msgbox DewfordUnderground_AssistantText, MSGBOX_DEFAULT
	setflag FLAG_NEO_C4_ASSISTANT_SAFE
	setflag FLAG_NEO_C4_READING_CHECKED
	release
	end
DewfordUnderground_AssistantText:
	.string "I recorded a pressure spike\nbefore the tremor.\pI'm safe. Take these readings\nto the warden.$"

DewfordUnderground_Aqua::
	lock
	faceplayer
	goto_if_unset FLAG_NEO_C4_BRIEF, DewfordUnderground_NoBrief
	goto_if_defeated TRAINER_GRUNT_UNUSED, DewfordUnderground_AquaDefeated
	msgbox DewfordUnderground_AquaText, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_GRUNT_UNUSED, DewfordUnderground_AquaLoseText
DewfordUnderground_AquaDefeated:
	msgbox DewfordUnderground_AquaAfterText, MSGBOX_DEFAULT
	release
	end
DewfordUnderground_AquaText:
	.string "RILL: These pressure logs are\n"
	.string "exactly what NEO AQUA needs.\p"
	.string "I won't let you take them!$"
DewfordUnderground_AquaLoseText:
	.string "The readings are already sent.$"
DewfordUnderground_AquaAfterText:
	.string "RILL: Ask STERN what he knows\n"
	.string "about the pressure readings.$"
DewfordUnderground_AssistantWait:
	msgbox DewfordUnderground_AssistantWaitText, MSGBOX_DEFAULT
	release
	end
DewfordUnderground_AssistantWaitText:
	.string "NEO AQUA has the pressure logs!\n"
	.string "Please stop them first, RANGER.$"
DewfordUnderground_NoBrief:
	msgbox DewfordUnderground_NoBriefText, MSGBOX_DEFAULT
	release
	end
DewfordUnderground_NoBriefText:
	.string "Speak to BRAWLY about the\nmissing residents first.$"

DewfordUnderground_AnnexRepairIdle::
	msgbox GraniteCave_AnnexRepairText, MSGBOX_NPC
	end
DewfordUnderground_AnnexResidentIdle::
	msgbox GraniteCave_AnnexResidentText, MSGBOX_NPC
	end
DewfordUnderground_SurveyIdle::
	msgbox DewfordUnderground_NoBriefText, MSGBOX_NPC
	end
