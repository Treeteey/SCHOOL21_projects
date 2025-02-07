# Exercise 00: Functional Purse

# from decorator import squeak

# The @squeak syntax is just a shortcut for add_ingot = squeak(add_ingot). 
# It applies the squeak decorator to the add_ingot function.
# @squeak is equal to: add_ingot = squeak(add_ingot)
# BUT: @squeak - placed before functions
# and "add_ingot = squeak(add_ingot)" - after functions

# можно добавить декораторы с функциями в текущем файле в другие файлы
# смотри decorator.py


def add_ingot(purse):
    purse2 = {"gold_ingots": 1}
    if "gold_ingots" in purse:
        purse2["gold_ingots"] = purse["gold_ingots"] + 1
    return purse2

def get_ingot(purse):
    purse2 = {"gold_ingots": 0}
    if "gold_ingots" in purse and purse["gold_ingots"] > 0:
        purse2["gold_ingots"] = purse["gold_ingots"] - 1
    return purse2

def empty(purse):
    purse2 = {"gold_ingots": 0}
    return purse2

# testing 00 ex
if __name__ == "__main__":
    purse = {"dawg", 3}
    print(empty(purse))
    print(add_ingot(get_ingot(add_ingot(empty(purse)))))
    print()

    purse2 = {"gold_ingots": 32}
    print(purse2)
    print(get_ingot(purse2))
    print(add_ingot(purse2))
    print(empty(purse2))


# purse = {"gold_ingots": 15}
# print(add_ingot(purse)) 

# print(get_ingot(purse)) 

# print(empty(purse)) 