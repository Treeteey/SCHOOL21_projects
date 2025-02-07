def Check(str: str) -> bool:
    ret = True
    count_dot = 0
    for i in range(len(str)):
        ch = str[i]
        if not (ch.isdigit() or ch == '.' or ch == '-'):
            return False
        if ch == '-' and i != 0:
            return False
        if ch == '.':
            count_dot += 1
            if count_dot > 1:
                return False
    return ret
        

def ToFloat(str) -> float:
    integ = 0.0
    frac = 0.0
    nega = False
    if str[0] == '-':
        nega = True
        str = str[1:]
    integ_str = ''
    frac_str = ''
    if '.' in str:
        integ_str, frac_str = str.split('.')
    else:
        integ_str = str
    if integ_str != '':
        for i in range(len(integ_str)):
            integ = integ * 10 + int(integ_str[i])
    if frac_str != '':
        for j in range(len(frac_str)):
            frac = frac * 10 + int(frac_str[j])
    frac /= 10 ** len(frac_str)
    sum_ = integ + frac
    if nega:
        sum_ = -sum_
    return sum_*2


def main() -> float:
    str = input().strip()
    if Check(str):
        print(format(ToFloat(str), '.3f'))
        


def test():
    cases = [
        ('-14.97', -29.94), 
        ('-42.0', -84.0), 
        ('-4.3', -8.6), 
        ('0.01', 0.02), 
        ('1.0', 2.0), 
        ('-1.0', -2.0),
        ('231', 462.0),
    ]
    for case in cases:
        try:
            assert ToFloat(case[0]) == case[1]
            print(ToFloat(case[0]), case[1])
        except:
            print(case[0], case[1],' - Test failed = ', ToFloat(case[0]))
            


if __name__ == '__main__':
    # test()
    main()



