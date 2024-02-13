#A = [1, 2, 3, 5, 2, 2, 5, 4]
import random

size = 10
A = []

for _ in range(size):
    A.append(random.randint(1, 5))

print(A)
left = 0
right = len(A) - 1

while left < right:
    
        mid = (left + right) // 2
        max1 = max(A[left:mid+1])
        max2 = max(A[mid+1:right+1])
        if max1 > max2:
            right=mid
            
        else:
            left=mid+1
maxx=A[left]
print(maxx)
            
