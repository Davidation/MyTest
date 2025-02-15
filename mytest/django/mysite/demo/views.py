from django.shortcuts import render
from django.http import HttpResponse

def index(request):
    return HttpResponse("req path:{}".format(request.path))


