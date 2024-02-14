#include <stdio.h>
#include <omp.h>

int main() {
    int list[4] = {0, 0, 0, 0};  // Original list

    #pragma omp parallel firstprivate(list)
    {
        int thread_id = omp_get_thread_num();
        list[thread_id] = thread_id + 1;  // Modify private copy of list

        // Print private copy of list
        printf("Thread %d: List[%d] = %d\n", thread_id, thread_id, list[thread_id]);
    }

    // Print original list (not modified by threads)
    printf("Original List: [%d, %d, %d, %d]\n", list[0], list[1], list[2], list[3]);

    return 0;
}
