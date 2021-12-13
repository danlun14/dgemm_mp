all: pthreads serial_main openmp

openmp: openmp.c
	gcc -Wall openmp.c hpctimer.c -o openmp -O0 -fopenmp

serial_main: serial.main.c
	gcc -Wall serial.main.c hpctimer.c -o main -O0

pthreads: pthreads.c
	gcc -opth_main hpctimer.c pthreads.c -Wall -lpthread
	
	