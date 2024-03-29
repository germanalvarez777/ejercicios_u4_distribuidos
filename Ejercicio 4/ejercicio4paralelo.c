#include <stdio.h>
#include <omp.h>

#define N 1000 // Elementos Arreglo

void inicializar(int vector1[], int vector2[])
{
    int base = 100000;
#pragma omp parallel for
    for (int i = 0; i < N; i++)
    {
        vector1[i] = base + i;
        vector2[i] = base + i;
    }
}

double sumar(int vector1[], int vector2[], int resultado[], int hilos)
{
    omp_set_num_threads(hilos);
    double tiempo_inicio = omp_get_wtime();

#pragma omp for
    for (int i = 0; i < N; i++)
    {
        resultado[i] = vector1[i] + vector2[i];
    }

    double tiempo_fin = omp_get_wtime();
    double tiempo_diferencia = tiempo_fin - tiempo_inicio;

    return tiempo_diferencia;
}

double promedio(double tiempos[])
{
    double promedio = 0.0;
    for (int i = 0; i < 100; i++)
    {
        promedio += tiempos[i];
    }
    promedio /= 100;

    return promedio;
}

int main()
{
    int hilos = 1;
    int vector1[N];
    int vector2[N];
    int resultado[N];

    double tiempos[200];
    int posicion = 0;

    inicializar(vector1, vector2);

    while (posicion < sizeof(tiempos))
    {
        double tiempo_diferencia = sumar(vector1, vector2, resultado, hilos);

        if (tiempo_diferencia > 0.0)
        {
            tiempos[posicion] = tiempo_diferencia;
            posicion++;
        }
    }

    printf("[Hilos: %d, Arreglo: %d] Tiempo Promedio: %.9f", hilos, N, promedio(tiempos));

    return 0;
}
