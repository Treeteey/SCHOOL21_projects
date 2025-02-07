from django.shortcuts import render, redirect
from django.http import HttpResponse, JsonResponse
from django.views.decorators.csrf import csrf_exempt  # Для отключения CSRF проверки
from .forms import AudioFileForm
from .models import AudioFile
import os
import mimetypes  # Для проверки MIME типа файла
import hashlib  # Для проверки хэш-суммы файла (определение дубликатов)

# Вспомогательные функции

def delete_orphaned_files():
    """
    Удаляет записи из базы данных, если соответствующие файлы отсутствуют на диске.
    """
    audio_files = AudioFile.objects.all()
    for audio_file in audio_files:
        if not os.path.exists(audio_file.file.path):  # Проверяем, существует ли файл
            audio_file.delete()  # Удаляем запись из базы данных

def is_duplicate(file):
    """
    Проверяет, является ли загруженный файл дубликатом на основе хэш-суммы.

    file: загружаемый файл.
    """
    file_hash = hashlib.md5(file.read()).hexdigest()  # Вычисляем MD5 хэш файла
    file.seek(0)  # Возвращаем указатель файла в начало

    # Сравниваем хэш загруженного файла с хэшами уже загруженных
    for audio_file in AudioFile.objects.all():
        with open(audio_file.file.path, 'rb') as existing_file:
            existing_hash = hashlib.md5(existing_file.read()).hexdigest()
            if file_hash == existing_hash:
                return True  # Найден дубликат
    return False  # Дубликатов нет

def handle_upload(file):
    """
    Обрабатывает загрузку файла: проверяет MIME тип, имя и дубликаты.

    file: загружаемый файл.
    Возвращает сообщение об ошибке или None, если ошибок нет.
    """
    mime_type = mimetypes.guess_type(file.name)[0]
    if mime_type not in ['audio/mpeg', 'audio/ogg', 'audio/wav']:
        return "Non-audio file detected."  # Некорректный MIME тип
    if AudioFile.objects.filter(file__icontains=file.name).exists():
        return "A file with this name already exists."  # Файл с таким именем уже существует
    if is_duplicate(file):
        return "This song has already been uploaded."  # Файл с таким содержимым уже загружен

    # Если ошибок нет, сохраняем файл
    audio_file = AudioFile(file=file)
    audio_file.save()
    return None  # Нет ошибок

# Основные представления

def index(request):
    """
    Отображает веб-страницу с формой загрузки и списком загруженных файлов.
    """
    delete_orphaned_files()  # Удаляем записи о файлах, которых нет на диске
    audio_files = AudioFile.objects.all()
    audio_files_with_names = [
        {'file': audio_file.file, 'filename': os.path.basename(audio_file.file.name)}
        for audio_file in audio_files
    ]
    error = None
    form = None  # Инициализируем форму

    if request.method == 'POST':
        form = AudioFileForm(request.POST, request.FILES)
        if form.is_valid():
            file = request.FILES['file']
            error = handle_upload(file)  # Проверяем файл
            if not error:
                return redirect('index')  # Перенаправляем на страницу при успешной загрузке
        else:
            error = "Invalid form submission"  # Ошибка валидации формы

    return render(request, 'audio_uploader/index.html', {
        'form': form,
        'audio_files': audio_files_with_names,
        'error': error,
    })

@csrf_exempt
def upload_view(request):
    """
    Обрабатывает запросы загрузки файлов от клиента через HTTP POST.
    CSRF защита отключена.
    """
    if request.method == 'POST':
        file = request.FILES.get('file')
        if file:
            error = handle_upload(file)  # Проверяем файл
            if not error:
                return HttpResponse("File uploaded successfully.")  # Успешная загрузка
            return HttpResponse(error, status=400)  # Возвращаем ошибку
        return HttpResponse("No file uploaded.", status=400)  # Файл не передан

def list_view(request):
    """
    Возвращает список загруженных файлов в формате JSON.
    """
    if request.method == 'GET':
        audio_files = AudioFile.objects.all()
        file_list = [os.path.basename(audio.file.name) for audio in audio_files]
        return JsonResponse(file_list, safe=False)  # JSON ответ
