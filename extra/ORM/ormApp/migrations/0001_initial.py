# Generated by Django 2.2 on 2020-03-15 03:00

from django.db import migrations, models


class Migration(migrations.Migration):

    initial = True

    dependencies = [
    ]

    operations = [
        migrations.CreateModel(
            name='COLOR',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('COLOR_ID', models.IntegerField()),
                ('NAME', models.CharField(max_length=50)),
            ],
        ),
        migrations.CreateModel(
            name='PLAYER',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('PLAYER_ID', models.IntegerField()),
                ('TEAM_ID', models.IntegerField()),
                ('UNIFORM_ID', models.IntegerField()),
                ('FIRST_NAME', models.CharField(max_length=50)),
                ('LAST_NAME', models.CharField(max_length=50)),
                ('MPG', models.IntegerField()),
                ('PPG', models.IntegerField()),
                ('RPG', models.IntegerField()),
                ('APG', models.IntegerField()),
                ('SPG', models.FloatField()),
                ('BPG', models.FloatField()),
            ],
        ),
        migrations.CreateModel(
            name='STATE',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('STATE_ID', models.IntegerField()),
                ('NAME', models.CharField(max_length=50)),
            ],
        ),
        migrations.CreateModel(
            name='TEAM',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('TEAM_ID', models.IntegerField()),
                ('NAME', models.CharField(max_length=50)),
                ('STATE_ID', models.IntegerField()),
                ('COLOR_ID', models.IntegerField()),
                ('WINS', models.IntegerField()),
                ('LOSSES', models.IntegerField()),
            ],
        ),
    ]