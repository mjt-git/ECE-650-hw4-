from django.db import models

# Create your models here.


class STATE(models.Model):
    STATE_ID = models.AutoField(primary_key=True)
    NAME = models.CharField(max_length=50, null=False)


class COLOR(models.Model):
    COLOR_ID = models.AutoField(primary_key=True)
    NAME = models.CharField(max_length=50, null=False)


class TEAM(models.Model):
    TEAM_ID = models.AutoField(primary_key=True)
    NAME = models.CharField(max_length=50, null=False)
    STATE_ID = models.ForeignKey(STATE, on_delete=models.CASCADE)
    COLOR_ID = models.ForeignKey(COLOR, on_delete=models.CASCADE)
    WINS = models.IntegerField(null=False)
    LOSSES = models.IntegerField(null=False)


class PLAYER(models.Model):
    PLAYER_ID = models.AutoField(primary_key=True)
    TEAM_ID = models.ForeignKey(TEAM, on_delete=models.CASCADE)
    UNIFORM_NUM = models.IntegerField(null=False)
    FIRST_NAME = models.CharField(max_length=50, null=False)
    LAST_NAME = models.CharField(max_length=50, null=False)
    MPG = models.IntegerField(null=False)
    PPG = models.IntegerField(null=False)
    RPG = models.IntegerField(null=False)
    APG = models.IntegerField(null=False)
    SPG = models.FloatField(null=False)
    BPG = models.FloatField(null=False)