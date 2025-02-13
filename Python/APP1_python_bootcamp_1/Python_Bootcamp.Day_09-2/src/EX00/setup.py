from distutils.core import setup, Extension

def main():
    setup(name="calculator",
          version="1.0.0",
          description="Python interface for the calculator C library function",
          author="Craydlec",
          author_email="",
          ext_modules=[Extension("calculator", ["calculator.c"])])

if __name__ == "__main__":
    main()