#ifndef PERSONA_H
#define PERSONA_H

#include <stdio.h>
#include <stdbool.h>

// Definición de la estructura Persona en C
typedef struct {
    char nombre[50];             // Nombre de pila
    char apellido[50];           // Apellidos
    char id[20];                 // Identificador único (cédula)
    char ciudadNacimiento[50];   // Ciudad de nacimiento
    char fechaNacimiento[20];    // Fecha de nacimiento (DD/MM/AAAA)
    double ingresosAnuales;      // Ingresos anuales
    double patrimonio;           // Patrimonio total
    double deudas;               // Deudas totales
    bool declaranteRenta;        // Si es declarante de renta
    char calendarioDeclaracion;  // Calendario de declaración (A, B o C)
} Persona;

// "Constructor" en C: inicializa una persona con todos los datos
Persona crearPersona(
    const char *nombre,
    const char *apellido,
    const char *id,
    const char *ciudad,
    const char *fecha,
    double ingresos,
    double patrimonio,
    double deudas,
    bool declarante,
    char calendario
);

// Mostrar toda la información de la persona
void mostrarPersona(Persona p);

// Mostrar resumen de la persona
void mostrarResumenPersona(Persona p);

#endif // PERSONA_H
