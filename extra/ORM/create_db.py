import os
os.environ.setdefault("DJANGO_SETTINGS_MODULE", "ORM.settings")
import django
django.setup()

from ormApp.models import *
from django.core.management.color import no_style
from django.db import connection

def create_color():
    f = open('./color.txt', 'r')
    while True:
        line = f.readline()
        if not line:
            break
        COLOR.objects.create(NAME=line.split(' ')[1][:-1])
    f.close()


def create_state():
    f = open('./state.txt', 'r')
    while True:
        line = f.readline()
        if not line:
            break
        STATE.objects.create(NAME=line.split(' ')[1][:-1])
    f.close()


def create_team():
    f = open('./team.txt', 'r')
    while True:
        line = f.readline()
        if not line:
            break
        team_id, name, state_id, color_id, wins, losses = line.split(' ')
        TEAM.objects.create(NAME=name, STATE_ID=STATE.objects.get(STATE_ID=state_id),
                            COLOR_ID=COLOR.objects.get(COLOR_ID=color_id), WINS=wins, LOSSES=losses)
    f.close()


def create_player():
    f = open('./player.txt', 'r')
    while True:
        line = f.readline()
        if not line:
            break
        player_id, team_id, uniform_num, fname, lname, mpg, ppg, rpg, apg, spg, bpg = line.split(' ')
        PLAYER.objects.create(TEAM_ID=TEAM.objects.get(TEAM_ID=team_id), UNIFORM_NUM=uniform_num, FIRST_NAME=fname,
                              LAST_NAME=lname, MPG=mpg, PPG=ppg, RPG=rpg, APG=apg, SPG=spg, BPG=bpg)
    f.close()


def reset_sequence(model):
    """
    Reset the ID sequence for a model.
    """
    sql = connection.ops.sequence_reset_sql(no_style(), [model])
    for cmd in sql:
        connection.cursor().execute(cmd)


def main():
    reset_sequence(STATE)
    reset_sequence(COLOR)
    reset_sequence(TEAM)
    reset_sequence(PLAYER)
    # sequence_sql = connection.ops.sequence_reset_sql(no_style(), [STATE, COLOR, TEAM, PLAYER])
    # print("**************")
    # print(sequence_sql)
    # print('**************')
    # with connection.cursor() as cursor:
    #     for sql in sequence_sql:
    #         cursor.execute(sql)
    create_color()
    create_state()
    # create_team()
    # create_player()


if __name__ == '__main__':
    main()
