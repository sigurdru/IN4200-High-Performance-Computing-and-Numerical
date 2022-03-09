// Standard libraries
#include<stdio.h>
#include<stdlib.h>

// Header file we define
#include"header.h"

int main(int narg, char **argv) {

    if (narg < 2)
    {
        printf("Filename required.\n");
        exit(0);
    }
    int **row_ptr, **col_ptr;
    double **val;
    int *N;
    char *filename = argv[1];

    read_graph_from_file(filename, N, row_ptr, col_ptr, val);
    return 0;
}   