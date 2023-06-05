from libc.stdlib cimport rand

cpdef multiply_matrices(int n, int m):
    cdef list A = [0] * n
    cdef list B = [0] * m
    cdef list C = [0] * n

    cdef int i = 0
    cdef int j = 0
    cdef int k = 0

    for i in range(n):
        A[i] = [0] * m
        C[i] = [0] * n
    for i in range(m):
        B[i] = [0] * n

    for i in range(0, n):
        for j in range(0, m):   
            A[i][j] = rand() % 25

    for i in range(0, m):
        for j in range(0, n):
            B[i][j] = rand() % 25

    '''for i in range(n):
        print(A[i])
    print("\n")
    
    for i in range(m):
        print(B[i])
    print("\n")
    '''

    for i in range(0, n):
        for k in range(0, m):
            for j in range(0, n):
                C[i][j] += A[i][k] * B[k][j]
    '''
    for i in range(n):
        print(C[i])
    '''

    file = open("output_pyx.txt", "w")
    for i in range(n):
        file.write(str(C[i]))
        file.write("\n")
    file.close()

    return C
 