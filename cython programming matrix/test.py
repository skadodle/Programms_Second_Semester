import main
import matrix_py
import time

if __name__ == "__main__":
    n, m = map(int, input().split())

    start_time = time.time()
    main.multiply_matrices(n, m)
    res1 = time.time() - start_time

    start_time = time.time()
    matrix_py.multiply_matrices(n, m)
    res2 = time.time() - start_time

    print(res1)
    print(res2)
    print(res2 / res1)