#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>
#include <sys/time.h>

void sieveOfEratosthenes(int n) {
    int* primes = (int*)malloc((n + 1) * sizeof(int));

    #pragma omp parallel for
    for (int i = 0; i <= n; i++) {
        primes[i] = 1;
    }

    primes[0] = primes[1] = 0;

    for (int p = 2; p * p <= n; p++) {
        if (primes[p] == 1) {
            #pragma omp parallel for
            for (int i = p * p; i <= n; i += p) {
                primes[i] = 0;
            }
        }
    }

    int count = 0;
    for (int i = 2; i <= n; i++) {
        if (primes[i] == 1) {
            count++;
        }
    }

    free(primes);
}

int main() {
    int n;
    printf("Enter the value of n: ");
    scanf("%d", &n);

    printf("Using OpenMP to find prime numbers from 2 to %d.\n", n);

    struct timeval start, end;

    printf("Threads\tTime (seconds)\n");

    for (int i = 0; i <= 9; i++) {
        int numThreads = (int)pow(2, i);
        omp_set_num_threads(numThreads);

        gettimeofday(&start, NULL);

        sieveOfEratosthenes(n);

        gettimeofday(&end, NULL);
        double elapsed = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;

        printf("%d\t%.6f\n", numThreads, elapsed);
    }

    return 0;
}
