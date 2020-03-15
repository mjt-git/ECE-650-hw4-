import os
os.environ.setdefault("DJANGO_SETTINGS_MODULE", "ORM.settings")
import django
django.setup()

from ormApp.models import COLOR

def create_color():
    COLOR.objects.create(COLOR_ID=1, NAME="CDS")

create_color()
