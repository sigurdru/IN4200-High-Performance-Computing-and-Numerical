#include<stdio.h>
#include<math.h>
#include<stdlib.h>

// Functions
double exer1a();
void exer1b(double*, double*);
void exer1c();
void exer1d();

int main(){
    // Solution 1a)
    double solution_exer1a = exer1a();
    printf("solution of exer1a = %f \n", solution_exer1a); 

    // Solution 1b)
    double max_solution_exer1b, min_solution_exer1b;
    exer1b(&max_solution_exer1b, &min_solution_exer1b);
    printf("max value = %.2f ", max_solution_exer1b);
    printf("min value = %.2f \n", min_solution_exer1b);

    // Solution 1c)
    exer1c();
    
    // Solution 1d)
    exer1d();
    return 0;
}

double exer1a(){
    double sum = 0.0;
    int n = 20;
    for(int i = 0; i < n; i++){
        sum = sum + pow(-1, i)/pow(2, 2*i);
    }  
    return sum;
}

void exer1b(double *max, double *min){
    int n = 4;
    double arr[n];
    // Fill array with random numbers
    for(int i = 0; i<n; i++){
        arr[i] = rand();
        // printf("%.6f", arr[i]); printf("\n");
    }
    // Finding minimum and maximum value
    *max = arr[0];
    *min = *max;
    for(int i = 0; i<n; i++){
        if(arr[i]>*max){
            *max = arr[i];
        }
        if(arr[i]<*min){
            *min = arr[i];
        }
    }
}

void exer1c(){
    int m, n, h;
    m = 4;
    n = 3;
    h = 0;
    int mat1[m][n];
    int mat2[m][n];


    for (int i = 0; i<n; i++) {
        for (int j = 0; j<m; j++) {
            mat1[j][i] = h;
            h += 1;
        }
    }
    h = 0;
    for (int i = 0; i<m; i++){
        for (int j = 0; j<n; j++){
            mat2[i][j] = h;
            h += 1; 
        }
    }

    for (int j = 0; j<m; j++) {
        for (int i = 0; i<n; i++) {
            printf("(%i|", mat1[j][i]);
            printf("%i)", mat2[j][i]);
        }
        printf("\n");
    }
}

int index3d(int i, int j, int k, int nx, int ny){
    /*
    Used to index 1D array which represent 3D array.
    */
    int index = i + j*nx + k*nx*ny;
    return index;
}
void exer1d(){
    int nx, ny, nz;
    nx = 2;
    ny = 3;
    nz = 4;
    double *u = (double*)malloc(nx*ny*nz*sizeof(double));
    // Store data
    for (int i=0; i<nx; i++) {
        for (int j=0; j<ny; j++) {
            for (int k=0; k<nz; k++){
                u[index3d(i, j, k, nx, ny)] = i*ny*nz + j*nz + k;
            }
        }
    }
    // Free space
    free(u);
}