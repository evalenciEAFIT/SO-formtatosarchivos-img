#include "AlgoritmosIMG.h"
#include <cmath>  // Para la función round

void AlgoritmosIMG::invertirPixeles(std::vector<std::vector<Pixel>>& matrizPixeles) {
    for (auto& fila : matrizPixeles) {
        for (auto& pixel : fila) {
            pixel.r = 255 - pixel.r;
            pixel.g = 255 - pixel.g;
            pixel.b = 255 - pixel.b;
        }
    }
}

std::vector<std::vector<Pixel>> AlgoritmosIMG::reducirTamaño(const std::vector<std::vector<Pixel>>& matrizPixeles, int factor) {
    if (factor <= 1) {
        return matrizPixeles;  // No se reduce si el factor es 1 o menos
    }

    int alturaOriginal = matrizPixeles.size();
    int anchoOriginal = matrizPixeles[0].size();
    int nuevaAltura = std::max(1, alturaOriginal / factor);
    int nuevoAncho = std::max(1, anchoOriginal / factor);

    std::vector<std::vector<Pixel>> nuevaMatriz(nuevaAltura, std::vector<Pixel>(nuevoAncho));

    for (int y = 0; y < nuevaAltura; ++y) {
        for (int x = 0; x < nuevoAncho; ++x) {
            int r = 0, g = 0, b = 0;
            int pixelesPromediados = 0;

            // Promedia los píxeles en el área correspondiente de la imagen original
            for (int dy = 0; dy < factor && y * factor + dy < alturaOriginal; ++dy) {
                for (int dx = 0; dx < factor && x * factor + dx < anchoOriginal; ++dx) {
                    const Pixel& pixelOriginal = matrizPixeles[y * factor + dy][x * factor + dx];
                    r += pixelOriginal.r;
                    g += pixelOriginal.g;
                    b += pixelOriginal.b;
                    ++pixelesPromediados;
                }
            }

            // Calcula el promedio y asigna al nuevo píxel
            nuevaMatriz[y][x].r = static_cast<unsigned char>(std::round(static_cast<double>(r) / pixelesPromediados));
            nuevaMatriz[y][x].g = static_cast<unsigned char>(std::round(static_cast<double>(g) / pixelesPromediados));
            nuevaMatriz[y][x].b = static_cast<unsigned char>(std::round(static_cast<double>(b) / pixelesPromediados));
        }
    }

    return nuevaMatriz;
}