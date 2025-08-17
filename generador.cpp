#include "generador.h"
#include <cstdlib>   // rand(), srand()
#include <ctime>     // time()
#include <random>    // std::mt19937, std::uniform_real_distribution
#include <vector>
#include <algorithm> // std::find_if
#include <map>


// Bases de datos para generación realista

// Nombres femeninos comunes en Colombia
const std::vector<std::string> nombresFemeninos = {
    "María", "Luisa", "Carmen", "Ana", "Sofía", "Isabel", "Laura", "Andrea", "Paula", "Valentina",
    "Camila", "Daniela", "Carolina", "Fernanda", "Gabriela", "Patricia", "Claudia", "Diana", "Lucía", "Ximena"
};

// Nombres masculinos comunes en Colombia
const std::vector<std::string> nombresMasculinos = {
    "Juan", "Carlos", "José", "James", "Andrés", "Miguel", "Luis", "Pedro", "Alejandro", "Ricardo",
    "Felipe", "David", "Jorge", "Santiago", "Daniel", "Fernando", "Diego", "Rafael", "Martín", "Óscar",
    "Edison", "Nestor", "Gertridis"
};

// Apellidos comunes en Colombia
const std::vector<std::string> apellidos = {
    "Gómez", "Rodríguez", "Martínez", "López", "García", "Pérez", "González", "Sánchez", "Ramírez", "Torres",
    "Díaz", "Vargas", "Castro", "Ruiz", "Álvarez", "Romero", "Suárez", "Rojas", "Moreno", "Muñoz", "Valencia",
};

// Principales ciudades colombianas
const std::vector<std::string> ciudadesColombia = {
    "Bogotá", "Medellín", "Cali", "Barranquilla", "Cartagena", "Bucaramanga", "Pereira", "Santa Marta", "Cúcuta", "Ibagué",
    "Manizales", "Pasto", "Neiva", "Villavicencio", "Armenia", "Sincelejo", "Valledupar", "Montería", "Popayán", "Tunja"
};

/**
 * Implementación de generarFechaNacimiento.
 * 
 * POR QUÉ: Simular fechas de nacimiento realistas.
 * CÓMO: Día (1-28), mes (1-12), año (1960-2009).
 * PARA QUÉ: Atributo fechaNacimiento de Persona.
 */
std::string generarFechaNacimiento() {
    int dia = 1 + rand() % 28;       // Día: 1 a 28 (evita problemas con meses)
    int mes = 1 + rand() % 12;        // Mes: 1 a 12
    int anio = 1960 + rand() % 50;    // Año: 1960 a 2009
    return std::to_string(dia) + "/" + std::to_string(mes) + "/" + std::to_string(anio);
}

/**
 * Implementación de generarID.
 * 
 * POR QUÉ: Generar identificadores únicos y secuenciales.
 * CÓMO: Contador estático que inicia en 1000000000 y se incrementa.
 * PARA QUÉ: Simular números de cédula.
 */
std::string generarID() {
    static long contador = 1000000000; // Inicia en 1,000,000,000
    return std::to_string(contador++); // Convierte a string e incrementa
}

/**
 * Implementación de randomDouble.
 * 
 * POR QUÉ: Generar números decimales aleatorios en un rango.
 * CÓMO: Mersenne Twister (mejor que rand()) y distribución uniforme.
 * PARA QUÉ: Valores de ingresos, patrimonio, etc.
 */
double randomDouble(double min, double max) {
    static std::mt19937 generator(time(nullptr)); // Semilla basada en tiempo
    std::uniform_real_distribution<double> distribution(min, max);
    return distribution(generator);
}

/**
 * Implementación de generarPersona.
 * 
 * POR QUÉ: Crear una persona con datos aleatorios.
 * CÓMO: Seleccionando aleatoriamente de las bases de datos y generando números.
 * PARA QUÉ: Generar datos de prueba.
 */
