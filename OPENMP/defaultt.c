#include <stdio.h>
#include <omp.h>
int main() {
   int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10,11,12};
   int size = sizeof(data) / sizeof(data[0]);
   int threshold = 5;
   printf("Starting the program.\n");
   // Use parallelism with shared variables
   #pragma omp parallel default(shared)
   {
       int thread_id = omp_get_thread_num();
       int chunk_size = size / omp_get_num_threads();
       int start = thread_id * chunk_size;
       int end = start + chunk_size;


       // Distribute work among threads
       printf("Thread %d is processing elements from index %d to %d.\n", thread_id, start, end);
       for (int i = start; i < end; ++i) {
           data[i] *= 2;  // Perform some processing on the data
       }
   }
   printf("All processing has been completed.\n");


   // Print the modified array
   printf("Modified array: ");
   for (int i = 0; i < size; ++i) {
       printf("%d ", data[i]);
   }
   printf("\n");
   return 0;
}
