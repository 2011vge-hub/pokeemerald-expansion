#!/usr/bin/env python3
"""Guard the orientation->live-reception scene and one-time starter grant."""
import json
from pathlib import Path
ROOT=Path(__file__).resolve().parents[2]
r=lambda path: (ROOT/path).read_text()
ng=r("src/new_game.c")
room=r("data/maps/MossdeepCity_RangerBriefingRoom/scripts.inc")
lobby=r("data/maps/MossdeepCity_RangerBase_1F/scripts.inc")
assert "SetWarpDestination(MAP_GROUP(MAP_MOSSDEEP_CITY_RANGER_BRIEFING_ROOM)" in ng
assert "warp MAP_MOSSDEEP_CITY_RANGER_BASE_1F, 7, 8" in room
assert "VAR_NEO_FERRY_DISPATCH, 1" in room and "VAR_NEO_FERRY_DISPATCH, 1" in lobby
assert "MossdeepCity_RangerBase_1F_Movement_AriApproaches" in lobby
assert "MossdeepCity_RangerBase_1F_Movement_JuneApproaches" in lobby
assert lobby.index("applymovement LOCALID_RANGER_BASE_ROOKIE") < lobby.index("MossdeepCity_RangerBase_1F_Text_AriGreeting, MSGBOX_DEFAULT")
assert lobby.index("applymovement LOCALID_RANGER_BASE_DISPATCH") < lobby.index("MossdeepCity_RangerBase_1F_Text_JuneAssignment, MSGBOX_DEFAULT")
intro=lobby.split("MossdeepCity_RangerBase_1F_EventScript_NewRecruit:",1)[1].split("MossdeepCity_RangerBase_1F_Movement_AriApproaches:",1)[0]
assert intro.count("special ChooseStarter")==1
assert intro.index("setvar VAR_NEO_FERRY_DISPATCH, 2") < intro.index("special ChooseStarter")
group=json.loads(r("data/maps/map_groups.json"))
assert group["gMapGroup_IndoorMossdeep"][-1]=="MossdeepCity_RangerBriefingRoom"
layouts=json.loads(r("data/layouts/layouts.json"))["layouts"]
assert sum(l["id"]=="LAYOUT_MOSSDEEP_CITY_RANGER_BRIEFING_ROOM" for l in layouts)==1
room_data=json.loads(r("data/maps/MossdeepCity_RangerBriefingRoom/map.json"))
assert room_data["object_events"]==[] and room_data["map_type"]=="MAP_TYPE_INDOOR"
assert len((ROOT/"data/layouts/MossdeepCity_RangerBriefingRoom/map.bin").read_bytes())==320
print("Ranger opening checks OK: recording, approaching actors, one-time partner")
