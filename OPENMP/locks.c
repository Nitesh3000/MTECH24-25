//program to get one thread per processor
#include<stdio.h>
#include<omp.h>
void main(){
int num_threads;
omp_set_dynamic(0); ///turns of dynamic mode
omp_set_num_threads(omp_get_num_procs()); //give one thread per processor
#pragma omp parallel
{
int id = omp_get_thread_num();
printf("\nid = %d\n",id);
#pragma omp single //one thread gets inside this
{ 
num_threads = omp_get_num_threads();
printf("\nid inside = %d\n",id);
printf("\n num_threads = %d\n",num_threads);
}
//Do_lots_of_stuff(id);
}
}
