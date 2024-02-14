#include<stdio.h>
#include"omp.h"
#define r1 3
#define c1 2
#define r2 2
#define c2 3
int matMul(int a[][c1], int b[][c2],int result[][c2]){
    double time1=omp_get_wtime();
    for (int i =0 ; i<r1;i++){
        for(int j=0;j<c2;j++){
            result[i][j]=0;
            for(int k=0;k<c1;k++){
                result[i][j]+=a[i][k]*b[k][j];
            }
        }
    }
    for (int i =0 ; i<r1;i++){
        for(int j=0;j<c2;j++){
            printf("%d ",result[i][j]);
        }
        printf("\n");
        }
        printf("time for execution is %f\n", omp_get_wtime()-time1);
}
void ompMatMul(int a[][c1], int b[][c2],int result[][c2]){
     double time1=omp_get_wtime();
     #pragma omp parallel
     {
    for (int i =0 ; i<r1;i++){
        for(int j=0;j<c2;j++){
            result[i][j]=0;
            for(int k=0;k<c1;k++){
                result[i][j]+=a[i][k]*b[k][j];
            }
        }
    }
     }
    for (int i =0 ; i<r1;i++){
        for(int j=0;j<c2;j++){
            printf("%d ",result[i][j]);
        }
        printf("\n");
        }
        printf("time for execution is %f\n", omp_get_wtime()-time1);
}
int main(){
    int m1[r1][c1]={{1,1},
                     {1,1},
                     {1,1}};
     int m2[r2][c2] = {{1, 1, 1},
                       {1, 1, 1}};
    int result[r1][c2];
    matMul(m1,m2,result);
    ompMatMul(m1,m2,result);
}