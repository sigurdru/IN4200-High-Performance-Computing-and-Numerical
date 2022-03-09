#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{   
    int n,m,p;
    n = 10;
    m = 15;
    p = 5;
    
    double *A_1d = malloc(n * m * sizeof(double));
    double *B_1d = malloc(m * p * sizeof(double));
    double *C_1d = malloc(n * p * sizeof(double));
    double **A = malloc(n * sizeof(double *));
    double **B = malloc(m * sizeof(double *));
    double **C = malloc(n * sizeof(double *));

    // Setup of matrices
    for (int i = 0; i<n; i++) A[i] = A_1d + m*i;
    for (int i = 0; i<m; i++) B[i] = B_1d + p*i;
    for (int i = 0; i<n; i++) C[i] = C_1d + p*i;

    // fill matrix with random values
    for (int i = 0; i<n*m; i++) A_1d[i] = rand();
    for (int i = 0; i<m*p; i++) B_1d[i] = rand();


    // The actual multiplication
    for (int i = 0; i<n; i++)
    {
        for (int j = 0; j<p; j++)
        {
            for (int k = 0; k<m; k++)
            {
                C[i][j] += A[i][k]*B[k][j];
            } 
        }
    }

    free(A_1d);
    free(B_1d);
    free(C_1d);
    free(A);
    free(B);
    free(C);
    return 0;
}