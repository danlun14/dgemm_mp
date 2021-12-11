#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <time.h>
#include "hpctimer.h"
#include <pthread.h>

#define NUM_THREADS 6

int *X, *Y, *C;

struct Data
{
    int lb, ub, size, number;
} data[NUM_THREADS];

void *saxpy_blas(void *arg)
{

    struct Data *data2 = (struct Data *)arg;
    unsigned int i, j;

    printf("%d\n", (*data2).size);
    C = (int *)malloc(sizeof(int) * (*data2).size * (*data2).size);
    X = (int *)malloc(sizeof(int) * (*data2).size * (*data2).size);
    Y = (int *)malloc(sizeof(int) * (*data2).size * (*data2).size);

    srand(time(NULL));
    for (i = (*data2).lb * (*data2).size; i < (*data2).ub * (*data2).size; ++i)
    {
        C[i] = 0;
        X[i] = 1;
        Y[i] = 2;
    }

    for (i = (*data2).lb; i < (*data2).ub; ++i)
    {
        for (j = 0; j < (*data2).size; ++j)
        {
            for (int j2 = 0; j2 < (*data2).size; ++j2)
            {
                C[i * (*data2).size + j] += X[i * (*data2).size + j2] * Y[j + j2 * (*data2).size];
            }
        }
    }

    printf("Thread %d\n", (*data2).number);

    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    double t1 = -hpctimer_getwtime();

    int i, check, n, n0 = atoi(argv[1]);

    pthread_t thread[NUM_THREADS];
    pthread_attr_t attr;

    //init
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);

    //create 0
    n = (int)((float)n0 / (float)NUM_THREADS);
    data[0].size = n0;
    data[0].lb = 0;
    data[0].ub = n + (n0 % NUM_THREADS);
    data[0].number = 0;
    check = pthread_create(&thread[0], &attr, saxpy_blas, (void *)&data[0]);
    if (check != 0)
    {
        printf("Create failed!\n");
        return 2;
    }

    //create others
    for (i = 1; i < NUM_THREADS; ++i)
    {
        data[i].size = n0;
        data[i].lb = data[i - 1].ub;
        data[i].ub = data[i].lb + n;
        data[i].number = i;

        check = pthread_create(&thread[i], &attr, saxpy_blas, (void *)&data[i]);
        if (check != 0)
        {
            printf("Thread %d failed\n", i);
            return 2;
        }
    }

    //check
    for (i = 0; i < NUM_THREADS; ++i)
    {
        check = pthread_join(thread[i], NULL);
        if (check)
        {
            printf("thread %d error\n", i);
            return 3;
        }
    }
    t1 += hpctimer_getwtime();
    printf("Time %lf\n", t1);

    return 0;
}