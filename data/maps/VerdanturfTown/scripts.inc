VerdanturfTown_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, VerdanturfTown_OnTransition
	.byte 0

VerdanturfTown_OnTransition:
	setflag FLAG_VISITED_VERDANTURF_TOWN
	setvar VAR_CONTEST_HALL_STATE, 0
	end

VerdanturfTown_EventScript_Twin::
	lock
	faceplayer
	goto_if_eq VAR_NEO_CH3_STEP, 9, Verdanturf_NeoTunnelSafe
	msgbox Verdanturf_NeoTunnelWaitText, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_EventScript_TwinTunnelOpen::
	msgbox VerdanturfTown_Text_ManDugTunnelForLove, MSGBOX_DEFAULT
	applymovement LOCALID_VERDANTURF_TWIN, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

VerdanturfTown_EventScript_Man::
	lock
	faceplayer
	goto_if_ne VAR_NEO_CH3_STEP, 9, Verdanturf_NeoGeneral
	goto_if_set FLAG_NEO_VERDANTURF_VISIT, Verdanturf_NeoGeneral
	msgbox Verdanturf_NeoThanksText, MSGBOX_DEFAULT
	setflag FLAG_NEO_VERDANTURF_VISIT
	release
	end

VerdanturfTown_EventScript_Camper::
	msgbox VerdanturfTown_Text_MakeBattleTentDebut, MSGBOX_NPC
	end

VerdanturfTown_EventScript_Boy::
	msgbox Verdanturf_NeoHabitatText, MSGBOX_NPC
	end

VerdanturfTown_EventScript_BoyTunnelOpen::
	msgbox VerdanturfTown_Text_EasyToGetToRustboroNow, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_EventScript_TownSign::
	msgbox VerdanturfTown_Text_TownSign, MSGBOX_SIGN
	end

VerdanturfTown_EventScript_WandasHouseSign::
	msgbox VerdanturfTown_Text_WandasHouse, MSGBOX_SIGN
	end

VerdanturfTown_EventScript_BattleTentSign::
	msgbox VerdanturfTown_Text_BattleTentSign, MSGBOX_SIGN
	end

VerdanturfTown_EventScript_RusturfTunnelSign::
	msgbox VerdanturfTown_Text_RusturfTunnelSign, MSGBOX_SIGN
	end

VerdanturfTown_Text_ManTryingToDigTunnel:
	.string "My papa told me.\p"
	.string "He says this tunnel is full of\n"
	.string "timid POKéMON.\p"
	.string "They get all scared of loud noise and\n"
	.string "make a big uproar.\p"
	.string "So they had to stop the big tunnel\n"
	.string "project.\p"
	.string "But there's one man. He's trying to dig\n"
	.string "the tunnel by himself!$"

VerdanturfTown_Text_ManDugTunnelForLove:
	.string "There was a man who dug a tunnel for\n"
	.string "a lady he loved.\p"
	.string "I don't really get it, but hey!$"

VerdanturfTown_Text_AirCleanHere:
	.string "The way the winds blow, volcanic ash\n"
	.string "is never blown in this direction.\p"
	.string "The air is clean and delicious here.\n"
	.string "Living here should do wonders for even\l"
	.string "frail and sickly people.$"

VerdanturfTown_Text_MakeBattleTentDebut:
	.string "My POKéMON and I, we've been riding\n"
	.string "a hot winning streak.\p"
	.string "So I decided to make my BATTLE TENT\n"
	.string "debut in this town.$"

VerdanturfTown_Text_GuyTryingToBustThroughCave:
	.string "Did you see the cave next to the\n"
	.string "POKéMON MART?\p"
	.string "There's a guy in there who's trying to\n"
	.string "bust up boulders so he can bust out\l"
	.string "through to the other side.\p"
	.string "It'd be great if we could go through…\n"
	.string "It'll make it easy to visit RUSTBORO.$"

VerdanturfTown_Text_EasyToGetToRustboroNow:
	.string "That cave next to the POKéMON MART\n"
	.string "is now a tunnel to the other side.\p"
	.string "It's great--it's easy to go shop for\n"
	.string "new DEVON products in RUSTBORO now.$"

VerdanturfTown_Text_TownSign:
	.string "VERDANTURF TOWN\p"
	.string "A sanctuary for people and\n"
	.string "POKéMON.$"

VerdanturfTown_Text_WandasHouse:
	.string "WANDA'S HOUSE$"

VerdanturfTown_Text_BattleTentSign:
	.string "BATTLE TENT VERDANTURF SITE\n"
	.string "“Feast Your Eyes on Battles!”$"

VerdanturfTown_Text_RusturfTunnelSign:
	.string "RUSTURF TUNNEL\p"
	.string "Survey and maintenance corridor.\n"
	.string "Follow RANGER safety notices.$"


Verdanturf_NeoTunnelSafe:
	msgbox Verdanturf_NeoSafeText, MSGBOX_DEFAULT
	release
	end
Verdanturf_NeoGeneral:
	msgbox Verdanturf_NeoGeneralText, MSGBOX_DEFAULT
	release
	end
Verdanturf_NeoTunnelWaitText:
	.string "The survey crew is working in\n"
	.string "RUSTURF. Please give them room.$"
Verdanturf_NeoSafeText:
	.string "The two technicians are home!\p"
	.string "We can tend the gardens again\n"
	.string "without worrying about them.$"
Verdanturf_NeoHabitatText:
	.string "We look after POKéMON that\n"
	.string "lost their homes in the storms.$"
Verdanturf_NeoThanksText:
	.string "You helped the RUSTURF crew?\p"
	.string "Their families are grateful.\n"
	.string "You're welcome here anytime.$"
Verdanturf_NeoGeneralText:
	.string "Our air is still clean.\p"
	.string "We help people and POKéMON\n"
	.string "recover from the coastal storms.$"
