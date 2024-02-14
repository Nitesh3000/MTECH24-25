#include <stdio.h>
#include <omp.h>

int main() {
    int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10,11,12};
    int size = sizeof(data) / sizeof(data[0]);
    int threshold = 5;
    int num_threads = 3;  // Number of threads to use

    printf("Starting the program.\n");

    // Use parallelism if the array size exceeds the threshold, with a specified number of threads
    #pragma omp parallel if(size > threshold) num_threads(num_threads)
    {
        int thread_id = omp_get_thread_num();
        int chunk_size = size / num_threads;
        int start = thread_id * chunk_size;
        int end = start + chunk_size;

        // Distribute work among threads if the array size is large enough
        if (size > threshold) {
            printf("Thread %d is processing elements from index %d to %d.\n", thread_id, start, end);
            for (int i = start; i < end; ++i) {
                data[i] *= 2;  // Perform some processing on the data
            }
        } else {
            printf("Thread %d is processing the entire array.\n", thread_id);
            for (int i = 0; i < size; ++i) {
                data[i] *= 2;  // Perform some processing on the data
            }
        }
    }

    printf("All processing has been completed.\n");

    // Print the modified array
    printf("Modified array: ");
    for (int i = 0; i < size; ++i) {
        printf("%d ", data[i]);
    }
    printf("\n");

    return 0;
}
