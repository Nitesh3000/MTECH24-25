#include <stdio.h>
#include<omp.h>
#define ARRAY_SIZE 1000000

void calculateSquaresSerial(long long int array[]) {
    for (long long int i = 0; i < ARRAY_SIZE; ++i) {
        array[i] = array[i] * array[i];
    }
}

int main() {
    long long int array[ARRAY_SIZE];

    for (long long int i = 0; i < ARRAY_SIZE; ++i) {
        array[i] = i + 1;
    }

    double start_time = omp_get_wtime();
    calculateSquaresSerial(array);
    double end_time = omp_get_wtime();

    printf("Serial Execution Time: %.4f seconds\n", end_time - start_time);

    return 0;
}
