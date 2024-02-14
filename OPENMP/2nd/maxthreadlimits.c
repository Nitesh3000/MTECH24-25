#include <stdio.h>
#include <omp.h>

int main() {
    int max_thread_limit = omp_get_thread_limit();
    printf("Maximum Thread Limit: %d\n\n", max_thread_limit);


    return 0;
}
