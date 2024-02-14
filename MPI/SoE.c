#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define LIMIT 10000

int main(int argc, char** argv) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

   
    int start = rank * (LIMIT / size) + 2;
    int end = (rank == size - 1) ? LIMIT : (rank + 1) * (LIMIT / size) + 1;

    //store prime flags
    int* isPrime = (int*)malloc((end - start + 1) * sizeof(int));

  
    for (int i = 0; i <= end - start; i++) {
        isPrime[i] = 1; // Assume all numbers are prime..will change in the code furthur
    }

    for (int p = 2; p * p <= LIMIT; p++) {
        for (int i = 0; i <= end - start; i++) {
            if (isPrime[i]) {
                int num = i + start;
                if (num % p == 0 && num != p) {
                    isPrime[i] = 0; // Marked as not prime
                }
            }
        }
    }

    int* allPrimes = (int*)malloc(LIMIT * sizeof(int));
    MPI_Gather(isPrime, end - start + 1, MPI_INT, allPrimes, end - start + 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Prime numbers up to %d are:\n", LIMIT);
        for (int i = 0; i < LIMIT - 1; i++) {
            if (allPrimes[i]) {
                printf("%d, ", i + 2);
            }
        }
        printf("\n");
    }

    free(isPrime);
    free(allPrimes);

    MPI_Finalize();
    return 0;
}
