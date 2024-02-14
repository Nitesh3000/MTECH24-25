#include <stdio.h>
#include <omp.h>

int main() {
    int shared_variable = 0;  // The shared variable that all threads will update and access

    #pragma omp parallel private(shared_variable)
    {
        int thread_id = omp_get_thread_num();  // Get the ID of the current thread
        int private_variable = thread_id + 1;  // Create a private variable for each thread

        // Print the private variable
        printf("Thread %d: Private Variable = %d\n", thread_id, private_variable);

        // Synchronize threads before updating the shared variable
        #pragma omp barrier

        // Update the shared variable atomically to avoid data races
        #pragma omp atomic
        shared_variable += private_variable;

        
        #pragma omp barrier

        
        printf("Thread %d: Shared Variable = %d\n", thread_id, shared_variable);
    }

    return 0; 
