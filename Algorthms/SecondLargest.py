import random

size=10
A = []

for _ in range(size):
    A.append(random.randint(1,1000))

def secLar(A,left,right):
    mid=(left+right)//2
    if left==right:
        max1=A[left]
        return max1,-1
    elif right-left==1:
        if A[left]>=A[right]:
            max1=A[left]
            max2=A[right]
            return max1,max2
        else:
            max1=A[right]
            max2=A[left]
            return max1,max2
    else:
        max3,max4=secLar(A,left,mid)
        max5,max6=secLar(A,mid+1,right)
        if max3 >= max5:
            max1=max3
            if max4>=max5:
                max2=max4
            else:
                max2=max5
        else:
            max1=max5
            if max6>=max3:
                max2=max6
            else:
                max2=max3
    return max1,max2
print(A)
if A:
    Largest,secLargest=secLar(A,0,len(A)-1)
    print("Largest and Second Largest Element are: "+ str(Largest)+ " and " +str(secLargest))
else:
    secLar="Not Element in the Array"




