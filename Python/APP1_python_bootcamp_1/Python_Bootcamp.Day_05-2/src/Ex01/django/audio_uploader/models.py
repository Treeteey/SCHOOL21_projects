from django.db import models

class AudioFile(models.Model):
    """
    Модель для хранения загруженных аудиофайлов.
    """
    file = models.FileField(upload_to='')  # Файлы будут сохраняться в MEDIA_ROOT

    def __str__(self):
        return self.file.name  # Возвращает имя файла как строковое представление
