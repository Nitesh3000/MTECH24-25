#include <stdio.h>
#include <omp.h>

int main() {
    int list[4] = {1, 2, 3, 4};  // Master thread's list

    #pragma omp parallel copyin(list)
    {
        int thread_id = omp_get_thread_num();

        // Modify private copy of list
        list[thread_id] += thread_id;

        // Print private copy of list
        printf("Thread %d: List[%d] = %d\n", thread_id, thread_id, list[thread_id]);
    }

    // Print master thread's original list (not modified by threads)
    printf("Master's List: [%d, %d, %d, %d]\n", list[0], list[1], list[2], list[3]);

    return 0;
}
