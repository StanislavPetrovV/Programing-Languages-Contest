import math
from time import perf_counter
from numba import njit, prange

@njit(fastmath=True, cache=True)
def is_prime(num):
    if num == 2:
        return True
    if num <= 1 or not num % 2:
        return False
    for div in range(3, int(math.sqrt(num)) + 1, 2):
        if not num % div:
            return False
    return True

@njit(fastmath=True, parallel=True, cache=True)
def run_program(N):
    for i in prange(N):
        is_prime(i)


if __name__ == '__main__':
    N = 10000000
    start = perf_counter()
    run_program(N)
    end = perf_counter()
    print(end - start)