#!/usr/bin/env python3
"""Build 22 hatless Ranger overworld integration candidate, 2026-11-26.
Approved visual direction supersedes helmeted Option A. Runtime walking steps
are derived candidates, not emulator-validated. Run after legacy generator.
Running uses walking frames temporarily; other action geometry is retained.
"""
import base64, hashlib, io
from pathlib import Path
from PIL import Image
ROOT = Path(__file__).resolve().parents[2]
ASSETS = ROOT / "graphics/object_events/pics/people"
PAL = ROOT / "graphics/object_events/palettes"
DATA = {
    "brendan": ("iVBORw0KGgoAAAANSUhEUgAAAJAAAAAgBAMAAAAPouz+AAAAMFBMVEUA/wAQECEhKUI6QlpSWoRrhK0hKTqcQineWiH/lEL/xZT/3r3OhGOMUkKctdbm9/8f+diqAAAAAXRSTlMAQObYZgAAAiVJREFUeJztlD9rFEEYh5+ZHIlaHDOumCZu9gwI6bKmsDXYx3wCSR0Q1Ca130AsLKxELBViIRZp0qSVkM7G3RMkBMzNJAb8k9sdi5vd0/dAv0DeYh/u+T3FcsXC+Z3f+f3nrAFARaLMX17uE50ygAa7nFtAmeXcANgkt9B6uU92SW5BYZOlMlR7XE0NR4Vn5ZshLDxvvdxlF6nRRmX2FKoMLgP71sA2rZe77CI7kPlaz3897illAqAdqnA03otdyS5Sq5uuGHgP3hFcDzVfhpDdoPFyn+giNR/wh0XtgyN4CnBv2FOVabzcJ7rITlib2agWnhXHxlkfjA+/Dp+uu9oTvRe7kl2k7n68de17dQ/Ahfo2uJnTV76g8RO76BrqkxIo8WEAlC8AX3rWaLzcZddQ82Xx86K+CycDpgJQX+Rnd4vWy112kZrwsi53PVS+PgOo0atHntbLXXaRGub209l1UJvlwUPgx/25RyfQernLLlJzwPsHWJgdXs+mDcAOPWi93GUX2WH41nK2A2fveu41wHC4BbRe7rKL1FQbhu09uLDh2QSoHwO0Xu6yi9RcqnHlDoSaAQB+6gnQernLrmU37af9JZhO+6sJwJWVOwYgydP+EnTTfpIDJNlqAkyn/QXzZ9eQJG/CUWDtsgFQJvp89Cm0ZrQn2egTqWySj9GBQXVcAdReAeDUJw8QfDL6EwgewNH8diPrbDHGP0+Z8XP0TuOnvN9K/8qDuroE9QAAAABJRU5ErkJggg==", "71e1bed7b972ca32d322276a6d8a6d488bada412dd3e8eb38459973165c046fc"),
    "may": ("iVBORw0KGgoAAAANSUhEUgAAAJAAAAAgBAMAAAAPouz+AAAAMFBMVEUA/wAQECEhKUI6QlpSWoRrhK0hKTqcQineWiH/lEL/xZT/3r3OhGOMUkKctdbm9/8f+diqAAAAAXRSTlMAQObYZgAAAhpJREFUeJztlLFqU1Ech79zosUWbM/1QgaxMS0uTu01m0OF4gO4iJtNHXWpk6OLD+AbCOKm0DpKoeYBlEahiMs1wTqIJPeEglJs7t/h3nNT/wV9gf6HfJzv9w0ZQuD0Tu/0/nNRVLIOgImc8n/vuitoIGrxPoPZWot3HmouGe96Kq933ZW0mCsR1xwctCAB3Cq1BCqvd92VtNCUOXMLVh3EbbCZIXZUXu+6K2mJpXcw6sOHkYn8FmapK85D5dWuu0ALWe/nkgdEBGC4iReYeLXrrqQ1l7++ze8ZZwS8GJj53ssxVF7tugu0pC8+b0ztQ9ODbyIpz3Z9k8qrXXeBlsVP+a90ByLAODAb2RtzwVVe77oraeMYgCQWQaTmkHyEeCqvdt0FWhlcZdqu7Q26xo9mBx6eTh+61Aevd90FWp8+h730uuQiwhcYuIttM0fwetddoB37Sx8bU7KFv51+W/ZweNfcmF8m+BO76gItde6smXWon11s1h2Ydifa3GLi1a67kpaj1w/nf3fg6GV0/hXAdt4BJl7tuitpGd+H7S6ce4A8AvjxGKDyetddSctMzWe9DkjuMwDhCUDlT+yqC8Q0+o2+A9Por6wD3GzsO4A4CT5OAOKFlfWib7njXSBxEsIiiOKCxpU+MeW78PFC8ddoolYywRkYjkdjgOHYA5CZ3AOIL37UIH7yCZAVNktlgn9e+CbhHan38fsDhSu3/oQ/Lj4AAAAASUVORK5CYII=", "22800d7693446bca5b0b2a44bbab4cfa737de71b81e1a72cf6743ca9f1672e9b"),
}
def paltext(colors):
    return "JASC-PAL\n0100\n16\n" + "".join("%d %d %d\n" % tuple(c) for c in colors)
def apply():
    for gender,(encoded,expected) in DATA.items():
        data = base64.b64decode(encoded, validate=True)
        assert hashlib.sha256(data).hexdigest() == expected
        with Image.open(io.BytesIO(data)) as raw:
            sprite = raw.copy()
        assert sprite.mode == "P" and sprite.size == (144,32)
        assert max(sprite.getdata()) <= 15 and sprite.info.get("transparency") == 0
        assert len({sprite.crop((16*i,0,16*(i+1),32)).tobytes() for i in range(9)}) == 9
        palette = sprite.getpalette()[:48]
        colors = [tuple(palette[i:i+3]) for i in range(0,48,3)]
        # Preserve existing non-walking geometry; remap legacy colors to the
        # shared overworld palette so indexed action sprites remain compatible.
        for path in (ASSETS/gender).glob("*.png"):
            if path.name in ("walking.png","running.png"):
                assert Image.open(path).size == (144,32), path
                path.write_bytes(data)
            else:
                with Image.open(path) as original:
                    assert original.mode == "P" and max(original.getdata()) <= 15, path
                    old = original.getpalette()
                    lut = [0] + [min(range(1,16), key=lambda j: sum((old[i*3+k]-colors[j][k])**2 for k in range(3))) for i in range(1,16)]
                    mapped = Image.new("P",original.size)
                    mapped.putdata([lut[i] for i in original.getdata()])
                    mapped.putpalette(palette+[0]*720)
                    mapped.save(path,bits=4,transparency=0)
        (PAL/(gender+".pal")).write_text(paltext(colors))
        reflection = [tuple((v*2+t)//3 for v,t in zip(c,(80,115,160))) for c in colors]
        reflection[0] = (148,230,230)
        (PAL/(gender+"_reflection.pal")).write_text(paltext(reflection))
        for action in ("walking.png","running.png"):
            assert hashlib.sha256((ASSETS/gender/action).read_bytes()).hexdigest() == expected
        print("Installed hatless Ranger overworld candidate:",gender,expected)
if __name__ == "__main__":
    apply()
