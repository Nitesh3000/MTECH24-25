import random

size=10
A = []

for _ in range(size):
    A.append(random.randint(1,1000))

def minmax(A,left,right):
    if left==right:
        minm=maxm=A[left]
        return minm,maxm
    elif right-left==1:
        maxm=max(A[left],A[right])
        minm=min(A[left],A[right])
        return minm,maxm
    else:
        mid=(left+right)//2
        min1,max1=minmax(A,left,mid-1)
        min2,max2=minmax(A,mid,right)
        if min1<=min2:
            minm=min1
        else:
            minm=min2
        if max1>=max2:
            maxm=max1
        else:
            maxm=max2
        return minm,maxm

print(A)
if A:
    print("minimum and maximum number are: "+ str(minmax(A,0,len(A)-1))  )
else:
    print("No element found")      

    
