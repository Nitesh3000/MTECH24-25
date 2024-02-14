#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 10

void matrix_multiply(int A[N][N], int B[N][N], int C[N][N]) {
    #pragma omp parallel for
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            C[i][j] = 0;
            for (int k = 0; k < N; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main() {
    int A[N][N], B[N][N], C[N][N];

    // Initialize matrices A and B
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            A[i][j] = i + j;
            B[i][j] = i - j;
        }
    }

    printf("Matrix A:\n");
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            printf("%3d ", A[i][j]);
        }
        printf("\n");
    }

    printf("\nMatrix B:\n");
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            printf("%3d ", B[i][j]);
        }
        printf("\n");
    }

    double start_time = omp_get_wtime();
    matrix_multiply(A, B, C);
    double end_time = omp_get_wtime();

    double execution_time = end_time - start_time;
    printf("\nMatrix Multiplication Execution Time: %.6f seconds\n", execution_time);

    double precision = omp_get_wtick();
    printf("Timer Precision: %.6e seconds\n", precision);

    if (execution_time < precision) {
        printf("Execution time is significantly smaller than timer precision.\n");
    } else {
        printf("Execution time is comparable to or larger than timer precision.\n");
    }

    // Print resulting matrix C
    printf("\nMatrix C (Result):\n");
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            printf("%6d ", C[i][j]);
        }
        printf("\n");
    }

    return 0;
}
