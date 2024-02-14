#include <stdio.h>
#include <omp.h>

int main() {
    omp_lock_t lock;
    omp_init_lock(&lock);

    int num_threads = 4;
    omp_set_num_threads(num_threads);

    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();

        if (thread_id % 2 == 0) {
            // Try to acquire the lock using omp_test_lock
            int lock_acquired = omp_test_lock(&lock);
            if (lock_acquired) {
                printf("Thread %d: Lock acquired using omp_test_lock\n", thread_id);
                omp_unset_lock(&lock);
            } else {
                printf("Thread %d: Lock not acquired using omp_test_lock\n", thread_id);
            }
        } else {
            // Try to acquire the nested lock using omp_test_nest_lock
            omp_nest_lock_t nest_lock;
            omp_init_nest_lock(&nest_lock);

            int lock_acquired = omp_test_nest_lock(&nest_lock);
            if (lock_acquired) {
                printf("Thread %d: Nested lock acquired using omp_test_nest_lock\n", thread_id);
                omp_unset_nest_lock(&nest_lock);
            } else {
                printf("Thread %d: Nested lock not acquired using omp_test_nest_lock\n", thread_id);
            }
        }
    }

    omp_destroy_lock(&lock);

    return 0;
}
