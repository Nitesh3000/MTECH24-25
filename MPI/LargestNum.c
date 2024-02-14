#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (argc != 2) {
        if (rank == 0) {
            printf("Usage: %s <array_size>\n", argv[0]);
        }
        MPI_Finalize();
        return 1;
    }

    int array_size = atoi(argv[1]);
    int *arr = (int *)malloc(sizeof(int) * array_size);

    if (rank == 0) {
        // Initialize the array with random values
        for (int i = 0; i < array_size; i++) {
            arr[i] = rand() % 8756;
        }
    }

    // Scatter the array across processes
    int local_size = array_size / size;
    int *local_arr = (int *)malloc(sizeof(int) * local_size);
    MPI_Scatter(arr, local_size, MPI_INT, local_arr, local_size, MPI_INT, 0, MPI_COMM_WORLD);

    // Find the local maximum
    int local_max = local_arr[0];
    for (int i = 1; i < local_size; i++) {
        if (local_arr[i] > local_max) {
            local_max = local_arr[i];
        }
    }

    // Reduce the local maxima to find the global maximum
    int global_max;
    MPI_Reduce(&local_max, &global_max, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Array: ");
        for (int i = 0; i < array_size; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
        printf("The largest number in the array is %d\n", global_max);
    }

    free(arr);
    free(local_arr);

    MPI_Finalize();

    return 0;
}
