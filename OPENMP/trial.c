#include <stdio.h>
#include <omp.h>
 static long num_steps = 100000;
    double step;

void trial(int threadID, double A[]){
    printf("Thread %d executing trial()\n",threadID);
}
int main() {
        omp_set_num_threads(4);

  /*  #pragma omp parallel   //give number number of threads
    {
    
        int ID = omp_get_thread_num(); //gives id for each threads
        printf("Hello (%d)", ID);
        printf("World (%d)\n", ID);
    }
    */
    double A[1000];
    #pragma omp parallel
    {
        int ID = omp_get_thread_num();
        trial(ID,A);
    }
    printf("all done\n");
    /*
    int i;
    double x,pi, sum=0;
    step= 1.0/(double) num_steps;

    for(i=0;i<num_steps;i++){
        x=(i+0.5)*steps;
        sum=sum+4.0/(1.0+x*x);
            }
        pi=step*sum;
    */
    return 0;
}
