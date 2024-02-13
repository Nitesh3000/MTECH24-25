A="abaababaab"
Next=[]
Next.append(0)
for i in range(1,len(A)):
    j=Next[i-1]
    flag=False
    while not flag and j!=0:
        if A[i]==A[j]:
            Next.append(j+1)
            flag=True
        else:
            j=Next[j-1]
    else:
        if not flag:
            if A[i]==A[0]:
                Next.append(1)
            else:
                Next.append(0)
print(Next)