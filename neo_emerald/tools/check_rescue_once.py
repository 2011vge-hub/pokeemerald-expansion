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
# Chapter 2 has its own one-time certified payout after Briney's evidence.
# Restrict additional credit to one known guarded event; never allow a free
# mission/XP change from arbitrary map scripts.
city_path='data/maps/RustboroCity/scripts.inc'
office_path='data/maps/RustboroCity_Flat1_1F/scripts.inc'
expected_payers=[expected,expected,city_path,city_path,office_path,office_path]
if [str(x[0]) for x in payers]!=expected_payers:
    fail.append(f'Unexpected mission/XP writers: {payers}')
city=(ROOT/city_path).read_text()
try:
    liaison=city.split('RustboroCity_EventScript_NeoCampusFieldStudentRanger:',1)[1].split('RustboroCity_EventScript_C2ReportComplete:',1)[0]
    debrief=city.split('RustboroCity_EventScript_C2ReportComplete:',1)[1].split('RustboroCity_EventScript_C2ReportDone:',1)[0]
    if 'goto_if_set FLAG_NEO_C2_DEBRIEF_DONE, RustboroCity_EventScript_C2ReportDone' not in liaison:
        fail.append('Chapter 2 liaison must skip completed reward')
    if not (0<=debrief.find('setflag FLAG_NEO_C2_DEBRIEF_DONE')<debrief.find('addvar VAR_NEO_RANGER_MISSIONS')):
        fail.append('Chapter 2 completion flag must precede mission credit')
    if debrief.count('addvar VAR_NEO_RANGER_MISSIONS, 1')!=1 or debrief.count('addvar VAR_NEO_RANGER_XP, 150')!=1:
        fail.append('Chapter 2 reward counts must be exactly once')
except (ValueError,IndexError):
    fail.append('Missing guarded Chapter 2 liaison/debrief labels')
office=(ROOT/office_path).read_text()
report=office.split('NeoOffice_Report:',1)[1].split('NeoOffice_Complete:',1)[0]
if report.index('setvar VAR_NEO_CH3_STEP, 9') >= report.index('call NeoOffice_MissionCredit'):
    fail.append('Chapter 3 completion must precede mission credit')
assert office.count('call NeoOffice_MissionCredit')==1
assert 'goto_if_eq VAR_NEO_CH3_STEP, 9, NeoOffice_Complete' in office
assert 'goto_if_eq VAR_NEO_CH3_STEP, 8, NeoOffice_Report' in office
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
print('Ranger mission credit checks OK: separately guarded boarding and Chapter 2 payouts')
