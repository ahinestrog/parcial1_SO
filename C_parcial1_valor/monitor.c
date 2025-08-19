#define _POSIX_C_SOURCE 199309L
#include "monitor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // sysconf
#include <time.h>

// Inicializa el monitor
void inicializar_monitor(Monitor *m) {
    m->registros = malloc(sizeof(Registro) * 10);
    m->num_registros = 0;
    m->capacidad = 10;
    m->total_tiempo = 0.0;
    m->max_memoria = 0;
}

// Libera la memoria del monitor
void liberar_monitor(Monitor *m) {
    if (m->registros) {
        free(m->registros);
        m->registros = NULL;
    }
    m->num_registros = 0;
    m->capacidad = 0;
}

// Inicia el cronómetro
void iniciar_tiempo(Monitor *m) {
    clock_gettime(CLOCK_MONOTONIC, &m->inicio);
}

// Detiene el cronómetro y devuelve tiempo en ms
double detener_tiempo(Monitor *m) {
    struct timespec fin;
    clock_gettime(CLOCK_MONOTONIC, &fin);
    double sec = (fin.tv_sec - m->inicio.tv_sec) * 1000.0;
    double nsec = (fin.tv_nsec - m->inicio.tv_nsec) / 1000000.0;
    return sec + nsec;
}

// Obtiene memoria residente en KB
long obtener_memoria() {
    FILE* file = fopen("/proc/self/statm", "r");
    if (!file) {
        perror("Error al abrir /proc/self/statm");
        return 0;
    }

    long size, resident, shared, text, lib, data, dt;
    if (fscanf(file, "%ld %ld %ld %ld %ld %ld %ld",
               &size, &resident, &shared, &text, &lib, &data, &dt) != 7) {
        fclose(file);
        return 0;
    }
    fclose(file);

    long page_size_kb = sysconf(_SC_PAGESIZE) / 1024;
    return resident * page_size_kb;
}

// Registra una operación
void registrar(Monitor *m, const char *operacion, double tiempo, long memoria) {
    if (m->num_registros >= m->capacidad) {
        m->capacidad *= 2;
        m->registros = realloc(m->registros, sizeof(Registro) * m->capacidad);
    }
    Registro r;
    strncpy(r.operacion, operacion, sizeof(r.operacion) - 1);
    r.operacion[sizeof(r.operacion) - 1] = '\0';
    r.tiempo = tiempo;
    r.memoria = memoria;

    m->registros[m->num_registros++] = r;

    m->total_tiempo += tiempo;
    if (memoria > m->max_memoria) {
        m->max_memoria = memoria;
    }
}

// Muestra estadísticas de una operación
void mostrar_estadistica(double tiempo, long memoria) {
    printf("\n[ESTADÍSTICAS] - Tiempo: %.3f ms, Memoria: %ld KB\n",
            tiempo, memoria);
}

// Muestra resumen de todas las operaciones
void mostrar_resumen(Monitor *m) {
    printf("\n=== RESUMEN DE ESTADÍSTICAS ===");
    for (int i = 0; i < m->num_registros; i++) {
        printf("\n%s: %.3f ms, %ld KB",
               m->registros[i].operacion,
               m->registros[i].tiempo,
               m->registros[i].memoria);
    }
    printf("\nTotal tiempo: %.3f ms", m->total_tiempo);
    printf("\nMemoria máxima: %ld KB\n", m->max_memoria);
}

// Exporta estadísticas a CSV
void exportar_csv(Monitor *m, const char *nombre_archivo) {
    FILE *archivo = fopen(nombre_archivo, "w");
    if (!archivo) {
        perror("Error al abrir archivo CSV");
        return;
    }
    fprintf(archivo, "Operacion,Tiempo(ms),Memoria(KB)\n");
    for (int i = 0; i < m->num_registros; i++) {
        fprintf(archivo, "%s,%.3f,%ld\n",
                m->registros[i].operacion,
                m->registros[i].tiempo,
                m->registros[i].memoria);
    }
    fclose(archivo);
    printf("Estadísticas exportadas a %s\n", nombre_archivo);
}