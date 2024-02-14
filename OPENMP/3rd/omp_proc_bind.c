#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
    // Set OMP_PROC_BIND to true (threads will be bound)
    putenv("OMP_PROC_BIND=true");

    int num_threads = omp_get_max_threads();
    printf("Number of Threads: %d\n", num_threads);

    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        printf("Thread %d is executing\n", thread_id);
    }

    return 0;
}
