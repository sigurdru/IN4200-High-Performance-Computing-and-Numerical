# IN4200 Oblig2 15907
This README includes a description of how to compile and run the code and a file breakdown.

# How to run the code
 
First chose if you want to run the parallelized or serialized code 
```
cd serial_code #For serialized code
cd parallel_code #For parallelized code
``` 
Then you need to compile with (NOTE: before you compile you need to have simple-jpeg 
outside the IN4200_Oblig2_15907 folder)
```
make all
```
this will produce an executable file `serial_main` or `parallel_main` depending on if you 
are running the serialized code or not. In order to execute this file you have to provide 
it with kappa, numer of iterations (iters), input black and gray image and
output image name. Alternatively you can run the example image with
```
make run
```

# File breakdown
## header.h
Declares functions called on by main.c

## serial_main.c/parallel_main.c
Makes necessary allocations and function calls

## functions.c
Contains functions called by serial_main.c/parallel_main.c

## Makefile
Used for compiling and example runs

## mona_lisa_noisy.jpgg
Example noisy image

## parallel_main/serial_main 
Already compiled executable