MossdeepCity_ShopLoft_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, NeoLoft_OnFrame
	.byte 0
NeoLoft_OnFrame:
	map_script_2 VAR_NEO_FERRY_DISPATCH, 4, NeoLoft_Escape
	.2byte 0
NeoLoft_Escape:
	lockall
	msgbox NeoLoft_Upstairs, MSGBOX_DEFAULT
	msgbox NeoLoft_Board, MSGBOX_DEFAULT
	closemessage
	warp MAP_MOSSDEEP_CITY_WATERFRONT, 19, 37
	waitstate
	releaseall
	end
NeoLoft_Passengers::
	msgbox NeoLoft_Upstairs, MSGBOX_NPC
	end
NeoLoft_Upstairs:
	.string "SHOPKEEPER: Front door's upstairs\n"
	.string "now. Get the pup onto my balcony!$"
NeoLoft_Board:
	.string "You brace the rescue board against\n"
	.string "the rail. The child crawls across.\p"
	.string "Only then does the siren sound.\n"
	.string "The quay crew pulls you to safety.$"
