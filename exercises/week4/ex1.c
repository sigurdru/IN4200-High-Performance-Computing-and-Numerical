#include<time.h>
#include<math.h>
#include<stdlib.h>
#include<stdio.h>


int main(int argc)
{
    if (argc < 2){
        printf("Usage: ./prog.exe N_ELEMENTS\n");
        return 1;
    }
    // int N = argc;
    int N = 100000;
    double A[N], B[N];
    double s = M_PI;
    double time_taken, B_eff;
    // Fill with data

    for (int i = 0; i < N; i++){
        A[i] = rand();
        B[i] = rand();
    }


    clock_t start, end;
    start = clock();
    for (int i = 0; i < N; i++) A[i] = s * B[i];
    end = clock();
    time_taken = (double)(end-start)/CLOCKS_PER_SEC;
    // printf("%f \n", time_taken);
    B_eff = 2*8*N/time_taken*pow(10,-6);
    printf("B_eff:%f MB/sec\n", B_eff);
    return 0;
}
