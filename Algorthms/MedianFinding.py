import numpy as np
import math
import random
size=1000
A=[]
for _ in range(size):
     A.append(random.randint(0,10))
#A=[1,3,6,78,8,3,56,45,1,354,65,754,3,132,46,57,5,234,9,66,55,5,6,35,9,88,66]
n=len(A)
print(A)
x=A

def matrixFormation(A):
    n=len(A)
    if (n<140):
         x=A
         x.sort()
         print("X: ",x)
         return x[len(x)//2]
    if len(A)%5!=0:
        while len(A)%5!=0:
            A=np.append(A,float('inf'))
    rows=5
    cols=int(math.ceil(len(A)//5))
    matrix = np.reshape(A, (rows, cols), order='F')
    return sort_matrix(matrix,rows,cols)
    

def sort_matrix(matrix,rows,cols): 
    matrix = np.sort(matrix,axis=0)
    print("sorted matrix: ",matrix)
    return median(matrix,rows,cols)
    

def median(matrix,rows,cols):
    

        column_median = matrix[2, :cols-1]
        if n%5 == 1 or n%5 ==2:
            column_median=np.append(column_median,matrix[0,-1]) 
        elif n%5 == 3 or n%5 ==4:
            column_median=np.append(column_median,matrix[1,-1]) 
        elif n%5 == 5:
            column_median=np.append(column_median,matrix[2,-1]) 

        
        median_value=medianofmedian(column_median,)
        return median_value
       
def medianofmedian(matrix):
            matrixx=matrix.flatten()
            if len(matrixx)>140:
                
                matrixx=matrixx[matrixx != float('inf')]
               
                mm=len(matrixx)//2
                median=matrixx[mm]
                return partition(matrixx,median)
            else:
                
                column = matrix.flatten()
                column = column[column != float('inf')]
                
                length = len(column)
                if length==1 or length==2:
                    return partition(A,column[0])
                elif length==3 or length==4:
                    return partition(A,column[1])
                elif length==5:
                    return partition(A,column[2])
            
                
def partition(A,part):
    print('part: ',part)
    n=len(A)

    loc=A.index(part)
    print("location: ",loc)
   
    i=0
    j=n-1
    print("Befor pivoting: ",A)
    A[0],A[loc]=A[loc],A[0]
    pivot = A[0]
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
        A[j],A[0]=A[0],A[j]
    print("After pivoting: ",A)
    m=len(A[j:])
    if m>5:
         return matrixFormation(A[j:])
    else:
         sortPartition = A[j:].copy()
         sortPartition.sort()

         if m==0 or m==1:
              return sortPartition[0]
         elif m==2 or m==3:
              return sortPartition[1]
         else:
              return sortPartition[3]
    
    
x.sort()
print(x)
mat=matrixFormation(A)
print("starting: ",mat)
