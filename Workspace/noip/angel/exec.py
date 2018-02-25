import os
for i in range(1,21):
    print i
    os.system("angel.exe < angel"+str(i)+".in"+" > angel"+str(i)+".ans")
