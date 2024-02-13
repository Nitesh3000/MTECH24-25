import random
size=20
A=[]
for _ in range(size):
  A.append(random.randint(0,1000))
#print(A)
B=A.copy()
n=len(A)
#bottomUp
def Alg_BottomUp(A):
    count=0
    for i in range((n//2)-1,-1,-1):
      for j in range(i,(n//2)):
        small=j
        if (2*j+1)<n:
          if A[2*j+1]<A[small]:
            small=2*j+1

        if (2*j+2)<n:
          if A[2*j+2]<A[small]:
            small=2*j+2

        if j!=small:
          A[j],A[small]=A[small],A[j]
          j=small
          count=count+1
    return count

def Alg_topDown(B):
    count=0
    for i in range(0,(n//2)-1):
      for j in range(i,(n//2)-1):
        small=j
        if (2*j+1)<n:
          if B[2*j+1]<B[small]:
            small=2*j+1
        if (2*j+2)<n:
          if B[2*j+2]<B[small]:
            small=2*j+2
        if j!=small:
          B[j],B[small]=B[small],B[j]
          j=small
          count=count+1
    return count
print()
print(Alg_BottomUp(A))
print(Alg_topDown(B))