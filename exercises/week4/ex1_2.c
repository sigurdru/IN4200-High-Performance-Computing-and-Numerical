#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
    int N = 100000;
    double A[N], B[N];
    double s = M_PI;
    double sum;
    time_t t;
    for (int i = 0; i < N; i++)
    {
        A[i] = rand();
        B[i] = rand();
    }
    clock_t start, end;
    double cpu_time_used;
    start = clock();
    for (int i = 0; i < N; i++)
        A[i] = s * B[i]; // A ->store. B-->load. loader s en gang.
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf(" Took %f seconds. \n ", cpu_time_used);
    printf("Our computer stores integers with %lu bytes. \n", sizeof(double));
    sum = 8 * 2 * N / cpu_time_used * pow(10, -6);
    printf("%f", sum);
}