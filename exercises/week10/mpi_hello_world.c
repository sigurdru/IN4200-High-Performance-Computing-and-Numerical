#include <mpi.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
    // Initialize the MPI environment
    int size, rank;
    char sentence[50];
    MPI_Init(NULL, NULL);

    // Get the number of processes
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Get the rank of the process
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Print off a hello world message


    sprintf(sentence, "Hello world I have rank %d out of %d processors\n", rank, size);
    
    if (rank != 0)
    {
        MPI_Send(sentence, strlen(sentence) + 1, MPI_UNSIGNED_CHAR, 0, 0, MPI_COMM_WORLD);
    }
    else
    {

        printf("%s", sentence);
        for (int i = 1; i<size; i++)
        {
            MPI_Recv(sentence, strlen(sentence) + 1, MPI_UNSIGNED_CHAR, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("%s", sentence);
        }
    }

    

    // Finalize the MPI environment.
    MPI_Finalize();
}

// mpicc mpi_hello_world.c -o hello-world
// mpirun --hostfile hostfile -np 8 ./hello-world
