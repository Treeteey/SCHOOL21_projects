import time
from itertools import tee
from matrix import mul as cython_mul

def python_mul(a, b):
    b_iter = tee(zip(*b), len(a))
    return [
        [
            sum(ele_a * ele_b for ele_a, ele_b in zip(row_a, col_b))
            for col_b in b_iter[i]
        ] for i, row_a in enumerate(a)
    ]

x = [[i for i in range(100)] for _ in range(100)]
y = [[i for i in range(100)] for _ in range(100)]

# Test Python implementation
start = time.time()
python_mul(x, y)
print(f"Python mul time: {time.time() - start:.5f} seconds")

# Test Cython implementation
start = time.time()
cython_mul(x, y)
print(f"Cython mul time: {time.time() - start:.5f} seconds")