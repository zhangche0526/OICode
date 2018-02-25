import os
for i in range(1,26):
    print i
    os.system("harmonics.exe < harmonics"+str(i)+".in"+" > harmonics"+str(i)+".ans")
