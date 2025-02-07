cimport cython

@cython.boundscheck(False) # This disables bounds checking on array or list indices
@cython.wraparound(False) # This disables negative indexing for lists and arrays
def mul(list a, list b):
    cdef int rows_a = len(a)      # Number of rows in matrix 'a'
    cdef int cols_a = len(a[0])   # Number of columns in matrix 'a'
    cdef int cols_b = len(b[0])   # Number of columns in matrix 'b'
    cdef int rows_b = len(b)      # Number of rows in matrix 'b'
    cdef int row, col, k   
    # resulting matrix of size rows_a x cols_b      
    cdef list result = [[0 for _ in range(cols_b)] for _ in range(rows_a)] 
    cdef int temp               

    if cols_a != rows_b:
        raise ValueError("Matrices are not compatible for multiplication")

    for row in range(rows_a):
        for col in range(cols_b):
            temp = 0
            for k in range(cols_a):
                temp += a[row][k] * b[k][col]
            result[row][col] = temp
    return result