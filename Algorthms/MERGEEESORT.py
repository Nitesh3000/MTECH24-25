def merge_sort(arr):
    if len(arr) <= 1:
        return arr

    mid = len(arr) // 2
    left_half = arr[:mid]
    right_half = arr[mid:]

    left_half = merge_sort(left_half)
    right_half = merge_sort(right_half)

    return merge(left_half, right_half)

def merge(left, right):
    merged_arr = []
    left_index, right_index = 0, 0

    while left_index < len(left) and right_index < len(right):
        if left[left_index] < right[right_index]:
            merged_arr.append(left[left_index])
            left_index += 1
        else:
            merged_arr.append(right[right_index])
            right_index += 1

    # Append any remaining elements from both lists
    merged_arr.extend(left[left_index:])
    merged_arr.extend(right[right_index:])
    
    return merged_arr

A = [3, 8, 1, 2, 6, 4, 7]
sorted_array = merge_sort(A)
print("Sorted array is:", sorted_array)
