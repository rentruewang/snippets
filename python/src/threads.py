import time
from multiprocessing.pool import ThreadPool


def print_periodically(num: int) -> None:
    while True:
        time.sleep(1)
        print(num)


if __name__ == "__main__":
    pool = ThreadPool(2)
    pool.map_async(print_periodically, range(2))

    print("here")
    time.sleep(10)
    print("done")
