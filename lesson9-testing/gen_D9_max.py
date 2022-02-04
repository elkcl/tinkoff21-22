from random import randint as ri

n = 2*10**5
print(n)
print(*[ri(10**8, 10**9) for _ in range(n)])
