#ifndef GENERADOR_JPEG_H
#define GENERADOR_JPEG_H

#include <string>
#include <vector>

class GeneradorJPEG {
public:
    // Genera un archivo JPEG a partir de una matriz de píxeles
    // Parámetros:
    //   nombreArchivo: nombre del archivo de salida
    //   matrizPixeles: matriz 2D de píxeles en escala de grises
    //   calidad: calidad de compresión JPEG (0-100)
    // Retorna: true si la operación fue exitosa, false en caso contrario
    static bool generarJPEG(const std::string& nombreArchivo, 
                            const std::vector<std::vector<unsigned char>>& matrizPixeles, 
                            int calidad = 90);
};

#endif // GENERADOR_JPEG_H