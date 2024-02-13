import random

size=1000
A = []

for _ in range(size):
    A.append(random.randint(1,1000))


def largest(Array,left,right):
    if left==right:
        return Array[left]
    else:
        mid=(left+right)//2
        max1=largest(Array,left,mid)
        max2=largest(Array,mid+1,right)
        if max1>max2:
            return max1
        else:
            return max2

maxx_value=largest(A,0,size-1)
print(A)
print(maxx_value)
