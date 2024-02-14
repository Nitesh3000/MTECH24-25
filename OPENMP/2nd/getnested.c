#include <stdio.h>
#include <omp.h>

int main() {
    int nested_enabled = omp_get_nested();
    printf("Nested Parallelism Enabled: %s\n", nested_enabled ? "Yes" : "No");

    #pragma omp parallel num_threads(2)
    {
        int thread_id = omp_get_thread_num();
        printf("Thread %d: Start - Outer Parallel Region\n", thread_id);

        // Outer Parallel Computation
        int outer_result = 0;
        for (int i = 0; i < 1000; ++i) {
            outer_result += i;
        }
        printf("Thread %d: Outer Parallel Computation Result: %d\n", thread_id, outer_result);

        // Enable Nested Parallelism
        #pragma omp master
        {
            omp_set_nested(1);
            nested_enabled = omp_get_nested();
            printf("Thread %d: Nested Parallelism Enabled: %s\n", thread_id, nested_enabled ? "Yes" : "No");
        }

        // Nested Parallel Region
        #pragma omp parallel num_threads(3)
        {
            int nested_thread_id = omp_get_thread_num();
            printf("Thread %d: Start - Nested Parallel Region (Inner Thread %d)\n", thread_id, nested_thread_id);

            // Nested Parallel Computation
            int nested_result = 0;
            for (int j = 0; j < 500; ++j) {
                nested_result += j;
            }
            printf("Thread %d: Nested Parallel Computation Result (Inner Thread %d): %d\n", thread_id, nested_thread_id, nested_result);

            printf("Thread %d: End - Nested Parallel Region (Inner Thread %d)\n", thread_id, nested_thread_id);
        }

        printf("Thread %d: End - Outer Parallel Region\n", thread_id);
    }

    return 0;
}
