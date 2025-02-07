
def main() -> bool:
    try:
        str = input()
        num = int(str)
        if num < 0:
            return False
        inverted = str[::-1]
        return str == inverted
    except:
        return False

    
if __name__ == "__main__":
    print(main())