Persona generarPersona() {
    // Decide si es hombre o mujer
    bool esHombre = rand() % 2;
    
    // Selecciona nombre según género
    std::string nombre = esHombre ? 
        nombresMasculinos[rand() % nombresMasculinos.size()] :
        nombresFemeninos[rand() % nombresFemeninos.size()];
    
    // Construye apellido compuesto (dos apellidos aleatorios)
    std::string apellido = apellidos[rand() % apellidos.size()];
    apellido += " ";
    apellido += apellidos[rand() % apellidos.size()];
    
    // Genera los demás atributos
    std::string id = generarID();
    std::string ciudad = ciudadesColombia[rand() % ciudadesColombia.size()];
    std::string fecha = generarFechaNacimiento();
    
    // Genera datos financieros realistas
    double ingresos = randomDouble(10000000, 500000000);   // 10M a 500M COP
    double patrimonio = randomDouble(0, 2000000000);       // 0 a 2,000M COP
    double deudas = randomDouble(0, patrimonio * 0.7);     // Deudas hasta el 70% del patrimonio
    bool declarante = (ingresos > 50000000) && (rand() % 100 > 30); // Probabilidad 70% si ingresos > 50M
    char calendarioDeclaracion; // Determinado por los últimos dos dígitos del ID
    if(std::stoi(id.substr(id.length()-2, 2)) < 40) {
        calendarioDeclaracion = 'A';
    } else if(std::stoi(id.substr(id.length()-2, 2)) < 80) {
        calendarioDeclaracion = 'B';
    } else {
        calendarioDeclaracion = 'C';
    }
    
    return Persona(nombre, apellido, id, ciudad, fecha, ingresos, patrimonio, deudas, declarante, calendarioDeclaracion);
}

/**
 * Implementación de generarColeccion.
 * 
 * POR QUÉ: Generar un conjunto de n personas.
 * CÓMO: Reservando espacio y agregando n personas generadas.
 * PARA QUÉ: Crear datasets para pruebas.
 */
std::vector<Persona> generarColeccion(int n) {
    std::vector<Persona> personas;
    personas.reserve(n); // Reserva espacio para n personas (eficiencia)
    
    for (int i = 0; i < n; ++i) {
        personas.push_back(generarPersona());
    }
    
    return personas;
}

/**
 * Implementación de buscarPorID.
 * 
 * POR QUÉ: Encontrar una persona por su ID en una colección.
 * CÓMO: Usando un algoritmo de búsqueda secuencial (lineal).
 * PARA QUÉ: Para operaciones de búsqueda en la aplicación.
 */
const Persona* buscarPorID(const std::vector<Persona>& personas, const std::string& id) {
    // Usa find_if con una lambda para buscar por ID
    auto it = std::find_if(personas.begin(), personas.end(),
        [&id](const Persona& p) { return p.getId() == id; });
    
    if (it != personas.end()) {
        return &(*it); // Devuelve puntero a la persona encontrada
    } else {
        return nullptr; // No encontrado
    }
}

//  Búsqueda de persona más longeva ciudad
const Persona* buscarLongevaCiudad(const std::vector<Persona>& personas, const std::string& ciudad){
    const Persona* longeva = nullptr;
    int mayorEdad = -1;

    for (const Persona& p: personas){
        if (p.getCiudadNacimiento() == ciudad){
            std::string fecha = p.getFechaNacimiento();
            int anio = std::stoi(fecha.substr(fecha.rfind('/') + 1));
            int edad = 2025 - anio;

            if (edad > mayorEdad){
                mayorEdad = edad;
                longeva = &p;
            }
        }
    }
    
    return longeva;    
}

// Búsqueda de persona más longeva por todo el país
const Persona* buscarLongevaPais(const std::vector<Persona>& personas){
    const Persona* longeva = nullptr;
    int mayorEdad = -1;

    for (const Persona& p: personas){
        std::string fecha = p.getFechaNacimiento();
        int anio = std::stoi(fecha.substr(fecha.rfind('/') + 1));
        int edad = 2025 - anio;

        if (edad > mayorEdad) {
            mayorEdad = edad;
            longeva = &p;
        }
    }

    return longeva;    
}

