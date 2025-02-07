import json


def main():

    with open("input.txt", "r") as f:
        data = json.load(f)
        if CheckData(data):
            list1 = data["list1"]
            list2 = data["list2"]

            list_sum = list1 + list2
            list_sum = sorted(list_sum, key=lambda y: y['year'])
            list_sum = {"list0": list_sum}
            print(list_sum)

    
def CheckData(data: dict) -> bool:
    if "list1" not in data or "list2" not in data:
        print("Wrong data with list1 or list2")
        return False
    for line in data["list1"]:
        if "title" not in line or "year" not in line:
            print("Wrong data at:", str(line))
            return False
        try:
            int(line["year"])
        except:
            print("Wrong data at \"year\" : " + line["year"])
            return False
        if not isinstance(line["title"], str):
            print("Wrong data at : ", str(line))
            return False
    return True

if __name__ == "__main__":
    main()