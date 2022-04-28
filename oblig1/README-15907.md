# **Required Work**

## Serial functions

```c++
void read_graph_from_file(char *filename, int *N, int **row_ptr, int **col_idx, double **val)
```

> **row_ptr**, **col_idx** and **val** are passed in as double pointers and allocated
inside the function:
>> Takes in the Correct arguments

***

```c++
void PageRank_iterations(int N, int *row_ptr, int *col_idx, double *val, double d,\
                                                double epsilon, double *scores)
```

> Implementing the iterative procedure of the ***PageRank*** algorithm
>> Takes in the correct arguments

> The computed PageRank scores are contained inside the pre-allocated 1D array **scores**
>> **scores** is pre-allocated in `main`

***

 ```c++
 void top_n_webpages(int N, double *socres, int n)  
 ```
 > The function goes through the PageRank scores and prints out the top **n** webpages with both their scores and webpage indices
 >> Prints the top `n` webpages with the highest scores as a command line input

## OpenMP parallelization

```c++
// Both IN3200 and IN4200 students
void PageRank_iterations(int N, int *row_ptr, int *col_idx, double *val, double d,\
                                                double epsilon, double *scores)
```
> ***PageRank_iterations*** parallelized using OpenMP
>> OpenMP implemented

***

```c++
// Only IN4200 studens
void top_n_webpages(int N, double *socres, int n)
```
> ***top_n_webpages*** parallelized using OpenMP
>> OpenMP implemented

# **File format & scores**

## Example webgraph-file Figure 1

```
# Directed graph (each unordered pair of nodes is saved once): 8-webpages.txt
# Just an example
# Nodes: 8   Edges: 17
# FromNodeId    ToNodeId
0       1
0       2
1       3
2       4
2       1
3       4
3       5
3       1
4       6
4       7
4       5
5       7
6       0
6       4
6       7
7       5
7       6
```
[Small example (Figure 1) link](https://www.uio.no/studier/emner/matnat/ifi/IN3200/v22/teaching-material/simple-webgraph.txt)

### CRS format

```c++
row_ptr = [0, 1, 4, 5, 6, 9, 12, 14, 17]
col_idx = [6, 0, 2, 3, 0, 1, 2, 3, 6, 3, 4, 7, 4, 7, 4, 5, 6]
val     = [0.333333, 0.500000, 0.500000, 0.333333, 0.500000,
            1.000000, 0.500000, 0.333333, 0.333333, 0.333333, 0.333333,
                0.500000, 0.333333, 0.500000, 0.333333, 1.000000, 0.333333]
```

### Student's CRS format

```c++
row_ptr = [0, 1, 4, 5, 6, 9, 12, 14, 17]
col_idx = [6, 0, 2, 3, 0, 1, 2, 3, 6, 3, 4, 7, 4, 7, 4, 5, 6]
val= [0.333333, 0.500000, 0.500000, 0.333333, 0.500000,
        1.000000, 0.500000, 0.333333, 0.333333, 0.333333, 0.333333,
          0.500000, 0.333333, 0.500000, 0.333333, 1.000000, 0.333333]
```

Runing the ***PageRank*** algorithm using `d=1` **(no damping)** will produce the following results:

```
---Initial guess:
scores=[0.125000,0.125000,0.125000,0.125000,0.125000,0.125000,0.125000,0.125000]
---After iteration 1:
scores=[0.041667,0.166667,0.062500,0.125000,0.145833,0.145833,0.104167,0.208333]
---After iteration 2:
scores=[0.034722,0.093750,0.020833,0.166667,0.107639,0.194444,0.152778,0.229167]
---After iteration 3:
scores=[0.050926,0.083333,0.017361,0.093750,0.116898,0.206019,0.150463,0.281250]
---After iteration 4:
scores=[0.050154,0.065394,0.025463,0.083333,0.090085,0.210841,0.179591,0.295139]
---After iteration 5:
scores=[0.059864,0.065586,0.025077,0.065394,0.100373,0.205376,0.177598,0.300733]
etc...
```

The student's results
```
scores= [0.041667, 0.166667, 0.062500, 0.125000, 0.145833, 0.145833, 0.104167, 0.208333]
scores= [0.034722, 0.093750, 0.020833, 0.166667, 0.107639, 0.194444, 0.152778, 0.229167]
scores= [0.050926, 0.083333, 0.017361, 0.093750, 0.116898, 0.206019, 0.150463, 0.281250]
scores= [0.050154, 0.065394, 0.025463, 0.083333, 0.090085, 0.210841, 0.179591, 0.295139]
scores= [0.059864, 0.065586, 0.025077, 0.065394, 0.100373, 0.205376, 0.177598, 0.300733]
```

> Comments on the results for the simple graph
>> Correct CRS-format and scores

## 100 nodes webgraph-file d= 0.85

[100 nodes link](https://www.uio.no/studier/emner/matnat/ifi/IN3200/v22/teaching-material/100nodes_graph.txt)

**scores:** [1](https://www.uio.no/studier/emner/matnat/ifi/IN3200/v19/teaching-material/scores_001.txt), [2](https://www.uio.no/studier/emner/matnat/ifi/IN3200/v19/teaching-material/scores_002.txt), [3](https://www.uio.no/studier/emner/matnat/ifi/IN3200/v19/teaching-material/scores_003.txt), [4](https://www.uio.no/studier/emner/matnat/ifi/IN3200/v19/teaching-material/scores_004.txt), [5](https://www.uio.no/studier/emner/matnat/ifi/IN3200/v19/teaching-material/scores_005.txt), [6](https://www.uio.no/studier/emner/matnat/ifi/IN3200/v19/teaching-material/scores_006.txt), [7](https://www.uio.no/studier/emner/matnat/ifi/IN3200/v19/teaching-material/scores_007.txt), [8](https://www.uio.no/studier/emner/matnat/ifi/IN3200/v19/teaching-material/scores_008.txt), [9](https://www.uio.no/studier/emner/matnat/ifi/IN3200/v19/teaching-material/scores_009.txt), [10](https://www.uio.no/studier/emner/matnat/ifi/IN3200/v19/teaching-material/scores_010.txt)

> Comments on the results of 100 nodes
>> Correct scores as well

# **Submission**
> Folder name **IN3200_Oblig1_xxx** or **IN4200_Oblig1_xxx** (**xxx** is the candidate number of the student)
>> Correct folder-format

> - Inside the folder, there should be at least the following files:
    - ***read_graph_from_file.c***
    - ***PageRank_iterations.c***
    - ***top_n_webpages.c***
    - ***main.c***
    - ***README.txt/README.md***
    >> Correct list of files

# **Student's README and additional comments**

A detailed README describing how to compile and run the program with a small description of the functions that has been implemented.

Your code was stopping at the first iteration in the while-loop. I don't know if you had the same problem on your end, but it was like that on my end. This is because

```
#pragma omp parallel for
for (i = 0; i < N; i++)
{
    old_scores[i] = scores[i];
    if (fabs(old_scores[i] - scores[i]) > barrier)
        barrier = fabs(old_scores[i] - scores[i]);
}
```

which I changed to

```
#pragma omp parallel for
for (i = 0; i < N; i++)
{
    if (fabs(old_scores[i] - scores[i]) > barrier) {
        barrier = fabs(old_scores[i] - scores[i]);
    }
    old_scores[i] = scores[i];
}
```

In your code you update `old_scores` then you test for difference, which means `old_scores = scores` before the if-test kicks in and naturally `fabs` is going to return 0. I fixed it by testing and updating barrier first (if true) then after that update the values in `old_scores`. And from there it worked just fine :)
