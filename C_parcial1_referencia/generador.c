#include "generador.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// --- Bases de datos en C ---
const char *nombresFemeninos[] = {
    "María","Luisa","Carmen","Ana","Sofía","Isabel","Laura","Andrea","Paula","Valentina",
    "Camila","Daniela","Carolina","Fernanda","Gabriela","Patricia","Claudia","Diana","Lucía","Ximena"
};
const int nNombresF = 20;

const char *nombresMasculinos[] = {
    "Juan","Carlos","José","James","Andrés","Miguel","Luis","Pedro","Alejandro","Ricardo",
    "Felipe","David","Jorge","Santiago","Daniel","Fernando","Diego","Rafael","Martín","Óscar",
    "Edison","Nestor","Gertridis"
};
const int nNombresM = 23;

const char *apellidos[] = {
    "Gómez","Rodríguez","Martínez","López","García","Pérez","González","Sánchez","Ramírez","Torres",
    "Díaz","Vargas","Castro","Ruiz","Álvarez","Romero","Suárez","Rojas","Moreno","Muñoz","Valencia"
};
const int nApellidos = 20;

const char *ciudadesColombia[] = {
    "Bogotá","Medellín","Cali","Barranquilla","Cartagena","Bucaramanga","Pereira","Santa Marta","Cúcuta","Ibagué",
    "Manizales","Pasto","Neiva","Villavicencio","Armenia","Sincelejo","Valledupar","Montería","Popayán","Tunja"
};
const int nCiudades = 20;

// --- Generación básica ---
void generarFechaNacimiento(char *buffer) {
    int dia = 1 + rand() % 28;
    int mes = 1 + rand() % 12;
    int anio = 1960 + rand() % 50;
    sprintf(buffer, "%d/%d/%d", dia, mes, anio);
}

void generarID(char *buffer) {
    static long contador = 1000000000;
    sprintf(buffer, "%ld", contador++);
}

double randomDouble(double min, double max) {
    return min + (rand() / (double)RAND_MAX) * (max - min);
}

// --- Generación de personas ---
void generarPersona(Persona *p) {
    int esHombre = rand() % 2;

    if (esHombre) {
        strcpy(p->nombre, nombresMasculinos[rand() % nNombresM]);
    } else {
        strcpy(p->nombre, nombresFemeninos[rand() % nNombresF]);
    }

    sprintf(p->apellido, "%s %s", apellidos[rand() % nApellidos], apellidos[rand() % nApellidos]);
    generarID(p->id);
    strcpy(p->ciudadNacimiento, ciudadesColombia[rand() % nCiudades]);
    generarFechaNacimiento(p->fechaNacimiento);

    p->ingresosAnuales = randomDouble(10000000, 500000000);
    p->patrimonio = randomDouble(0, 2000000000);
    p->deudas = randomDouble(0, p->patrimonio * 0.7);
    p->declaranteRenta = (p->ingresosAnuales > 50000000) && (rand() % 100 > 30);

    int ultimos2 = atoi(p->id + strlen(p->id) - 2);
    if (ultimos2 < 40) p->calendarioDeclaracion = 'A';
    else if (ultimos2 < 80) p->calendarioDeclaracion = 'B';
    else p->calendarioDeclaracion = 'C';
}

void generarColeccion(Persona *personas, int n) {
    for (int i = 0; i < n; i++) {
        generarPersona(&personas[i]);
    }
}

// --- Búsqueda ---
Persona* buscarPorID(Persona *personas, int n, const char *id) {
    for (int i = 0; i < n; i++) {
        if (strcmp(personas[i].id, id) == 0) {
            return &personas[i];
        }
    }
    return NULL;
}

Persona* buscarLongevaCiudad(Persona *personas, int n, const char *ciudad) {
    Persona *longeva = NULL;
    int mayorEdad = -1;

    for (int i = 0; i < n; i++) {
        if (strcmp(personas[i].ciudadNacimiento, ciudad) == 0) {
            int anio;
            sscanf(personas[i].fechaNacimiento, "%*d/%*d/%d", &anio);
            int edad = 2025 - anio;
            if (edad > mayorEdad) {
                mayorEdad = edad;
                longeva = &personas[i];
            }
        }
    }
    return longeva;
}

