#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
  // Set the thread limit to 2
  setenv("OMP_THREAD_LIMIT", "2", 1);

  // Print the number of available processors
  int num_processors = omp_get_num_procs();
  printf("Number of available processors: %d\n", num_processors);

  // Start a parallel region with 2 threads
  #pragma omp parallel num_threads(2)
  {
    // Print the thread ID
    int thread_num = omp_get_thread_num();
    printf("Thread ID: %d\n", thread_num);

    // Print the number of active threads
    int num_active_threads = omp_get_num_threads();
    printf("Number of active threads: %d\n", num_active_threads);
  }

  return 0;
}
