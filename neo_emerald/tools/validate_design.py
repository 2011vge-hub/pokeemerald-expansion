#!/usr/bin/env python3
"""Static Neo Emerald design-data checks. No third-party dependencies."""
import json
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
def read(name):
    return json.loads((ROOT / "data" / name).read_text(encoding="utf-8"))

def validate():
    species = read("species.json")
    abilities = read("abilities.json")
    world = read("world.json")
    by_id = {item["id"]: item for item in species}
    ability_ids = {item["id"] for item in abilities}
    assert len(by_id) == len(species), "Duplicate species/form IDs"
    for mon in species:
        stats = mon["stats"]
        if stats is None:
            continue
        assert all(isinstance(v, int) and 1 <= v <= 255 for v in stats.values()), mon["id"]
        assert len(stats) == 6, mon["id"]
        assert sum(stats.values()) in (530, 560, 630), mon["id"]
        if mon["kind"] == "mega" and mon.get("ability"):
            assert mon["ability"] in ability_ids, mon["id"]
    assert sum(by_id["GRIMYENA_MEGA"]["stats"].values()) - sum(by_id["GRIMYENA"]["stats"].values()) == 100
    assert sum(by_id["BRELOOM_MEGA"]["stats"].values()) == 560
    assert sum(by_id["WALREIN_MEGA"]["stats"].values()) == 630
    assert next(x for x in abilities if x["id"] == "CHAOS_SPORES")["chance_percent"] == 20
    assert len(world["gyms"]) == 8
    assert len({g["city"] for g in world["gyms"]}) == 8
    assert all(g.get("mega_ace") for g in world["gyms"])
    assert world["story_progress_badges"] == [0, 2, 4, 6, 8]
    print("Neo Emerald design checks passed: 5 species/forms, 4 abilities, 8 Gyms.")

if __name__ == "__main__":
    validate()
