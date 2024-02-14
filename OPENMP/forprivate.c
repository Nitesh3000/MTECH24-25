#include <stdio.h>
#include <omp.h>
#define ARRAY_SIZE 10

int main() {
    int my_array[ARRAY_SIZE];
    int total_sum = 0;

    for (int i = 0; i < ARRAY_SIZE; i++) {
        my_array[i] = i + 1;
    }

    // The 'local_sum' variable will be private to each thread
    int local_sum = 0;
    #pragma omp parallel for private(local_sum)
    // Each thread will have its private copy of 'local_sum'
    for (int i = 0; i < ARRAY_SIZE; i++) {
        local_sum += my_array[i]; // Each thread has its own 'local_sum'
        printf("Thread %d: Partial sum = %d\n", omp_get_thread_num(), local_sum);
    }

    return 0;
}
