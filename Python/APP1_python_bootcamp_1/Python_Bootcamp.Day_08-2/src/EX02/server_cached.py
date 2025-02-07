from fastapi import FastAPI, HTTPException  # Основной фреймворк и исключения
from pydantic import BaseModel  # Для валидации данных
import asyncio  # Для работы с асинхронным кодом
import httpx  # Для выполнения HTTP-запросов к URL-ам
import uuid  # Для генерации уникальных идентификаторов
from typing import Union
## EX02
import redis.asyncio as aioredis  # Asynchronous Redis client
from urllib.parse import urlparse
from contextlib import asynccontextmanager


# Настройки Redis
REDIS_HOST = "localhost"
REDIS_PORT = 6379
CACHE_TTL = 60  # Time-to-live время жизни кэша в секундах

# Конфигурация Redis клиента, подключение к Redis
# работает в качестве базы данных
# Redis сохраняет данные в формате key-value пар
# методы set() - добавляет пару ключ-значение в базу данных
# get() - возвращает значение по ключу
# incr() - увеличивает значение по ключу на 1
redis_client = aioredis.Redis(host=REDIS_HOST, port=REDIS_PORT, decode_responses=True)


# 
@asynccontextmanager
async def lifespan(app: FastAPI):
    try:
        await redis_client.ping()
        print("Redis connection established.")
    except Exception as e:
        print(f"Redis connection failed: {e}")
        raise e
    yield 
    await redis_client.close()


# Создаем FastAPI-приложение
app = FastAPI(lifespan=lifespan)



# Хранилище для задач в оперативной памяти
# key - uuid, value - {"status": "running" or "ready", "result": [int or None]}
# result - коды ответов
tasks = {}

# Модели данных получаемые от клиента
class TaskRequest(BaseModel):
    urls: list[str]  # Список URL-ов, переданных клиентом

# Модели данных отправляемые клиенту
class TaskResponse(BaseModel):
    id: str  # Уникальный идентификатор задачи
    status: str  # Статус задачи: "running" или "ready"
    result: list[Union[int, None]] = None  # Список кодов HTTP-ответов или None





@app.post("/api/v1/tasks/", response_model=TaskResponse, status_code=201)
async def create_task_id(task_request: TaskRequest):
    '''
    Ответ на запрос клиента с url'ами app.post()

    1) Создается id задачи
    2) Добавляется задача в хранилище tasks с начальным статусом "running"
    и пустыми результатами
    3) Асинхронно обрабатываются URL-ы в задаче
    4) Возвращается ответ клиенту в виде id задачи и статуса "running"

    response_model - возвращаемый тип данных

    :param task_request:
    :return: TaskResponse
    '''
    task_id = str(uuid.uuid4())  # Генерация уникального идентификатора
    tasks[task_id] = {"status": "running", "result": [None] * len(task_request.urls)}
    asyncio.create_task(process_urls(task_id, task_request.urls))
    return TaskResponse(id=task_id, status="running")


@app.get("/api/v1/tasks/{task_id}", response_model=TaskResponse)
async def get_task_status(task_id: str):
    '''
    Ответ на запрос клиента с id задачи app.get()

    1) Проверяется, существует ли задача в хранилище tasks
    2) Если задача существует, возвращается ответ клиенту в виде id задачи,
    статуса и результатов

    :param task_id:
    :return: TaskResponse
    '''
    if task_id not in tasks:  # Проверяем, существует ли задача
        raise HTTPException(status_code=404, detail="Задача не найдена")
    return TaskResponse(id=task_id, status=tasks[task_id]["status"], result=tasks[task_id]["result"])



async def process_urls(task_id: str, urls: list[str]):
    '''
    Функция для обработки URL-ов асинхронно  

    Запускается асинхронно в отдельном потоке
    Проверяется каждый URL и сохраняется код ответа
    Обновляется задача в tasks со статусом "ready" и результатами

    '''
    async with httpx.AsyncClient() as client:  # Асинхронный HTTP-клиент
        results = []
        for url in urls:
            try:
                cached_value = await redis_client.get(url)
                if cached_value:
                    results.append(int(cached_value))
                    print(f"URL {url} is cached")
                else:
                    # Выполняем HTTP GET-запрос к каждому URL
                    response = await client.get(url)
                    results.append(response.status_code)  # Сохраняем код ответа
                    # создает новую пару ключ-значение: url - code
                    # ex= - время жизни
                    await redis_client.set(url, response.status_code, ex=CACHE_TTL)

                # update domain counter
                # <scheme>://<netloc>/<path>;<params>?<query>#<fragment>
                domain = urlparse(url).netloc
                await redis_client.incr(f"domain:{domain}")

            except httpx.RequestError:
                # если запрос не удался, записываем пользовательский код ошибки
                default_error_code = 599  # Custom code for failed requests
                await redis_client.set(url, default_error_code, ex=CACHE_TTL)
                results.append(default_error_code)
                print(f"URL {url} encountered an exception. Cached as {default_error_code}")

        # Обновляем задачу со статусом "ready" и результатами
        tasks[task_id] = {"status": "ready", "result": results}


# запрос от клиента чтобы узнать сколько раз domain встречался
@app.get("api/v1/domains/{domain}", response_model=dict)
async def get_domain_metrics(domain: str):
    count = await redis_client.get(f"domain:{domain}")
    return {"domain" : domain, "request_count" : int(count) if count else 0}


async def cleanup_cache():
    while True:
        try:
            keys = await redis_client.keys("*")
            for key in keys:
                ttl = await redis_client.ttl(key)
                if ttl == -2:  # Key has expired
                    await redis_client.delete(key)
        except Exception as e:
            print(f"Error during cache cleanup: {e}")
        await asyncio.sleep(60)  # Run every 60 seconds



# Запуск сервера через Uvicorn
if __name__ == "__main__":
    import uvicorn
    uvicorn.run("server_cached:app", host="127.0.0.1", port=8888, reload=True)
