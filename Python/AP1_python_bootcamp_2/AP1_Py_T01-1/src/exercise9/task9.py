def calc_expr():

    str1 = input().strip().split(' ')
    if len(str1) != 2:
        return
    try:
        power = int(str1[0])
        point = float(str1[1])
    except:
        return

    coefs = []
    for i in range(power+1):
        n = input().strip().split()
        try:
            num = float(n[0])
            coefs.append(num)
        except:
            print("wrong input at ", i + 1, "line")
            return
    coefs.reverse() # чтобы коэффициенты лежали согласно индексам
    
    integral = 0
    for i in range(power,0,-1):
        integral += (i * point ** (i-1) * coefs[i])
    
    print(integral)

if __name__ == "__main__":
    calc_expr()
