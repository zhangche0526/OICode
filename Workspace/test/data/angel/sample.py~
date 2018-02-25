from cyaron import *
import random

_n = ati([0, 3, 10, 50, 100, 5, 50, 100, 200, 5, 50, 500, 1000, 2000, 1e4, 50, 1000, 1e4, 100, 1e4, 1e5])
_m = ati([0, 10, 100, 1e3, 1e3, 1e3, 1e3, 1e3, 1e3, 1e3, 1e5, 1e5, 1e5, 1e5, 1e5, 1e5, 1e5, 1e5, 1e6, 1e6, 1e6])
_t = [0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0]

for Case in range(1, 21):
    print Case
    test_data = IO(file_prefix="angel", data_id=Case)
    t = _t[Case]
    n = _n[Case]
    P = range(1, n+1)
    random.shuffle(P)
    sP = String.random(n, charset="LRUDFB")

    test_data.input_writeln(n)
    for i in range(0, n):
        if t == 1:
            test_data.input_writeln(sP[i], i+1)
        else:
            test_data.input_writeln(sP[i], P[i])

    m = _m[Case]
    vis = []
    T = range(0, m)
    sT = range(0, m)
    la = -1
    for i in range(0, m):
        T[i] = 0
    l = 0
    while l < m-n:
        p = randint(l,min(l+2*n,m-n))
        double_match = random.uniform(0,1) < 0.6
        if double_match == True:
            det = randint(1,9e4)
            while vis.count(det)>0:
                det = randint(1,9e4)
            vis.append(det)
            for i in range(0, n):
                T[p+i] = P[i]+det*100000
        else:
            for i in range(0, n):
                T[p+i] = randint(9e8,1e9)
        for i in range(0, n):
            sT[p+i] = sP[i]
        l = p+n

    for i in range(0, m):
        if T[i]==0:
            T[i] = randint(1,1e9)
            sT[i] = sP[randint(0,n-1)]

    test_data.input_writeln(m)
    for i in range(0, m):
        if t == 1:
            test_data.input_writeln(sT[i],i+1)
        else:
            test_data.input_writeln(sT[i],T[i])

