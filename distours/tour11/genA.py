from random import randint as ri
from random import shuffle

n = ri(1, 10)
print(n)
l = []
for i in range(n):
    l.append(ri(1, 5))
print(*l)
shuffle(l)
print(*l)