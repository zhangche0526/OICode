import random

out_file = open("teleport10.in", "w")

MAXN = 1e6
n = random.randint(MAXN*0.9,MAXN)
out_file.write(str(n)+"\n")

rate = random.uniform(0.4,0.8)
m = int(n*rate)

ans = range(1,n+1)
random.shuffle(ans)
for i in range(1,m):
    out_file.write(str(ans[i-1])+" "+str(ans[i])+"\n")
for i in range(m,n):
    out_file.write(str(ans[random.randint(m-1,i-1)])+" "+str(ans[i])+"\n")

