def MergeSort(A,left,right):
    if len(A) <= 1:
            return A
    
    mid=(left+right)//2
    MergeSort(A,left,mid)
    MergeSort(A,mid+1,right)
    return Merge(A,left,mid,mid+1,right)
              
        
    
def Merge(A,left1,right1,left2,right2):
    i=0
    C=[0]* (right2-left1+1)
    
    while right1>=left1 and right2>=left2:
        if A[left1]>=A[left2]:
            print("here")
            C[i]=A[left2]
            left2+=1
        else:
            print("a here")
            C[i]=A[left1]
            left1+=1
        i=i+1
    
    while left1<=right1:
            print("aa here")

            C[i]=A[left1]
            left1+=1
            i+=1
    while left2<=right2:
            print("ab here")

            C[i]=A[left2]
            left2+=1
            i+=1
    print(C)
    for i in range(left1,right1):
        print("ac here") 
        A[i]=C[i]
    print(A)
          
    


        
    

A=[3,8,1,2,6,4,7]
sorted=MergeSort(A,0,len(A)-1)
print("Sorted array is: " ,sorted)

    
