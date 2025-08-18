# Makefile para el sistema de generación y análisis de datos de personas (C)
# ------------------------------------------------------------
# Autor: Tu Nombre
# Versión: 1.0
# Fecha: $(date)
# ------------------------------------------------------------

# Configuración del compilador y flags
CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99 -O2

# Configuración de archivos fuente
SRC = main.c persona.c generador.c monitor.c
OBJ = $(SRC:.c=.o)
EXEC = programa

.PHONY: all clean run

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(EXEC)
	@echo "============================================="
	@echo "  Iniciando ejecución del programa..."
	@echo "============================================="
	@./$(EXEC)
	@echo "============================================="
	@echo "  Ejecución completada"
	@echo "============================================="

clean:
	rm -f $(OBJ) $(EXEC)
	@echo "Archivos de compilación eliminados"
