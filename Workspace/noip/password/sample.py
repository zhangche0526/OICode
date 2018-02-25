import random

out_file = open("password_sample3.in","w")

MAXN = 7e4
MAXM = 1e9

n = random.randint(MAXN*0.9,MAXN)
m = random.randint(MAXM*0.9,MAXM)

out_file.write(str(n)+" "+str(m)+"\n")

for i in range(1,n+1):
    a = random.randint(2,1e9)
    out_file.write(str(a)+" ")
