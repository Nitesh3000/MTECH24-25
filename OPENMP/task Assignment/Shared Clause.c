#include <stdio.h>
#include <omp.h>

int main() {
    int shared_var = 0;

    #pragma omp parallel shared(shared_var)
    {
        #pragma omp single
        {
            #pragma omp task shared(shared_var)
            {
                shared_var = 0;
                int result = 0;
                for (int i = 0; i < 1000; ++i) {
                    result += i;
                }
                printf("Task Thread ID: %d, Shared Variable: %d, Result: %d\n\n\n", omp_get_thread_num(), shared_var, result);
            }
        }
    }

    return 0;
}
