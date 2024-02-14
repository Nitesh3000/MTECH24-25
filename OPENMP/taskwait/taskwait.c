#include <stdio.h>
#include <omp.h>

int main() {
    int result1 = 0;
    int result2 = 0;

    #pragma omp parallel
    {
        #pragma omp single
        {
            #pragma omp task
            {
                for (int i = 1; i <= 100; ++i) {
                    result1 += i;
                }
                printf("Task 1 Result: %d\n", result1);
            }

            #pragma omp task
            {
                for (int i = 101; i <= 200; ++i) {
                    result2 += i;
                }
                printf("Task 2 Result: %d\n", result2);
            }

            #pragma omp taskwait

            printf("Sum of Task Results: %d\n", result1 + result2);
        }
    }

    return 0;
}
