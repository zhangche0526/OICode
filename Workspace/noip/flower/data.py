import random

out_file = open("flower3.in","w")


MAXN = 10
MAXW = 1000

n = random.randint(MAXN*0.9,MAXN)
m = 0
'''
out_file.write(str(n)+" "+str(m)+"\n")

lst = range(2,n)
random.shuffle(lst)
lst.append(1)
lst.append(n)
lst.append(lst[0])
for i in range(1,len(lst)):
    u = lst[i-1]
    v = lst[i]
    w = random.randint(1,MAXW)
    out_file.write(str(u)+" "+str(v)+" "+str(w)+"\n")
'''
G = [(0,0,0)]
del G[0]

rate = random.uniform(0.3,0.9)

for u in range(1,n):
    for v in range(u+1,n+1):
        tmp = random.uniform(0,1)
        if tmp < rate:
            w = random.randint(1,MAXW)
            G.append((u,v,w))
            m += 1
out_file.write(str(n)+" "+str(m)+"\n")
random.shuffle(G)
for i in range(0,len(G)):
    out_file.write(str(G[i][0])+" "+str(G[i][1])+" "+str(G[i][2])+"\n")
