#ifndef ALGORITMOS_IMG_H
#define ALGORITMOS_IMG_H

#include <vector>
#include "FormatoJPEG.h"  // Para usar la estructura Pixel

class AlgoritmosIMG {
public:
    // Invierte los colores de cada píxel en la matriz de píxeles
    static void invertirPixeles(std::vector<std::vector<Pixel>>& matrizPixeles);

    // Reduce el tamaño de la imagen por un factor dado
    // Parámetros:
    // - matrizPixeles: matriz de píxeles original
    // - factor: factor de reducción (por ejemplo, 2 para reducir a la mitad)
    // Retorna: nueva matriz de píxeles con tamaño reducido
    static std::vector<std::vector<Pixel>> reducirTamaño(const std::vector<std::vector<Pixel>>& matrizPixeles, int factor);
};

#endif // ALGORITMOS_IMG_H