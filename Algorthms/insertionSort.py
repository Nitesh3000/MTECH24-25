import random
A=[]
size=10
for _ in range(size):
    A.append(random.randint(0,100))


#A=[2,4,1,4,6]
print(A)
def InsertionSort(A,key):
    for i in range(0,len(A)):
        key=A[i]
        j=i-1
        while j>=0 and key<A[j]:
            A[j+1]=A[j]
            j=j-1
        A[j+1]=key
    print(A)
InsertionSort(A,2)