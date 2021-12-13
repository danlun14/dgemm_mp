#include <stdio.h>
#include <stdlib.h>
#include "hpctimer.h"

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
    double t1 = -hpctimer_getwtime();
    for (int i = 0; i < NREPS; i++)
    {

        for (int id = 0; id <= N; id++)
        {

            for (int j = 0; j < n; j++)
            {
                for (int j2 = 0; j2 < n; j2++)
                {
                    c[id * n + j] += a[id * n + j2] * b[j + j2 * n];
                }
            }
        }
    }

    t1 += hpctimer_getwtime();
    t1 = t1 / NREPS;

    printf("Elapsed time: %.6f sec.\n", t1);
    return 0;
}
