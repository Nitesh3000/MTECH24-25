#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

void matrix_multiply(int n, long double** A, long double** B, long double** C) {
    #pragma omp parallel for
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            long double temp = 0.0;
            for (int k = 0; k < n; ++k) {
                temp += A[i][k] * B[k][j];
            }
            C[i][j] = temp;
        }
    }
}

int main() {
    FILE* outputFile = fopen("matrix_multiplication_times.txt", "w");
    
    for (int n = 1000; n <= 10000; n += 1000) {
        long double** A = (long double**)malloc(n * sizeof(long double*));
        long double** B = (long double**)malloc(n * sizeof(long double*));
        long double** C = (long double**)malloc(n * sizeof(long double*));
        
        for (int i = 0; i < n; ++i) {
            A[i] = (long double*)malloc(n * sizeof(long double));
            B[i] = (long double*)malloc(n * sizeof(long double));
            C[i] = (long double*)malloc(n * sizeof(long double));
        }
        
        // Initialize matrices A and B with random values
        srand(time(NULL));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                A[i][j] = (long double)rand() / RAND_MAX;
                B[i][j] = (long double)rand() / RAND_MAX;
            }
        }
        
        clock_t start_time = clock();
        
        matrix_multiply(n, A, B, C);
        
        clock_t end_time = clock();
        double execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
        
        fprintf(outputFile, "%d %lf\n", n, execution_time);
        
        // Clean up
        for (int i = 0; i < n; ++i) {
            free(A[i]);
            free(B[i]);
            free(C[i]);
        }
        
        free(A);
        free(B);
        free(C);
    }
    
    fclose(outputFile);
    
    return 0;
}
