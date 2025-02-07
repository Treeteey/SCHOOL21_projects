# Exercise 01: Splitwise

# foo(*args)  - several arguments

def split_booty(*purses):
    purse1 = {"gold_ingots": 0}
    purse2 = {"gold_ingots": 0}
    purse3 = {"gold_ingots": 0}
    sum: int = 0
    left: int = 0
    base: int = 0
    for purse in purses:
        if "gold_ingots" in purse and purse["gold_ingots"] > 0:
            sum += purse["gold_ingots"]
    base = int(sum /3)
    left = sum % 3
    purse1["gold_ingots"] = base
    purse2["gold_ingots"] = base
    purse3["gold_ingots"] = base


    if left == 1:
        purse1["gold_ingots"] += 1
    elif left == 2:
        purse1["gold_ingots"] += 1
        purse2["gold_ingots"] += 1

    return purse1, purse2, purse3

# if __name__ == "__main__":
# означает что эта часть скрипта будет выполняться
# только тогда когда этот файл будет запущен через
#   "py splitwise.py"
# если же это файл будет импортирован в другой через
# "import splitwise", то эти тесты не будут выполнены


if __name__ == "__main__":
    purse1 = {"gold_ingots": 5}
    purse2 = {"gold_ingots": 0}
    purse3 = {"dog": 15}
    purse4 = {"gold_ingots": 20}

    purse_list = [purse1, purse2, purse3, purse4]

    # print(split_booty(*purse_list)) # тоже работает
    print(split_booty(purse1, purse2, purse3, purse4))