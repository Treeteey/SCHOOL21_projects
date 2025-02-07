import math

def main() -> float:
    while True:
        coords1 = input()
        try:
            coords1 = [float(x) for x in coords1.split()]
        except:
            print("Invalid input")
            continue
        if len(coords1) == 3:
            break
        else:
            print("Invalid input")

    while True:
        coords2 = input()
        try:
            coords2 = [float(x) for x in coords2.split()]
        except:
            print("Invalid input")
            continue
        if len(coords2) == 3:
            break
        else:
            print("Invalid input")
    # print(coords1, coords2)
    length = coords1[0]*coords2[0] + coords1[1]*coords2[1] + coords1[2]*coords2[2]    # print(length)
    return length

if __name__ == "__main__":
    print(main())
