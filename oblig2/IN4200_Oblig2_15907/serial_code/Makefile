CC = gcc
CFLAGS = -O2

LDFLAGS = -L../../simple-jpeg/ -lsimplejpeg

PROJ = serial_main

all: simple-jpeg $(PROJ)

serial_main: serial_main.c functions.c
	$(CC) $(CFLAGS) -o $@ serial_main.c functions.c $(LDFLAGS) 

simple-jpeg:
	$(MAKE) -C ../../simple-jpeg

run:
	./serial_main 0.2 50 ../mona_lisa_noisy.jpg ../mona_lisa.jpg

# -fsanitize=address