import random
size=10
#A=[1,2,3,3,4,5]
A=[]
for _ in range(size):
    A.append(random.randint(1,5))
#A=[]
A.sort()
print(A)
left=0
right=len(A)-1

#print(A)
key=4
if A:
    while(left<=right):
        mid=(left+right)//2
        if A[mid]==key:
            if mid==len(A)-1 or A[mid+1]>key:
                print( "the element ",key," is found in ",mid, " position" )
                print("found")
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
