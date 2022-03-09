#include<math.h>
#include<stdio.h>

double numerical_integration (double x_min, double x_max, int slices)
{
    double delta_x = (x_max - x_min)/slices;
    double x, sum = 0.;
    for (int i=0; i<slices; i++) {
        x = x_min + (i+0.5)*delta_x;
        sum += 4./(1. + x*x);
    }
    return sum*delta_x;
}

int main() 
{
    double x_min = 0.;
    double x_max = 1.;
    int slice_size = 10;
    double solution, diff;
    for (int i=1; i<10; i++) {
        solution = numerical_integration(x_min, x_max, slice_size*i);
        diff = solution - M_PI;
        printf("Absolute difference: %f\n", fabs(diff));
    }
    
}

/* 
If the floating-point division operation can not be pipelined we can replace it with multiplication.
Although this would not give correct results, we could see if this yield performance increase.
This can give us an estimate of the latency of a floating point division.
 */