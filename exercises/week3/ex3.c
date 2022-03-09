#include<math.h>
#include<time.h>
#include<stdio.h>

double my_pow(double x)
{
    double x100 = x;
    for (int i = 0; i<5; i++) x100 *= x100;
    // after this loop we have x^32
    x100 = x100*x100*x100*x*x*x*x;
    return x100;
}

int main()
{   
    double x = 1.00000000001;
    double x100, my_time, their_time;
    
    clock_t time;
    time = clock();
    x100 = my_pow(x);
    time = clock() - time;
    my_time = ((double)time) / CLOCKS_PER_SEC;

    time = clock();
    x100 = pow(x, 100);
    time = clock() - time;
    their_time = ((double)time) / CLOCKS_PER_SEC;

    printf("Mine: %f seconds\n", my_time);
    printf("Thei: %f seconds\n", their_time);

    return 0;
}