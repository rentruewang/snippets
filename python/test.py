def threeargs(a, b, c):
    print(a, b, c)


if __name__ == "__main__":
    a = [1, 2, 3]

    threeargs(*a)

    b = [1, 2]
    threeargs(*b, 3)

    c = [2, 3]
    threeargs(1, *c)
