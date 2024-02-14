#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

int main( int argc, char *argv[]){
    int rank, size;
    int local_sum=0;
    int global_sum=0;
    int array_size=10;
    int *local_array;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);

    int local_size=array_size/size;
    local_array = (int *)malloc(local_size * sizeof(int));

    for (int i=0;i<local_size;i++){
        local_array[i]=rank*local_size+1;
        local_sum+=local_array[i];
    }

    MPI_Reduce(&local_sum, &global_sum, 1, MPI_INT, MPI_SUM,0,MPI_COMM_WORLD);
    
    if(rank==0)
    printf("Global Sum: %d\n",global_sum);

    free(local_array);
    MPI_Finalize();

    return 0;

}