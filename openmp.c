#include <stdio.h>
#include <stdlib.h>
#include "hpctimer.h"
#include <omp.h>

enum
{
	NREPS = 1
};
int N = 1000;
void printVector(double *v, int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("%.3lf ", v[i]);
	}
	printf("\n");
}

int main(int argc, char *argv[])
{
	N = atoi(argv[1]);
	int m = N, n = N;
	int numt = 6;
	double *a, *b, *c;
	fflush(stdout);
	// Allocate memory for 2-d array a[m, n]
	a = malloc(sizeof(*a) * m * n);
	b = malloc(sizeof(*b) * m * n);
	c = malloc(sizeof(*c) * m * n);

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			a[i * n + j] = 1;
			b[i * n + j] = 2;
			c[i * n + j] = 0.0;
		}
	}
	printf("\nN = %d\n", N);
	fflush(stdout);
	double t1 = -omp_get_wtime();
	for (int i = 0; i < NREPS; i++)
	{

#pragma omp parallel num_threads(numt)
		{
#pragma omp master
			printf("Num Threads = %d\n", omp_get_num_threads());

			int nthreads = omp_get_num_threads();
			int threadid = omp_get_thread_num();
			int items_per_thread = N / nthreads;
			int lb = threadid * items_per_thread;
			int ub = (threadid == nthreads - 1) ? (m - 1) : (lb + items_per_thread - 1);

			for (int id = lb; id <= ub; id++)
			{

				for (int j = 0; j < n; j++)
				{
					for (int j2 = 0; j2 < n; j2++)
					{
						c[id * n + j] += a[id * n + j2] * b[j + j2 * n];
					}
				}
			}

#pragma omp barrier
		}
	}
	t1 += omp_get_wtime();
	t1 = t1 / NREPS;

	printf("Elapsed time: %.6f sec.\n", t1);
	return 0;
}
