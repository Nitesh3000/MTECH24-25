import random

def partitionl(A, left, right, compare):
    A[left], A[right] = A[right], A[left]
    pivot = A[left]
    i = left + 1
    j = right
    while i <= j:
        if pivot >= A[i]:
            i += 1
            compare += 1
        elif pivot < A[j]:
            j -= 1
            compare += 1
        else:
            A[i], A[j] = A[j], A[i]
            i += 1
            j -= 1
            compare += 1
    
    A[j], A[left] = A[left], A[j]
    compare += 1
    return j, compare

def quickSortl(A, left, right, compare):
    if left <= right:
        mid, compare = partitionl(A, left, right, compare)
        compare = quickSortl(A, left, mid - 1, compare)
        compare = quickSortl(A, mid + 1, right, compare)
    return compare

size = 10000
A = []
compare = 0
for _ in range(size):
    A.append(random.randint(0, 100))
print("Original Array: ", A)
if A:
    compare = quickSortl(A, 0, len(A) - 1, compare)
    print(A, size - 1, compare)
else:
    print("No element in the Array")
