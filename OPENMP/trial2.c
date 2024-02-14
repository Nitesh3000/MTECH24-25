 #include"omp.h"
#include<stdio.h>

static long num_steps = 10000;
double step;
#define NUM_THREADS 4

void main() {
    int i, nthreads;
    double pi = 0.0, sum;
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
        
        for (i = id, sum= 0.0; i < num_steps; i = i + nthrds) {
            x = (i + 0.5) * step;
            sum += 4.0 / (1.0 + x * x);
        }
        #pragma omp critical //strictly dont put this inside the loop
            pi+=sum*step;    // else it will make the exucution serial
                            //// so make the critical statement only after the loop
            /*
            sum=sum*step;
            #pragma omp atomic   //as the instruction needed to perform is simple addition
                pi+=sum;
            */
            
            
            }                          
    
   
    
    
    double time2 = omp_get_wtime();
    
    printf("%f\n", pi);
    printf("total time = %f\n", time2 - time1);
}
