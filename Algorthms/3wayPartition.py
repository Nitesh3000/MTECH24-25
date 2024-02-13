import random
A=[]
size=20
for _ in range(size):
    A.append(random.randint(0,8))
print(A)
def partition(A,lt,rt):
    x=A[lt]
    left=lt
    right=rt
    #i,j,k=0,1,right
    i=left+1
    while i<=right:
        if A[i]<x:
           A[left],A[i]=A[i],A[left]
           i+=1
           left+=1
        elif A[i]>x:
           A[i],A[right]=A[right],A[i]
           right-=1
        else: 
            i+=1
    return A
if A:
    print(partition(A,0,len(A)-1))
else:
    print("No Element")