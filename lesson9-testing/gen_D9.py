from random import randint as ri

n = ri(1, 2*10**5)
print(n)
print(*[ri(0, 10**9) for _ in range(n)])
