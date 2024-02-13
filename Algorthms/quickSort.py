import random
def partition(A,left,right,compare):
    i=left+1
    j=right
    pivot = A[left]
    while i<=j:
        if pivot>=A[i]:
            i+=1
            compare+=1
        elif pivot<A[j]:
            j-=1
            compare+=1

        else:
            A[i],A[j]=A[j],A[i]
            i+=1
            j-=1
            compare+=1
    else:
        A[j],A[left]=A[left],A[j]
        compare+=1
    return j,compare
def quickSort(A,left,right,compare):
    if left<=right:
        mid,compare=partition(A,left,right,compare)
        A,compare=quickSort(A,left,mid-1,compare)
        A,compare=quickSort(A,mid+1,right,compare)
    return A,compare

for size in range(1,1000,100):
    #size=10
    A=[]
    compare=0
    for _ in range(size):
        A.append(random.randint(0,100))
    #print("Original Array: ",A)
    if A:
        #print("The Sorted Array is: ",quickSort(A,0,len(A)-1))
        A,compare=quickSort(A,0,len(A)-1,compare)
        #print(A,size-1,compare)
        print(size-1 , compare)
    else:
        print("No element in the Array")