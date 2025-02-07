from typing import Tuple

def main() -> Tuple():
    mat = []

    with(open("input.txt","r") as file):
        for line in file:
            new_line = "".join(line.split(" "))
            print(new_line)
            mat.append(new_line)

    # print(mat)
    for i in range(len(mat)):
        for j in range(len(mat[i])):
            count = 0
            if mat[i][j] == "1":
                count += 1
                cur_col = j+1
                cur_row = i
                while cur_col < len(mat[0]) and cur_row < len(mat) and mat[cur_row][cur_col] == "1":
                    count += 1
                    cur_col += 1
                


if __name__ == "__main__":
