# IN4200 Oblig2 15907
This README includes a description of how to compile and run the code and a file breakdown.

# How to run the code

First compile the program with
```
make compile
```
this will produce an executable file `run.exe`. In order to execute this file you have to provide it with the filename of a web graph, damping constant (d), convergence threashold value (epsilon) and number of top websites you want displayed (n).
```
./run.exe webgraph.txt 1. 0.000001 3
```
Alternatively you can run two of the example files by
```
#Use simple-webgraph.txt and displayes top 3 websites
make simple-webgraph:
#Use 100nodes_graph.txt and displayes top 10 websites
make 100nodes_graph
```

# File breakdown
## header.h
Declares functions called on by main.c

## main.c
Makes necessary allocations and function calls

## read_graph_from_file.c
Reads file containing web graph and storing the data using CRS format

## PageRank_iterations.c
Does performes the page rank algorithm (parallelized using OpenMP)

## top_n_webpages.c
Finds top n webpages and prints it in the terminal (parallelized using OpenMP)

## Makefile
Used for compiling and example runs

## simple-webgraph.txt & 100nodes_graph.txt
Example web graphs

## run.exe
Already compiled executable
