str="aab"
rows, cols = (len(str), len(str))
LCNRS = [[0]*cols]*rows
print(LCNRS)
            
def LNONRS(str):
    for i in range(n):
        for j in range(i+1,n):
            if str[i-1]==str[j-1] and (j-i)>LCNRS[i-1][j-1]:
                LCNRS[i][j]+=1
            else:
                LCNRS[i][j]=0

print(LNONRS(str))