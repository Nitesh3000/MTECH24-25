import random
#A=[6, 66, 99, 45, 87, 81, 30, 5, 46, 1]
size=100000
A=[]
for _ in range(size):
    A.append(random.randint(0,100))
print(A)
def MaxHeap(A,n,i):
            # print("the element for min heap",A)
            #  for j in range(len(A) // 2 - 1,-1,-1):
            #    i=j
            #   while(i<=(len(A)-1)//2):
            big=i
            if (2*i +1)<n:
                    
                if (A[big]< A[(2*i)+1]):
                    
                    big=2*i+1
            if (2*i+2)<n:
                if(A[big]< A[(2*i)+2]):
                    
                    big=(2*i)+2
                
            if big!=i:
                A[big],A[i]=A[i],A[big]
                i=big
                MaxHeap(A,n,big)
           
                
   
def HeapSort(A):
    for i in range(len(A)//2-1,-1,-1):
         MaxHeap(A,len(A),i)
    print("Max Heap: ",A)

    for i in range(len(A)-1,0,-1):
        A[0],A[i]=A[i],A[0]
        #print(i,"th element in place ",A)
        MaxHeap(A,i,0)
       
print("Original Array",A)   
if A:      
    print(HeapSort(A))
    print(A)
else:
     print("empty Input")
