/* needed header files .... */
// Standard libraries
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

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
    int my_m, my_n, my_rank, num_procs;
    float kappa;
    image u, u_bar, whole_image;
    unsigned char *image_chars, *my_image_chars;
    char *input_jpeg_filename, *output_jpeg_filename;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
    /* read from command line: kappa, iters, input_jpeg_filename, output_jpeg_file
    name */
    if (my_rank == 0)
    {
        if (argc < 5)
        {
            printf("Error: Not enough arguments given.\n");
            printf("Please give the following arguments:\n");
            printf("- kappa [double] (for algorithm)\n");
            printf("- iters [int] (damping constant)\n");
            printf("- input_jpeg_filename [char] (input jpeg filename with destination)\n");
            printf("- output_jpeg_filename [char] (output jpeg filename with destination)\n");
            printf("Example: mpirun -np 4 ./parallel_main 0.2 50 ../mona_lisa_noisy.jpg ../mona_lisa_parallel.jpg \n");

            exit(0);
        }
        printf("Number of cores: %d\n", num_procs);
        kappa = atof(argv[1]);
        iters = atoi(argv[2]);
        input_jpeg_filename = argv[3];
        output_jpeg_filename = argv[4];
    }

    MPI_Bcast(&kappa, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&iters, 1, MPI_INT, 0, MPI_COMM_WORLD);
    if (my_rank == 0)
    {
        import_JPEG_file(input_jpeg_filename, &image_chars, &m, &n, &c);
        allocate_image(&whole_image, m, n);
        printf("Succeeded! vertical pixels: %d, horizontal pixels: %d, num components: %d\n",
               m, n, c);
    }
    MPI_Bcast(&m, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    /* 2D decomposition of the m x n pixels evenly among the MPI processes */
    /* each process asks process 0 for a partitioned region */
    /* of image_chars and copy the values into u */
    int rows = m / num_procs;
    int remainder = m % num_procs;
    int *n_rows = malloc(num_procs * sizeof(*n_rows));
    int *sendcounts = malloc(num_procs * sizeof(*sendcounts));
    int *displs = malloc(num_procs * sizeof(*displs));
    displs[0] = 0;
    for (int i = 0; i < num_procs - 1; i++)
    {
        n_rows[i] = rows + ((i >= (num_procs - remainder)) ? 1 : 0);
        sendcounts[i] = n_rows[i] * n;
        displs[i + 1] = displs[i] + sendcounts[i];
    }
    n_rows[num_procs - 1] = rows + ((num_procs)-1 >= (num_procs - remainder) ? 1 : 0);
    sendcounts[num_procs - 1] = n_rows[num_procs - 1] * n;
    my_m = n_rows[my_rank];
    my_n = n;
    allocate_image(&u, my_m, my_n);
    allocate_image(&u_bar, my_m, my_n);
    my_image_chars = malloc(n * n_rows[my_rank] * sizeof(*my_image_chars));
    MPI_Scatterv(image_chars,
                 sendcounts,
                 displs,
                 MPI_UNSIGNED_CHAR,
                 my_image_chars,
                 n*n_rows[my_rank],
                 MPI_UNSIGNED_CHAR,
                 0,
                 MPI_COMM_WORLD);

    convert_jpeg_to_image(my_image_chars, &u);
    iso_diffusion_denoising_parallel(&u, &u_bar, kappa, iters);
    /* each process sends its resulting content of u_bar to process 0 */
    /* process 0 receives from each process incoming values and */
    /* copy them into the designated region of struct whole_image */
    // Have to introduce these variables, don't know why the solution below
    // does not work!!!!!!
    float *tmp_var = u_bar.image_data[0];
    float *tmp_var_main;
    if (my_rank == 0) 
    {
        tmp_var_main = whole_image.image_data[0];
    }
    MPI_Gatherv(tmp_var,
                sendcounts[my_rank],
                MPI_FLOAT,
                tmp_var_main,
                sendcounts,
                displs,
                MPI_FLOAT,
                0,
                MPI_COMM_WORLD);

    // MPI_Gatherv((u_bar.image_data[0]),
    //             sendcounts[my_rank],
    //             MPI_FLOAT,
    //             (whole_image.image_data[0]),
    //             sendcounts,
    //             displs,
    //             MPI_FLOAT,
    //             0,
    //             MPI_COMM_WORLD);
    if (my_rank == 0)
    {
        convert_image_to_jpeg(&whole_image, image_chars);
        export_JPEG_file(output_jpeg_filename, image_chars, m, n, c, 75);
        deallocate_image(&whole_image);
    }
    deallocate_image(&u);
    deallocate_image(&u_bar);
    free(sendcounts);
    free(displs);
    free(n_rows);
    free(my_image_chars);
    MPI_Finalize();
    return 0;
}