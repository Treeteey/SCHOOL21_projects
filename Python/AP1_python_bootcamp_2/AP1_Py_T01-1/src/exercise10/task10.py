from typing import List
import math

def get_data() -> list[(int,int,int)]:
    line = input().strip().split()
    if len(line) != 2:
        return
    try:
        line[0] = int(line[0]) 
        line[1] = int(line[1]) 
    except:
        print("not int")
        return

    if line[0] < 0 or line[1] < 0:
        print("Negative")
        return
    data_container = []
    for i in range(line[0]):
        data_line = input().strip().split()
        if len(data_line) != 3:
            return
        try:
            data_line[0] = int(data_line[0]) 
            data_line[1] = int(data_line[1]) 
            data_line[2] = int(data_line[2]) 
        except:
            print("not int")
            return
        data_container.append(data_line)
    # print(data_container)
    return line[0], line[1], data_container

def find_cheapest_pair(data: List, sum_: float):
    minimum_cost = math.inf
    data_dict = {}

    for line in data:
        if line[0] not in data_dict:
            data_dict[line[0]] = []        
        data_dict[line[0]].append(line)

    # print(data_dict)

    for key in data_dict.keys():
        value_list = data_dict[key]
        length = len(value_list)
        
        if  length > 1:
            for i in range(length - 1):
                for j in range(i+1, length):
                    if (value_list[i][2] + value_list[j][2]) == sum_ \
                        and minimum_cost > (value_list[i][1] + value_list[j][1]):
                        minimum_cost = (value_list[i][1] + value_list[j][1])
    print(minimum_cost)



if __name__ == "__main__":
    n, sum_, data_container = get_data()
    find_cheapest_pair(data_container, sum_)
    
