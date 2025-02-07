# EX00

1) install ProtoBuf: `pip install protobuf3`


2) install gRPC: `python -m pip install grpcio`

    gRPC tools: `python -m pip install grpcio-tools`

3) generate classes with `protoc` compiler in current dir:

    `python -m grpc_tools.protoc -I. --python_out=. --pyi_out=. --grpc_python_out=. ship.proto`

4) `py reporting_server.py`
5) `py reporting_client.py 17 45 40.0409 −29 00 28.118`

---


Explanation on how stuff works:
1. Protobuf Definition (ship.proto)

    The .proto file defines the structure of messages and the gRPC service.

    Messages:

        Ship describes the attributes of a spaceship.
        Coordinates describes the galactic coordinates sent from the client to the server.
    Service:

        ServerResponce defines the gRPC service with one method, RouteChat, which:
            Accepts a stream of Coordinates messages from the client.
            Returns a stream of Ship messages from the server.
    Example: The client sends two Coordinates messages, and the server responds with a random number (1–10) of Ship messages.

2. Compiling the .proto File

    Using the grpc_tools Python library, you compile the .proto file into Python classes:
    bash
    ```
    python -m grpc_tools.protoc -I. --python_out=. --grpc_python_out=. ship.proto
    ```
    This generates two files:

        ship_pb2.py: Contains the Python representations of the Ship and Coordinates messages.
        ship_pb2_grpc.py: Contains the gRPC server and client stubs for the ServerResponce service.

3. gRPC Server Implementation

    The server implements the RouteChat method from the ServerResponce service:
    
    Key Steps in the Server:

        1) Receive Coordinates:
        2) Generate Ship Data:
            If exactly 2 Coordinates are received, the server generates a random number of Ship messages (1–10).
        3) Stream Ship Data:
            The server uses the yield statement to send Ship messages back to the client in real-time.
    
    The server runs and listens for incoming requests:

4. gRPC Client Implementation

    The client communicates with the server via a ServerResponceStub, which provides the RouteChat method.
    
    Key Steps in the Client:
        
        1) Parse Command-Line Arguments:
        2) Send Coordinates to Server:
            The client streams the Coordinates messages to the server:
        3) Receive and Process Ship Data:
            The client processes the stream of Ship messages from the server, converting each one into JSON format:

5. Communication Workflow
    
    - Server Start:

        The server listens on localhost:50051 for incoming gRPC requests.
    
    - Client Execution:

        The client sends two Coordinates messages to the server.
    
    - Server Response:

        The server receives the Coordinates, validates them, and generates a random number of Ship messages.
        These Ship messages are streamed back to the client.
    
    - Client Output:

        The client receives and prints the Ship messages in JSON format.



## EX01

1) `pip install pydantic`
2) `py reporting_server.py`
3) `py reporting_client_2v.py 17 45 40.0409 −29 00 28.118`


## EX02

