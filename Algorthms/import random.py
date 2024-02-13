import random
A=[6, 66, 99, 45, 87, 81, 30, 5, 46, 1]
size=10
'''for _ in range(size):
    A.append(random.randint(0,100))'''
print(A)
def MinHeap(A):
    for j in range(len(A) // 2 - 1,-1,-1):
        i=j
        print("end of iteration ",j , A,i)
        while(i<=(len(A))//2-1):
            small=i
            if (2*i +1)<len(A):
                    
                if (A[i]> A[(2*i)+1]):
                    #A[(2*i)+1],A[i]=A[i],A[(2*i)+1]
                    #i=(2*i)+1
                    small=2*i+1
                    print(A,i)
            if (2*i+2)<len(A):
                if(A[small]> A[(2*i)+2]):
                    #A[(2*i)+2],A[i]=A[i],A[(2*i)+2]
                    small=(2*i)+2
                    print(A,i)
                
            if small!=i:
                A[small],A[i]=A[i],A[small]
                i=small
                print(A,"jf",i)
            else:
                break
                '''if A[2*i+2]:
                    if (A[(2*i)+1]<A[(2*i)+2]):
                        i=(2*i)+1
                        print(A,i)
                    else:
                        i=(2*i)+2
                        print(A,i)
                else:
                    i=2*i+1
                    print(A,i)
            else: 
                break'''
                
    return A
print(MinHeap(A))
