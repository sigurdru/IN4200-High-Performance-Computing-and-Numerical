# CC := gcc
all:
	gcc -o run.exe -Wall -lm -fopenmp main.c read_graph_from_file.c PageRank_iterations.c top_n_webpages.c
run1:
	./run.exe simple-webgraph.txt 1. 0.000001 8
run2:
	./run.exe 100nodes_graph.txt 0.85 0.000001 20