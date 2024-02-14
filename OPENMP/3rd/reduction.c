#include <stdio.h>
#include <omp.h>

#define ARRAY_SIZE 1000000

int main() {
    long long int array[ARRAY_SIZE];
    
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        array[i] = i + 1;
    }

    long long int sum = 0;
    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        sum += array[i];
    }

    printf("Parallel Sum: %lld\n", sum);

    return 0;
}
