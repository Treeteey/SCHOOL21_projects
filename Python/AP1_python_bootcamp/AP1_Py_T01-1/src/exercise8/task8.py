def count_unique_numbers():
    n = input().strip()

    try:
        n = int(n)
    except:
        return

    dic = {}
    for i in range(n):
        num = input().strip()

        try:
            number = int(num[0])
            dic[number] = 1
        except:
            continue
    
    print(len(dic.keys()))

if __name__ == "__main__":
    count_unique_numbers()