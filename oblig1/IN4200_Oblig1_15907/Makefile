compile:
	gcc -o run.exe -Wall -lm -fopenmp main.c read_graph_from_file.c PageRank_iterations.c top_n_webpages.c
simple-webgraph:
	./run.exe simple-webgraph.txt 1. 0.000001 3
100nodes_graph:
	./run.exe 100nodes_graph.txt 0.85 0.000001 10