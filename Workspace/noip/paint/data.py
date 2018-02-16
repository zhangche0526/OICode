import random

out_file = open("paint.in","w")

MAXN = 10
MAXK = 10

n = random.randint(MAXN*0.9, MAXN)
m = random.randint(MAXN*0.9, MAXN)
k = random.randint(MAXK*0.9, MAXK)

out_file.write( str(n)+" "+str(m)+" "+str(k)+"\n" )

for i in range(0,k):
    t = random.randint(0,1)
    x1 = random.randint(1,n)
    y1 = random.randint(1,m)
    x2 = 0
    y2 = 0
    if t == 0:
        if random.randint(0,1) == 0:
            det = random.randint(0,min(n-x1,m-y1))
            x2 = x1 + det
            y2 = y1 + det
        else:
            det = random.randint(0,min(n-x1,y1-1))
            x2 = x1 + det
            y2 = y1 - det
    else:
        x2 = random.randint(x1,n)
        y2 = random.randint(y1,m)
    out_file.write( str(t)+" "+str(x1)+" "+str(y1)+" "+str(x2)+" "+str(y2)+"\n" )
