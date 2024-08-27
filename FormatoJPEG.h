#ifndef FORMATO_JPEG_H
#define FORMATO_JPEG_H

#include <string>     // Para manejar nombres de archivo
#include <vector>     // Para almacenar la matriz de píxeles

// Estructura para representar un píxel RGB
struct Pixel {
    unsigned char r, g, b;
};

class FormatoJPEG {
private:
    std::string nombreArchivo;
    std::vector<std::vector<Pixel>> matrizPixeles;
    int canales; // Número de canales de color (1 para escala de grises, 3 para RGB)

public:
    // Constructor: Inicializa el objeto con el nombre del archivo
    FormatoJPEG(const std::string& nombreArchivo);

    // Destructor
    ~FormatoJPEG();

    // Abre y lee el contenido del archivo JPEG
    bool abrirArchivo();

    // Guarda la imagen actual en un nuevo archivo JPEG
    bool guardarArchivo(const std::string& nuevoNombreArchivo);

    // Devuelve la matriz de píxeles actual
    std::vector<std::vector<Pixel>> obtenerMatrizPixeles() const;

    // Modifica la matriz de píxeles
    bool modificarMatrizPixeles(const std::vector<std::vector<Pixel>>& nuevaMatriz);

    // Devuelve el número de canales de color de la imagen
    int obtenerCanales() const { return canales; }
};

#endif // FORMATO_JPEG_H