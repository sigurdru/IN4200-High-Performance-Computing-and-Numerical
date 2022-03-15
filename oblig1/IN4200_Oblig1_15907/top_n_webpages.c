// Standard libraries
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

// Header file we define
#include "header.h"


void top_n_webpages(int N, double *scores, int n)
{
    int *top_list = calloc(n, sizeof(int));
    double *top_list_score = calloc(n, sizeof(double));
    int i, j, k;
    double max_val;
    int max_val_idx;
    int update = 0;
    for (i = 0; i<n; i++)
    {
        max_val = 0.;
        for (j = 0; j<N; j++)
        {
            if (scores[j] > max_val)
            {
                max_val_idx = j;
                update = 1;
            }
            for (int k = 0; k<i; k++)
            {
                if (max_val_idx == top_list[k])
                    update = 0;
            }
            if (update == 1)
            {
                top_list[i] = max_val_idx;
                top_list_score[i] = scores[max_val_idx];
            }
        }
    }


    for (i = 0; i<n; i++)
    {
        printf("No. %d spot goes to node %d, with a score of %f\n", i+1, top_list[i], top_list_score[i]);
    }

    free(top_list);
    free(top_list_score);
}
