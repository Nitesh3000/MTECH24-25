#include"omp.h"
#include<stdio.h>

static long num_steps = 10000;
double step;
#define NUM_THREADS 4

void main() {
    int i, nthreads;
    double pi = 0.0, sum[NUM_THREADS];
    step = 1.0 / (double)num_steps;
    double time1 = omp_get_wtime();
    
    omp_set_num_threads(NUM_THREADS);
    
    #pragma omp parallel
    {
        int i, id, nthrds;
        double x;
        id = omp_get_thread_num();
        nthrds = omp_get_num_threads();
        
        if (id == 0) {
            nthreads = nthrds;
        }
        
        for (i = id, sum[id] = 0.0; i < num_steps; i = i + nthrds) {
            x = (i + 0.5) * step;
            sum[id] += 4.0 / (1.0 + x * x);
        }
    }
    
    for (i = 0; i < nthreads; i++) {
        pi = pi + sum[i] * step;
        printf("%f  ", pi);
    }
    
    double time2 = omp_get_wtime();
    
    printf("%f\n", pi);
    printf("total time = %f\n", time2 - time1);
}
