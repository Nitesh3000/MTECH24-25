#include<stdio.h>
#include<omp.h>
int main(){
    int n=omp_get_num_procs();
    printf("%d\n",n);
    omp_set_num_threads(4);
    #pragma omp parallel
    {
        
    }

}