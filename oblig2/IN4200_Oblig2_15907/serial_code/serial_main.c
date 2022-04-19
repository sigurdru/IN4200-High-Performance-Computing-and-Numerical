/* needed header files .... */
// Standard libraries
#include <stdio.h>
#include <stdlib.h>

// Header file we define
#include "header.h"

/* declarations of functions import_JPEG_file and export_JPEG_file */
void import_JPEG_file(const char *filename, unsigned char **image_chars,
                      int *image_height, int *image_width,
                      int *num_components);
void export_JPEG_file(const char *filename, const unsigned char *image_chars,
                      int image_height, int image_width,
                      int num_components, int quality);

int main(int argc, char *argv[])
{
    int m, n, c, iters;
    float kappa;
    image u, u_bar;
    unsigned char *image_chars;
    char *input_jpeg_filename, *output_jpeg_filename;
    /* read from command line: kappa, iters, input_jpeg_filename, output_jpeg_filename */
    if (argc < 5)
    {
        printf("Error: Not enough arguments given.\n");
        printf("Please give the following arguments:\n");
        printf("- kappa [double] (for algorithm)\n");
        printf("- iters [int] (damping constant)\n");
        printf("- input_jpeg_filename [char] (input jpeg filename with destination)\n");
        printf("- output_jpeg_filename [char] (output jpeg filename with destination)\n");
        printf("Example: ./serial.main 0.2 1000 ../mona_lisa_noisy.jpg ../mona_lisa.jpg \n");

        exit(0);
    }
    kappa = atof(argv[1]);
    iters = atoi(argv[2]);
    input_jpeg_filename = argv[3];
    output_jpeg_filename = argv[4];

    import_JPEG_file(input_jpeg_filename, &image_chars, &m, &n, &c);
    printf("Succeeded! vertical pixels: %d, horizontal pixels: %d, num components: %d\n",
           m, n, c);
    allocate_image(&u, m, n);
    allocate_image(&u_bar, m, n);
    convert_jpeg_to_image(image_chars, &u);
    // iso_diffusion_denoising(&u, &u_bar, kappa, iters);
    convert_image_to_jpeg(&u_bar, image_chars);
    export_JPEG_file(output_jpeg_filename, image_chars, m, n, c, 75);
    deallocate_image(&u);
    deallocate_image(&u_bar);
    return 0;
}