Persona* buscarLongevaPais(Persona *personas, int n) {
    Persona *longeva = NULL;
    int mayorEdad = -1;

    for (int i = 0; i < n; i++) {
        int anio;
        sscanf(personas[i].fechaNacimiento, "%*d/%*d/%d", &anio);
        int edad = 2025 - anio;
        if (edad > mayorEdad) {
            mayorEdad = edad;
            longeva = &personas[i];
        }
    }
    return longeva;
}

// --- Consultas de patrimonio ---
Persona* mayorpatrimonioPais(Persona *personas, int n) {
    Persona *mejor = NULL;
    double maxP = -1;
    for (int i = 0; i < n; i++) {
        if (personas[i].patrimonio > maxP) {
            maxP = personas[i].patrimonio;
            mejor = &personas[i];
        }
    }
    return mejor;
}

Persona* mayorpatrimonioCiudad(Persona *personas, int n, const char *ciudad) {
    Persona *mejor = NULL;
    double maxP = -1;
    for (int i = 0; i < n; i++) {
        if (strcmp(personas[i].ciudadNacimiento, ciudad) == 0 &&
            personas[i].patrimonio > maxP) {
            maxP = personas[i].patrimonio;
            mejor = &personas[i];
        }
    }
    return mejor;
}

Persona* mayorpatrimonioRenta(Persona *personas, int n, char calendarioRenta) {
    Persona *mejor = NULL;
    double maxP = -1;
    for (int i = 0; i < n; i++) {
        if (personas[i].calendarioDeclaracion == calendarioRenta &&
            personas[i].patrimonio > maxP) {
            maxP = personas[i].patrimonio;
            mejor = &personas[i];
        }
    }
    return mejor;
}

// --- Estadísticas ---
void listarPersonasPorCalendario(Persona *personas, int n,
                                 Persona **grupoA, int *nA,
                                 Persona **grupoB, int *nB,
                                 Persona **grupoC, int *nC) {
    *nA = *nB = *nC = 0;
    for (int i = 0; i < n; i++) {
        if (personas[i].calendarioDeclaracion == 'A') {
            grupoA[(*nA)++] = &personas[i];
        } else if (personas[i].calendarioDeclaracion == 'B') {
            grupoB[(*nB)++] = &personas[i];
        } else {
            grupoC[(*nC)++] = &personas[i];
        }
    }
}

char* ciudadMayorDeclarantesCalendario(Persona *personas, int n, char calendarioRenta) {
    static char ciudadMayor[50] = "";
    int maxDecl = -1;

    for (int i = 0; i < nCiudades; i++) {
        int contador = 0;
        for (int j = 0; j < n; j++) {
            if (personas[j].calendarioDeclaracion == calendarioRenta &&
                personas[j].declaranteRenta &&
                strcmp(personas[j].ciudadNacimiento, ciudadesColombia[i]) == 0) {
                contador++;
            }
        }
        if (contador > maxDecl) {
            maxDecl = contador;
            strcpy(ciudadMayor, ciudadesColombia[i]);
        }
    }
    return ciudadMayor;
}

double promedioIngresosCalendario(Persona *personas, int n, char calendarioRenta) {
    double suma = 0;
    int cont = 0;
    for (int i = 0; i < n; i++) {
        if (personas[i].calendarioDeclaracion == calendarioRenta && personas[i].declaranteRenta) {
            suma += personas[i].ingresosAnuales;
            cont++;
        }
    }
    return (cont > 0) ? (suma / cont) : 0.0;
}

double promedioEdadesCiudad(Persona *personas, int n, const char *ciudad) {
    double suma = 0;
    int cont = 0;
    for (int i = 0; i < n; i++) {
        if (strcmp(personas[i].ciudadNacimiento, ciudad) == 0) {
            int anio;
            sscanf(personas[i].fechaNacimiento, "%*d/%*d/%d", &anio);
            int edad = 2025 - anio;
            suma += edad;
            cont++;
        }
    }
    return (cont > 0) ? (suma / cont) : 0.0;
}