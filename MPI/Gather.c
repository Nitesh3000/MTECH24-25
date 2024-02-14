#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

int main(int argc, char** argv) {
    int rank, size;
    int* sendbuf = NULL;
    int* recvbuf = NULL;
    int root = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int num_elements = 5;//number of elements on each process

    sendbuf = (int*)malloc(num_elements * sizeof(int));
    srand(time(NULL));
    for (int i = 0; i < num_elements; i++) {
        sendbuf[i] = rand() % 100;
    }

    if (rank == root) {
        recvbuf = (int*)malloc(num_elements * size * sizeof(int));
    }

    MPI_Gather(sendbuf, num_elements, MPI_INT, recvbuf, num_elements, MPI_INT, root, MPI_COMM_WORLD);

    if (rank == root) {
        printf("Gathered data at root process:\n");
        for (int i = 0; i < num_elements * size; i++) {
            printf("%d ", recvbuf[i]);
        }
        printf("\n");
    }

    free(sendbuf);
    if (rank == root) {
        free(recvbuf);
    }
    MPI_Finalize();

    return 0;
}
