#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

#define INF 99999

void generateRandomGraph(int n, int*** graph) {
    srand(time(NULL)); 

    *graph = (int**)malloc(n * sizeof(int*));

   
    for (int i = 0; i < n; i++) {
        (*graph)[i] = (int*)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            (*graph)[i][j] = INF;
        }
    }

    
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int weight = rand() % 10 + 1; 
            (*graph)[i][j] = weight;
            (*graph)[j][i] = weight; 
        }
    }

    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                (*graph)[i][j] = 0;
            } else if (rand() % 4 == 0) {
                (*graph)[i][j] = INF; // INF values for some random edges
                (*graph)[j][i] = INF; 
            }
        }
    }
}

void printGraph(int n, int** graph) {
    printf("Initial graph:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (graph[i][j] == INF) {
                printf("INF\t");
            } else {
                printf("%d\t", graph[i][j]);
            }
        }
        printf("\n");
    }
}

int main(int argc, char* argv[]) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int n = 5; 
    int** graph;
    generateRandomGraph(n, &graph);

    // Broadcast the number of nodes to all processes
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    int localDist[n][n];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            localDist[i][j] = graph[i][j];     // Initializing localDist with the values from the graph

        }
    }

    if (rank == 0) {
        printGraph(n, graph);
    }

   //parallel portion...

    for (int k = 0; k < n; k++) {
        MPI_Bcast(localDist, n * n, MPI_INT, 0, MPI_COMM_WORLD);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (localDist[i][k] + localDist[k][j] < localDist[i][j]) {
                    localDist[i][j] = localDist[i][k] + localDist[k][j];
                }
            }
        }
    }

    if (rank == 0) {
        printf("Shortest distances:\n");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (localDist[i][j] == INF) {
                    printf("INF\t");
                } else {
                    printf("%d\t", localDist[i][j]);
                }
            }
            printf("\n");
        }
    }

    // Free dynamically allocated memory
    for (int i = 0; i < n; i++) {
        free(graph[i]);
    }
    free(graph);

    MPI_Finalize();
    return 0;
}
