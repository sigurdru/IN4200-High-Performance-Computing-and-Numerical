// Standard libraries
#include <stdio.h>
#include <stdlib.h>

// Header file we define
#include "header.h"

int main(int narg, char **argv) 
    {
    if (narg < 5)
    {
        printf("Error: Not enough arguments given.\n");
        printf("Please give the following arguments:\n");
        printf("- webgraph.txt [char] (filename of file containing webgraph)\n");
        printf("- d [double] (damping constant)\n");
        printf("- epsilon [doube] (convergence threshold value)\n");
        printf("- n [int] (top n nodes displayed)\n");
        printf("Example: ./run.exe simple-webgraph.txt 1. 0.000001\n");

        exit(0);
    }
    int *row_ptr, *col_idx;
    double *val;
    int N;
    char *filename = argv[1];
    double d = atof(argv[2]);
    double epsilon = atof(argv[3]);
    int n = atoi(argv[4]);

    // Read from file and store data
    read_graph_from_file(filename, &N, &row_ptr, &col_idx, &val);
    double *scores = calloc(N, sizeof(double));
    // Do algorithm
    PageRank_iterations(N, row_ptr, col_idx, val, d, epsilon, scores);
    // Print top n webpages
    top_n_webpages(N, scores, n);

    free(row_ptr);
    free(col_idx);
    free(scores);
    free(val);
    return 0;
}   