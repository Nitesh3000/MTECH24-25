#include <stdio.h>
#include <omp.h>

#define ARRAY_SIZE 1000000

void calculateSquaresParallel(long long int array[]) {
    #pragma omp parallel sections
    {
        #pragma omp section
        for (long long int i = 0; i < ARRAY_SIZE / 5; ++i) {
            array[i] = array[i] * array[i];
        }

        #pragma omp section
        for (long long int i = ARRAY_SIZE / 5; i < 2 * ARRAY_SIZE / 5; ++i) {
            array[i] = array[i] * array[i];
        }

        #pragma omp section
        for (long long int i = 2 * ARRAY_SIZE / 5; i < 3 * ARRAY_SIZE / 5; ++i) {
            array[i] = array[i] * array[i];
        }

        #pragma omp section
        for (long long int i = 3 * ARRAY_SIZE / 5; i < 4 * ARRAY_SIZE / 5; ++i) {
            array[i] = array[i] * array[i];
        }

        #pragma omp section
        for (long long int i = 4 * ARRAY_SIZE / 5; i < ARRAY_SIZE; ++i) {
            array[i] = array[i] * array[i];
        }
    }
}

int main() {
    long long int array[ARRAY_SIZE];

    for (long long int i = 0; i < ARRAY_SIZE; ++i) {
        array[i] = i + 1;
    }

    double start_time = omp_get_wtime();
    calculateSquaresParallel(array);
    double end_time = omp_get_wtime();

    printf("Parallel Execution Time: %.4f seconds\n", end_time - start_time);

    return 0;
}
