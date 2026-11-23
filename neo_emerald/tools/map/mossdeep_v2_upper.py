"""Mossdeep City 2.0, upper-city pass: place Space Center campus annexes built
from the existing Space Center metatiles (no new art, no door/warp changes).

usage:
  python3 neo_emerald/tools/map/mossdeep_v2_upper.py search   # list safe footprints
  python3 neo_emerald/tools/map/mossdeep_v2_upper.py apply    # write the chosen placements

Every placement must: sit on walkable tiles of one elevation, cover no map
event, and keep all route checks passing (see ROUTES).
"""
import collections, json, os, struct, sys

ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), '../../..')) + '/'
LAYOUT = ROOT + 'data/layouts/MossdeepCity_Storm/map.bin'
MAP = ROOT + 'data/maps/MossdeepCity/map.json'
W, H = 80, 40

# Space Center source block: columns 60..68, rows 8..15 of the vanilla layout.
# Columns 61/62 and 66/67 repeat horizontally; rows 11/12 are repeatable wall rows.
SRC_X, SRC_Y = 60, 8
# Annex = left edge, right-of-centre, dish pair, right edge; roof + one wall row + base.
ANNEX_COLS = [60, 65, 66, 67, 68]
ANNEX_ROWS = [8, 9, 10, 11, 13, 14, 15]

# Must stay reachable from the New Game spawn (28,17).
ROUTES = {
    'Pokemon Center door front': (28, 17), 'sailor neighbour': (38, 13), 'Mart door front': (37, 19),
    'Gym door front': (38, 10), 'Space Center door front': (64, 16), 'child landing': (33, 29),
    'Steven house door front': (49, 7), 'House2 door front': (67, 26), 'girl NPC': (45, 18),
    'man NPC': (55, 5), 'woman NPC': (56, 21), 'flooded SE shelf': (50, 33),
}

# Chosen placements (top-left x, y). Filled in after search + visual review.
PLACEMENTS = [(46, 10)]  # Space Center weather-observatory annex (facade only, no door yet)


def load(path=LAYOUT):
    d = open(path, 'rb').read()
    return [struct.unpack_from('<H', d, 2 * i)[0] for i in range(W * H)]


def save(g, path=LAYOUT):
    d = bytearray(len(g) * 2)
    for i, v in enumerate(g):
        struct.pack_into('<H', d, 2 * i, v)
    open(path, 'wb').write(d)


def reachable(g, start=(28, 17)):
    col = lambda x, y: (g[y * W + x] >> 10) & 3
    elv = lambda x, y: g[y * W + x] >> 12
    st = (start[0], start[1], elv(*start)); seen = {st}; q = collections.deque([st])
    while q:
        x, y, ce = q.popleft()
        for nx, ny in ((x + 1, y), (x - 1, y), (x, y + 1), (x, y - 1)):
            if not (0 <= nx < W and 0 <= ny < H) or col(nx, ny):
                continue
            e = elv(nx, ny)
            if not (e in (0, 15) or ce in (0, 15) or e == ce):
                continue
            ns = (nx, ny, ce if e == 15 else e)
            if ns not in seen:
                seen.add(ns); q.append(ns)
    return {(a, b) for a, b, _ in seen}


def event_tiles():
    m = json.load(open(MAP))
    return {(o['x'], o['y']) for k in ('object_events', 'warp_events', 'bg_events', 'coord_events') for o in m[k]}


def footprint(x0, y0):
    return [(x0 + i, y0 + j) for j in range(len(ANNEX_ROWS)) for i in range(len(ANNEX_COLS))]


def place(g, src, x0, y0):
    """Copy annex metatiles + their collision; elevation taken from the site."""
    for j, sy in enumerate(ANNEX_ROWS):
        for i, sx in enumerate(ANNEX_COLS):
            s = src[sy * W + sx]; t = (y0 + j) * W + (x0 + i)
            g[t] = (s & 0x0fff) | (g[t] & 0xf000)


def site_ok(g, x0, y0, events):
    fp = footprint(x0, y0)
    if any(not (0 <= x < W and 0 <= y < H) for x, y in fp):
        return False
    elevs = {g[y * W + x] >> 12 for x, y in fp}
    # land only: water sits at elevation 1, transitions at 0/15
    if len(elevs) != 1 or elevs & {0, 1, 15}:
        return False
    if any((g[y * W + x] >> 10) & 3 for x, y in fp) or any(p in events for p in fp):
        return False
    # keep a walkable apron along the front so the base doesn't sit on a cliff lip
    front = [(x0 + i, y0 + len(ANNEX_ROWS)) for i in range(len(ANNEX_COLS))]
    return all(0 <= y < H and not (g[y * W + x] >> 10) & 3 for x, y in front)


def check_routes(g):
    r = reachable(g)
    bad = [n for n, p in ROUTES.items() if p not in r]
    sea = sum(1 for p in r if g[p[1] * W + p[0]] & 0x3ff == 368)
    return bad, sea


def main():
    mode = sys.argv[1] if len(sys.argv) > 1 else 'search'
    src = load(ROOT + 'data/layouts/MossdeepCity/map.bin')  # vanilla Space Center as the art source
    g = load(); events = event_tiles()
    bad, sea = check_routes(g)
    assert not bad and not sea, f'baseline already failing: {bad} sea={sea}'
    if mode == 'search':
        for y0 in range(H):
            for x0 in range(W):
                if site_ok(g, x0, y0, events):
                    t = list(g); place(t, src, x0, y0); bad, sea = check_routes(t)
                    print((x0, y0), 'OK' if not bad and not sea else f'breaks {bad} sea={sea}')
        return
    for x0, y0 in PLACEMENTS:
        assert site_ok(g, x0, y0, events), f'site {x0},{y0} no longer valid'
        place(g, src, x0, y0)
    bad, sea = check_routes(g)
    assert not bad and not sea, f'placement breaks routes: {bad} sea={sea}'
    save(g)
    print('applied', PLACEMENTS, '- all routes reachable, 0 reachable sea tiles')


if __name__ == '__main__':
    main()
