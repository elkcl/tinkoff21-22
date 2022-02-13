from subprocess import run
from random import randint as ri
from random import choice as ch
import sys

sol = '../../cmake-build-debug/C_spbf'
cnt = 100
m = 100000

for t in range(cnt):
    print('test', t+1)
    test = str(m) + '\n'
    for i in range(m):
        n = ri(2, 10)
        for j in range(n):
            test += ch(('0', '1'))
        test += '\n'
    #print(test)
    #break
    enc = run(['./%s' % sol], encoding='utf-8', capture_output=True, input=test).stdout
    sts = enc.split('\n')
    for st in sts:
        if st.count('?') < len(st) // 2:
            print('not enough ?')
            print()
            print('test:')
            print(test)
            print()
            print('enc:')
            print(enc)
            sys.exit()
    enc = str(m) + '\n' + enc
    dec = run(['./%s' % sol], encoding='utf-8', capture_output=True, input=enc).stdout
    dec = str(m) + '\n' + dec
    if test != dec:
        print('fail!\n')
        print('test:')
        print(test)
        print()
        print('enc:')
        print(enc)
        print()
        print('dec:')
        print(dec)
        print()
        # ts = test.split('\n')
        # es = enc.split('\n')
        # ds = dec.split('\n')
        # ind = 0
        # while ind < min(len(ts), len(ds)) and ts[ind] == ds[ind]:
        #     ind += 1
        # print(ind)
        # print('ts:', ts[ind])
        # print('es:', es[ind])
        # print('ds:', ds[ind])
        sys.exit()
