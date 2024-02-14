#include <stdio.h>
#include <omp.h>

int main() {
    #pragma omp parallel
    {
        #pragma omp single
        {
            #pragma omp task untied
            {
                int result = 0;
                for (int i = 0; i < 1000; ++i) {
                    result += i;
                }
                printf("Task Result: %d\n", result);
            }
        }
    }

    return 0;
}
