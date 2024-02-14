#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {

    putenv("OMP_NUM_THREADS=3");

    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        printf("Thread %d: Hello from thread %d!\n", thread_id, thread_id);
    }

    return 0;
}
