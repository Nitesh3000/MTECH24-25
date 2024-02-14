#include <stdio.h>
#include <omp.h>

int main() {
    int max_threads = omp_get_max_threads();
    printf("Maximum number of threads: %d\n", max_threads);
    
    int total_sum = 0;
    
    #pragma omp parallel num_threads(max_threads)
    {
        int local_result = 0;
        #pragma omp for
        for (int i = 0; i < 1000; ++i) {
            local_result += i;
        }
        
        #pragma omp critical
        {
            total_sum += local_result;
            printf("Thread %d, Local Result: %d\n", omp_get_thread_num(), local_result);
        }
    }
    
    printf("Total Sum of All Threads' Results: %d\n", total_sum);
    
    return 0;
}
