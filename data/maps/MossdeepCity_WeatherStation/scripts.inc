MossdeepCity_WeatherStation_MapScripts::
	.byte 0

MossdeepCity_WeatherStation_Research::
	lock
	faceplayer
	goto_if_ge VAR_NEO_FERRY_DISPATCH, 5, MossdeepCity_WeatherStation_ResearchAfter
	msgbox MossdeepCity_WeatherStation_Text_Research, MSGBOX_DEFAULT
	release
	end
MossdeepCity_WeatherStation_ResearchAfter:
	msgbox MossdeepCity_WeatherStation_Text_ResearchAfter, MSGBOX_DEFAULT
	release
	end
MossdeepCity_WeatherStation_Supply::
	msgbox MossdeepCity_WeatherStation_Text_Supply, MSGBOX_NPC
	end
MossdeepCity_WeatherStation_Text_Research:
	.string "We're tracking the storm surge.\p"
	.string "The readings rose faster than\n"
	.string "our models predicted.$"
MossdeepCity_WeatherStation_Text_ResearchAfter:
	.string "The ferry is safe, but we're\n"
	.string "still checking the tide gauges.\p"
	.string "Something disrupted our warning\n"
	.string "system. We need more data.$"
MossdeepCity_WeatherStation_Text_Supply:
	.string "Food, water and emergency gear\n"
	.string "are being sent to the docks.\p"
	.string "RANGER HQ is at the waterfront.$"
