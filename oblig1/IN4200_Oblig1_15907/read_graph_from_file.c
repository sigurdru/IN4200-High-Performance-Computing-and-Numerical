// Standard libraries
#include <stdio.h>
#include <stdlib.h>

// Header file we define
#include "header.h"

void read_graph_from_file(char *filename, int *N, int **row_ptr, 
                            int **col_idx, double **val)
{
    int N_links, N_nodes, from, to, N_col_ptr;
    int *num_links_sent, *num_links_recieved;
    N_links = N_nodes = N_col_ptr = 0;
    // Try to open file
    FILE *datafile;
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

    // Count the number of links recieved and sent for each node
    num_links_sent = calloc(N_nodes, sizeof(int));
    num_links_recieved = calloc(N_nodes, sizeof(int));
    for (int i = 0; i<N_links; i++)
    {
        fscanf(datafile, "%d %d", &from, &to);
        if (from != to)
        {
            num_links_sent[from] += 1 ;
            num_links_recieved[to] += 1;
        }
    }

    // Allocate memmory and fill row_ptr
    *row_ptr = calloc((N_nodes + 1), sizeof(int));
    (*row_ptr)[0] = 0;
    for (int i = 0; i<N_nodes; i++)
    {
        N_col_ptr += num_links_recieved[i];
        (*row_ptr)[i+1] = N_col_ptr;
    }
    *col_idx = calloc(N_col_ptr, sizeof(int));
    *val = calloc(N_col_ptr, sizeof(double));
    *N = N_nodes;

    // Rewind and skip the first four lines
    rewind(datafile);
    for (int i = 0; i<4; i++)
        fscanf(datafile, "%*[^\n]\n");


    // Fill col_idx and val without sorting
    for (int i = 0; i < N_links; i++)
    {
        fscanf(datafile, "%d %d", &from, &to);
        if (from != to)
        {
            (*col_idx)[(*row_ptr)[to] + num_links_recieved[to] - 1] = from;
            (*val)[(*row_ptr)[to] + num_links_recieved[to] - 1] = 1./num_links_sent[from];
            num_links_recieved[to] -= 1;
        }
    }
    fclose(datafile);

    // Sort col_idx and val
    int start, stop, temp_col;
    double temp_val;
    for (int i = 0; i<N_nodes; i++)
    {
        start = (*row_ptr)[i];
        stop = (*row_ptr)[i+1];
        for (int j = start; j<stop; j++)
        {
            for (int k = j + 1; k<stop; k++)
            {
                if ((*col_idx)[j] > (*col_idx)[k])
                {
                    temp_col = (*col_idx)[j];
                    temp_val = (*val)[j];
                    (*col_idx)[j] = (*col_idx)[k];
                    (*val)[j] = (*val)[k]; 
                    (*col_idx)[k] = temp_col;
                    (*val)[k] = temp_val;                }
            }
        }
    }

    free(num_links_sent);
    free(num_links_recieved);
}