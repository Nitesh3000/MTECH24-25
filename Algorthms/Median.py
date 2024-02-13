import math
import random

size=37
A=[]
for _ in range(size):
    A.append(random.randint(1,1000))
print(A)
sorte=A
sorte.sort()
print(sorte)
def median_of_medians(medianList):
    medianList.sort()
    return medianList[len(medianList) // 2]

def grouping(A,left,right):

    B=[]
    group=[]
    medianList=[]
    for i in range(left,right+1):
        
        B.append(A[i])
        if(len(B)==5):
            j=0
            B.sort()
            midd=median(B,0,len(B)-1)
            medianList.append(midd)
            print(medianList)
            group.append(B)
            B=[]
            
    group.append(B)
    medianList.append(median(B,0,len(B)-1))
    print("Median List before Sorting: ",medianList)
    return group,medianList

def median(medianList,left,right):
   lenghth=right-left
   if lenghth==5 or lenghth==4:
       #print("Arrayyy",A[left::right+1])
       print(right,left)
       return medianList[left+2]
   elif lenghth==3 or lenghth==2:
       return medianList[left+1]
   else:
       return medianList[left]

def Partition(A,left,right,l):
    if(left==right):
        return A[left]
    
    
    group,medianList=grouping(A,left,right)
    '''if len(medianList)<=5:
        medianList.sort()
        print("returning ", medianList)
        pivot= median(medianList,0,len(medianList)-1)
    else:
        print("returning ", medianList)
        pivot= Partition(medianList,0,len(medianList)-1)'''
    pivot = median_of_medians(medianList)
    pivotI=A.index(pivot)
    A[pivotI],A[left]=A[left],A[pivotI] 
    i=left
    j=right
    while i<=j:
        if pivot>=A[i]:
            i+=1
        elif pivot<A[j]:
            j-=1
        else:
            A[i],A[j]=A[j],A[i]
            i+=1
            j-=1
    else:
        A[j],A[left]=A[left],A[j]
    
    k=i-left+1

    if l==k:
        return pivot
    elif l<k:
        return Partition(A,left,i-1,l)
    else:
        return Partition(A,i+1,right,l-k)
    

    

    
l=5
print(Partition(A,0,len(A)-1,l))


