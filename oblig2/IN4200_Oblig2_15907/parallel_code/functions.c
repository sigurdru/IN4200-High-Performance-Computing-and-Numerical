// Standard libraries
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

// Header file we define
#include "header.h"

void allocate_image(image *u, int m, int n)
{
    // This function allocate the 2D array image_date inside u for given m (heigth) and n (width)
    (*u).m = m;
    (*u).n = n;
    (*u).image_data = (float **)malloc(m * sizeof(float *));
    (*u).image_data[0] = (float *)malloc(m * n * sizeof(float));
    for (int i = 1; i < m; i++)
    {
        (*u).image_data[i] = &((*u).image_data[0][n * i]);
    }
}
void deallocate_image(image *u)
{
    // This function free the storage used by image_data inside u
    free((*u).image_data[0]);
    free((*u).image_data);
}
void convert_jpeg_to_image(const unsigned char *image_chars, image *u)
{
    // This function converts a 1D array of unsigned char into an image struct
    for (int i = 0; i < (*u).m; i++)
    {
        for (int j = 0; j < (*u).n; j++)
        {
            (*u).image_data[i][j] = (float)image_chars[i * (*u).n + j];
        }
    }
}
void convert_image_to_jpeg(const image *u, unsigned char *image_chars)
{
    // This function converts an image struct into an array of unsigned char
    for (int i = 0; i < (*u).m; i++)
    {
        for (int j = 0; j < (*u).n; j++)
        {
            image_chars[i * (*u).n + j] = (unsigned char)(*u).image_data[i][j];
        }
    }
}
void iso_diffusion_denoising_parallel(image *u, image *u_bar, float kappa, int iters)
{
    // This function carries out iters iterations of isotropic diffusion in parallel
    int my_rank, num_procs;
    float *lower_boundary, *upper_boundary;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

    // For upper and lower boundary conditions
    if (my_rank != num_procs - 1) lower_boundary = malloc((*u).n * sizeof(*lower_boundary));
    if (my_rank != 0) upper_boundary = malloc((*u).n * sizeof(*upper_boundary));

    // Doing the algorithm
    for (int it = 0; it < iters; it++)
    {
        printf("\rProcessing picture %.2f%%", 100. / (double)(iters - 1) * it);
        fflush(stdout);
        // Deal with missing boundary conditions each iteration
        if (my_rank != num_procs - 1)
        {
            MPI_Send((*u).image_data[(*u).m - 1],
                     (*u).n,
                     MPI_FLOAT,
                     my_rank + 1,
                     0,
                     MPI_COMM_WORLD);
            MPI_Recv(lower_boundary,
                     (*u).n,
                     MPI_FLOAT,
                     my_rank + 1,
                     0,
                     MPI_COMM_WORLD,
                     MPI_STATUS_IGNORE);
        }
        if (my_rank != 0)
        {
            MPI_Recv(upper_boundary,
                     (*u).n,
                     MPI_FLOAT,
                     my_rank - 1,
                     0,
                     MPI_COMM_WORLD,
                     MPI_STATUS_IGNORE);
            MPI_Send((*u).image_data[0],
                     (*u).n,
                     MPI_FLOAT,
                     my_rank - 1,
                     0,
                     MPI_COMM_WORLD);
        }

        // First do the inner part
        for (int i = 1; i < (*u).m - 1; i++)
        {
            for (int j = 1; j < (*u).n - 1; j++)
            {
                (*u_bar).image_data[i][j] = (*u).image_data[i][j] + kappa *
                    ((*u).image_data[i - 1][j] + (*u).image_data[i][j - 1] - 4 * (*u).image_data[i][j] + (*u).image_data[i][j + 1] + (*u).image_data[i + 1][j]);
            }
        }
        // Do upper boundary
        if (my_rank != 0)
        {
            for (int i = 1; i < (*u).n - 1; i++)
            {
                (*u_bar).image_data[0][i] = (*u).image_data[0][i] + kappa *
                    (upper_boundary[i] + (*u).image_data[0][i-1] - 4 * (*u).image_data[0][i] + (*u).image_data[0][i + 1] + (*u).image_data[1][i]);
            }
        }
        // Do lower boundary
        if (my_rank != num_procs - 1)
        {
            for (int i = 1; i < (*u).n - 1; i++)
            {
                (*u_bar).image_data[(*u).m - 1][i] = (*u).image_data[(*u).m - 1][i] + kappa *
                    ((*u).image_data[(*u).m - 2][i] + (*u).image_data[(*u).m - 1][i-1] - 4 * (*u).image_data[(*u).m - 1][i] + (*u).image_data[(*u).m - 1][i + 1] + lower_boundary[i]);
            }
        }

        // Copy to u
        if (it != iters - 1)
        {
            if (my_rank == 0)
            {
                for (int i = 1; i < (*u).m; i++)
                {
                    for (int j = 1; j < (*u).n - 1; j++)
                    {
                        (*u).image_data[i][j] = (*u_bar).image_data[i][j];
                    }
                }
            }
            if (my_rank == num_procs - 1)
            {
                for (int i = 0; i < (*u).m - 1; i++)
                {
                    for (int j = 1; j < (*u).n - 1; j++)
                    {
                        (*u).image_data[i][j] = (*u_bar).image_data[i][j];
                    }
                }
            }
            if (my_rank != 0 && my_rank != num_procs - 1)
            {
                for (int i = 0; i < (*u).m; i++)
                {
                    for (int j = 1; j < (*u).n - 1; j++)
                    {
                        (*u).image_data[i][j] = (*u_bar).image_data[i][j];
                    }
                }
            }
        }
        // last iteration copy boundary
        if (it == iters - 1)
        {
            for (int i = 1; i < (*u).m - 1; i++)
            {
                (*u_bar).image_data[i][(*u).n - 1] = (*u).image_data[i][(*u).n - 1];
                (*u_bar).image_data[i][0] = (*u).image_data[i][0];
            }
            for (int i = 1; i < (*u).n - 1; i++)
            {
                (*u_bar).image_data[(*u).m - 1][i] = (*u).image_data[(*u).m - 1][i];
                (*u_bar).image_data[0][i] = (*u).image_data[0][i];
            }
        }
    }
    if (my_rank == 0) printf("\n");
    if (my_rank != num_procs - 1) free(lower_boundary);
    if (my_rank != 0) free(upper_boundary);
}