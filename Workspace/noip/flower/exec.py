import os
for i in range(1,21):
    print i
    os.system("flower.exe < flower"+str(i)+".in > flower"+str(i)+".ans")
