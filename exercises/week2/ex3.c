#include<math.h>
#include<stdlib.h>
#include<stdio.h>

int Index3D(int i, int j, int k, int nx, int ny)
{
    return i + nx*j + nx*ny*k;
}

int main()
{
    // Create everything
    int nx, ny, nz;
    nx = 10;
    ny = 20;
    nz = 10;
    double *u = (double *)malloc(nx*ny*nz*sizeof(double)); 
    double *v = (double *)malloc(nx*ny*nz*sizeof(double));

    // Insert values
    for (int i=0; i<nx; i++)
    {
        for (int j=0; j<ny; j++)
        {
            for (int k = 0; k < nz; k++)
            {
                v[Index3D(i, j, k, nx, ny)] = 2.0 + sin((i*j*k*M_PI)/(nx - 1)*(ny - 1)*(nz - 1));
                u[Index3D(i, j, k, nx, ny)] = 0.;
            }
        }
    }
    
    int n_iter = 100;
    // Do this n_iter iterations!
    for (int n=0; n<n_iter; n++)
    {
        // Qualculate
        for (int i = 1; i < nx - 1; i++)
        {
            for (int j = 1; j < ny - 1; j++)
            {
                for (int k = 1; k < nz - 1; k++)
                {
                    u[Index3D(i, j, k, nx, ny)] = v[Index3D(i, j, k, nx, ny)] +
                                                  (v[Index3D(i - 1, j, k, nx, ny)] + v[Index3D(i, j - 1, k, nx, ny)] +
                                                   v[Index3D(i, j, k - 1, nx, ny)] - 6 * v[Index3D(i, j, k, nx, ny)] +
                                                   v[Index3D(i + 1, j, k, nx, ny)] + v[Index3D(i, j + 1, k, nx, ny)] +
                                                   v[Index3D(i, j, k + 1, nx, ny)]) /
                                                      6;
                }
            }
        }
        // Copy
        for (int i = 0; i < nx; i++)
        {
            for (int j = 0; j < ny; j++)
            {
                for (int k = 0; k < nz; k++)
                {
                    v[Index3D(i, j, k, nx, ny)] = u[Index3D(i, j, k, nx, ny)];
                }
            }
        }
    }


    // DeALlOcaTe
    free(u);
    free(v);
}