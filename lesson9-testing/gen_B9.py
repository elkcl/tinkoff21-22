from random import randint as ri

n = 1
print(n)
for i in range(n):
    l = 10**5
    print(l, end=' ')
    print(*[ri(-10**9, 10**9) for x in range(l)])

