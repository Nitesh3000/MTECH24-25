#include <stdio.h>
#include <omp.h>

int main() {
    int shared_var = 5;

    #pragma omp parallel
    {
        #pragma omp master
        {
            // Code executed by the master thread only
            shared_var = omp_get_thread_num();
            int result = 0;
            for (int i = 0; i < 1000; ++i) {
                result += i;
            }
            printf("Master Thread ID: %d, Shared Variable: %d, Computation Result: %d\n", omp_get_thread_num(), shared_var, result);
        }

        // Code executed by all threads
        printf("Thread ID: %d, Shared Variable: %d\n", omp_get_thread_num(), shared_var);
    }

    return 0;
}
