#ifndef PERSONA_H
#define PERSONA_H

#include <stdbool.h>

typedef struct {
    char nombre[50];
    char apellido[50];
    char id[20];
    char ciudadNacimiento[50];
    char fechaNacimiento[20];
    double ingresosAnuales;
    double patrimonio;
    double deudas;
    bool declaranteRenta;
    char calendarioDeclaracion;
} Persona;

// Crear y mostrar persona
Persona* crearPersona(const char *nombre,
                      const char *apellido,
                      const char *id,
                      const char *ciudad,
                      const char *fecha,
                      double ingresos,
                      double patrimonio,
                      double deudas,
                      bool declarante,
                      char calendario);

void mostrarPersona(Persona *p);
void mostrarResumenPersona(Persona *p);

#endif
