import unittest

# __magic_methods__ - several default class methods
# 1) __init__  - when object is created, 
#   and is used to initialize objects attribute
# 2) __str__ - when you try to convert object to a string (or print() func)
# 3) __repr__: This method is called when you try to get a string
#    representation of an object using the repr() function
# 4) __len__: This method is called when you try to get the length 
#   of an object using the len() function.
# 5) __getitem__: This method is called when you try to access 
#   an object's attributes using square brackets ([]). 
# 6) __gt__ method is defined to compare two MyClass objects
#   based on their value attribute.




class Key:
    passphrase = "zax2rulez"
    def __init__(self):
        pass

    def __len__(self):
        return 1337
    
    def __getitem__(self, index):
        if index == 404:
            return 3
        
    def __gt__(self, other):
        if other == 9000:
            return True
    
    def __str__(self):
        return "GeneralTsoKeycard"
    

if __name__ == '__main__':
    key: Key = Key()
    print("Base checks:")
    print('len(key) == 1337  :', len(key) == 1337)
    print('key[404] == 3  :',key[404] == 3)
    print('key > 9000  :', key > 9000)
    print('key.passphrase == "zax2rulez" :',key.passphrase == "zax2rulez")
    print('str(key) == "GeneralTsoKeycard"  :', str(key) == "GeneralTsoKeycard")

    print()
    print("Another checks:")
    print('len(key) == 1330  :',len(key) == 1330)
    print('key[403] == 3  :',key[403] == 3)
    print('key[404] == 6  :',key[404] == 6)
    print('key > 8000  :', key > 8000)
    print('key > 10000  :', key > 10000)
    print('key.passphrase == "zax" :',key.passphrase == "zax")
    print('str(key) == "General"  :', str(key) == "General")

