// Standard libraries
#include<stdio.h>
#include<stdlib.h>

// Header file we define
#include"header.h"

void read_graph_from_file(char *filename, int *N, int **row_ptr, 
                            int **col_idx, double **val)
{
    FILE *datafile;

    datafile = fopen(filename, "r");

    if (datafile == NULL) {
        printf("Failure to open file: %s\n", filename);
        exit(0);
    }
}