import random
size=100
A = []

for _ in range(size):
    A.append(random.randint(1,100))
#size=1000

'''for _ in range(size):
    A.append(random.randint(1,1000))'''
#finding left most occuance
def BSearchLeft(A,left,right,key):
    if left>right:
            return " Not Found "
    else:
        mid=(left+right)//2

        ''' if A[mid]==key:
            i=mid
            if A[i-1]==key:
                while A[i]==key:
                   i=i-1 
                return i+1'''
        if A[mid]==key:
            if mid==0 or A[mid-1]<key:
                 return mid
            else:
                 return BSearchLeft(A,left,mid-1,key)

        elif A[mid]<key:
            return BSearchLeft(A,mid+1,right,key)
        else:
                return BSearchLeft(A,left,mid-1,key)
print(A)
print(BSearchLeft(A,0,len(A)-1,98))

            