1) `pip install SQLAlchemy`
2) `pip install psycopg2`
3) Создай базу данных в PostgreSql `spaceships_db`, пользователь `postgres`, пароль `password`, порт `5432`
4) `cd EX02\`
5) `py reporting_server.py`
6) `py reporting_client_3v.py scan 17 45 40.0409 -29 00 28.118`
---

Чтобы проверить `list_traitor` флаг можно в базу данных добавить пару строк:
```sql
-- вставить вручную предателя чтобы проверить list_traitor
INSERT INTO officers (alignment, first_name, last_name, rank, spaceship_id)
VALUES ('Ally', 'Michael', 'Sins', 'Captain', 5);
INSERT INTO officers (alignment, first_name, last_name, rank, spaceship_id)
VALUES ('Enemy', 'Michael', 'Sins', 'Captain', 5);
```
6) `py reporting_client_3v.py list_traitors`



## Как работает Pydantic в данном коде?
**Основные аспекты:**

1) Модель Ship и Officer:

    - Pydantic используется для валидации входящих данных.
    - Каждая модель (Ship и Officer) определяет структуру данных и типы полей:
        
        - alignment: str — строковое поле.
        - length: float — вещественное число.
        - officers: List[Officer] — список объектов типа Officer.

2) Валидация через декоратор @model_validator:

    - Метод validate_constraints выполняет валидацию сразу после проверки типов.
    - Здесь проверяются дополнительные правила, например:
        
        - Длина корабля должна быть в пределах, указанных в CLASS_CONSTRAINTS.
        - Размер экипажа должен соответствовать классу корабля.
        - Корабли класса Carrier не могут быть вооружены.
        - У вражеских кораблей имя должно быть Unknown.
3) Работа с Pydantic:

    - При обработке ответа от сервера данные из gRPC-сообщений конвертируются в словарь (ship_data).
    - Словарь передается в Pydantic-модель Ship:
        ```python
        validated_ship = Ship(**ship_data)
        ```
        Это:

        - Проверяет соответствие типов.
        - Выполняет дополнительные проверки через validate_constraints.
4) Преимущества Pydantic:

    - Если данные некорректны, выбрасывается исключение ValidationError, которое можно обработать и игнорировать "неправильные" данные.
    - После успешной валидации данные легко преобразовать в JSON или использовать в других частях программы.
---


## Как происходит работа с базой данных?
**Основные аспекты:**

1) Настройка SQLAlchemy:

    - Base = declarative_base() — базовый класс для всех ORM-моделей.
    - Создается подключение к базе данных:
        ```python
        engine = create_engine("postgresql+psycopg2://postgres:password@localhost:5432/spaceships_db")
        ```
        Здесь указывается:

        - Драйвер (postgresql+psycopg2).
        - Пользователь (postgres).
        - Пароль (password).
        - База данных (spaceships_db).

    - Создается сессия для взаимодействия с базой данных:
        ```python
        Session = sessionmaker(bind=engine)
        session = Session()
        ```
2) Определение ORM-моделей:

- `SpaceshipORM`: модель для хранения данных о кораблях.
- `OfficerORM`: модель для хранения данных об офицерах.
- Модели определяют таблицы, столбцы и связи между ними (например, связь между кораблем и офицерами через `spaceship_id`).

3) Создание таблиц:

- При первом запуске код создает таблицы в базе данных, если они еще не существуют:
    ```python
    Base.metadata.create_all(engine)
    ```
4) Сохранение данных (store_spaceship):

    - Функция принимает валидированные данные корабля.
    - Создается объект SpaceshipORM и добавляется в базу:
        ```python
        spaceship = SpaceshipORM(
            alignment=ship_data["alignment"],
            name=ship_data["name"],
            ...
        )
        session.add(spaceship)
        session.flush()  # Сохраняет объект и обновляет его ID.
        ```
    - После сохранения корабля добавляются данные офицеров:
        ```python
        officer_orm = OfficerORM(
            alignment=ship_data["alignment"],
            first_name=officer["first_name"],
            ...
            spaceship_id=spaceship.id,
        )
        session.add(officer_orm)
        ```
    - Изменения фиксируются в базе данных:
        ```python
        session.commit()
        ```

5) Работа с уникальными данными:

    - Для предотвращения дублирования используется ограничение UniqueConstraint в моделях:
        - Офицеры: `alignment`, `first_name`, `last_name`, `rank`.

6) Вывод "предателей" (`list_traitors`):

    - Запрос SQL находит офицеров, которые встречаются как на союзных, так и на вражеских кораблях:
        ```sql
        SELECT first_name, last_name, rank
        FROM officers
        WHERE alignment = 'Ally'
        INTERSECT
        SELECT first_name, last_name, rank
        FROM officers
        WHERE alignment = 'Enemy';
        ```
    - Результат выводится в формате JSON:
        ```python
        traitors = [{"first_name": row[0], "last_name": row[1], "rank": row[2]} for row in result]
        print(json.dumps(traitors, indent=2))
        ```

---

### `SQLAlchemy`
**ORM (Object-Relational Mapping)** — это технология программирования, которая позволяет работать с базой данных, используя объекты языка программирования вместо написания SQL-запросов напрямую.

**ORM-модель** — это класс в программе, который отражает структуру таблицы базы данных. С помощью ORM разработчики могут манипулировать данными, работая с объектами, а не с сырыми строками SQL.

Через объект **Session** ORM взаимодействует с базой данных: выполняет запросы, добавляет, удаляет или изменяет записи.


---
### `SQLAlchemy`
`declarative_base()` — это функция из SQLAlchemy, которая создает базовый класс для всех ORM-моделей.
- Этот базовый класс используется как основа для определения таблиц базы данных. Все модели (например, User, Spaceship) должны наследоваться от этого класса.
- Base знает обо всех моделях, которые от него наследуются.
- Позволяет создавать таблицы в базе данных с помощью
    ```python
    Base.metadata.create_all(engine)
    ```

---

### `protobuf` (`stub`)

`responses = stub.RouteChat(generate_coordinates_from_args())`

**stub** — это клиентский объект, сгенерированный grpcio, который используется для отправки запросов на сервер.

`stub` реализует интерфейс, определенный в `ship.proto` (например, `RouteChat`), чтобы клиент мог вызывать удаленные процедуры на сервере.
- Работа `RouteChat`:

    - Клиент отправляет данные координат (поток через generate_coordinates_from_args()).
    - Сервер отвечает потоком объектов (например, данные о кораблях).
    - Клиент считывает поток ответов через responses.