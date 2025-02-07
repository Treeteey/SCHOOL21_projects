# cat m.txt | py mfinder.py
# rstrip() - remove newline symbol

# r'' — это "сырая" строка в Python, что означает, 
# что обратные слеши (\) обрабатываются как буквальные символы, а не как спецсимволы.

# ^ соответствует началу строки

# \* соответствует литеральной звездочке (*). 
# Обратный слеш используется для экранирования звездочки

# [^\*] — это класс символов, который соответствует любому символу, 
# который не является звездочкой (*)

# {3} — это квантификатор, который указывает ровно 3 вхождения предыдущего шаблона

# $ соответствует концу строки


import sys
import re

# pattern1 = r'^\*[^\*][^\*][^\*]\*$' 
pattern1 = r'^\*[^\*]{3}\*$'        # или * + !* + !* + !* + *
pattern2 = r'^\*\*[^\*]\*\*$'       # или * + * + !* + * + *
pattern3 = r'^\*[^\*]\*[^\*]\*$'    # или * + !* + * + !* + *

count_line: int = 0
line_len: int = 0
nice: bool = True
for line in sys.stdin:
    count_line += 1
    line_len = len(line.rstrip())
    if line_len != 5 or count_line > 3:
        print('Error')
        exit()
    if count_line == 1 and not re.fullmatch(pattern1, line.rstrip()):
        nice = False
    elif count_line == 2 and not re.fullmatch(pattern2, line.rstrip()):
        nice = False
    elif count_line == 3 and not re.fullmatch(pattern3, line.rstrip()):
        nice = False
if nice:
    print('True')
else:
    print('False')