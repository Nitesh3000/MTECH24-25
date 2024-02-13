import random
A=[]
size=20
for _ in range(size):
    A.append(random.randint(0,8))
#print(A)
def quickSort3way(A,left,right,compare):
    if left<=right:
        lt,rt,compare=partition3way(A,left,right,compare)
        A,compare=quickSort3way(A,left,lt-1,compare)
        A,compare=quickSort3way(A,rt+1,right,compare)
    return A,compare
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
if A:
    compare=0
    A,count=quickSort3way(A,0,len(A)-1,0)
    print(A,count)
else:
    print("No Element")