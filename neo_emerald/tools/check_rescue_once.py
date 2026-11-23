#!/usr/bin/env python3
"""Static guard for one-time Mossdeep rescue mission credit.

Guards the single boarding payout, the state 4 -> 5 transition and
the sailor-gated rescue. This is static source analysis, not a runtime
transaction, ROM build or emulator test.
"""
import pathlib,re,sys
ROOT=pathlib.Path(__file__).resolve().parents[2]
fail=[]
payers=[]
for f in sorted((ROOT/'data').rglob('*.inc')):
    for i,line in enumerate(f.read_text(errors='replace').splitlines(),1):
        if re.match(r'\s*(addvar|setvar)\s+VAR_NEO_RANGER_(MISSIONS|XP)\b',line):
            payers.append((f.relative_to(ROOT),i,line.strip()))
expected='data/maps/MossdeepCity_Waterfront/scripts.inc'
office='data/maps/RustboroCity_Flat1_1F/scripts.inc'
if sorted(str(x[0]) for x in payers)!=sorted([expected,expected,office,office]):
    fail.append(f'mission/XP changed outside the boarding scene: {payers}')
wf=(ROOT/expected).read_text()
if not re.search(r'map_script_2 VAR_NEO_FERRY_DISPATCH, 4, MossdeepCity_Waterfront_EventScript_Boarding',wf):
    fail.append('boarding scene must run only at state 4')
if wf.count('MossdeepCity_Waterfront_EventScript_Boarding')!=2:
    fail.append('boarding referenced somewhere other than ON_FRAME and its label')
body=wf.split('MossdeepCity_Waterfront_EventScript_Boarding:',1)[1].split('\tend',1)[0]
i_state=body.find('setvar VAR_NEO_FERRY_DISPATCH, 5')
i_pay=body.find('addvar VAR_NEO_RANGER_MISSIONS')
if not(0<=i_state<i_pay):
    fail.append('state 5 must be set before mission credit')
md=(ROOT/'data/maps/MossdeepCity/scripts.inc').read_text()
if 'setvar VAR_NEO_FERRY_DISPATCH, 4' not in md.split('MossdeepCity_RangerChildRescue:',1)[-1].split('\tend',1)[0]:
    fail.append('escort must set state 4')
if md.count('setvar VAR_NEO_FERRY_DISPATCH, 4')!=1:
    fail.append('state 4 assigned in more than one place')
if 'goto_if_eq VAR_NEO_FERRY_DISPATCH, 3, MossdeepCity_RangerChildRescue' not in md:
    fail.append('child rescue must be gated on state == 3')
if fail:
    print('Ferry rescue once-only check FAILED:\n  '+'\n  '.join(fail))
    sys.exit(1)
print('Ferry rescue once-only check OK: credit only on boarding, state 4 -> 5 before payment')
