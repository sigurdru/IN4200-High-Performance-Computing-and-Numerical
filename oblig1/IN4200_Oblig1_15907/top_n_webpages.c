// Standard libraries
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

// Header file we define
#include "header.h"

void top_n_webpages(int N, double *scores, int n)
{
    // Defining needed variables
    int *top_list = calloc(n, sizeof(int));
    double *top_list_score = calloc(n, sizeof(double));
    int i, j, k;
    double max_val;
    int max_val_idx;
    int update = 0;

    // Defining needed variables for parallelization
    int threadID;
    int num_threads = omp_get_max_threads();
    int *top_contender = calloc(num_threads, sizeof(int));

    // Finding top n items
    for (i = 0; i < n; i++)
    {
        max_val = 0.;
        // Each thread finds its contender (top_contender)
        #pragma omp parallel for firstprivate(update, max_val) private(threadID, max_val_idx, k)
        for (j = 0; j < N; j++)
        {   
            threadID = omp_get_thread_num();
            if (scores[j] > max_val)
            {
                max_val_idx = j;
                update = 1;
            }
            for (k = 0; k < i; k++)
            {
                if (max_val_idx == top_list[k])
                    update = 0;
            }
            if (update == 1)
            {
                top_contender[threadID] = max_val_idx;
                max_val = scores[max_val_idx];
            }

        }

        // Here we choose the largest contender from each thread
        for (j = 0; j<num_threads; j++)
        {
            if (scores[top_contender[j]] > max_val && top_contender[j] != -1)
            {
                top_list[i] = top_contender[j];
                top_list_score[i] = scores[top_contender[j]];
                max_val = scores[top_contender[j]];
            }
            top_contender[j] = -1;
        }
    }

    // Printing the result
    for (i = 0; i<n; i++)
    {
        printf("No. %d spot goes to website %d, with a score of %f\n", i+1, top_list[i], top_list_score[i]);
    }

    free(top_list);
    free(top_list_score);
    free(top_contender);
}