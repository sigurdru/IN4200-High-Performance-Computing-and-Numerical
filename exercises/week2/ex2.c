#include<stdio.h>
#include<string.h>
#include<time.h>

// #include<stdlib.h>
// #include<math.h>

void hand_copy(char *, char *, int);
void memcpy_copy(char *, char *);

int main()
{
    // Create array with values
    char a[200] = "Dette er en tekst jeg skal kopiere. Den kan være ganske lang, slik at jeg faktisk kan måle hvordan det er å kopiere den";
    char b[200];
    char c[200];
    int N = strlen(a);

    // Call and time functions
    clock_t t1;
    clock_t t2;
    t1 = clock();
    hand_copy(a, b, N);
    t1 = clock() - t1;
    t2 = clock();
    memcpy_copy(a, c);
    t2 = clock() - t2;
    double time_taken1 = ((double)t1) / CLOCKS_PER_SEC;
    double time_taken2 = ((double)t2) / CLOCKS_PER_SEC;

    // Make sure everything copied correctly
    printf("a: %s\n", a);
    printf("b: %s\n", b);
    printf("c: %s\n", c);

    // Print time it took
    
    printf("manual: %lf seconds\n", time_taken1);
    printf("memcpy: %lf seconds\n", time_taken2);

    return 0;
}

void hand_copy(char *a, char *b, int N)
{
    for (int i=0; i<N; i++) 
    {
        b[i] = a[i];
    }
}

void memcpy_copy(char *a, char *b)
{
    memcpy(b, a, strlen(a)+1);
}