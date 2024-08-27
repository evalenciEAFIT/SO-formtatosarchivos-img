# Compilador
CC = g++

# Banderas de compilación
CFLAGS = -std=c++11 -Wall -Wextra

# Banderas para libjpeg
JPEG_LIBS = -ljpeg

# Nombre del ejecutable
EJECUTABLE = procesador_jpeg

# Archivos fuente
FUENTES = main.cpp FormatoJPEG.cpp AlgoritmosIMG.cpp

# Objetos generados a partir de los archivos fuente
OBJETOS = $(FUENTES:.cpp=.o)

# Regla por defecto
all: $(EJECUTABLE)

# Regla para construir el ejecutable
$(EJECUTABLE): $(OBJETOS)
	$(CC) $(CFLAGS) -o $@ $^ $(JPEG_LIBS)

# Regla para compilar archivos fuente a objetos
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Regla para limpiar archivos generados
limpiar:
	rm -f $(OBJETOS) $(EJECUTABLE) original_*.jpg invertido_*.jpg reducido_*.jpg

# Regla para ejecutar el programa
ejecutar: $(EJECUTABLE)
	./$(EJECUTABLE) imagen.jpg $(FACTOR)

# Regla para compilar y ejecutar el programa
run: $(EJECUTABLE)
	@echo "Compilando y ejecutando el programa..."
	@./$(EJECUTABLE) imagen.jpg $(FACTOR)

# Reglas ficticias
.PHONY: all limpiar ejecutar run