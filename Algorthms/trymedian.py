import numpy as np
import math
import random

size = 1000
A = [random.randint(0, 10) for _ in range(size)]
n = len(A)
print(A)
x = A.copy()

def matrixFormation(A):
    global n
    if n < 140:
        x = A.copy()
        x.sort()
        print("X:", x)
        return x[len(x) // 2]
    if len(A) % 5 != 0:
        num_inf_values = 5 - (len(A) % 5)
        A = A + [float('inf')] * num_inf_values  # Append the inf values
    rows = 5
    cols = (len(A) - 1) // rows + 1
    matrix = np.reshape(A, (rows, cols), order='F')
    return sort_matrix(matrix, rows, cols)

def sort_matrix(matrix, rows, cols):
    matrix = np.sort(matrix, axis=0)
    return median(matrix, rows, cols)

def median(matrix, rows, cols):
    column_median = matrix[2, :cols - 1]
    if n % 5 == 1 or n % 5 == 2:
        column_median = np.append(column_median, matrix[0, -1])
    elif n % 5 == 3 or n % 5 == 4:
        column_median = np.append(column_median, matrix[1, -1])
    elif n % 5 == 5:
        column_median = np.append(column_median, matrix[2, -1])

    return medianofmedian(column_median, len(column_median))

def medianofmedian(matrix, size):
    if len(matrix) <= 5:
        matrixx = matrix.flatten()
        matrixx = matrixx[matrixx != float('inf')]
        mm = size // 2
        median = matrixx[mm]
        return partition(matrixx, median)
    else:
        return matrixFormation(matrix)

def partition(A, part):
    n = len(A)
    loc = np.where(A == part)[0][0]  # Find index using numpy.where()
    i = 0
    j = n - 1
    A[0], A[loc] = A[loc], A[0]
    pivot = A[0]
    while i <= j:
        if pivot >= A[i]:
            i += 1
        elif pivot < A[j]:
            j -= 1
        else:
            A[i], A[j] = A[j], A[i]
            i += 1
            j -= 1
    else:
        A[j], A[0] = A[0], A[j]
    m = len(A[j:])
    if m > 5:
        return matrixFormation(A[j:])
    else:
        sortPartition = A[j:].copy()
        sortPartition.sort()

        if m == 0 or m == 1:
            return sortPartition[0]
        elif m == 2 or m == 3:
            return sortPartition[1]
        else:
            return sortPartition[3]

x.sort()
median_x = x[len(x) // 2]
mat = matrixFormation(A)

print("Median using sort():", median_x)
print("Median using matrixFormation:", mat)
