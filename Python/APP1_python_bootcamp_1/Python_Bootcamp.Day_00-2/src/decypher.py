# python decypher.py "Have you delivered eggplant pizza at restored keep?"
# sys.stdin - file-like object
# readline() - read one line, wait for user input
# strip() - remove newline symbol after reading first line


import sys

line: str = sys.argv[1]
words = line.split() # split string by spaces into list of words
return_: str = ""
for word in words:
    return_ += word[0]
print(return_)

# print(''.join(word[0] for word in sys.argv[1].split()))