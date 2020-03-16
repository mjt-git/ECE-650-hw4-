import os
os.environ.setdefault("DJANGO_SETTINGS_MODULE", "ORM.settings")
import django
django.setup()
from ormApp.models import *

def add_player(team_id, jersey_num, first_name, last_name,
             mpg, ppg, rpg, apg, spg, bpg):
    PLAYER.objects.get_or_create(TEAM_ID=TEAM.objects.get(TEAM_ID=team_id), UNIFORM_NUM=jersey_num, FIRST_NAME=first_name,
                          LAST_NAME=last_name, MPG=mpg, PPG=ppg, RPG=rpg, APG=apg, SPG=spg, BPG=bpg)

def add_team(name, state_id, color_id, wins, losses):
    TEAM.objects.get_or_create(NAME=name, STATE_ID=STATE.objects.get(STATE_ID=state_id),
                        COLOR_ID=COLOR.objects.get(COLOR_ID=color_id), WINS=wins, LOSSES=losses)

def add_state(name):
    STATE.objects.get_or_create(NAME=name)

def add_color(name):
    COLOR.objects.get_or_create(NAME=name)

def query1(use_mpg, min_mpg, max_mpg,
             use_ppg, min_ppg, max_ppg,
             use_rpg, min_rpg, max_rpg,
             use_apg, min_apg, max_apg,
             use_spg, min_spg, max_spg,
             use_bpg, min_bpg, max_bpg):
    print("PLAYER_ID TEAM_ID UNIFORM_NUM FIRST_NAME LAST_NAME MPG PPG RPG APG SPG BPG")
    res = PLAYER.objects.all()
    if use_mpg == 1:
        res = res.filter(MPG__gte=min_mpg, MPG__lte=max_mpg)
    if use_ppg == 1:
        res = res.filter(PPG__gte=min_ppg, PPG__lte=max_ppg)
    if use_rpg == 1:
        res = res.filter(RPG__gte=min_rpg, RPG__lte=max_rpg)
    if use_apg == 1:
        res = res.filter(APG__gte=min_apg, APG__lte=max_apg)
    if use_spg == 1:
        res = res.filter(SPG__gte=min_spg, SPG__lte=max_spg)
    if use_bpg == 1:
        res = res.filter(BPG__gte=min_bpg, BPG__lte=max_bpg)
    for ply in res:
        print(str(ply.PLAYER_ID) + " " + str(ply.TEAM_ID.TEAM_ID) + " " + str(ply.UNIFORM_NUM) + " " + str(ply.FIRST_NAME) + " "
              + str(ply.LAST_NAME) + " " + str(ply.MPG) + " " + str(ply.PPG) + " " + str(ply.RPG) + " " + str(ply.APG)
              + " " + str(ply.SPG) + " " + str(ply.BPG))

def query2(team_color):
    print('NAME')
    res = TEAM.objects.all()
    res = res.filter(COLOR_ID__NAME=team_color)
    for team in res:
        print(team.NAME)

def query3(team_name):
    print('FIRST_NAME LAST_NAME')
    res = PLAYER.objects.all()
    res = res.filter(TEAM_ID__NAME=team_name).order_by('-PPG')
    for ply in res:
        print(ply.FIRST_NAME + ' ' + ply.LAST_NAME)

def query4(team_state, team_color):
    print('FIRST_NAME LAST_NAME UNIFORM_NUM')
    res = PLAYER.objects.all();
    res = res.filter(TEAM_ID__STATE_ID__NAME=team_state, TEAM_ID__COLOR_ID__NAME=team_color)
    for ply in res:
        print(ply.FIRST_NAME + ' ' + ply.LAST_NAME + ' ' + str(ply.UNIFORM_NUM))

def query5(num_wins):
    print('FIRST_NAME LAST_NAME NAME WINS')
    res = PLAYER.objects.all()
    res = res.filter(TEAM_ID__WINS__gt=num_wins)
    for ply in res:
        print(ply.FIRST_NAME + ' ' + ply.LAST_NAME + ' ' + ply.TEAM_ID.NAME + ' ' + str(ply.TEAM_ID.WINS))

query1(1, 35, 40,
    0, 10, 20,
    0, 1, 5,
    0, 1, 10,
    0, 0.3, 1,
    0, 0.2, 1)
print('*************************************************************')
query2("Maroon")
print('*************************************************************')

query3("Duke")
print('*************************************************************')

query4("NC", "DarkBlue")
print('*************************************************************')

query5(10)
