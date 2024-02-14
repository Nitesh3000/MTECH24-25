#include<stdio.h>
#include<omp.h>
int main(){
    int a[2][3]={{1,2,3},
                {4,5,6}};
    int b[2][3]={{7,8,9},
                {10,11,12}};
    double initial_time = omp_get_wtime();
        #pragma omp parrall for

    for(int i=0;i<2;i++){
            //#pragma omp parrall for

        for(int j=0;j<3;j++){
            printf("%d ",a[i][j]+b[i][j]);
        }
        printf("\n");
    }
    printf("%f \n",omp_get_wtime()-initial_time);
}

///home/et2023/Desktop/Algorthms/MatrixAddition.c