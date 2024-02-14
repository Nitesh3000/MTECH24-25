#include <stdio.h>
#include <omp.h>

int main() {
    #pragma omp parallel
    {
        #pragma omp for ordered
        for (int i = 0; i < 4; ++i) {
            int thread_id = omp_get_thread_num();
            int result = 0;
            for (int j = 0; j < 1000; ++j) {
                result += j;
            }
            #pragma omp ordered
            printf("Thread %d: Iteration %d, Result: %d\n", thread_id, i, result);
        }
    }

    return 0;
}
