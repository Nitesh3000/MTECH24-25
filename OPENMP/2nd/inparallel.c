#include <stdio.h>
#include <omp.h>

int main() {
    int in_parallel;
    
    // Check if the code is executed within an active parallel region
    in_parallel = omp_in_parallel();
    if (in_parallel) {
        printf("Outside Parallel Region: No (Main Thread)\n");
    } else {
        printf("Outside Parallel Region: Yes (Main Thread)\n");
    }
    
    #pragma omp parallel
    {
        // Check again within the parallel region
        in_parallel = omp_in_parallel();
        if (in_parallel) {
            printf("Inside Parallel Region: Yes (Thread %d)\n", omp_get_thread_num());
        } else {
            printf("Inside Parallel Region: No (Thread %d)\n", omp_get_thread_num());
        }
    }
    
    return 0;
}
