#include <stdio.h>
#include <omp.h>

int main() {
    int dynamic_enabled = omp_get_dynamic();
    printf("Dynamic Adjustment Enabled: %s\n", dynamic_enabled ? "Yes" : "No");

    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        printf("Thread %d: Start - Phase 1\n", thread_id);

        // Big Computation - Phase 1
        int result = 0;
        for (int i = 0; i < 1000; ++i) {
            result += i;
        }
        printf("Thread %d: Computation Result - Phase 1: %d\n", thread_id, result);

        #pragma omp barrier

        // Disable dynamic adjustment
        #pragma omp single
        omp_set_dynamic(0);
        dynamic_enabled = omp_get_dynamic();
        printf("Thread %d: Dynamic Adjustment Disabled: %s\n", thread_id, dynamic_enabled ? "Yes" : "No");

        printf("Thread %d: Phase 2\n", thread_id);

        result = 0;
        for (int i = 0; i < 1000; ++i) {
            result += i;
        }
        printf("Thread %d: Computation Result - Phase 2: %d\n", thread_id, result);

        #pragma omp barrier

        printf("Thread %d: End - Phase 3\n", thread_id);

        // Enable dynamic adjustment
        #pragma omp single
        omp_set_dynamic(1);
        dynamic_enabled = omp_get_dynamic();
        printf("Thread %d: Dynamic Adjustment Enabled: %s\n", thread_id, dynamic_enabled ? "Yes" : "No");
    }

    return 0;
}
