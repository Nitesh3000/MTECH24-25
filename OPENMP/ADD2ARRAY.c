#include <omp.h>
#include <stdio.h>
int add( int a[], int b[],int n){
    int c[n];
        double time1=omp_get_wtime();
printf("\n the added array is as follows \n");
 for(int i = 0; i < n; i++) {
            printf("%d ", a[i] + b[i]);
        }
printf("\n and the total execution time is %f \n",omp_get_wtime()-time1);

        
}
int main() {
    printf("input size : ");
    int n;
    scanf("%d",&n);
    int a[n],b[n];
    for (int i = 0; i<n;i++){
        scanf("%d",&a[i]);
    }
    for (int i = 0; i<n;i++){
        scanf("%d",&b[i]);
    }
    //int a[] = {3, 4, 5, 6};
    //int b[] = {7, 8, 9, 10};
    int c[n] ;

    int k;
    int nthreads;
    omp_set_num_threads(n);
    double time1=omp_get_wtime();

   /* #pragma omp parallel
    {
        int id = omp_get_thread_num();
        int i;
        int nthrds = omp_get_num_threads();
        //printf("%d ",nthrds);
        int istart=id*n/nthrds;
        int iend=(id+1)*n/nthrds;
        for (i=istart;i<iend;i++) {
            c[i] = a[i] + b[i];
        }
    }*/
    #pragma omp parallel
    {
        int i;
        #pragma omp for    //same code as above but using loop worksharing
            for(i=0;i<n;i++)
                c[i]=a[i]+b[i];
    }
            double time2=omp_get_wtime() - time1;

    for (k = 0; k < n; k++) {
        printf("%d ", c[k]);
    }
        printf("\n total time for execution using threads is %f \n", time2);
        printf("\n\n\n =============and for serial output ================= "); 
        add(a,b,n);
    return 0;
}
