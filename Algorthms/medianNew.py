import numpy as np
import math
import random
size=1000
A=[]
for _ in range(size):
     A.append(random.randint(0,200))
#A=[1,3,6,78,8,3,56,45,1,354,65,754,3,132,46,57,5,234,9,66,55,5,6,35,9,88,66]

print(A)
def matrixFormation(A):
    n=len(A)
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
        n=np.sum(matrix != np.inf)
        #n=len(matrix)
        column_median = matrix[2, :cols-1]
        if n%5 == 1 or n%5 ==2:
            column_median=np.append(column_median,matrix[0,-1]) 
        elif n%5 == 3 or n%5 ==4:
            column_median=np.append(column_median,matrix[1,-1]) 
        elif n%5 == 5:
            column_median=np.append(column_median,matrix[2,-1]) 

        
        median_value=medianofmedian(column_median,matrix)
        return median_value
def lessthan150(array,matrix):
    n=len(array)
    
    array.sort()
    median=array[n//2]
    return median,matrix
def medianofmedian(median,matrix):
    array=median.flatten()
    n=len(array)
    if n<150:
        median,matrix=lessthan150(array,matrix)
    else:
        matrixFormation(array)
    return partition(array,matrix,median)

def find_element(matrix, target):
    target_broadcasted = np.full(matrix.shape, target)
    indices = np.argwhere(np.isclose(matrix, target_broadcasted))
    return indices[0] if indices.size > 0 else None


def partition(array,matrix,median):
    print(median)
    n=np.sum(matrix != np.inf)
    if n<150:
        return median
    else:
        indices=find_element(matrix,median)
        print("median is present in index: ",indices)

        

  
print(matrixFormation(A))
    