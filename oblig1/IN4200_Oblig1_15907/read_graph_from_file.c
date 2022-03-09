// Standard libraries
#include<stdio.h>
#include<stdlib.h>

// Header file we define
#include"header.h"

void read_graph_from_file(char *filename, int *N, int **row_ptr, 
                            int **col_idx, double **val)
{
    int N_links, N_nodes;
    FILE *datafile;
    // Try to open file
    datafile = fopen(filename, "r");

    if (datafile == NULL) {
        printf("Failure to open file: %s\n", filename);
        exit(0);
    }
    // Skip first two lines
    fscanf(datafile, "%*[^\n]\n");
    fscanf(datafile, "%*[^\n]\n");

    // Store number of nodes and edges
    fscanf(datafile, "# Nodes: %d Edges: %d %*s\n", &N_nodes, &N_links);

    // Skip one more line
    fscanf(datafile, "%*[^\n]\n");

    int n, m;
    for (int i = 0; i<N_links; i++)
    {
        fscanf(datafile, "%d %d", &n, &m);
        printf("%d %d\n", n, m);
    }
    fclose(datafile);
    N = &N_nodes;
}