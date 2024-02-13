import random

size = 10
A = []

for _ in range(size):
    A.append(random.randint(1, 5))

A.sort()
print(A)

left = 0
right = len(A) - 1
key = 4

while left <= right:
    mid = (right + left) // 2

    if A[mid] == key:
        if mid == 0 or A[mid-1]<key:
            print(mid)
            print("Found")
            break
        else:
            right = mid - 1

    elif A[mid] < key:
        left = mid + 1

    else:
        right = mid - 1

else:
    print("Not Found")
