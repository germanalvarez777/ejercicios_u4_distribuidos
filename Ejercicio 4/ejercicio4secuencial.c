#include <stdio.h>
#include <sys/time.h>

#define N 100 // Elementos Arreglo

void inicializar(int vector1[], int vector2[])
{
    int base = 100000;
    for (int i = 0; i < N; i++)
    {
        vector1[i] = base + i;
        vector2[i] = base + i;
    }
}

double sumar(int vector1[], int vector2[], int resultado[])
{
    struct timeval inicio, fin;
    gettimeofday(&inicio, NULL);

    for (int i = 0; i < N; i++)
    {
        resultado[i] = vector1[i] + vector2[i];
    }

    gettimeofday(&fin, NULL);
    double tiempo_inicio = inicio.tv_sec + inicio.tv_usec / 1000000.0;
    double tiempo_fin = fin.tv_sec + fin.tv_usec / 1000000.0;
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
    int vector1[N];
    int vector2[N];
    int resultado[N];

    double tiempos[200];
    int posicion = 0;

    inicializar(vector1, vector2);

    while (posicion < sizeof(tiempos))
    {
        double tiempo_diferencia = sumar(vector1, vector2, resultado);

        if (tiempo_diferencia > 0.0)
        {
            tiempos[posicion] = tiempo_diferencia;
            posicion++;
        }
    }

    printf("[Arreglo: %d] Tiempo Promedio: %.9f", N, promedio(tiempos));

    return 0;
}
