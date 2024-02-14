#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char **argv) {
    int rank, size;
    int N = 16;  // Size of the matrix and vector
    double *A, *x, *y_local, *y;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Allocate memory for the matrix and vectors
    A = (double *)malloc(N * N * sizeof(double));
    x = (double *)malloc(N * sizeof(double));
    y_local = (double *)malloc(N * sizeof(double));
    y = (double *)malloc(N * sizeof(double));

    if (rank == 0) {
        for (int i = 0; i < N * N; i++) {
            A[i] = i + 1;
        }
        for (int i = 0; i < N; i++) {
            x[i] = i + 1;
        }
    }

    // Scatter the matrix rows to all processes
    MPI_Scatter(A, N * N / size, MPI_DOUBLE, A, N * N / size, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // Broadcast the vector to all processes
    MPI_Bcast(x, N, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    for (int i = 0; i < N; i++) {
        y_local[i] = 0.0;
        for (int j = 0; j < N; j++) {
            y_local[i] += A[i * N + j] * x[j];
        }
    }

    MPI_Gather(y_local, N / size, MPI_DOUBLE, y, N / size, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Matrix A:\n");
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                printf("%.2f ", A[i * N + j]);
            }
            printf("\n");
        }

        printf("Vector x:\n");
        for (int i = 0; i < N; i++) {
            printf("%.2f\n", x[i]);
        }

        printf("Result vector y:\n");
        for (int i = 0; i < N; i++) {
            printf("%.2f\n", y[i]);
        }
    }

    MPI_Finalize();
    free(A);
    free(x);
    free(y_local);
    free(y);

    return 0;
}
