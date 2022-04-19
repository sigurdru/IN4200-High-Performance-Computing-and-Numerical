CC = gcc
CFLAGS = -O2

LDFLAGS = -L../../simple-jpeg/ -lsimplejpeg

PROJ = serial_main
OBJS = serial_main.o functions.c

all: simple-jpeg $(PROJ)

serial_main: $(OBJS)
	$(CC) $(CFLAGS) $< -o $@ functions.c $(LDFLAGS) 

simple-jpeg:
	$(MAKE) -C ../../simple-jpeg

obj-clean:
	$(RM) *.o

exec-clean:
	$(RM) $(PROJ)

autosave-clean:
	$(RM) *~

clean:
	$(MAKE) obj-clean
	$(MAKE) exec-clean
	$(MAKE) autosave-clean
	$(MAKE) -C ../simple-jpeg clean

run:
	./serial_main 0.2 50 ../mona_lisa_noisy.jpg ../mona_lisa.jpg

# -fsanitize=address