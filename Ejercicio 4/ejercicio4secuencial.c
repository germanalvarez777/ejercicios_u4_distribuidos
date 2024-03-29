#include <stdio.h>
#include <time.h>

#define N 100000       // 100.000 elementos
#define GRANDE 1000000 // 1.000.000 base

void inicializar(int vector1[], int vector2[])
{
    for (int i = 0; i < N; i++)
    {
        vector1[i] = GRANDE + i;
        vector2[i] = GRANDE + i;
    }
}

void suma(int vector1[], int vector2[], int resultado[])
{
    for (int i = 0; i < N; i++)
    {
        resultado[i] = vector1[i] + vector2[i];
    }
}

void main()
{
    int vector1[N];
    int vector2[N];
    int resultado[N];

    inicializar(vector1, vector2);

    clock_t tiempo_inicio = clock();

    suma(vector1, vector2, resultado);

    clock_t tiempo_fin = clock();

    double tiempo_transcurrido = (double)(tiempo_fin - tiempo_inicio) / CLOCKS_PER_SEC;
    printf("Tiempo de suma: %f segundos\n", tiempo_transcurrido);
}
