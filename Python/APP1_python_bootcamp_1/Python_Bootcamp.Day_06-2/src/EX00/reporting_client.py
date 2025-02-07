import grpc
import sys
import json
import ship_pb2
import ship_pb2_grpc


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
                "class": ship_pb2.Ship.Class.Name(ship.class_ship),
                "length": ship.length,
                "crew_size": ship.size,
                "armed": ship.armed,
                "officers": [
                    {
                        "first_name": officer.first_name,
                        "last_name": officer.last_name,
                        "rank": officer.rank,
                    } for officer in ship.officers
                ],
            }
            print(json.dumps(ship_data, indent=2))
    except grpc.RpcError as e:
        print(f"Error from server: {e.details()} (code: {e.code()})")


def run():
    """Запуск клиента gRPC."""
    with grpc.insecure_channel("localhost:50051") as channel:
        stub = ship_pb2_grpc.ServerResponceStub(channel)
        guide_route_chat(stub)


if __name__ == "__main__":
    run()
