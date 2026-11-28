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
	msgbox DewfordUnderground_AssistantText, MSGBOX_DEFAULT
	setflag FLAG_NEO_C4_ASSISTANT_SAFE
	setflag FLAG_NEO_C4_READING_CHECKED
	release
	end
DewfordUnderground_AssistantText:
	.string "I recorded a pressure spike\nbefore the tremor.\pI'm safe. Take these readings\nto the warden.$"

DewfordUnderground_Aqua::
	msgbox DewfordUnderground_AquaText, MSGBOX_NPC
	end
DewfordUnderground_AquaText:
	.string "NEO AQUA: These pressure logs\nare exactly what we need.$"
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
