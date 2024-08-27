#ifndef ALGORITMOS_IMG_H
#define ALGORITMOS_IMG_H

#include <vector>
#include "FormatoJPEG.h"  // Para usar la estructura Pixel

class AlgoritmosIMG {
public:
    // Invierte los colores de cada píxel en la matriz de píxeles
    static void invertirPixeles(std::vector<std::vector<Pixel>>& matrizPixeles);
};

#endif // ALGORITMOS_IMG_H