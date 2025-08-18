#include <iostream>
#include <vector>
#include <limits>
#include <memory>
#include "persona.h"
#include "generador.h"
#include "monitor.h"

/**
 * Muestra el menú principal de la aplicación.
 * 
 * POR QUÉ: Guiar al usuario a través de las funcionalidades disponibles.
 * CÓMO: Imprimiendo las opciones en consola.
 * PARA QUÉ: Interacción amigable con el usuario.
 */
void mostrarMenu() {
    std::cout << "\n\n=== MENÚ PRINCIPAL ===";
    std::cout << "\n0. Crear nuevo conjunto de datos";
    std::cout << "\n1. Mostrar resumen de todas las personas";
    std::cout << "\n2. Mostrar detalle completo por índice";
    std::cout << "\n3. Buscar persona por ID";
    std::cout << "\n4. Buscar persona más longeva por ciudad";
    std::cout << "\n5. Buscar persona persona más longeva";
    std::cout << "\n6. Listar y contar personas por calendario";
    std::cout << "\n7. Mayor patrimonio en el país";
    std::cout << "\n8. Mayor patrimonio por ciudad";
    std::cout << "\n9. Mayor patrimonio por grupo de declaración";
    std::cout << "\n10. Ciudad con mayores declarantes";
    std::cout << "\n11. Promedio de ingresos declarantes por calendario";
    std::cout << "\n12. Edad promedio de las personas por ciudad de nacimiento";
    std::cout << "\n13. Mostrar estadísticas de rendimiento";
    std::cout << "\n14. Exportar estadísticas a CSV";
    std::cout << "\n15. Salir";
    std::cout << "\nSeleccione una opción: ";
}

/**
 * Punto de entrada principal del programa.
 * 
 * POR QUÉ: Iniciar la aplicación y manejar el flujo principal.
 * CÓMO: Mediante un bucle que muestra el menú y procesa la opción seleccionada.
 * PARA QUÉ: Ejecutar las funcionalidades del sistema.
 */
