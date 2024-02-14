#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

void matrixMultiply(int N, int num_threads, double* execution_times) {
    int **A, **B, **C;
    int i, j, k;

    // Dynamically allocate memory for matrices A, B, and C
    A = (int **)malloc(N * sizeof(int *));
    B = (int **)malloc(N * sizeof(int *));
    C = (int **)malloc(N * sizeof(int *));
    for (i = 0; i < N; i++) {
        A[i] = (int *)malloc(N * sizeof(int));
        B[i] = (int *)malloc(N * sizeof(int));
        C[i] = (int *)malloc(N * sizeof(int));
    }

    // Initialize matrices A and B
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            A[i][j] = i + j;
            B[i][j] = i - j;
        }
    }

    // Measure execution time
    double start_time = omp_get_wtime();

    // Parallelize matrix multiplication
    #pragma omp parallel for num_threads(num_threads) private(i, j, k)
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            C[i][j] = 0;
            for (k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    // Measure execution time
    double end_time = omp_get_wtime();
    execution_times[num_threads] = end_time - start_time;

    // Free dynamically allocated memory
    for (i = 0; i < N; i++) {
        free(A[i]);
        free(B[i]);
        free(C[i]);
    }
    free(A);
    free(B);
    free(C);
}

int main() {
    FILE *outputFile;
    outputFile = fopen("matrix_multiplication_times.txt", "w");

    int num_threads;
    int N_values[] = {5000};

    for (int N_index = 0; N_index < 4; N_index++) {
        int N = N_values[N_index];
        double execution_times[17];
        printf("N=%d\n", N);
        fprintf(outputFile, "N=%d\n", N);

        for (num_threads = 1; num_threads <= 16; num_threads++) {
            printf("Threads=%d: ", num_threads);
            fprintf(outputFile, "Threads=%d: ", num_threads);
            matrixMultiply(N, num_threads, execution_times);
            printf("Time=%.6f seconds\n", execution_times[num_threads]);
            fprintf(outputFile, "Time=%.6f seconds\n", execution_times[num_threads]);
        }
    }

    fclose(outputFile);

    return 0;
}
