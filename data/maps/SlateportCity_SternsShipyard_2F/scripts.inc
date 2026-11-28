SlateportCity_SternsShipyard_2F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, NeoSlateport_ResearchVisibility
	.byte 0

NeoSlateport_ResearchVisibility:
	setflag FLAG_TEMP_1
	goto_if_unset FLAG_NEO_C4_SURVEY, NeoSlateport_ResearchVisibilityDone
	clearflag FLAG_TEMP_1
NeoSlateport_ResearchVisibilityDone:
	end

SlateportCity_SternsShipyard_2F_EventScript_Scientist1::
	msgbox SlateportCity_SternsShipyard_2F_Text_ShipDesignMoreLikeBuilding, MSGBOX_NPC
	end

SlateportCity_SternsShipyard_2F_EventScript_Scientist2::
	msgbox SlateportCity_SternsShipyard_2F_Text_FloatsBecauseBuoyancy, MSGBOX_NPC
	end

SlateportCity_SternsShipyard_2F_Text_ShipDesignMoreLikeBuilding:
	.string "Designing a large ship is more like\n"
	.string "making a big building than putting\l"
	.string "together a transportation vehicle.$"

SlateportCity_SternsShipyard_2F_Text_FloatsBecauseBuoyancy:
	.string "Don't you think it's strange that\n"
	.string "a ship made of heavy iron floats?\p"
	.string "It floats because of a principle\n"
	.string "called buoyancy.$"


@ First visit is a research briefing, not the later Devon cargo event.
NeoSlateport_Stern::
	lock
	faceplayer
	goto_if_unset FLAG_NEO_C4_SURVEY, NeoSlateport_SternWait
	goto_if_set FLAG_NEO_C4_STERN_REVIEWED, NeoSlateport_SternRepeat
	msgbox NeoSlateport_SternEvidence, MSGBOX_DEFAULT
	setflag FLAG_NEO_C4_STERN_REVIEWED
NeoSlateport_SternRepeat:
	msgbox NeoSlateport_SternNext, MSGBOX_DEFAULT
	release
	end
NeoSlateport_SternWait:
	msgbox NeoSlateport_SternWaitText, MSGBOX_DEFAULT
	release
	end
NeoSlateport_Hale::
	lock
	faceplayer
	goto_if_unset FLAG_NEO_C4_STERN_REVIEWED, NeoSlateport_HaleWait
	goto_if_set FLAG_NEO_C4_REPORTED, NeoSlateport_HaleOrders
	setflag FLAG_NEO_C4_REPORTED
	addvar VAR_NEO_RANGER_MISSIONS, 1
	addvar VAR_NEO_RANGER_XP, 100
	setvar VAR_0x8004, 0
	special NeoRangerCreditMissionTraining
	msgbox NeoSlateport_HaleFiled, MSGBOX_DEFAULT
NeoSlateport_HaleOrders:
	msgbox NeoSlateport_HaleOrdersText, MSGBOX_DEFAULT
	release
	end
NeoSlateport_HaleWait:
	msgbox NeoSlateport_HaleWaitText, MSGBOX_DEFAULT
	release
	end
NeoSlateport_SternEvidence:
	.string "STERN: BRAWLY sent word. Let me\n"
	.string "see the DEWFORD readings.\p"
	.string "These pressure spikes match our\n"
	.string "inland tremor records.\p"
	.string "The sea and land are responding\n"
	.string "to the same disturbance.\p"
	.string "But we still don't know why.$"
NeoSlateport_SternNext:
	.string "STERN: Tell HALE what we found.\n"
	.string "He's here in the research room.$"
NeoSlateport_SternWaitText:
	.string "STERN: Bring the DEWFORD survey\n"
	.string "when your crew has finished.$"
NeoSlateport_HaleFiled:
	.string "HALE: Good work, RANGER.\p"
	.string "I'll file the DEWFORD report\n"
	.string "with STERN's findings.$"
NeoSlateport_HaleOrdersText:
	.string "HALE: CAYTON reports trouble\n"
	.string "at his desert excavation.\p"
	.string "These readings resemble those\n"
	.string "from GROUDON's awakening.\p"
	.string "That doesn't mean it's back.\p"
	.string "Our next assignment is inland.\n"
	.string "We'll head through MAUVILLE.\p"
	.string "Wait for the desert route to\n"
	.string "be cleared before departure.$"
NeoSlateport_HaleWaitText:
	.string "HALE: Speak with CAPT. STERN.\n"
	.string "We need his comparison first.$"
