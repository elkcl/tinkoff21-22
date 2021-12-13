from random import randint as ri
from random import choice as ch
from string import ascii_lowercase as asc

n = ri(1, 10**5)
s = ''
for i in range(n):
    s += ch(asc)
print(s)
