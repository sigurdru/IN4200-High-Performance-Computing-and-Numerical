// Standard libraries
#include <stdio.h>
#include <stdlib.h>

// Header file we define
#include "header.h"

int main(int narg, char **argv) 
    {
    if (narg < 2)
    {
        printf("Filename required.\n");
        exit(0);
    }
    int *row_ptr, *col_idx;
    double *val;
    int N = 0;
    char *filename = argv[1];
    double d = 1;
    double epsilon = 0.000001;

    // Read from file and store data
    read_graph_from_file(filename, &N, &row_ptr, &col_idx, &val);
    double *scores = calloc(N, sizeof(double));
    // Do algorithm
    PageRank_iterations(N, row_ptr, col_idx, val, d, epsilon, scores);


    free(row_ptr);
    free(col_idx);
    free(scores);
    free(val);
     return 0;
}   