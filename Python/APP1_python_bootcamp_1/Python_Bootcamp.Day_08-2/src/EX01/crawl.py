import httpx  # Библиотека для выполнения HTTP-запросов
import sys  # Для работы с аргументами командной строки
import asyncio  # Для работы с асинхронным кодом

async def main():
    '''
    Выполнение скрипта клиентской части

    `py crawl.py <url1> <url2> ...`

    Проверяются аргументы и сохраняются в переменную urls
    Далее создается httpx клиент и отправляется запрос на сервер со списком URL-ов
    В ответ сервер отправляет ID созданной задачи и статус

    Далее клиент периодически запрашивает статус задачи обрабатываемой на сервере
    Если все URL-ы обработаны, то сервер отправляет обновленный статус задачи
    Если статус не "ready", то клиент ждет 1 секунду и снова запрашивает статус
    
    '''
    # Проверяем, что переданы аргументы (URL-ы)
    if len(sys.argv) < 2:
        print("Использование: python crawl.py <url1> <url2> ...")
        sys.exit(1)

    # Получаем список URL-ов из аргументов командной строки
    urls = sys.argv[1:]

    # Создаем асинхронный HTTP-клиент
    async with httpx.AsyncClient() as client:
        # Отправляем POST-запрос с URL-ами на сервер
        response = await client.post('http://127.0.0.1:8888/api/v1/tasks/', json={"urls": urls})
        if response.status_code != 201:  # Если сервер вернул ошибку
            print(f"Не удалось создать задачу: {response.status_code}, {response.text}")
            sys.exit(1)

        # Извлекаем ID созданной задачи из ответа сервера
        task = response.json()
        task_id = task["id"]
        print(f"Задача создана с ID: {task_id}. Ожидание завершения...")

        # Периодически запрашиваем статус задачи
        while True:
            status_response = await client.get(f'http://127.0.0.1:8888/api/v1/tasks/{task_id}')
            if status_response.status_code != 200:
                print(f"Ошибка при получении статуса задачи: {status_response.status_code}, {status_response.text}")
                sys.exit(1)

            # Проверяем статус задачи
            status_data = status_response.json()
            if status_data["status"] == "ready":  # Если задача завершена
                print("Задача завершена! Результаты:")
                # Выводим код ответа и URL
                for url, code in zip(urls, status_data["result"]):
                    print(f"{code}\t{url}")
                break

            await asyncio.sleep(1)  # Ждем 1 секунду перед следующим запросом

# Запуск асинхронной основной функции
if __name__ == "__main__":
    asyncio.run(main())



# async def - асинхронная функция (корутина). Асинхронные функции
# работают в рамаках цикла событий (event loop), который управляет переключением между
# корутинами (каждый 100 байт кода, управление передается следующей функции, а 
# предыдущая приостанавливается)
# При встрече с await выполнение текущей корутины приостанавливается, пока операция не завершится.
# Это позволяет другим корутинам продолжать выполнение в это время.

# httpx.AsyncClient()
# Создает асинхронный HTTP-клиент для выполнения запросов. 
# Это позволяет работать с HTTP в неблокирующем режиме, 
# идеально подходящем для асинхронных программ

# async with httpx.AsyncClient()
# Используется для автоматического управления подключениями. 
# Клиент открывается в начале блока async with и закрывается в конце, 
# гарантируя, что ресурсы не утекут.

# await приостанавливает выполнение текущей корутины до завершения 
# асинхронного запроса. Он "ждет" результата от сервера.

# response = await client
# Возвращается объект httpx.Response, содержащий статус, 
# тело ответа, заголовки и другие данные.

# Union[int, None]
# Указывает, что переменная может быть либо int, либо None. 
# Это полезно для обработки случаев, когда результат может отсутствовать.

# @app.post("/api/v1/tasks/", response_model=TaskResponse, status_code=201)
# response_model в @app.post
# Указывает, какую модель данных использовать для сериализации ответа. 
# Данные отправляются в формате JSON.

# uuid.uuid4()
# Генерирует уникальный идентификатор. Шанс повторения крайне мал, практически отсутствует.

# Зачем нужен Pydantic
# Для валидации входящих данных (например, список URL-ов) и сериализации ответов
# в стандартный формат (JSON). Это упрощает обработку данных и повышает надежность кода.

