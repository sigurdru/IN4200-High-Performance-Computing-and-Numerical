#include "stdio.h"
#include "time.h"
#include "stdlib.h"
#include "mpi.h"


int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);
    int n_cores, rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &n_cores);
    int i, j;
    int N = 13;
    int x[N];
    int y[N];

    // Generate A and x and allocate A and y for main core
    if (rank == 0)
    {
        // Generate random seed
        srand(time(NULL));
        int A[N][N];
        for (i = 0; i<N; i++)
        {
            x[i] = rand();
            for (j = 0; j<N; j++)
            {
                A[i][j] = rand();
            }
        }
    }
    // Generate start and stop index for each core and generate each A part
    int start, stop, chunk_size, rest;
    rest = N%n_cores;
    chunk_size = (N-rest)/n_cores;

    start = chunk_size*rank;
    stop  = chunk_size*(rank + 1) - 1;

    int partial_A[chunk_size][N];



    // printf("%d \n", num_chunks);
    // printf("%d \n", rest);


    MPI_Finalize();
}