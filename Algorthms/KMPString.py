def Next(A):
    Next=[]
    Next.append(0)
    for i in range(1,len(A)-1):
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
    return Next
def KMP(S,P,Next):
    Found=False
    i,j=0,0
    n,m=len(S)-1,len(P)-1
    while not Found and n-i>=m-j:
        #print(i,j)
        if j==m:
            Found=True
            break
        elif S[i]==P[j]:
            i+=1
            j+=1

        elif S[i]!=P[j]:
            if j!=0:
                j=Next[j-1]
            i+=1
    if Found:
        print("String matched from index ", i-m, "to index ", i-1)
        return
    else:
        print("String not matched")
        return
# Load strings from files
with open('/home/et2023/Desktop/Algorthms/dna.txt', 'r') as file1, open('/home/et2023/Desktop/Algorthms/smalldna.txt', 'r') as file2:
    S = file1.read()
    P = file2.read()
#S="acctctgtgctccaccgaaccgtccaattttcggcgttaaagagtccgtgccgcatttcagtcagggtgcccacaaatctgaagagcgggggcggaaactcctctattatcctgacttcgcgacactttaacacaccgaagataacgttctatagatacgcgtccaggttgctgtctggaagaagtgacatacttttggtaagaccatgattcagcggggggtctgtatacagcctgaattggtacgatgttgcgccctacacggctattagccccttaaacgatctggccttaacatatgaacgtgatccttgccacgcgacgcgatatttaccccttttgtttgccccacgattttgtcgataatcctgaccttcgggattcgacccgccgcttcgcattcagttacagcatgttactaccaactcttccctatctcagtgactagaatccagctaaaaattccgacggacgtgttcaaattgttagggtcaggcctccacccggtgaggcgttgcagactatggagacattgttaattccatctgggcgttctcactcgactgcacctgcacacagcacttacgcttcgattcctgcaatctatgcggacacggcccgattgtaaccagataacgaagtttgcccctcctgcgagatttcctcttcatgtcatgacccccagccgcgcggttgccgcgggagggtgtccacacgacacgcgtagacgattggtgcactgtccaagactgcattggtacgtccagacgaatatgctatggaccgcatgaagcttttggccttgcggacgatgattcgcttgcaataacgttcatgtgcaacccatttaggaggcgtggtttcaacgcatctatagtaggaaggcacacctaatttcccgtgaatagtcctatgtcagctgcgtcacacttagcttccatcatgtggttttaacaatggcgagaccttgtaaggcacctcgaagatacatagagggttggctagctacgcgtatttactgagtccagtaaatatagtttagatttaattagaaagcagggcgcgattgtggtgatgcggagccacagcttaagtga"
#P="tttgccc"
if not S or not P:
    print("emtpy file")
else:
    Nex=Next(P)
    KMP(S,P,Nex)