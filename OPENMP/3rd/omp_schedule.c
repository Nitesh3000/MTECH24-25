#include <stdio.h>
#include <omp.h>

int main() {
    int array_size = 10;
    int array[array_size];

    for (int i = 0; i < array_size; ++i) {
        array[i] = i + 1;
    }

    // Set the scheduling kind to omp_sched_dynamic with a modifier of 2
    omp_set_schedule(omp_sched_dynamic, 2);

    int sum = 0;

    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < array_size; ++i) {
        sum += array[i];
        printf("Thread %d: Array[%d] = %d\n", omp_get_thread_num(), i, array[i]);
    }

    printf("Total Sum: %d\n", sum);

    return 0;
}
