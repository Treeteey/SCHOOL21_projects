from django import forms
from .models import AudioFile

class AudioFileForm(forms.ModelForm):
    """
    Форма для загрузки файлов на основе модели AudioFile.
    """
    class Meta:
        model = AudioFile
        fields = ('file',)  # Поле для выбора файла