int main() {
    srand(time(nullptr)); // Semilla para generación aleatoria
    
    // Puntero inteligente para gestionar la colección de personas
    // POR QUÉ: Evitar fugas de memoria y garantizar liberación automática.
    std::unique_ptr<std::vector<Persona>> personas = nullptr;
    
    Monitor monitor; // Monitor para medir rendimiento
    
    int opcion;
    do {
        mostrarMenu();
        std::cin >> opcion;
        
        // Variables locales para uso en los casos
        size_t tam = 0;
        int indice;
        std::string idBusqueda;
        std::string ciudadBusqueda;
        char grupoCalendario;
        
        // Iniciar medición de tiempo y memoria para la operación actual
        monitor.iniciar_tiempo();
        long memoria_inicio = monitor.obtener_memoria();
        
        switch(opcion) {
            case 0: { // Crear nuevo conjunto de datos
                int n;
                std::cout << "\nIngrese el número de personas a generar: ";
                std::cin >> n;
                
                if (n <= 0) {
                    std::cout << "Error: Debe generar al menos 1 persona\n";
                    break;
                }
                
                // Generar el nuevo conjunto de personas
                auto nuevasPersonas = generarColeccion(n);
                tam = nuevasPersonas.size();
                
                // Mover el conjunto al puntero inteligente (propiedad única)
                personas = std::make_unique<std::vector<Persona>>(std::move(nuevasPersonas));
                
                // Medir tiempo y memoria usada
                double tiempo_gen = monitor.detener_tiempo();
                long memoria_gen = monitor.obtener_memoria() - memoria_inicio;
                
                std::cout << "Generadas " << tam << " personas en " 
                          << tiempo_gen << " ms, Memoria: " << memoria_gen << " KB\n";
                
                // Registrar la operación
                monitor.registrar("Crear datos", tiempo_gen, memoria_gen);
                break;
            }
                
            case 1: { // Mostrar resumen de todas las personas
                if (!personas || personas->empty()) {
                    std::cout << "\nNo hay datos disponibles. Use opción 0 primero.\n";
                    break;
                }
                
                tam = personas->size();
                std::cout << "\n=== RESUMEN DE PERSONAS (" << tam << ") ===\n";
                for(size_t i = 0; i < tam; ++i) {
                    std::cout << i << ". ";
                    (*personas)[i].mostrarResumen();
                    std::cout << "\n";
                }
                
                double tiempo_mostrar = monitor.detener_tiempo();
                long memoria_mostrar = monitor.obtener_memoria() - memoria_inicio;
                monitor.registrar("Mostrar resumen", tiempo_mostrar, memoria_mostrar);
                break;
            }
                
            case 2: { // Mostrar detalle por índice
                if (!personas || personas->empty()) {
                    std::cout << "\nNo hay datos disponibles. Use opción 0 primero.\n";
                    break;
                }
                
                tam = personas->size();
                std::cout << "\nIngrese el índice (0-" << tam-1 << "): ";
                if(std::cin >> indice) {
                    if(indice >= 0 && static_cast<size_t>(indice) < tam) {
                        (*personas)[indice].mostrar();
                    } else {
                        std::cout << "Índice fuera de rango!\n";
                    }
                } else {
                    std::cout << "Entrada inválida!\n";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
                
                double tiempo_detalle = monitor.detener_tiempo();
                long memoria_detalle = monitor.obtener_memoria() - memoria_inicio;
                monitor.registrar("Mostrar detalle", tiempo_detalle, memoria_detalle);
                break;
            }
                
            case 3: { // Buscar por ID
                if (!personas || personas->empty()) {
                    std::cout << "\nNo hay datos disponibles. Use opción 0 primero.\n";
                    break;
                }
                
                std::cout << "\nIngrese el ID a buscar: ";
                std::cin >> idBusqueda;
                
                if(const Persona* encontrada = buscarPorID(*personas, idBusqueda)) {
                    encontrada->mostrar();
                } else {
                    std::cout << "No se encontró persona con ID " << idBusqueda << "\n";
                }
                
                double tiempo_busqueda = monitor.detener_tiempo();
                long memoria_busqueda = monitor.obtener_memoria() - memoria_inicio;
                monitor.registrar("Buscar por ID", tiempo_busqueda, memoria_busqueda);
                break;
            }

            case 4: { // Buscar persona más longeva por ciudad
                if (!personas || personas->empty()) {
                    std::cout << "\nNo hay datos disponibles. Use opción 0 primero.\n";
                    break;
                }
                
                std::cout << "\nIngrese la ciudad a buscar persona más longeva: ";
                std::cin >> ciudadBusqueda;
                
                if(const Persona* encontrada = buscarLongevaCiudad(*personas, ciudadBusqueda)) {
                    encontrada->mostrar();
                } else {
                    std::cout << "No se encontró persona más longeva en " << ciudadBusqueda << "\n";
                }
                
                double tiempo_busqueda = monitor.detener_tiempo();
                long memoria_busqueda = monitor.obtener_memoria() - memoria_inicio;
                monitor.registrar("Buscar persona más longeva ciudad", tiempo_busqueda, memoria_busqueda);
                break;
            }

            case 5: { // Buscar persona más longeva
                if (!personas || personas->empty()) {
                    std::cout << "\nNo hay datos disponibles. Use opción 0 primero.\n";
                    break;
                }
                
                if(const Persona* encontrada = buscarLongevaPais(*personas)) {
                    encontrada->mostrar();
                } else {
                    std::cout << "No se encontró persona más longeva \n";
                }
                
                double tiempo_busqueda = monitor.detener_tiempo();
                long memoria_busqueda = monitor.obtener_memoria() - memoria_inicio;
                monitor.registrar("Buscar persona más longeva", tiempo_busqueda, memoria_busqueda);
                break;
            }

            case 6: { // Listar y contar por calendario renta
                if (!personas || personas->empty()) {
                    std::cout << "\nNo hay datos disponibles. Use opción 0 primero.\n";
                    break;
                }
                
                auto calendarioMap = listarPersonasPorCalendario(*personas);
                std::cout << "\n=== Listado y conteo por calendario de declaración ===\n";
                for (const auto& par : calendarioMap) {
                    std::cout << "Calendario " << par.first << ": " << par.second.size() << " personas\n";
                    for (const Persona* p : par.second) {
                        p->mostrarResumen();
                        std::cout << "\n";
                    }
                }

                double tiempo_busqueda = monitor.detener_tiempo();
                long memoria_busqueda = monitor.obtener_memoria() - memoria_inicio;
                monitor.registrar("Listar y contar calendario renta", tiempo_busqueda, memoria_busqueda);
                break;
            }
            
            case 7: { // Patrimonio por pais
                if (!personas || personas->empty()) {
                    std::cout << "\nNo hay datos disponibles. Use opción 0 primero.\n";
                    break;
                }
                
                if(const Persona* encontrada = mayorpatrimonioPais(*personas)) {
                    encontrada->mostrar();
                } else {
                    std::cout << "No se encontró persona con mayor patrimonio \n";
                }

                double tiempo_busqueda = monitor.detener_tiempo();
                long memoria_busqueda = monitor.obtener_memoria() - memoria_inicio;
                monitor.registrar("Buscar por ID", tiempo_busqueda, memoria_busqueda);
                break;
            }


            case 8: { // Patrimonio por ciudad
                if (!personas || personas->empty()) {
                    std::cout << "\nNo hay datos disponibles. Use opción 0 primero.\n";
                    break;
                }

                std::cout << "\nIngrese la ciudad a buscar persona con mayor patrimonio: ";
                std::cin >> ciudadBusqueda;
                
                if(const Persona* encontrada = mayorpatrimonioCiudad(*personas, ciudadBusqueda)) {
                    encontrada->mostrar();
                } else {
                    std::cout << "No se encontró persona mayor patrimonio en la ciudad:" << ciudadBusqueda << "\n";
                }

                double tiempo_busqueda = monitor.detener_tiempo();
                long memoria_busqueda = monitor.obtener_memoria() - memoria_inicio;
                monitor.registrar("Buscar persona con mayor patrimonio por ciudad", tiempo_busqueda, memoria_busqueda);
                break;
            }

            case 9: { // Patrimonio por calendario de declaración de renta
                if (!personas || personas->empty()) {
                    std::cout << "\nNo hay datos disponibles. Use opción 0 primero.\n";
                    break;
                }

                std::cout << "\nIngrese el grupo para buscar la persona con mayor patrimonio: ";
                std::cin >> grupoCalendario;
                
                if(const Persona* encontrada = mayorpatrimonioRenta(*personas, grupoCalendario)) {
                    encontrada->mostrar();
                } else {
                    std::cout << "No se encontró persona mayor patrimonio en la ciudad:" << ciudadBusqueda << "\n";
                }

                double tiempo_busqueda = monitor.detener_tiempo();
                long memoria_busqueda = monitor.obtener_memoria() - memoria_inicio;
                monitor.registrar("Buscar persona con mayor patrimonio por ciudad", tiempo_busqueda, memoria_busqueda);
                break;
            }

            case 10: { // Ciudad con mayor número de declarantes en un calendario específico
                if (!personas || personas->empty()) {
                    std::cout << "\nNo hay datos disponibles. Use opción 0 primero.\n";
                    break;
                }

                std::cout << "\nIngrese el grupo para buscar la ciudad con mayores declarantes: ";
                std::cin >> grupoCalendario;
                
                const std::string encontrada = ciudadMayorDeclarantesCalendario(*personas, grupoCalendario);
                if (!encontrada.empty()) {
                    std::cout << "Ciudad con más declarantes en el grupo " << grupoCalendario << ": " << encontrada << "\n";
                } else {
                    std::cout << "No se encontró ciudad con declarantes en el grupo: " << grupoCalendario << "\n";
                }

                double tiempo_busqueda = monitor.detener_tiempo();
                long memoria_busqueda = monitor.obtener_memoria() - memoria_inicio;
                monitor.registrar("Buscar ciudad con mayores declarantes", tiempo_busqueda, memoria_busqueda);
                break;
            }

            case 11: { // Promedio de ingresos declarantes por calendario
                if (!personas || personas->empty()) {
                    std::cout << "\nNo hay datos disponibles. Use opción 0 primero.\n";
                    break;
                }

                std::cout << "\nIngrese el grupo para buscar el promedio de ingresos de los declarantes: ";
                std::cin >> grupoCalendario;
                
                const double encontrada = promedioIngresosCalendario(*personas, grupoCalendario);
                if (encontrada) {
                    std::cout << "Promedio de ingresos de los declarantes en el grupo " << grupoCalendario << ": " << encontrada << "\n";
                } else {
                    std::cout << "No se encontró promedio de ingresos en el grupo: " << grupoCalendario << "\n";
                }

                double tiempo_busqueda = monitor.detener_tiempo();
                long memoria_busqueda = monitor.obtener_memoria() - memoria_inicio;
                monitor.registrar("Buscar promedio de ingresos por grupo", tiempo_busqueda, memoria_busqueda);
                break;
            }

            case 12: { // Edad promedio de las personas por ciudad de nacimiento
                if (!personas || personas->empty()) {
                    std::cout << "\nNo hay datos disponibles. Use opción 0 primero.\n";
                    break;
                }

                std::cout << "\nIngrese la ciudad para ver la edad promedio de las personas nacidas allí: ";
                std::cin >> ciudadBusqueda;
                
                const double encontrada = promedioEdadesCiudad(*personas, ciudadBusqueda);
                if (encontrada) {
                    std::cout << "Promedio de edades en la ciudad " << ciudadBusqueda << ": " << encontrada << "\n";
                } else {
                    std::cout << "No se encontró promedio de edades la ciudad: " << ciudadBusqueda << "\n";
                }

                double tiempo_busqueda = monitor.detener_tiempo();
                long memoria_busqueda = monitor.obtener_memoria() - memoria_inicio;
                monitor.registrar("Buscar ciudad con mayores declarantes", tiempo_busqueda, memoria_busqueda);
                break;
            }

            case 13: // Mostrar estadísticas de rendimiento
                monitor.mostrar_resumen();
                break;
                
            case 14: // Exportar estadísticas a CSV
                monitor.exportar_csv();
                break;
                
            case 15: // Salir
                std::cout << "Saliendo...\n";
                break;
                
            default:
                std::cout << "Opción inválida!\n";
        }
        
        // Mostrar estadísticas de la operación
        if (opcion >= 0 && opcion <= 12) {
            double tiempo = monitor.detener_tiempo();
            long memoria = monitor.obtener_memoria() - memoria_inicio;
            monitor.mostrar_estadistica("Opción " + std::to_string(opcion), tiempo, memoria);
        }
        
    } while(opcion != 15);
    
    return 0;
}