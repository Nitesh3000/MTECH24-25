#include<stdio.h>
#include<omp.h>
#include<time.h>
int fun(int a[][2],int b[][2],int i,int j){
    return a[i][j]+b[i][j];
}
int main(){
    int i,j,n=2,m=2;
    int a[2][2]={{1,2},
                {4,5}};
    int b[2][2]={{7,8},
                {10,11}};
    int c[2][2]={{0,0},
                {0,0}};
double time1, time2;        /* use doubles to show small values */
    time1 = (double) clock();            /* get initial time */
    #pragma omp parallel for private(j) schedule(dynamic)
    for(i=0;i<n;i++)
    for(j=0;j<n;j++)
    c[i][j]=fun(a,b,i,j);

      for(i=0;i<n;i++){
    for(j=0;j<n;j++){
    printf("%d ",c[i][j]);
    }
    printf("\n");
      }
              time2 = (double) clock();            /* get initial time */

    printf("%f\n",(time2-time1)/CLOCKS_PER_SEC);
}