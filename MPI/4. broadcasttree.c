#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
int main(int argc, char *argv[]){
    int bvalue,size,rank,count;
    MPI_Status status;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    if (rank == 0)
        bvalue=100;
    for (count=1;count<size;count*=2){
        if (rank<count){
            if ((rank+count) < size){
                MPI_Send(&bvalue,1,MPI_INT,rank+count,1,MPI_COMM_WORLD);
            }
        }
        else if(rank<(2*count)){
            MPI_Recv(&bvalue,1,MPI_INT,rank-count,1,MPI_COMM_WORLD,&status);
        }
    }
    printf("value is %d by rank %d \n",bvalue,rank);
    MPI_Finalize();

}