//Persona con mayor patrimonio
const Persona* mayorpatrimonioPais(const std::vector<Persona>& personas){
    const Persona* patrimonio = nullptr;
    int mayorPatrimonio = -1;

    for (const Persona& p: personas) {
        double npatrimonio = p.getPatrimonio();
        
        if (npatrimonio > mayorPatrimonio){
            mayorPatrimonio = npatrimonio;
            patrimonio = &p;
        }
    }

    return patrimonio;
}

// Persona con mayor patrimonio por ciudad
const Persona* mayorpatrimonioCiudad(const std::vector<Persona>& personas, const std::string ciudad){
    const Persona* patrimonio = nullptr;
    int mayorPatrimonio = -1;

    for (const Persona& p: personas) {
        if ( ciudad == p.getCiudadNacimiento()){
            double npatrimonio = p.getPatrimonio();
            if (npatrimonio > mayorPatrimonio){
                mayorPatrimonio = npatrimonio;
                patrimonio = &p;
            }

        }
    }

    return patrimonio;
}


// Persona con mayor patrimonio por grupo declaración de renta
const Persona* mayorpatrimonioRenta(const std::vector<Persona>& personas, const char calendarioRenta){
    const Persona* patrimonio = nullptr;
    int mayorPatrimonio = -1;

    for (const Persona& p: personas) {
        if ( calendarioRenta == p.getCalendarioDeclaracion()){
            double npatrimonio = p.getPatrimonio();
            if (npatrimonio > mayorPatrimonio){
                mayorPatrimonio = npatrimonio;
                patrimonio = &p;
            }

        }
    }

    return patrimonio;
}


// Contar y listar personas según calendario
std::map<char, std::vector<const Persona*>> listarPersonasPorCalendario(const std::vector<Persona>& personas) {
    std::map<char, std::vector<const Persona*>> calendarioMap;

    for (const auto& p : personas) {
        char calendario = p.getCalendarioDeclaracion(); 
        calendarioMap[calendario].push_back(&p);
    }

    return calendarioMap;
}

// Ciudad con mayor número de declarantes en un calendario específico
std::string ciudadMayorDeclarantesCalendario(const std::vector<Persona>& personas, const char calendarioRenta) {
    std::map<std::string, int> contadorCiudades;

    for (const Persona& p : personas) {
        if (p.getCalendarioDeclaracion() == calendarioRenta && p.getDeclaranteRenta()) {
            contadorCiudades[p.getCiudadNacimiento()]++; // Cada que se aparezca una clave de ciudad (ej. bogotá) suma 1 (un declarante más), sino, crea la clave de ciudad
        }
    }

    std::string ciudadMayor;
    int maxDeclarantes = -1;
    for (const auto& par : contadorCiudades) {
        if (par.second > maxDeclarantes) {
            maxDeclarantes = par.second;
            ciudadMayor = par.first;
        }
    }

    return ciudadMayor;
}


// Promedio de ingresos por calendario de declaración
double promedioIngresosCalendario(const std::vector<Persona>& personas, const char calendarioRenta) {
    double sumaIngresos = 0.0;
    int contador = 0;

    for (const Persona& p : personas) {
        if (p.getCalendarioDeclaracion() == calendarioRenta && p.getDeclaranteRenta()) {
            sumaIngresos += p.getIngresosAnuales();
            contador++;
        }
    }

    return (contador > 0) ? (sumaIngresos / contador) : 0.0;
}


// Edad promedio de las personas por ciudad de nacimiento
double promedioEdadesCiudad(const std::vector<Persona>& personas, const std::string ciudad){
    double contadorEdades = 0.0;
    int contador = 0;

    for (const Persona& p : personas) {
        if (p.getCiudadNacimiento() == ciudad) {
            std::string fecha = p.getFechaNacimiento();
            int anio = std::stoi(fecha.substr(fecha.rfind('/') + 1));
            int edad = 2025 - anio;

            contadorEdades += edad;
            contador++;
        }
    }

    return (contador > 0) ? (contadorEdades / contador) : 0.0;
}
