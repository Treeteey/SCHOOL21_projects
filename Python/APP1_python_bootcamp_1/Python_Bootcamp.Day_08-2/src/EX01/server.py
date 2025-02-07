from fastapi import FastAPI, HTTPException  # Основной фреймворк и исключения
from pydantic import BaseModel  # Для валидации данных
import asyncio  # Для работы с асинхронным кодом
import httpx  # Для выполнения HTTP-запросов к URL-ам
import uuid  # Для генерации уникальных идентификаторов
from typing import Union


# Создаем FastAPI-приложение
app = FastAPI()

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
async def create_task(task_request: TaskRequest):
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
                # Выполняем HTTP GET-запрос к каждому URL
                response = await client.get(url)
                results.append(response.status_code)  # Сохраняем код ответа
            except httpx.RequestError:
                results.append(599)  # Если запрос не удался, записываем None
        # Обновляем задачу со статусом "ready" и результатами
        tasks[task_id] = {"status": "ready", "result": results}

# Запуск сервера через Uvicorn
if __name__ == "__main__":
    import uvicorn
    uvicorn.run("server:app", host="127.0.0.1", port=8888, reload=True)
