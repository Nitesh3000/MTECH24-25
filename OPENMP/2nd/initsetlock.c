#include <stdio.h>
#include <omp.h>
#include <unistd.h> // for usleep

int main() {
    omp_lock_t outer_lock;
    omp_nest_lock_t inner_lock;

    omp_init_lock(&outer_lock);
    omp_init_nest_lock(&inner_lock);

    printf("Locks initialized.\n\n");

    #pragma omp parallel sections
    {
        #pragma omp section
        {
            omp_set_lock(&outer_lock);
            printf("Thread %d: Acquired outer lock.\n", omp_get_thread_num());

            omp_set_nest_lock(&inner_lock);
            printf("Thread %d: Acquired inner nested lock.\n", omp_get_thread_num());

            printf("Thread %d: Inside inner nested lock critical section.\n", omp_get_thread_num());

            omp_unset_nest_lock(&inner_lock);
            printf("Thread %d: Released inner nested lock.\n", omp_get_thread_num());

            omp_unset_lock(&outer_lock);
            printf("Thread %d: Released outer lock.\n\n", omp_get_thread_num());
        }

        #pragma omp section
        {
            usleep(1000); // Introduce a small delay

            omp_set_lock(&outer_lock);
            printf("Thread %d: Acquired outer lock.\n", omp_get_thread_num());

            omp_set_nest_lock(&inner_lock);
            printf("Thread %d: Acquired inner nested lock.\n", omp_get_thread_num());

            printf("Thread %d: Inside inner nested lock critical section.\n", omp_get_thread_num());

            omp_unset_nest_lock(&inner_lock);
            printf("Thread %d: Released inner nested lock.\n", omp_get_thread_num());

            omp_unset_lock(&outer_lock);
            printf("Thread %d: Released outer lock.\n\n", omp_get_thread_num());
        }
    }

    omp_destroy_lock(&outer_lock);
    omp_destroy_nest_lock(&inner_lock);

    printf("Locks destroyed.\n");

    return 0;
}
