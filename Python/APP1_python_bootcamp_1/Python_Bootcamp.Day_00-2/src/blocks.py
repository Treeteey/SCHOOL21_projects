# cat data_hashes_10lines.txt | py blocks.py 10
# strip() - remove newline symbol
import sys

number_of_lines: int = int(sys.argv[1])
while number_of_lines > 0:
    number_of_lines -= 1
    for line in sys.stdin:
        if len(line.strip()) == 32:
            count: int = 0
            for char in line:
                if char == '0':
                    count += 1
                else: break
            if count == 5:
                print(line.strip())