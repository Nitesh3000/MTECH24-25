#include <stdio.h>
#include <omp.h>

int main() {
    int shared_var = 0;

    #pragma omp parallel
    {
        #pragma omp for
        for (int i = 0; i < 1000; ++i) {
            // Increment the shared variable atomically
            #pragma omp atomic update
            shared_var += i;
        }
    }

    printf("Final Shared Variable Value: %d\n", shared_var);

    return 0;
}
