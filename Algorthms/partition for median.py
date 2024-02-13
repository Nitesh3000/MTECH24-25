import numpy as np
import math
import random
import warnings
array=[1,5,2,5,7,3,2,5,7,4,6,8,3,21,7]
def swap_columns(matrix, col1, col2):
    matrix[:, [col1, col2]] = matrix[:, [col2, col1]]
    
def partition(array, matrix, median):
    median_indices = find_element_index(matrix, median)
    row,column=matrix.shape
    left=0
    right=column-2
    print("median indices are: ",median_indices)
    if median_indices:
        # Perform the partition here based on the median element
        median_row, median_col = median_indices
        # Get the column containing the median element

        swap_columns(matrix,0,median_col)
        array[0],array[median_col]=array[median_col],array[0]
        i=left+1
        j=right
        pivot = array[left]
        while i<=j:
            if pivot>=array[i]:
                i+=1
            elif pivot<array[j]:
                j-=1
            else:
                array[i],array[j]=array[j],array[i]
                swap_columns(matrix,i,j)
                i+=1
                j-=1
        else:
            array[j],array[left]=array[left],array[j]
            swap_columns(matrix,j,left)
        return j,array,matrix
    else:
        print("NO_MEDIAN")

    # For simplicity, let's just return the median value
    #return median
def find_element_index(matrix, target):
    warnings.filterwarnings("ignore", category=DeprecationWarning)
    indices = np.where(matrix == target)
    warnings.filterwarnings("default", category=DeprecationWarning)
    if len(indices[0]) > 0 and len(indices[1]) > 0:
        return indices[0][0], indices[1][0]
    else:
        return None

def matrixFormation(A):
    n = len(A)
    if len(A) % 5 != 0:
        while len(A) % 5 != 0:
            A = np.append(A, float('inf'))
    rows = 5
    cols = int(math.ceil(len(A) // 5))
    matrix = np.reshape(A, (rows, cols), order='F')
    return partition(A, matrix, 3)
sorted_array = matrixFormation(array)
print(sorted_array)
#print("Sorted array:", sorted_array)