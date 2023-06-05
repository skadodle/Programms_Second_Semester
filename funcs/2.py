import random


def random_number(number=16):
    global lst
    x = lst.pop()
    x = ((lst[number - 2] + x) * lst[number]) % 2 ** 32
    yield x


if __name__ == "__main__":
    lst = [x for x in range(1, 33)]
    random.shuffle(lst)
    while(True):
        print(lst)
        lst.insert(0, next(random_number()))
        print(lst[0])
        if input() == '0':
            break
