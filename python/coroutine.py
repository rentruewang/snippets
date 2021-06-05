def f():
    yield 1
    yield 2
    yield 3
    return 4


x = f()
print(x)
for i in x:
    print(i)
y = f()
print(next(y))
print(next(y))
print(next(y))
print(next(y))
