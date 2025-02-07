import sys
import requests

# Базовый URL сервера для взаимодействия
SERVER_URL = "http://127.0.0.1:8888/audio_uploader"

def upload_file(file_path):
    """
    Загружает файл на сервер через HTTP POST запрос.

    file_path: путь к файлу, который нужно загрузить.
    """
    try:
        with open(file_path, "rb") as file:  # Открываем файл в бинарном режиме
            # Отправляем файл на сервер
            response = requests.post(f"{SERVER_URL}/upload/", files={"file": file})
            if response.status_code == 200:
                print("File uploaded successfully.")  # Успешная загрузка
            else:
                print(f"Error: {response.text}")  # Ошибка, выводим ответ сервера
    except FileNotFoundError:
        print("File not found. Please check the file path.")  # Файл не найден

def list_files():
    """
    Получает список загруженных файлов с сервера через HTTP GET запрос.
    """
    response = requests.get(f"{SERVER_URL}/list/")  # Отправляем GET запрос
    if response.status_code == 200:
        files = response.json()  # Сервер возвращает JSON с именами файлов
        print("Uploaded files:")
        for file in files:
            print(file)  # Печатаем список файлов
    else:
        print(f"Error: {response.text}")  # Ошибка, выводим ответ сервера

if __name__ == "__main__":
    """
    Обрабатывает команды, переданные через аргументы командной строки.
    """
    if len(sys.argv) < 2:
        # Если аргументы не переданы, выводим инструкцию
        print("Usage:")
        print("  python screwdriver.py upload /path/to/file.mp3")  # Для загрузки файла
        print("  python screwdriver.py list")  # Для получения списка файлов
    elif sys.argv[1] == "upload" and len(sys.argv) == 3:
        # Загружаем файл, если команда и путь к файлу переданы
        upload_file(sys.argv[2])
    elif sys.argv[1] == "list":
        # Выводим список файлов
        list_files()
    else:
        print("Invalid command or arguments.")  # Некорректная команда
