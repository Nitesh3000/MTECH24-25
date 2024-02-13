import random
size=10
A=[]
for _ in range(size):
    A.append(random.randint(1,5))
A.sort()
print(A)
left=0
right=len(A)-1
key=4 #search element
if A:
    while(left<=right):
        mid=(left+right)//2
        if A[mid]==key:
            if mid==right or A[mid+1]>key:
                print( "the required element is found in index: ",mid)
                break
            else:
                left=mid+1           
        elif A[mid]<key:
            left=mid+1
        else:
            right=mid-1

    else:
        print( "Not Found" )
else:
    print("No element entered")
