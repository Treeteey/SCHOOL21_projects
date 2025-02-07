import grpc
import sys
import json
import ship_pb2
import ship_pb2_grpc
from pydantic import BaseModel, Field, ValidationError, model_validator
from typing import List, Optional

# Define the constraints for each ship class
# (80, 250) - кортеж, содержащий минимальную и максимальную длину корабля
CLASS_CONSTRAINTS = {
    "Corvette": {"length_range": (80, 250), "size_range": (4, 10), "armed": True, "hostile": True},
    "Frigate": {"length_range": (300, 600), "size_range": (10, 15), "armed": True, "hostile": False},
    "Cruiser": {"length_range": (500, 1000), "size_range": (15, 30), "armed": True, "hostile": True},
    "Destroyer": {"length_range": (800, 2000), "size_range": (50, 80), "armed": True, "hostile": False},
    "Carrier": {"length_range": (1000, 4000), "size_range": (120, 250), "armed": False, "hostile": True},
    "Dreadnought": {"length_range": (5000, 20000), "size_range": (300, 500), "armed": True, "hostile": True},
}


# Define the Pydantic model for ship validation
class Officer(BaseModel):
    first_name: str
    last_name: str
    rank: str

class Ship(BaseModel):
    alignment: str
    name: str
    class_ship: str = Field(alias="class_ship")
    length: float
    size: int
    armed: bool
    officers: List[Officer]

    # @root_validator — это специальный метод в Pydantic, который позволяет валидировать
    # все поля модели сразу (в отличие от валидации отдельных полей с помощью @validator).
    # Основные особенности:
        # Выполняется после всех валидаторов для отдельных полей.
        # Имеет доступ ко всем значениям модели через словарь self.
        # Используется для валидации взаимосвязанных полей или сложных условий, которые 
        # зависят от нескольких полей.
    @model_validator(mode="after")
    def validate_constraints(self):
        class_ship = self.class_ship
        length = self.length
        size = self.size
        armed = self.armed
        alignment = self.alignment
        name = self.name
        officers = self.officers

        if class_ship not in CLASS_CONSTRAINTS:
            # raise ValueError(f"Invalid class: {class_ship}")
            raise ValueError()

        constraints = CLASS_CONSTRAINTS[class_ship]

        # Validate length
        if not (constraints["length_range"][0] <= length <= constraints["length_range"][1]):
            # raise ValueError(f"Invalid length {length} for class {class_ship}")
            raise ValueError()

        # Validate size
        if not (constraints["size_range"][0] <= size <= constraints["size_range"][1]):
            # raise ValueError(f"Invalid size {size} for class {class_ship}")
            raise ValueError()

        # Validate armed status for Carrier
        if class_ship == "Carrier" and armed:
            # raise ValueError(f"Invalid armed status {armed} for class {class_ship}")
            raise ValueError()

        if (class_ship == "Destroyer" or class_ship == "Frigate") and alignment == "Enemy": 
            # raise ValueError(f"Invalid alignment {alignment} for class {class_ship}")
            raise ValueError()
        
        # Validate name for enemy ships
        if alignment == "Enemy" and name != "Unknown":
            # raise ValueError("Enemy ships must have the name 'Unknown'")
            raise ValueError()

        if alignment == "Enemy" and officers:
            # raise ValueError("Enemy ships cannot have officers")
            raise ValueError()

        return self
    


def make_coordinates(hours, minutes, seconds):
    """Создает объект Coordinates из переданных данных."""
    return ship_pb2.Coordinates(hours=hours, minutes=minutes, seconds=seconds)


def generate_coordinates_from_args():
    """Генерирует координаты из аргументов командной строки."""
    if len(sys.argv) != 7:
        print("Usage: python reporting_client.py \"<hours minutes seconds> <hours minutes seconds>\"")
        sys.exit(1)

    try:
        longitude = make_coordinates(int(sys.argv[1]), int(sys.argv[2]), float(sys.argv[3]))
        latitude = make_coordinates(int(sys.argv[4]), int(sys.argv[5]), float(sys.argv[6]))
        yield longitude
        yield latitude
    except (ValueError, IndexError):
        print("Invalid format. Use: hours minutes seconds for each coordinate.")
        sys.exit(1)


def guide_route_chat(stub):
    """Обработка ответа от сервера и вывод в JSON."""
    try:
        responses = stub.RouteChat(generate_coordinates_from_args())
        for ship in responses:
            ship_data = {
                "alignment": "Ally" if ship.alignment == ship_pb2.Ship.ALLY else "Enemy",
                "name": ship.name,
                "class_ship": ship_pb2.Ship.Class.Name(ship.class_ship),
                "length": ship.length,
                "size": ship.size,
                "armed": ship.armed,
                "officers": [
                    {"first_name": officer.first_name,"last_name": officer.last_name,
                     "rank": officer.rank} for officer in ship.officers
                ],
            }
            try:
                # **ship_data - распаковка словаря, ключи становятся атрибутами модели
                validated_ship = Ship(**ship_data)
                print(json.dumps(ship_data, indent=2))
                # print(json.dumps(validated_ship.dict(by_alias=True), indent=2))
            except ValidationError as e:
                pass
                # print(f"Invalid ship data: {e}")
            
    except grpc.RpcError as e:
        print(f"Error from server: {e.details()} (code: {e.code()})")


def run():
    """Запуск клиента gRPC."""
    with grpc.insecure_channel("localhost:50051") as channel:
        stub = ship_pb2_grpc.ServerResponceStub(channel) # 
        guide_route_chat(stub)


if __name__ == "__main__":
    run()
