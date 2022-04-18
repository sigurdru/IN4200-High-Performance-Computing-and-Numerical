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
    (*u).image_data = (float **)malloc(m * n * sizeof(float *));
}
void deallocate_image(image *u)
{
    // This function free the storage used by image_data inside u
    free((*u).image_data);
}
void convert_jpeg_to_image(const unsigned char *image_chars, image *u);
void convert_image_to_jpeg(const image *u, unsigned char *image_chars);
void iso_diffusion_denoising(image *u, image *u_bar, float kappa, int iters);