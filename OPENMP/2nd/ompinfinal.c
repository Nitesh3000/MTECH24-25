#include <stdio.h>
#include <omp.h>

int main() {
    int num_threads = 4;
    omp_set_num_threads(num_threads);

    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        int in_final_task = 0;

        // Create a task with final clause
        #pragma omp task final(thread_id == 0)
        {
            in_final_task = omp_in_final();
             if (in_final_task) {
            printf("Thread %d: Executing within a final task region.\n", thread_id);
        } else {
            printf("Thread %d: Not executing within a final task region.\n", thread_id);
        }
        }

        
    }

    return 0;
}
