#ifndef MONITOR_H
#define MONITOR_H

#include <time.h>

// Estructura para almacenar métricas de una operación
typedef struct {
    char operacion[100];  // Nombre de la operación
    double tiempo;        // Tiempo en milisegundos
    long memoria;         // Memoria en KB
} Registro;

typedef struct {
    struct timespec inicio; // Tiempo de inicio
    Registro *registros;    // Historial dinámico
    int num_registros;      // Número de registros
    int capacidad;          // Capacidad actual del array
    double total_tiempo;    // Tiempo total acumulado
    long max_memoria;       // Máxima memoria usada
} Monitor;

// Funciones de inicialización y destrucción
void inicializar_monitor(Monitor *m);
void liberar_monitor(Monitor *m);

// Tiempo
void iniciar_tiempo(Monitor *m);
double detener_tiempo(Monitor *m);

// Memoria
long obtener_memoria();

// Registro de métricas
void registrar(Monitor *m, const char *operacion, double tiempo, long memoria);
void mostrar_estadistica(double tiempo, long memoria);
void mostrar_resumen(Monitor *m);
void exportar_csv(Monitor *m, const char *nombre_archivo);

#endif // MONITOR_H

