// Standard libraries
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

// Header file we define
#include "header.h"

void PageRank_iterations(int N, int *row_ptr, int *col_idx,
                         double *val, double d,
                         double epsilon, double *scores)
{
    // First find number of dangling nodes and the index
    int Num_D = 0;
    int IsThere = 0;
    int i, j, k;
    int *floating_nodes = calloc(N, sizeof(int));
    for (i = 0; i<N; i++)
    {
        for (j = 0; j<N; j++)
        {
            for (k = row_ptr[j]; k<row_ptr[j+1]; k++){
                if (col_idx[k] == i) IsThere = 1;
            }
            if (IsThere == 1) break;
        }
        if (IsThere != 1)
        {
            floating_nodes[Num_D] = i;
            Num_D += 1;
        }
        IsThere = 0;
    }
    floating_nodes = realloc(floating_nodes, Num_D*sizeof(int));

    // Initialize scores and finding barrier
    #pragma omp parallel for
    for (i = 0; i<N; i++)
        scores[i] = (double)1./ N;

    double barrier = scores[0];

    // Defining needed params
    double scalar = 0.;
    double W = 0.;
    double MVM;
    double *old_scores = malloc(N*sizeof(double));

    #pragma omp parallel for
    for (i = 0; i<N; i++)
        old_scores[i] = scores[i];

    #pragma omp parallel for if(Num_D > 1000) reduction(+:W)
    for (i = 0; i<Num_D; i++) 
        W += scores[floating_nodes[i]];

    // Doing the actual algorithm
    while (barrier>epsilon)
    {   
        scalar = (1 - d + d*W)/N;
        W = 0.;
        barrier = 0.;
        #pragma omp parallel for private(j) reduction(+:MVM)
        for (i = 0; i<N; i++)
        {
            MVM = 0;
            for (j = row_ptr[i]; j<row_ptr[i+1]; j++)
            {
                MVM += val[j]*old_scores[col_idx[j]];
            }
            scores[i] = scalar + d * MVM;
        }

        #pragma omp parallel for if(Num_D > 1000) reduction(+:W)
        for (i = 0; i < Num_D; i++)
            W += scores[floating_nodes[i]];
        
        #pragma omp parallel for
        for (i = 0; i < N; i++)
        {
            if (fabs(old_scores[i] - scores[i]) > barrier)
            {
                barrier = fabs(old_scores[i] - scores[i]);
            }
            old_scores[i] = scores[i];
        }
    }

    free(old_scores);
    free(floating_nodes);
}