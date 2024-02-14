#include <stdio.h>
#include <omp.h>

#define ARRAY_SIZE 1000000

int main() {
    int result = 0;

    #pragma omp parallel
    {
        int local_result = 0;

        // Distribute loop iterations among threads and make local_result private
        #pragma omp for private(local_result)
        for (int i = 1; i <= ARRAY_SIZE; ++i) {
            local_result += i;
        }

        // Accumulate local results
        #pragma omp critical
        result += local_result;
    }

    printf("Final Result: %d\n", result);

    return 0;
}
