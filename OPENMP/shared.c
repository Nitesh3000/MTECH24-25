#include <stdio.h>
#include <omp.h>

int main() {
    int list[4] = {0, 0, 0, 0};  // Shared list

    #pragma omp parallel shared(list)
    {
        int thread_id = omp_get_thread_num();
        list[thread_id] = thread_id + 1;  // Modify shared list

        // Print shared list
        #pragma omp critical
        printf("Thread %d: List[%d] = %d\n", thread_id, thread_id, list[thread_id]);
    }

    // Print modified shared list
    printf("Modified List: [%d, %d, %d, %d]\n", list[0], list[1], list[2], list[3]);

    return 0;
}
