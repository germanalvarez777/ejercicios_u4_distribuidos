#include <stdio.h>
#include <omp.h>

#define N 100000       // 100.000 elementos
#define BASE 100000000 // 1.000.000 Base

void inicializar(int vector1[], int vector2[])
{

#pragma omp parallel for
    for (int i = 0; i < N; i++)
    {
        vector1[i] = BASE + i;
        vector2[i] = BASE + i;
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
    int num_threads = 1;
    omp_set_num_threads(num_threads);

    int vector1[N];
    int vector2[N];
    int resultado[N];

    inicializar(vector1, vector2);

    double tiempo_inicio = omp_get_wtime();
    printf("Tiempo de inicio: %.9f segundos\n", tiempo_inicio);

    suma(vector1, vector2, resultado);

    double tiempo_fin = omp_get_wtime();
    printf("Tiempo de finalizacion: %.9f segundos\n", tiempo_fin);

    double tiempo_transcurrido = tiempo_fin - tiempo_inicio;
    printf("Tiempo de suma: %.9f segundos\n", tiempo_transcurrido);
}