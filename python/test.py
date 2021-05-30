def args3(a, b, c):
    print(a, b, c)


if __name__ == "__main__":
    a = (1, 2, 3)

    args3(*a)

    b = (1, 2)
    args3(*b, 3)

    c = (2, 3)
    args3(1, *c)
