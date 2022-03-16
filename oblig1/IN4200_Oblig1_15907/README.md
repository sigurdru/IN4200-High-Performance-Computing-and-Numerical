# IN4200 Oblig1 15907
This README includes a description of code structure and how to run the code.

# How to run the code
 
First compile the program with 
```
make compile
``` 
this will produce an executable file `run.exe`. In order to execute this file you have to provide it with the filename of a file containing a web graph, a damping constant, convergence threashold value and number of top websites you want displayed.
```
./run.exe simple-webgraph.txt 1. 0.000001 3
```
Alternatively you can run two of the example files by
```
#Use simple-webgraph.txt and displayes top 3
make simple-webgraph:
#Use 100nodes_graph.txt and displayes top 10
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

## simple-webgraph.txt & 100nodes_graph.txt
Example files

## run.exe
Already compiled executable