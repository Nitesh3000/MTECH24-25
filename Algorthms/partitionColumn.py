import numpy as np
import math
import random
import warnings

size = 1000
A = []
for _ in range(size):
    A.append(random.randint(0, 200))
print(A)
B=A.copy()
B.sort()
n=len(A)
def matrixFormation(A):
    n = len(A)
    if len(A) % 5 != 0:
        while len(A) % 5 != 0:
            A = np.append(A, float('inf'))
    rows = 5
    cols = int(math.ceil(len(A) // 5))
    matrix = np.reshape(A, (rows, cols), order='F')
    return sort_matrix(matrix, rows, cols,A)

def sort_matrix(matrix, rows, cols,A): 
    matrix = np.sort(matrix, axis=0)
    return median(matrix, rows, cols,A)

def median(matrix, rows, cols,A):
    n = np.sum(matrix != np.inf)
    column_median = matrix[2, :cols-1]
    if n % 5 == 1 or n % 5 == 2:
        column_median = np.append(column_median, matrix[0, -1]) 
    elif n % 5 == 3 or n % 5 == 4:
        column_median = np.append(column_median, matrix[1, -1]) 
    elif n % 5 == 5:
        column_median = np.append(column_median, matrix[2, -1]) 

    median_value = medianofmedian(column_median, matrix,A)
    return median_value

def lessthan150(array, matrix,A):
    n = len(array)
    array.sort()
    median = array[n // 2]
    return partition(array,matrix,median,A)

def medianofmedian(median, matrix,A):
    array = median.flatten()
    n = len(array)
    if n < 150:
        median = lessthan150(array, matrix,A)
        return median
    else:
        return matrixFormation(array)

def find_element_index(matrix, target,A):
    warnings.filterwarnings("ignore", category=DeprecationWarning)
    indices = np.where(matrix == target)
    warnings.filterwarnings("default", category=DeprecationWarning)
    if len(indices[0]) > 0 and len(indices[1]) > 0:
        return indices[0][0], indices[1][0]
    else:
        return None
def swap_columns(matrix, col1, col2):
    matrix[:, [col1, col2]] = matrix[:, [col2, col1]]

def partition(array, matrix, median,A):
    #median_indices = find_element_index(matrix, median,A)
    #row,column=matrix.shape
    median_indices = np.where(A==median)[0]
    left=0
    right=len(A)-1
    print("median indices are: ",median_indices)
    # Perform the partition here based on the median element
    #median_row, median_col = median_indices
    # Get the column containing the median element
    #swap_columns(matrix,0,median_col)
    A[0],A[median_indices]=A[median_indices],A[0]
    i=left+1
    j=right
    pivot = A[left]
    while i<=j:
        if pivot>=A[i]:
            i+=1
        elif pivot<A[j]:
            j-=1
        else:
            A[i],A[j]=A[j],A[i]
    #        swap_columns(matrix,i,j)
            i+=1
            j-=1
    else:
        A[j],A[left]=A[left],A[j]
     #   swap_columns(matrix,j,left)
    k=len(A[:j])
    if (len(A)//2 )<k:
        return matrixFormation(A[:j])
    elif (len(A)//2 )>k:
        return matrixFormation(A[j:])
    else:
        return pivot
 

'''    low = [j for j in A if j < pivot]
    high = [j for j in A if j > pivot]

    k = len(low)
    if i < k:
        return median_of_medians(low,i)
    elif i > k:
        return median_of_medians(high,i-k-1)
    else: #pivot = k
        return pivot'''

# Call the main function with the input array 'A'
median_value = matrixFormation(A)
print("Median of the array is:", median_value)
print("direct median: ",B[(n-1)//2])
