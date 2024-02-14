#include <stdio.h>
#include <omp.h>

int main() {
    int num_threads = 4;
    int array_size = 10;
    int array[array_size];

    for (int i = 0; i < array_size; ++i) {
        array[i] = i + 1;
    }

    omp_set_num_threads(num_threads);

    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        int local_sum = 0;

        // Set the scheduling kind to omp_sched_static with a modifier of 2
        omp_set_schedule(omp_sched_static, 2);

        // Print scheduling information
        printf("Thread %d: Using static scheduling with a modifier of 2\n", thread_id);

        // Use runtime scheduling with the specified kind and modifier
        #pragma omp for schedule(runtime)
        for (int i = 0; i < array_size; ++i) {
            local_sum += array[i];
            printf("Thread %d: Array[%d] = %d\n", thread_id, i, array[i]);
        }

        // Print the local sum for each thread
        printf("Thread %d local sum: %d\n", thread_id, local_sum);
    }

    return 0;
}
