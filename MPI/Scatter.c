#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char** argv) {
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int* sendbuf = NULL;
    int* recvbuf = NULL;
    int root = 0;

    if (rank == root) {
        // root process initializes the data to scatter
        sendbuf = (int*)malloc(size * sizeof(int));
        for (int i = 0; i < size; i++) {
            sendbuf[i] = i * 2;
        }
    }

    // Allocate space
    recvbuf = (int*)malloc(sizeof(int));

    MPI_Scatter(sendbuf, 1, MPI_INT, recvbuf, 1, MPI_INT, root, MPI_COMM_WORLD);

    printf("Process %d received: %d\n", rank, *recvbuf);
 
    free(sendbuf);
    free(recvbuf);
    MPI_Finalize();

    return 0;
}
