#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char** argv) {
    int rank, size;
    int* data = NULL;
    int* local_data = NULL;
    int local_sum = 0;
    int total_sum = 0;
    int num_elements = 1000000;  // Total number of elements in the array

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        data = (int*)malloc(num_elements * sizeof(int));
        for (int i = 0; i < num_elements; i++) {
            data[i] = i;
        }
    }

    local_data = (int*)malloc((num_elements / size) * sizeof(int));
    MPI_Scatter(data, num_elements / size, MPI_INT, local_data, num_elements / size, MPI_INT, 0, MPI_COMM_WORLD);

    // sum of local data
    for (int i = 0; i < num_elements / size; i++) {
        local_sum += local_data[i];
    }

    // Gather the local sums to the root process
    MPI_Reduce(&local_sum, &total_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    
    if (rank == 0) {
        printf("Total sum: %d\n", total_sum);
    }

    if (rank == 0) {
        free(data);
    }
    free(local_data);
    MPI_Finalize();

    return 0;
}
