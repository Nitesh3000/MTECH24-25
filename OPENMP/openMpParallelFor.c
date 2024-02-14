#include <stdio.h>
#include <omp.h>

#define N 100000000LL

long long int parallelLoop() {
    long long int result = 0;

    #pragma omp parallel
    {
        long long int local_result = 0;

        #pragma omp for
        for (long long int i = 0; i < N; ++i) {
            local_result += i;
        }

        #pragma omp critical
        result += local_result;
    }

    printf("Parallel Result: %lld\n", result);

    return result;
}

int main() {
    printf("Parallel Loop:\n");
    long long int parallel_result = parallelLoop();

    return 0;
}
