import random
A=[]
size = 100000
for _ in range(size):
    A.append(random.randint(0,100))
def selectionSort(A):
    for i in range(len(A)):
        for j in range(i+1,len(A)):
            if A[i]>=A[j]:
                A[i],A[j]=A[j],A[i]
selectionSort(A)
print(A)
