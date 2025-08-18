#include "persona.h"
#include <string.h>

// "Constructor" que inicializa todos los atributos
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
) {
    Persona p;
    strncpy(p.nombre, nombre, sizeof(p.nombre)-1);
    p.nombre[sizeof(p.nombre)-1] = '\0';

    strncpy(p.apellido, apellido, sizeof(p.apellido)-1);
    p.apellido[sizeof(p.apellido)-1] = '\0';

    strncpy(p.id, id, sizeof(p.id)-1);
    p.id[sizeof(p.id)-1] = '\0';

    strncpy(p.ciudadNacimiento, ciudad, sizeof(p.ciudadNacimiento)-1);
    p.ciudadNacimiento[sizeof(p.ciudadNacimiento)-1] = '\0';

    strncpy(p.fechaNacimiento, fecha, sizeof(p.fechaNacimiento)-1);
    p.fechaNacimiento[sizeof(p.fechaNacimiento)-1] = '\0';

    p.ingresosAnuales = ingresos;
    p.patrimonio = patrimonio;
    p.deudas = deudas;
    p.declaranteRenta = declarante;
    p.calendarioDeclaracion = calendario;

    return p; // devuelve por valor
}

// Mostrar todos los datos de la persona
void mostrarPersona(Persona p) {
    printf("-------------------------------------\n");
    printf("[%s] Nombre: %s %s\n", p.id, p.nombre, p.apellido);
    printf("   - Ciudad de nacimiento: %s\n", p.ciudadNacimiento);
    printf("   - Fecha de nacimiento: %s\n\n", p.fechaNacimiento);
    printf("   - Ingresos anuales: $%.2f\n", p.ingresosAnuales);
    printf("   - Patrimonio: $%.2f\n", p.patrimonio);
    printf("   - Deudas: $%.2f\n", p.deudas);
    printf("   - Declarante de renta: %s\n", p.declaranteRenta ? "Sí" : "No");
    printf("   - Calendario de declaración: %c\n", p.calendarioDeclaracion);
}

// Mostrar resumen compacto de la persona
void mostrarResumenPersona(Persona p) {
    printf("[%s] %s %s | %s | $%.2f\n",
           p.id, p.nombre, p.apellido, p.ciudadNacimiento, p.ingresosAnuales);
}
