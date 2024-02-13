import random
Comp=[]
my_set=set()
for j in range(10000):
  A=[1,2,3,4,5,6]
  B=[]
  n=len(A)
  mapping = {element: random.randint(0, n**3) for element in A}
  sorted_mapping = dict(sorted(mapping.items(), key=lambda item: item[1]))
  shuffled_array = list(sorted_mapping.keys())
  #comp.append(A)
  my_set.add(tuple(shuffled_array))
  
print(len(my_set))