// Standard libraries
#include <stdio.h>
#include <stdlib.h>

// Header file we define
#include "header.h"
 
void allocate_image(image *u, int m, int n)
{
    // This function allocate the 2D array image_date inside u for given m (heigth) and n (width)
    (*u).m = m;
    (*u).n = n;
    (*u).image_data = (float **)malloc(m * sizeof(float *));
    (*u).image_data[0] = (float *) malloc(m * n * sizeof(float));
    for (int i = 1; i<m; i++)
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
    for (int i = 0; i<(*u).m; i++)
    {
        for (int j = 0; i<(*u).n; i++)
        {
            (*u).image_data[i][j] = (float)image_chars[i * (*u).m + j * (*u).n];
        }
    }
}
void convert_image_to_jpeg(const image *u, unsigned char *image_chars)
{
    // This function converts an image struct into an array of unsigned char
    for (int i = 0; i < (*u).m; i++)
    {
        for (int j = 0; i < (*u).n; i++)
        {
            image_chars[i * (*u).m + j * (*u).n] = (unsigned char)(*u).image_data[i][j];
        }
    }
}
void iso_diffusion_denoising(image *u, image *u_bar, float kappa, int iters)
{
    
}