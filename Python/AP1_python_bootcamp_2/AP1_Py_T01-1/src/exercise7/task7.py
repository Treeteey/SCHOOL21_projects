def get_data() -> list[[int]]:
    st = input().strip()
    data = st.split(' ')
    # size if first line
    if len(data) != 2:
        print("Wrong input at: ", st)
        return []
    inp = []
    # get only positive numbers
    for num in data:
        try:
            n = int(num)
            if n < 0:
                print("Negative number: ", n)
                return []
            inp.append(n)
        except:
            print("Wrong input at: ", st)
            return []
    # check numbers quantity
    if len(inp) != 2:
        print("Wrong input")
        return []
    mat = []
    # check each line
    for i in range(inp[0]):
        str_line = input().strip()
        line = str_line.split(' ')
        if len(line) != inp[1]:
            print("Wrong input at len: ", line)
            return []
        row = []
        for num in line:
            try:
                n = int(num)
                if n < 0:
                    print("Negative number: ", n)
                    return []
                row.append(n)
            except:
                print("Wrong input at:")
                return []
        if len(row) != inp[1]:
            print("Wrong input at:", row)
            return []
        mat.append(row)
    return mat



def main() -> int:
    data = get_data()
    if len(data) != 0:
        sum = data[0][0]
        i = 0
        j = 0
        while i < len(data)-1 or j < len(data[0])-1:
            if i < len(data) - 1 and j < len(data[0]) - 1:
                if data[i+1][j] > data[i][j+1]:
                    sum += data[i+1][j]
                    i += 1
                else:
                    sum += data[i][j+1]
                    j += 1
            elif i == (len(data)-1) and j < len(data[0]) - 1:
                sum += data[i][j+1]
                j += 1
            elif j == (len(data[0])-1) and i < len(data) - 1:
                sum += data[i+1][j]
                i += 1        
    else:
        print("bad data")
    return sum


if __name__ == "__main__":
    print(main())