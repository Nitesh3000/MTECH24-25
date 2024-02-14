#include <stdio.h>
#include <omp.h>

int main() {
    int private_var = 0;
    int firstprivate_var = 0;

    #pragma omp parallel
    {
        #pragma omp single
        {
            #pragma omp task private(private_var) firstprivate(firstprivate_var)
            {
                private_var = omp_get_thread_num(); // Each task has its own private_var
                firstprivate_var = omp_get_thread_num(); // Initialize firstprivate_var with thread num
                int result = 0;
                for (int i = 0; i < 1000; ++i) {
                    result += i;
                }
                printf("Task Thread ID: %d, Private: %d, Firstprivate: %d, Result: %d\n",
                       omp_get_thread_num(), private_var, firstprivate_var, result);
            }
            #pragma omp taskwait
        }
    }

    return 0;
}
