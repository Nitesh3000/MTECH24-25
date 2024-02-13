import random

size=100
A = []

for _ in range(size):
    A.append(random.randint(1,100))
#A=[1,2,3,4,5]
left=0
right=len(A)-1
while(left<=right):
    mid=(left+right)//2

    if left==right:
        max1=A[left]
        max2=-1
    elif right-left==1:
        if A[left]>=A[right]:
            max1=A[left]
            max2=A[right]
        else:
            max1=A[right]
            max2=A[left]
    else:
        max3,max4=A[left:mid+1]
        max5,max6=A[mid+1:right+1]
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
    print( max1,max2)

