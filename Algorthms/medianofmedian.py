import random

def median_of_medians(medianList):
    medianList.sort()
    return medianList[len(medianList) // 2]

def grouping(A, left, right):
    B = []
    group = []
    medianList = []
    for i in range(left, right + 1):
        B.append(A[i])
        if len(B) == 5 or i == right:
            B.sort()
            midd = median_of_medians(B)
            medianList.append(midd)
            group.append(B)
            B = []
    return group, medianList

def Partition(A, left, right, i_th):
    if left == right:
        return A[left]

    group, medianList = grouping(A, left, right)
    pivot = median_of_medians(medianList)
    pivotI = A.index(pivot)
    A[pivotI], A[right] = A[right], A[pivotI]

    i = left
    for j in range(left, right):
        if A[j] < pivot:
            A[i], A[j] = A[j], A[i]
            i += 1
    A[i], A[right] = A[right], A[i]

    k = i - left + 1

    if i_th == k:
        return pivot
    elif i_th < k:
        return Partition(A, left, i - 1, i_th)
    else:
        return Partition(A, i + 1, right, i_th - k)

# Example usage:
size = 1000000
A = [random.randint(1, 1000) for _ in range(size)]
print("Original Array:", A)
x=A
x.sort()
print("Sorted Array: ",x)

i_th = len(A)//2  
result = Partition(A, 0, len(A) - 1, i_th+1)
print(f"The median element is: {result}")
