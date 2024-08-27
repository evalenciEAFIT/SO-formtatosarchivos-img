#include "AlgoritmosIMG.h"

void AlgoritmosIMG::invertirPixeles(std::vector<std::vector<Pixel>>& matrizPixeles) {
    // Recorre cada fila de la matriz de píxeles
    for (auto& fila : matrizPixeles) {
        // Recorre cada píxel en la fila
        for (auto& pixel : fila) {
            // Invierte cada componente de color del píxel
            pixel.r = 255 - pixel.r;  // Rojo
            pixel.g = 255 - pixel.g;  // Verde
            pixel.b = 255 - pixel.b;  // Azul
        }
    }
}