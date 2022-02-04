from random import randint as ri

n = ri(2, 20)
print(n)
used = set()
for i in range(1, n):
    x, y = ri(1, i), i + 1
    print(x, y)
m = ri(1, 15)
print(m)
for i in range(m):
    x, y = ri(1, n), ri(1, n)
    while x == y:
        x, y = ri(1, n), ri(1, n)
    print(x, y)

