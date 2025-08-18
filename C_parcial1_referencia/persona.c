#include "persona.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Persona* crearPersona(const char *nombre,
                      const char *apellido,
                      const char *id,
                      const char *ciudad,
                      const char *fecha,
                      double ingresos,
                      double patrimonio,
                      double deudas,
                      bool declarante,
                      char calendario) {
    Persona *p = (Persona*) malloc(sizeof(Persona));
    if (!p) return NULL;

    strncpy(p->nombre, nombre, sizeof(p->nombre)-1);
    p->nombre[sizeof(p->nombre)-1] = '\0';

    strncpy(p->apellido, apellido, sizeof(p->apellido)-1);
    p->apellido[sizeof(p->apellido)-1] = '\0';

    strncpy(p->id, id, sizeof(p->id)-1);
    p->id[sizeof(p->id)-1] = '\0';

    strncpy(p->ciudadNacimiento, ciudad, sizeof(p->ciudadNacimiento)-1);
    p->ciudadNacimiento[sizeof(p->ciudadNacimiento)-1] = '\0';

    strncpy(p->fechaNacimiento, fecha, sizeof(p->fechaNacimiento)-1);
    p->fechaNacimiento[sizeof(p->fechaNacimiento)-1] = '\0';

    p->ingresosAnuales = ingresos;
    p->patrimonio = patrimonio;
    p->deudas = deudas;
    p->declaranteRenta = declarante;
    p->calendarioDeclaracion = calendario;

    return p; // Devuelve por referencia
}

void mostrarPersona(Persona *p) {
    if (!p) return;
    printf("-------------------------------------\n");
    printf("[%s] Nombre: %s %s\n", p->id, p->nombre, p->apellido);
    printf("   - Ciudad de nacimiento: %s\n", p->ciudadNacimiento);
    printf("   - Fecha de nacimiento: %s\n\n", p->fechaNacimiento);
    printf("   - Ingresos anuales: $%.2f\n", p->ingresosAnuales);
    printf("   - Patrimonio: $%.2f\n", p->patrimonio);
    printf("   - Deudas: $%.2f\n", p->deudas);
    printf("   - Declarante de renta: %s\n", p->declaranteRenta ? "Sí" : "No");
    printf("   - Calendario de declaración: %c\n", p->calendarioDeclaracion);
}

void mostrarResumenPersona(Persona *p) {
    if (!p) return;
    printf("[%s] %s %s | %s | $%.2f\n",
           p->id, p->nombre, p->apellido, p->ciudadNacimiento, p->ingresosAnuales);
}

