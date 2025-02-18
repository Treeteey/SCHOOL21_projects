from requests import get
import asyncio
from aioconsole import ainput
from contextlib import suppress
import os
import sys
from prettytable import PrettyTable
import aiohttp
import pytest
import tempfile


# 
download_dir = ""
counter = 0
log = {}

# скачивание файла
async def download(url: str, counter: int):
    """
    Асинхронная функция, которая представляет собой задачу обработки.
    Скачивает данные из url и записывает в файл в папку download_dir 
    с именем {counter}.txt.
    :param url: Адрес для скачивания.
    :return:
    """
    global log
    global download_dir
    try:
        async with aiohttp.ClientSession() as session:
            async with session.get(url) as response:
                if response.status == 200:
                    # print(download_dir) # WRONG download_dir - is empty
                    file_path = os.path.join(download_dir, f"{counter}.jpg")
                    with open(file_path, "wb") as file:
                        file.write(await response.read())
                        log[url] = "Успех"
                else:
                    # print(f"Error {response.status_code} downloading")
                    log[url] = "Ошибка"
    except Exception as e:
        log[url] = "Ошибка"
        # print(f"Ошибка скачивания {url}: {e}")


# взятие следующего адреса из queue и отправление его в качестве аргумента в download
async def get_from_queue_to_download(queue: asyncio.Queue):
    """
    Асинхронный рабочий процесс, который бесконечно извлекает элементы из очереди
    и отправляет их на обработку функции download.
    :param queue: Очередь элементов для обработки.
    :return:
    """
    local_counter = 0
    while True:
        url = await queue.get()
        await download(url, local_counter)
        local_counter += 1
        queue.task_done()

# ожидание ввода пока не будет введена пустоая строка 
async def iostream(queue: asyncio.Queue):
    """
    Асинхронный процесс, который ждет ввода с консоли до тех пор, пока не будет введена пустая строка.
    Введенные строки добавляются в очередь для последующей обработки.
    :param queue: Очередь элементов для обработки.
    :return:
    """
    global counter
    while True:
        url = await ainput()
        url = url.strip()
        if url == "":
            print("ожидайте завершения загрузки")
            asyncio.create_task(waiting_info(queue))
            return
        await queue.put(url)
        counter += 1


async def manager(queue: asyncio.Queue, iostream_task: asyncio.Task, worker_task: asyncio.Task):
    """
    Менеджер координирует работу между вводом/выводом и рабочим процессом.
    Дожидается окончания ввода/вывода и обработки накопившейся очереди и завершает рабочий процесс.
    :param queue: Очередь элементов для обработки.
    :param iostream_task: Процесс ввода/вывода.
    :param worker_task: Рабочий процесс.
    :return:
    """
    await iostream_task
    # print("Finish process")
    await queue.join()
    worker_task.cancel()
    await worker_task


def clear_console():
    os.system("cls" if os.name == "nt" else "clear")


def clear_last_line():
    sys.stdout.write("\033[F")  # move cursor to previous line
    sys.stdout.write("\033[K")  # clear line
    sys.stdout.flush()

async def waiting_info(queue: asyncio.Queue):
    global counter
    while True:
        print(queue.qsize(), '/', counter)
        await asyncio.sleep(1)
        clear_last_line()
        if queue.qsize() == 0 and counter == 0:
            break


def make_table():
    clear_console()
    global log
    table = PrettyTable()
    table.field_names = ["URL", "Статус"]
    table.add_rows(zip(log.keys(), log.values()))
    print(table)





def check_write_access(directory):
    while True:
        try:
            testfile = tempfile.TemporaryFile(dir=directory)
            testfile.close()
            return True
        except Exception as e:
            print(f"Нет доступа на запись в папку {directory}: {e}")
            return False

async def main():
    global download_dir
    while True:
        download_dir = input("Введи папку для скачивания файлов\n(Enter -> текущая папка по умолчанию)\n")
        if download_dir == "":
            download_dir = os.getcwd()
        if os.path.isdir(download_dir) and check_write_access(download_dir):
            break
        else:
            print("Указанная папка не существует. Попробуйте еще раз.")

    # создание очереди элементов для обработки
    queue = asyncio.Queue()

    # создание задач
    worker_task = asyncio.create_task(get_from_queue_to_download(queue))
    iostream_task = asyncio.create_task(iostream(queue))
    manager_task = asyncio.create_task(manager(queue, iostream_task, worker_task))

    with suppress(asyncio.exceptions.CancelledError): # подавление CancelledError
        # возникает при отмене задачи
        await asyncio.gather(iostream_task, worker_task, manager_task)
    
    make_table()

#           https://bad-link-no-website-here.strange/img.png
#           https://bad-link-no-website-here.strange/img.png
#           https://images2.pics4learning.com/catalog/s/swamp_15.jpg
#           https://bad-link-no-website-here.strange/img.png
#           https://images2.pics4learning.com/catalog/p/parrot.jpg





if __name__ == '__main__':
    asyncio.run(main())
