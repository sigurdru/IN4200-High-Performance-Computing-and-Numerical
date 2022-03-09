#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<omp.h>

void test();

void code1_1(int);
double code2_1(double *, double *, int);
double code2_2(double *, double *, int);
double code2_3(double *, double *, int);

int main() {
    omp_set_num_threads(1);
    // ex1 a)
    int x = 10000000;
    code1_1(x);

    // ex2)
    clock_t start, end;
    double time1, time2, time3;
    int n = 1000000;
    double *a = malloc(n * sizeof(double));
    double *b = malloc(n * sizeof(double));
    for (int i = 0; i<n; i++){
        a[i] = rand();
        b[i] = rand();
    }
    // static
    start = clock();
    code2_1(a, b, n);
    end = clock();
    time1 = (double)(end - start) / CLOCKS_PER_SEC;
    // dynamic
    start = clock();
    code2_2(a, b, n);
    end = clock();
    time2 = (double)(end - start) / CLOCKS_PER_SEC;
    // guided
    start = clock();
    code2_3(a, b, n);
    end = clock();
    time3 = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Static: %f\nDynamic: %f\nGuided: %f\n", time1, time2, time3);

    free(a);
    free(b);
    return 1;
}

void code1_1(int x) {
    int N = (int)sqrt(x);
    double *a = malloc(N * sizeof(double));
    double *b = malloc(N * sizeof(double));

    #pragma omp for
    for (int i = 0; i < N; i++)
    {
        a[i] = 2.3 * x;
        if (i < 10) 
            b[i] = a[i];
    }
    free(a);
    free(b);
}

double code2_1(double *a, double *b, int n) 
{
    double dotp = 0.;
    #pragma omp parallel for
    for (int i = 0; i < n; i++){
        dotp += a[i] * b[i];
    }
    return dotp;
}
double code2_2(double *a, double *b, int n)
{
    double dotp = 0.;
    #pragma omp parallel for schedule(dynamic)
    for (int i = 0; i < n; i++)
    {
        dotp += a[i] * b[i];
    }
    return dotp;
}
double code2_3(double *a, double *b, int n)
{
    double dotp = 0.;
    #pragma omp parallel for schedule(guided)
    for (int i = 0; i < n; i++)
        dotp += a[i] * b[i];
    return dotp;
}

