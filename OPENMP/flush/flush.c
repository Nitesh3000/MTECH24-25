#include <stdio.h>
#include <omp.h>

#define ARRAY_SIZE 10

int main() {
    int shared_var = 0;
    int array[ARRAY_SIZE];

    // Initialize the array with values from 1 to ARRAY_SIZE
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        array[i] = i + 1;
    }

    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();

        // Each thread performs its own computation
        int local_sum = 0;
        for (int i = 0; i < ARRAY_SIZE; ++i) {
            local_sum += array[i] * thread_id;
        }

        // Update the shared variable and ensure memory consistency
        #pragma omp critical
        {
            shared_var += local_sum;
            // Flush the shared variable to ensure memory consistency
            #pragma omp flush(shared_var)
        }

        printf("Thread %d: Local Sum: %d\n", thread_id, local_sum);
    }

    printf("Final Shared Variable Value: %d\n", shared_var);

    return 0;
}
