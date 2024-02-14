#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

int main(int argv, char *argc[]){
    int bvalue, size,rank;
    MPI_Status status;
    MPI_Init(&argv, &argc);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    if (rank==0){
        bvalue=100;
    }
    if (rank==0){
        MPI_Send(&bvalue,1,MPI_INT,1,1,MPI_COMM_WORLD);
    }
    else if(rank<size-1){
        MPI_Recv(&bvalue,1,MPI_INT,rank-1,1,MPI_COMM_WORLD,&status);
        MPI_Send(&bvalue,1,MPI_INT,rank+1,1,MPI_COMM_WORLD);
    }
    else{
        MPI_Recv(&bvalue,1,MPI_INT,rank-1,1,MPI_COMM_WORLD,&status);

    }
    printf("rank %d has %d \n",rank,bvalue);
MPI_Finalize();

}