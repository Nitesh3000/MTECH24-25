#include <stdio.h>
#include <omp.h>

#define ARRAY_SIZE 5

int main() {
    int shared_var = 0;
    int array[ARRAY_SIZE];

    // Initialize the array with values from 1 to ARRAY_SIZE
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        array[i] = i + 1;
    }

    #pragma omp parallel
    {
        #pragma omp for
        for (int i = 0; i < ARRAY_SIZE; ++i) {
            int temp_result = array[i] * array[i];

            #pragma omp critical
            {
                // Critical section: Accumulate the temporary result into the shared variable
                shared_var += temp_result;
            }
        }
    }

    printf("Final Shared Variable Value: %d\n", shared_var);

    return 0;
}
