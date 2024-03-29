#include <stdio.h>
#include <omp.h>

#define N 100000 // 100.000 elementos

void inicializar(int vector1[], int vector2[])
{
#pragma omp parallel for
    for (int i = 0; i < N; i++)
    {

        vector1[i] = omp_get_thread_num();
        vector2[i] = omp_get_thread_num();
    }
}

void suma(int vector1[], int vector2[], int resultado[])
{
#pragma omp parallel for
    for (int i = 0; i < N; i++)
    {
        resultado[i] = vector1[i] + vector2[i];
    }
}

void main()
{
    int num_threads = 100;
    omp_set_num_threads(num_threads);

    int vector1[N];
    int vector2[N];
    int resultado[N];

    inicializar(vector1, vector2);
    suma(vector1, vector2, resultado);
}