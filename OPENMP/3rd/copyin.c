#include <stdio.h>
#include <omp.h>

int thread_private_value = 0; // Declare the threadprivate variable

#pragma omp threadprivate(thread_private_value)

int main() {
    #pragma omp parallel copyin(thread_private_value)
    {
        int thread_id = omp_get_thread_num();
        thread_private_value = thread_id + 1;
        
        printf("Thread %d: Private Value = %d\n", thread_id, thread_private_value);
    }

    return 0;
}
