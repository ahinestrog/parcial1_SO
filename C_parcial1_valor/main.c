#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "persona.h"
#include "generador.h"
#include "monitor.h"

// Menú principal
void mostrarMenu() {
    printf("\n\n=== MENÚ PRINCIPAL ===");
    printf("\n0. Crear nuevo conjunto de datos");
    printf("\n1. Mostrar resumen de todas las personas");
    printf("\n2. Mostrar detalle completo por índice");
    printf("\n3. Buscar persona por ID");
    printf("\n4. Buscar persona más longeva por ciudad");
    printf("\n5. Buscar persona más longeva del país");
    printf("\n6. Listar y contar personas por calendario");
    printf("\n7. Mayor patrimonio en el país");
    printf("\n8. Mayor patrimonio por ciudad");
    printf("\n9. Mayor patrimonio por grupo de declaración");
    printf("\n10. Ciudad con mayores declarantes por grupo de declaración");
    printf("\n11. Promedio de ingresos declarantes por calendario");
    printf("\n12. Edad promedio de las personas por ciudad de nacimiento");
    printf("\n13. Mostrar estadísticas de rendimiento");
    printf("\n14. Exportar estadísticas a CSV");
    printf("\n15. Salir");
    printf("\nSeleccione una opción: ");
}

int main() {
    srand(time(NULL));

    Persona *personas = NULL;  // arreglo dinámico
    int cantidad = 0;

    Monitor monitor;
    inicializar_monitor(&monitor);

    int opcion;
    do {
        mostrarMenu();
        if (scanf("%d", &opcion) != 1) {
            printf("Entrada inválida!\n");
            while(getchar()!='\n'); // limpiar buffer
            continue;
        }

        int indice;
        char idBusqueda[20];
        char ciudadBusqueda[50];
        char grupoCalendario;

        iniciar_tiempo(&monitor);
        long memoria_inicio = obtener_memoria();

        switch(opcion) {
            case 0: {
                printf("\nIngrese el número de personas a generar: ");
                scanf("%d", &cantidad);

                if (cantidad <= 0) {
                    printf("Error: Debe generar al menos 1 persona\n");
                    break;
                }

                if (personas) free(personas); // liberar anterior
                personas = malloc(sizeof(Persona) * cantidad);

                if (!personas) {
                    printf("Error de memoria\n");
                    break;
                }
                generarColeccion(personas, cantidad);

                double tiempo_gen = detener_tiempo(&monitor);
                long memoria_gen = obtener_memoria() - memoria_inicio;

                printf("Generadas %d personas en %.2f ms, Memoria: %ld KB\n",
                       cantidad, tiempo_gen, memoria_gen);
                registrar(&monitor, "Crear datos", tiempo_gen, memoria_gen);
                break;
            }

            case 1: {
                if (!personas || cantidad == 0) {
                    printf("\nNo hay datos disponibles. Use opción 0 primero.\n");
                    break;
                }
                printf("\n=== RESUMEN DE PERSONAS (%d) ===\n", cantidad);
                for (int i=0; i<cantidad; i++) {
                    printf("%d. ", i);
                    mostrarResumenPersona(personas[i]);
                    printf("\n");
                }
                double t = detener_tiempo(&monitor);
                long m = obtener_memoria() - memoria_inicio;
                registrar(&monitor, "Mostrar resumen", t, m);
                break;
            }

            case 2: {
                if (!personas || cantidad == 0) {
                    printf("\nNo hay datos disponibles.\n");
                    break;
                }
                printf("\nIngrese el índice (0-%d): ", cantidad-1);
                if (scanf("%d", &indice) == 1 && indice >= 0 && indice < cantidad) {
                    mostrarPersona(personas[indice]);
                } else {
                    printf("Índice fuera de rango!\n");
                }
                break;
            }

            case 3: {
                if (!personas || cantidad == 0) { printf("\nNo hay datos.\n"); break; }
                printf("\nIngrese el ID a buscar: ");
                scanf("%s", idBusqueda);
                Persona encontrada = buscarPorID(personas, cantidad, idBusqueda);
                if (strlen(encontrada.id) > 0) {
                    mostrarPersona(encontrada);
                } else {
                    printf("No se encontró persona con ID %s\n", idBusqueda);
                }
                break;
            }

            case 4: {
                if (!personas || cantidad == 0) break;
                printf("\nIngrese la ciudad: ");
                scanf("%s", ciudadBusqueda);
                Persona encontrada = buscarLongevaCiudad(personas, cantidad, ciudadBusqueda);
                if (strlen(encontrada.id) > 0) mostrarPersona(encontrada);
                else printf("No se encontró persona en %s\n", ciudadBusqueda);
                break;
            }

            case 5: {
                if (!personas || cantidad == 0) break;
                Persona encontrada = buscarLongevaPais(personas, cantidad);
                if (strlen(encontrada.id) > 0) mostrarPersona(encontrada);
                else printf("No se encontró persona más longeva\n");
                break;
            }

            case 6: { //listar y contar personas por calendario
                if (!personas || cantidad == 0) break;

                printf("Ingrese el calendario (A/B/C): ");
                scanf(" %c", &grupoCalendario);

                int contador = 0;
                for (int i = 0; i < cantidad; i++) {
                    if (personas[i].calendarioDeclaracion == grupoCalendario) {
                        mostrarResumenPersona(personas[i]);
                        contador++;
                    }
                }
                printf("Total de personas en el calendario %c: %d\n", grupoCalendario, contador);
                break;
            }

            case 7: {
                if (!personas || cantidad == 0) break;
                Persona encontrada = mayorpatrimonioPais(personas, cantidad);
                mostrarPersona(encontrada);
                break;
            }

            case 8: {
                if (!personas || cantidad == 0) break;
                printf("\nIngrese la ciudad: ");
                scanf("%s", ciudadBusqueda);
                Persona encontrada = mayorpatrimonioCiudad(personas, cantidad, ciudadBusqueda);
                mostrarPersona(encontrada);
                break;
            }

            case 9: {
                if (!personas || cantidad == 0) break;
                printf("\nIngrese el calendario (A/B/C): ");
                scanf(" %c", &grupoCalendario);
                Persona encontrada = mayorpatrimonioRenta(personas, cantidad, grupoCalendario);
                mostrarPersona(encontrada);
                break;
            }

            case 10: {
                if (!personas || cantidad == 0) break;
                printf("\nIngrese el calendario (A/B/C): ");
                scanf(" %c", &grupoCalendario);
                char *ciudad = ciudadMayorDeclarantesCalendario(personas, cantidad, grupoCalendario);
                if (ciudad) {
                    printf("Ciudad con más declarantes: %s\n", ciudad);
                } else {
                    printf("No hay declarantes en ese grupo\n");
                }
                break;
            }

            case 11: {
                if (!personas || cantidad == 0) break;
                printf("\nIngrese el calendario (A/B/C): ");
                scanf(" %c", &grupoCalendario);
                double promedio = promedioIngresosCalendario(personas, cantidad, grupoCalendario);
                printf("Promedio ingresos: %.2f\n", promedio);
                break;
            }

            case 12: {
                if (!personas || cantidad == 0) break;
                printf("\nIngrese la ciudad: ");
                scanf("%s", ciudadBusqueda);
                double prom = promedioEdadesCiudad(personas, cantidad, ciudadBusqueda);
                printf("Promedio de edades en %s: %.2f\n", ciudadBusqueda, prom);
                break;
            }

            case 13: mostrar_resumen(&monitor); break;
            case 14: exportar_csv(&monitor, "estadisticas.csv"); break;
            case 15: printf("Saliendo...\n"); break;
            default: printf("Opción inválida!\n");
        }

    } while(opcion != 15);

    if (personas) free(personas);
    return 0;
}