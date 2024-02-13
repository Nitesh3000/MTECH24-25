import random
A=[1,2,3,4,5,6]
n=len(A)
for i in range(n-1):   
        k=random.randint(i,n-1)
        A[k],A[i]=A[i],A[k]
print(A)
