#ifndef GENERADOR_H
#define GENERADOR_H

#include "persona.h"

// --- Generación básica ---
void generarFechaNacimiento(char *buffer);   // escribe fecha dd/mm/yyyy
void generarID(char *buffer);                
double randomDouble(double min, double max);

// --- Generación de personas ---
Persona generarPersona();
void generarColeccion(Persona *personas, int n);

// --- Búsqueda ---
Persona buscarPorID(Persona *personas, int n, const char *id);
Persona buscarLongevaCiudad(Persona *personas, int n, const char *ciudad);
Persona buscarLongevaPais(Persona *personas, int n);

// --- Consultas de patrimonio ---
Persona mayorpatrimonioPais(Persona *personas, int n);
Persona mayorpatrimonioCiudad(Persona *personas, int n, const char *ciudad);
Persona mayorpatrimonioRenta(Persona *personas, int n, char calendarioRenta);

// --- Estadísticas ---
void listarPersonasPorCalendario(Persona *personas, int n,
                                 Persona *grupoA, int *nA,
                                 Persona *grupoB, int *nB,
                                 Persona *grupoC, int *nC);

char* ciudadMayorDeclarantesCalendario(Persona *personas, int n, char calendarioRenta);
double promedioIngresosCalendario(Persona *personas, int n, char calendarioRenta);
double promedioEdadesCiudad(Persona *personas, int n, const char *ciudad);

#endif
