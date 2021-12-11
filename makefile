all: pthreads openmp

openmp: openmp.c
	gcc -Wall openmp.c hpctimer.c -o openmp -O0 -g -fopenmp

pthreads: pthreads.c
	gcc -opth_main hpctimer.c pthreads.c -Wall -lpthread
	
	