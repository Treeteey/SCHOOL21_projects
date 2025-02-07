def pascal():
    n = input()
    while True:
        try:
            n = int(n)
            if n > 0:
                break
        except ValueError:
            return "Natural number was expected"
    
    l = [[1],
         [1,1],
    ]
    if n == 0:
        return
    elif n < 3:
        for line in l[:n]:
            for num in line:
                print(num, end=" ")
            print()
        return
    else:
        cur = 2
        while cur < n:
            prev_line = l[cur-1]
            temp = [1]
            for i in range(len(prev_line)-1):
                temp.append(prev_line[i] + prev_line[i+1])
            temp.append(1)
            # print(temp)
            l.append(temp)
            cur += 1
    
    for line in l:
        for num in line:
            print(num, end=" ")
        print()
        
# слишком круто! Надо было было сделать так
def Internet_version(rows):
    row = [1]
    for i in range(rows):
        print(row)
        row = [sum(x) for x in zip([0]+row, row+[0])]


if __name__ == "__main__":
    pascal()