import random

def find_median(numbers):
    n = len(numbers)
    numbers.sort()
    return numbers[n // 2]

def custom_partition(numbers, pivot):
    smaller, larger = [], []
    for num in numbers:
        if num < pivot:
            smaller.append(num)
        elif num > pivot:
            larger.append(num)
    return smaller, larger

def custom_select(numbers, index):
    if len(numbers) < 10:
        numbers.sort()
        return numbers[index]
    
    sublists = []
    idx = 0
    while idx + 5 < len(numbers) - 1:
        sublists.append(numbers[idx:idx + 5])
        idx += 5
    sublists.append(numbers[idx:])
    
    medians_of_sublists = []
    for sublist in sublists:
        medians_of_sublists.append(custom_select(sublist, (len(sublist) - 1) // 2))
    median_of_medians = custom_select(medians_of_sublists, (len(medians_of_sublists) - 1) // 2)
    
    list1, list2, list3 = [], [], []
    for num in numbers:
        if num < median_of_medians:
            list1.append(num)
        elif num > median_of_medians:
            list3.append(num)
        else:
            list2.append(num)
    
    if index < len(list1):
        return custom_select(list1, index)
    elif index < len(list1) + len(list2):
        return list2[0]
    else:
        return custom_select(list3, index - len(list1) - len(list2))

size = 1000000
A=[]
for _ in range(size):
    A.append(random.randint(0,1000000000000000000000))
print(A)
target_index = len(A) // 2

result = custom_select(A, target_index)
A.sort()  
print(f"The {target_index}th smallest element is:", result)
print(f"Expected value:", A[target_index])
