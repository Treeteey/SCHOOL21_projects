# В задании EX00 EX01 если корабль вражеский то список офицеров пустой!
# Однако в задании EX02 нужно найти предателей - офицеров с уникальными
# имя-фамилия-ранг но в с разными принадлежностями:
# Ally Jone Doe Lieutenant
# Enemy John Doe Lieutenant 
# поэтому изменим в EX02 файл reporting_server.py чтобы он также генерировал
# списки офицеров для вражеских кораблей!


from concurrent import futures
import random
import grpc
import ship_pb2
import ship_pb2_grpc
import json

names = [
    "Lando",
    "Calrissian",
    "Red Guy",
    "Darth", 
    "Vader",
    "Luke",
    "Skywalker",
    "Leia",
    "Organa",
    "Obi-Wan", 
    "Kenobi"
    ]

first_names = [
    "Seth",
    "Xander",
    "Danny",
    "Mick",
    "Charles",
    "Manuel",
    "Michael",
    "Keiran",
    "Rocco",
    "Jessy",
    "Jonny",
    "Lexington ",
    "Scott",
    "Ron"
]

second_names = [
    "Gamble",
    "Corvus",
    "D",
    "Blue",
    "Dera",
    "Ferrara",
    "Vegas",
    "Lee",
    "Siffredi",
    "Jones",
    "Sins",
    "Steel",
    "Nails",
    "Jeremy"
]

ranks = [
    "Admiral of the Fleet",
    "Admiral",
    "Vice Admiral",
    "Rear Admiral",
    "Commodore",
    "Captain",
    "Commander",
    "Lieutenant Commander",
    "Lieutenant",
    "Sublieutenant",
    "Midshipman",
    "Noob",
    "Veteran",
]

class ServerResponceServicer(ship_pb2_grpc.ServerResponceServicer):
    def RouteChat(self, request_iterator, context):
        count = 0
        # print("===========================================")
        for coordinates in request_iterator:
            print(f"Received: {coordinates.hours}° {coordinates.minutes}' {coordinates.seconds}''")
            count += 1
        
        if count == 2:
            # Генерация случайных кораблей
            num_ships = random.randint(1, 10)
            print(f"Sending {num_ships} ships...")
            for _ in range(num_ships):
                alignment_=random.choice([ship_pb2.Ship.ALLY, ship_pb2.Ship.ENEMY])
                name_ = "Unknown" if alignment_ == ship_pb2.Ship.ENEMY else random.choice(names)


                # if alignment_ == ship_pb2.Ship.ENEMY:
                #     officers = []
                # else:
                #     officers=[
                #             ship_pb2.Ship.Officer(
                #                 first_name=random.choice(first_names),
                #                 last_name=random.choice(second_names),
                #                 rank=random.choice(ranks),
                #             ) for i in range(random.randint(1, 10))
                #         ]
# Заменили чтобы всегде генерировался!
                officers=[
                    ship_pb2.Ship.Officer(
                        first_name=random.choice(first_names),
                        last_name=random.choice(second_names),
                        rank=random.choice(ranks),
                    ) for i in range(random.randint(1, 10))
                ]

                class_ship_=random.choice(list(ship_pb2.Ship.Class.values()))
                if  class_ship_ == ship_pb2.Ship.Class.Dreadnought or \
                    class_ship_ == ship_pb2.Ship.Class.Carrier or \
                    class_ship_ == ship_pb2.Ship.Class.Destroyer:
                    length_=random.uniform(500, 20000.0)
                    size_=random.randint(50, 500)
                else:
                    length_=random.uniform(80.0, 1000.0)
                    size_=random.randint(5, 50)
                
                ship = ship_pb2.Ship(
                    alignment=alignment_,
                    name=name_,
                    # class_ship=random.choice(list(ship_pb2.Ship.Class.values())),
                    class_ship=class_ship_,
                    # length=random.uniform(50.0, 19000.0),
                    length=length_,
                    size=size_,
                    armed=random.choice([True, False]),
                    officers=officers
                )
                # print(ship)
                yield ship


def serve():
    server = grpc.server(futures.ThreadPoolExecutor(max_workers=10))
    ship_pb2_grpc.add_ServerResponceServicer_to_server(ServerResponceServicer(), server)
    server.add_insecure_port("[::]:50051")
    server.start()
    print("Server started. Listening on port 50051...")
    server.wait_for_termination()


if __name__ == "__main__":
    serve()
