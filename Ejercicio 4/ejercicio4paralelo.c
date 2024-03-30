#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <omp.h>

#define N 5000 // Elementos Arreglo

void generar_csv(const char *filename)
{
    FILE *fp = fopen(filename, "w");
    if (fp == NULL)
    {
        printf("Error al abrir el archivo.\n");
        return;
    }

    srand(time(NULL)); // Semilla para la generación de números aleatorios

    for (int i = 0; i < N; i++)
    {
        double num = (double)rand() / RAND_MAX * 1000.0; // Generar número aleatorio entre 0 y 1000
        fprintf(fp, "%.9f\n", num);
    }

    fclose(fp);
}

void cargar_desde_csv(const char *filename, double vector[])
{
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Error al abrir el archivo.\n");
        return;
    }

    for (int i = 0; i < N; i++)
    {
        if (fscanf(fp, "%lf", &vector[i]) != 1)
        {
            printf("Error al leer el archivo.\n");
            break;
        }
    }

    fclose(fp);
}

double obtener_tiempo_actual()
{
    LARGE_INTEGER frecuencia;
    QueryPerformanceFrequency(&frecuencia);

    LARGE_INTEGER contador;
    QueryPerformanceCounter(&contador);

    return (double)contador.QuadPart / (double)frecuencia.QuadPart;
}

double sumar(double vector1[], double vector2[], double resultado[], int hilos)
{
    omp_set_num_threads(hilos);

    LARGE_INTEGER inicio, fin;
    QueryPerformanceCounter(&inicio);

#pragma omp parallel for
    for (int i = 0; i < N; i++)
    {
        resultado[i] = vector1[i] + vector2[i];
    }

    QueryPerformanceCounter(&fin);
    double tiempo_inicio = (double)inicio.QuadPart;
    double tiempo_fin = (double)fin.QuadPart;
    double tiempo_diferencia = (tiempo_fin - tiempo_inicio) / obtener_tiempo_actual();

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
    int hilos = 300;

    /* generar_csv("vector1.csv");
    generar_csv("vector2.csv"); */

    double vector1[N];
    double vector2[N];
    double resultado[N];

    cargar_desde_csv("vector1.csv", vector1);
    cargar_desde_csv("vector2.csv", vector2);

    double tiempos[4000];
    int posicion = 0;

    while (posicion < sizeof(tiempos) / sizeof(tiempos[0]))
    {
        double tiempo_diferencia = sumar(vector1, vector2, resultado, hilos);

        tiempos[posicion] = tiempo_diferencia;
        posicion++;
    }

    printf("[Hilos: %d, Arreglo: %d] Tiempo Promedio: %.9f\n", hilos, N, promedio(tiempos));

    printf("ultimo elemento de resultado: %.9f\n", resultado[N - 1]);
    printf("Ultimo tiempo de ejecucion: %.9f\n", tiempos[sizeof(tiempos) / sizeof(tiempos[0]) - 1]);

    return 0;
}
