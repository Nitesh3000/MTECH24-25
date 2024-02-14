#include <stdio.h>
#include <omp.h>

int main() {
    int max_active_levels = omp_get_max_active_levels();
    printf("Maximum Active Levels: %d\n\n", max_active_levels);

    // Set the maximum number of active levels
    omp_set_max_active_levels(2);
    
    // Enable nested parallelism
    omp_set_nested(1);

    #pragma omp parallel num_threads(2)
    {
        int outer_thread_id = omp_get_thread_num();
        printf("Outer Parallel Region - Thread %d\n", outer_thread_id);

        #pragma omp parallel num_threads(3)
        {
            int inner_thread_id = omp_get_thread_num();
            printf("Inner Parallel Region - Thread %d (Outer Thread %d)\n", inner_thread_id, outer_thread_id);
        }
    }

    return 0;
}
