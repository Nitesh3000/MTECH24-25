#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define NUM_THREADS 1
#define ROWS 100
#define COLS 100

int neighbors[8][2] = {
    {-1, 0},
    {1, 0},
    {0, -1},
    {0, 1},
    {-1, -1},
    {-1, 1},
    {1, -1},
    {1, 1}
};

int no_out_range(int i, int j, int rows, int cols) {
    return (i >= 0 && i < rows && j >= 0 && j < cols);
}

int dead_cell_check(int** board, int i, int j) {
    int count_neighbors = 0;

    #pragma omp parallel for
    for (int k = 0; k < 8; k++) {
        int ni = i + neighbors[k][0];
        int nj = j + neighbors[k][1];
        if (no_out_range(ni, nj, ROWS, COLS) && board[ni][nj] == 1)
            count_neighbors++;
    }
    return count_neighbors == 3;
}

int live_cell_check(int** board, int i, int j) {
    int count_neighbors = 0;
    #pragma omp parallel for reduction(+:count_neighbors)
    for (int k = 0; k < 8; k++) {
        int ni = i + neighbors[k][0];
        int nj = j + neighbors[k][1];
        if (no_out_range(ni, nj, ROWS, COLS) && board[ni][nj] == 1)
            count_neighbors++;
    }
    return count_neighbors < 2 || count_neighbors > 3;
}

void gameOfLife(int** board) {
    int need_to_be_updated[ROWS * COLS][2];
    int num_updates = 0;
    #pragma omp parallel for collapse(2) num_threads(NUM_THREADS)
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (board[i][j] == 0 && dead_cell_check(board, i, j)) {
                need_to_be_updated[num_updates][0] = i;
                need_to_be_updated[num_updates][1] = j;
                num_updates++;
            } else if (board[i][j] == 1 && live_cell_check(board, i, j)) {
                need_to_be_updated[num_updates][0] = i;
                need_to_be_updated[num_updates][1] = j;
                num_updates++;
            }
        }
    }

   
    for (int k = 0; k < num_updates; k++) {
        int i = need_to_be_updated[k][0];
        int j = need_to_be_updated[k][1];
        board[i][j] = 1 - board[i][j];
    }
    
}

void printMatrix(int** board) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (board[i][j] == 0) {
                printf("_ ");
            } else {
                printf("%d ", board[i][j]);
            }
        }
        printf("\n");
    }
}

int main() {
    double start_time_serial = omp_get_wtime();
    omp_set_num_threads(NUM_THREADS);
    int** board;
    board = (int**)malloc(ROWS * sizeof(int*));
    for (int i = 0; i < ROWS; i++) {
        board[i] = (int*)malloc(COLS * sizeof(int));
    }
    srand(time(NULL));
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            board[i][j] = rand() % 2;
        }
    }
   

    int n = 1;
    double start_time;
    double end_time;
    double total_parallel_time=0;
    while (n <= 1000) {
        start_time = omp_get_wtime();
        system("clear");
        gameOfLife(board);
        end_time = omp_get_wtime();
        printf("Current matrix:\n");
        printMatrix(board);
        n++;
        total_parallel_time=total_parallel_time+(end_time-start_time);
    }

    // Free allocated memory
    for (int i = 0; i < ROWS; i++) {
        free(board[i]);
    }
    free(board);

    printf("Total execution time for parallel portion is: %.6f seconds\n", total_parallel_time);
    //printf("Total serial time is: %.6f seconds\n", timeserial);
    double end_time_serial = omp_get_wtime();
    double timeserial = end_time_serial - start_time_serial;

    printf("Total execution time of the full code is: %.6f seconds\n", timeserial);
    printf("total executioni time just for the serial section = %.6f seconds\n", timeserial-total_parallel_time);
    return 0;
}
