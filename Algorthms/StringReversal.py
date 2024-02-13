import math
i=0
S="hgjh"
S = bytearray(S, 'utf-8')  
n=len(S)-1
while(i<=math.floor(n/2)):
    S[i],S[n-i]=S[n-i],S[i]
    i+=1
S = S.decode()
if S:  
    print(S)
else:
    print("Empty String")