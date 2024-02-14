#include <stdio.h>
#include <omp.h>

int main() {
    // Set the number of threads for subsequent parallel regions
    omp_set_num_threads(3);

    int result = 0;

    // Parallel region with the specified number of threads
    #pragma omp parallel for reduction(+:result)
    for (int i = 1; i < 1000; ++i) {
        result += i;
    }

    printf("Final Result: %d\n", result);

    return 0;
}
