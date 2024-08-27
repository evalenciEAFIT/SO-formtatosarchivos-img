# Procesador de Imágenes JPEG: Un Proyecto Didáctico en C++

Este proyecto sirve como una herramienta educativa para ilustrar conceptos fundamentales de programación orientada a objetos, manipulación de archivos binarios y procesamiento básico de imágenes utilizando C++.

## Conceptos Clave

### 1. Representación Digital de Imágenes

En el ámbito de la informática, las imágenes se representan como matrices bidimensionales de valores numéricos. Cada elemento de esta matriz se denomina píxel (abreviatura de "picture element").

#### 1.1 Imágenes en Escala de Grises

En una imagen monocromática o en escala de grises, cada píxel se codifica con un único valor que representa su intensidad lumínica. Convencionalmente, este valor oscila entre 0 (negro absoluto) y 255 (blanco puro). 

Ejemplo de una matriz 3x3 en escala de grises:

```cpp
unsigned char imagen[3][3] = {
    {120, 80, 200},
    {50, 90, 175},
    {230, 100, 70}
};
```

#### 1.2 Imágenes a Color (Modelo RGB)

Las imágenes policromáticas suelen emplear el modelo de color RGB (Rojo, Verde, Azul). En este paradigma, cada píxel se representa mediante una tupla de tres valores, correspondientes a la intensidad de cada componente cromático primario.

Ejemplo de una matriz 3x3 a color:

```cpp
struct Pixel {
    unsigned char r, g, b;
};

Pixel imagen[3][3] = {
    {{255, 0, 0},   {0, 255, 0},   {0, 0, 255}},
    {{255, 255, 0}, {255, 0, 255}, {0, 255, 255}},
    {{128, 128, 128}, {0, 0, 0},   {255, 255, 255}}
};
```

### 2. Operaciones Básicas de Procesamiento de Imágenes

#### 2.1 Inversión de Colores

La inversión cromática es una operación elemental que consiste en sustraer cada valor de píxel de 255. Matemáticamente:

```
pixel_invertido = 255 - pixel_original
```

Esta operación produce el negativo de la imagen original.

#### 2.2 Reducción de Resolución

La reducción de resolución, o downsampling, es una técnica que disminuye las dimensiones de una imagen. En nuestro implementación, utilizamos un método de promediado de píxeles:

1. Se define un factor de reducción `n`.
2. Se crea una nueva matriz con dimensiones reducidas por el factor `n`.
3. Cada píxel en la nueva imagen es el promedio de un bloque de `n x n` píxeles de la imagen original.

## Estructura del Proyecto

El proyecto está organizado en varias clases que demuestran principios de diseño orientado a objetos:

1. `FormatoJPEG`: Encapsula la lógica de lectura y escritura de archivos JPEG.
2. `AlgoritmosIMG`: Contiene métodos estáticos para procesar imágenes (inversión y reducción).
3. `Pixel`: Estructura que representa un píxel RGB.

## Uso del Programa

Compilación:
```bash
make
```

Ejecución:
```bash
./procesador_jpeg <archivo_entrada.jpg> [factor_reduccion]
```

El programa generará:
1. Una copia de la imagen original.
2. Una versión con colores invertidos.
3. (Opcional) Una versión reducida si se especifica el factor de reducción.

## Objetivos Pedagógicos

1. Demostrar la implementación práctica de clases y métodos en C++.
2. Ilustrar el manejo de archivos binarios y la estructura interna de imágenes JPEG.
3. Introducir conceptos básicos de procesamiento digital de imágenes.
4. Fomentar la comprensión de algoritmos de manipulación matricial.

## Requisitos del Sistema

- Compilador C++ con soporte para C++11
- Biblioteca libjpeg

## Instalación de Dependencias

### Sistemas basados en Debian/Ubuntu:
```bash
sudo apt-get install libjpeg-dev
```

### Sistemas basados en Red Hat/Fedora:
```bash
sudo dnf install libjpeg-devel
```

### macOS (utilizando Homebrew):
```bash
brew install libjpeg
```

Este proyecto proporciona una base sólida para explorar conceptos más avanzados de procesamiento de imágenes y puede ser extendido con algoritmos adicionales como detección de bordes, aplicación de filtros, o transformaciones geométricas.
