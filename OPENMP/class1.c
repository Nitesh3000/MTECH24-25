#include<stdio.h>
#include"omp.h"
    double func(int i){
            return i;
        
    }

int main(){
    int i;
    double zz,res=0.0;
    double a=2.0;
    int n=3;
    omp_set_num_threads(4);
    double initial_time=omp_get_wtime();
    #pragma omp parallel for reduction(+:res) private(zz)

        for(i=0;i<1000;i++){
            zz=func(i);
            res=res+zz;
        }
    
        printf("%f\n",res);
        printf("%f\n",omp_get_wtime()-initial_time);

}