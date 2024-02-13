import random
size=10
A=[]
B=[]
ran=3
for _ in range(size):
    A.append(random.randint(0,3))
print(A)
def count(A):
    for i in range(ran+1):
        count=0
        for j in range(size):
            if A[j]==i:
                count+=1
        B.append(count)
    return B
print(count(A))
                
            

