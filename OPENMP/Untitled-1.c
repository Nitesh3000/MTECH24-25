#include<stdio.h>
#include<omp.h>
static long num_steps = 10000;
double step;
#define NUM_THREADS 4
int main(){
    double area,pi=0.0,x;
   int i, nthreads;
    double sum;
    step = 1.0 / (double)num_steps;
    
    omp_set_num_threads(NUM_THREADS);
    int id = omp_get_thread_num();
    #pragma omp parallel for private(x) reduction(+:area)
        for(i=0;i<num_steps;i++){
            x=(i+0.5)/num_steps;
         //   #pragma omp critical 
            area+=4.0/(1.0+x*x);
    }
    pi=area/num_steps;
    printf("%f\n",pi);
}
///home/et2023/OPENMP/Untitled-1.c