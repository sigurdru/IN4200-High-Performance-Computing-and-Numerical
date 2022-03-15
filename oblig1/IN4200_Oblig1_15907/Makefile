# CC := gcc
all:
	gcc -o run.exe -Wall -lm -fopenmp main.c read_graph_from_file.c PageRank_iterations.c top_n_webpages.c
run:
	./run.exe simple-webgraph.txt
run2:
	./run.exe 100nodes_graph.txt