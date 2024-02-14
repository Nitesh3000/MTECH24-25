#include <stdio.h>
#include <omp.h>

int main() {
    int shared_variable = 0;  

    #pragma omp parallel private(shared_variable)
    {
        int thread_id = omp_get_thread_num();  
        int private_variable = thread_id + 1;  
        printf("Thread %d: Private Variable = %d\n", thread_id, private_variable);

        // Synchronize threads before updating the shared variable
        #pragma omp barrier

        // Update the shared variable atomically to avoid data races
        #pragma omp atomic
        shared_variable += private_variable;

        // Synchronize threads after updating the shared variable
        #pragma omp barrier

        printf("Thread %d: Shared Variable = %d\n", thread_id, shared_variable);
    }

    return 0;  
}