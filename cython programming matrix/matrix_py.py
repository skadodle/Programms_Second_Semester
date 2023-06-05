import random
import string

def multiply_matrices(n, m):
    arrA = [0] * n
    arrB = [0] * m
    arrC = [0] * n

    for i in range(n):
        arrA[i] = [0] * m
        arrC[i] = [0] * n
    for i in range(m):
        arrB[i] = [0] * n

    for i in range(n):
        for j in range(n):
            arrC[i][j] = 0
        for j in range(m):
            arrA[i][j] = random.randint(1, 25)
    for i in range(m):
        for j in range(n):
            arrB[i][j] = random.randint(1, 25)

    # print("\n")
    # [print(arrA[i]) for i in range(n)]
    # print("\n")
    # [print(arrB[i]) for i in range(m)]

    for i in range(n):
        for k in range(m):
            for j in range(n):
                arrC[i][j] += arrA[i][k] * arrB[k][j]

    # print("\n")

    file = open("output_py.txt", "w")
    for i in range(n):
        file.write(str(arrC[i]))
        file.write("\n")
    file.close()

    # [print(arrC[i]) for i in range(n)]
