from django.urls import path

from . import views

urlpatterns = [
    path("", views.index, name="index"),
    path('upload/', views.upload_view, name='upload'),
    path('list/', views.list_view, name='list'),
]