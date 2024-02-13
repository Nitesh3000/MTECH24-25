#S1="abababbbabbabbbabbbaaaabba"
#abbabS2="babbbaaaabb"
Hash1=[]
def hashTable(S1,S2):
    #S2 is string to be compared
        hash=0
        for i in range(len(S2)):
            hash+=ord(S2[i])
        hash=hash
        #print("hash: ",hash)
        length=len(S2)

        for i in range(len(S1)-length+1):
            if i==0:
                sum=0
                for j in range(i,length):
                     sum+=ord(S1[j])
                Hash1.append(sum)
                #print(Hash1)
            else:
                 
                 Hash1.append((Hash1[i-1]-ord(S1[i-1])+ord(S1[i+length-1]))) 
                # print(Hash1)
            if Hash1[i]==hash:
                # print("entered")
                 l=i
                 matched=True
                 for k in range(0,len(S2)-1):
                      if S2[k]==S1[l]:
                           l+=1
                      else:
                           matched=False
                           break
                 if matched:
                      return "String matched from index index " + str(i)  + " to index " + str(i+len(S2)-1)
                      
        return "string Not Matched"   
            
S1=input("Enter The First String: ")
S2 = input("Enter the second string that is to be compared(should have smaller length than that of first string): ")
print(hashTable(S1,S2))
             
                    


