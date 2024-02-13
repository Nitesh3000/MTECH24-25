import random

size=1000
A = []

for _ in range(size):
    A.append(random.randint(1,1000))
currentHigh=1
for i in range(size):
    if A[i]>A[currentHigh]:
        currentHigh=i
print(currentHigh,A[currentHigh])


