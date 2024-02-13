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
        compare=quickSort(A,left,mid-1,compare)
        compare=quickSort(A,mid+1,right,compare)
    return compare
def quickSort3way(A,left,right,compare):
    if left<=right:
        lt,rt,compare=partition3way(A,left,right,compare)
        compare=quickSort3way(A,left,lt-1,compare)
        compare=quickSort3way(A,rt+1,right,compare)
    return compare
def partition3way(A,lt,rt,compare):
    x=A[lt]
    left=lt
    right=rt
    i=left+1
    while i<=right:
        if A[i]<x:
           A[left],A[i]=A[i],A[left]
           i+=1
           left+=1
           compare+=1
        elif A[i]>x:
           A[i],A[right]=A[right],A[i]
           right-=1
           compare+=1
        else: 
            i+=1
            compare+=1
    return left,right,compare

def partitionl(A, left, right, compare):
    A[left], A[right] = A[right], A[left]
    pivot = A[left]
    i = left + 1
    j = right
    while i <= j:
        if pivot >= A[i]:
            i += 1
            compare += 1
        elif pivot < A[j]:
            j -= 1
            compare += 1
        else:
            A[i], A[j] = A[j], A[i]
            i += 1
            j -= 1
            compare += 1
    
    A[j], A[left] = A[left], A[j]
    compare += 1
    return j, compare

def quickSortl(A, left, right, compare):
    if left <= right:
        mid, compare = partitionl(A, left, right, compare)
        compare = quickSortl(A, left, mid - 1, compare)
        compare = quickSortl(A, mid + 1, right, compare)
    return compare

#partitioning using median of 1st median and last element
import random
def partitionm1l(A,left,right,compare):
    i=left+1
    j=right
    B={left:A[left],(right-left)//2:A[(right-left)//2],right:A[right]}
    print("B: ",B)
    C = dict(sorted(B.items(), key=lambda item: item[1]))
    print("C: ",C)
    sorte = list(C.keys())
    print("sorte: ",sorte)
    #sorte.sort()
    print("sorte sorted: ",sorte)
    if len(sorte)==3:
      A[sorte[1]],A[left]=A[left],A[sorte[1]]
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
def quickSortm1l(A,left,right,compare):
    if left<=right:
        mid,compare=partitionm1l(A,left,right,compare)
        compare=quickSortm1l(A,left,mid-1,compare)
        compare=quickSortm1l(A,mid+1,right,compare)
    return compare

import random
#for size in range(,100001,10000):
size=10 
A=[]
compare=0
for _ in range (size):
  A.append(random.randint(0,100))
B=C=D=E=A.copy()
n=len(A)
#print("Normal: ",quickSort(A,0,n-1,0),size)
#print("3way: ",quickSort3way(B,0,n-1,0),size)
#print("last: ",quickSortl(C,0,n-1,0),size)
print("med: ",quickSortm1l(D,0,n-1,0),size)
