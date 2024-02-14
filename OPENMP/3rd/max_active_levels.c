#include <stdio.h>
#include <omp.h>
#include<stdlib.h>
int main() {
  // Set OMP_MAX_ACTIVE_LEVELS to 2
  setenv("OMP_MAX_ACTIVE_LEVELS", "2", 1);

  // Print the max active levels
  int max_active_levels = omp_get_max_active_levels();
  printf("Max active levels: %d\n", max_active_levels);

  // Start a parallel region with 2 threads
  #pragma omp parallel num_threads(2)
  {
    // Print the max active levels
    int max_active_levels_in_child = omp_get_max_active_levels();
    printf("Max active levels in child: %d\n", max_active_levels_in_child);

    // Start a nested parallel region with 1 thread
    #pragma omp parallel num_threads(1)
    {
      // Print the max active levels
      int max_active_levels_in_grandchild = omp_get_max_active_levels();
      printf("Max active levels in grandchild: %d\n", max_active_levels_in_grandchild);
    }
  }

  return 0;
}
