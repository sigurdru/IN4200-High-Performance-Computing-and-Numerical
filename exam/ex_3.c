#include"omp.h"
#include"stdlib.h"
#include"stdio.h"

void func(int N, int *arr);

int main()
{
    int N = 10;
    int arr[10] = {3, 1, 9, 5, 1, 2, 5, 6, 2, 10};

    func(N, arr);

    for (int i = 0; i<N; i++)
    {
        printf("%i ", arr[i]);
    }
    printf("\n");
    free(arr);
    return 0;
}

void func(int N, int *arr)
{
    int pass, my_smallIndex, j, temp, myID, smallIndex;
    int num_threads = omp_get_max_threads();
    int *contenders = malloc(num_threads * sizeof(int));

    for (pass = 0; pass < N - 1; pass++)
    {
        my_smallIndex = pass;
        #pragma omp parallel for private(j, my_smallIndex, myID)
        for (j = pass + 1; j < N; j++)
        {
            myID = omp_get_thread_num();
            if (arr[j] < arr[my_smallIndex])
                my_smallIndex = j;
                contenders[myID] = my_smallIndex;
        }
        
        // Find actual smallest
        smallIndex = contenders[0]; 
        for(j = 1; j<num_threads && j < (N-1 - pass); j++)
        {
            if (arr[smallIndex] > arr[contenders[j]])
                smallIndex = contenders[j];
        }

        temp = arr[pass];
        arr[pass] = arr[smallIndex];
        arr[smallIndex] = temp;
    }
}

// void func(int N, int *arr)
// {
//     int pass, smallIndex, j, temp;
//     for (pass = 0; pass < N - 1; pass++)
//     {
//         smallIndex = pass;
//         for (j = pass + 1; j < N; j++)
//         {
//             if (arr[j] < arr[smallIndex])
//                 smallIndex = j;
//         }
//         temp = arr[pass];
//         arr[pass] = arr[smallIndex];
//         arr[smallIndex] = temp;
//     }
// }