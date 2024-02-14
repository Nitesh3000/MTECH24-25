#include <stdio.h>
#include <omp.h>

int main() {
    int list[4] = {1, 2, 3, 4};
    int sum = 0;  // Variable for the reduction

    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < 4; ++i) {
        sum += list[i];  // Accumulate the sum across threads
    }

    printf("Sum of the list: %d\n", sum);

    return 0;
}
