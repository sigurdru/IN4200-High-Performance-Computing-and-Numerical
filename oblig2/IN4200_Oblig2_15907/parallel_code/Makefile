MPICC = mpicc
CFLAGS = -O2

LDFLAGS = -L../../simple-jpeg/ -lsimplejpeg

PROJ = parallel_main

all: simple-jpeg $(PROJ)

parallel_main: parallel_main.c functions.c
	$(MPICC) $(CFLAGS) -o $@ parallel_main.c functions.c $(LDFLAGS) 

simple-jpeg:
	$(MAKE) -C ../../simple-jpeg

run:
	mpirun -np 4 ./parallel_main 0.2 50 ../mona_lisa_noisy.jpg ../mona_lisa_parallel.jpg
