# Exercise 02: Squeak

import purse

# This decorator takes a function func as an argument
# and returns a new function wrapper. The wrapper 
# function prints "SQUEAK" and then calls the original
# function func with the original arguments *args and **kwargs.

def squeak(func):
    def wrapper(*args, **kwargs):
        print('SQUEAK')
        return func(*args, **kwargs)
    return wrapper

# The @squeak syntax is just a shortcut for add_ingot = squeak(add_ingot). 
# It applies the squeak decorator to the add_ingot function.
# @squeak is equal to: add_ingot = squeak(add_ingot)
# BUT: @squeak - placed before functions
# and "add_ingot = squeak(add_ingot)" - after functions

purse.add_ingot = squeak(purse.add_ingot)
purse.get_ingot = squeak(purse.get_ingot)
purse.empty = squeak(purse.empty)

if __name__ == "__main__":
    print('Purse1 squeaking:')
    purse1 = {"dawg", 3}
    print('purse1 = ', purse1)
    print(purse.empty(purse1))
    print(purse.add_ingot(purse.get_ingot(purse.add_ingot(purse.empty(purse1)))))
    print()

    print('Purse2 squeaking:')
    purse2 = {"gold_ingots": 32}
    print('purse2 = ', purse2)
    print(purse.get_ingot(purse2))
    print(purse.add_ingot(purse2))
    print(purse.empty(purse2))





