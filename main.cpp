#include <iostream>
#include <string>
#include "FormatoJPEG.h"
#include "AlgoritmosIMG.h"
#include <cstdlib>

int main(int argc, char* argv[]) {
    if (argc != 2 && argc != 3) {
        std::cerr << "Uso: " << argv[0] << " <archivo_jpeg> [factor_reduccion]" << std::endl;
        return 1;
    }

    std::string nombreArchivo = argv[1];
    int factorReduccion = (argc == 3) ? std::stoi(argv[2]) : 1;

    FormatoJPEG formatoJpeg(nombreArchivo);

    if (!formatoJpeg.abrirArchivo()) {
        std::cerr << "No se pudo abrir el archivo JPEG." << std::endl;
        return 1;
    }

    auto matrizPixeles = formatoJpeg.obtenerMatrizPixeles();

    // Genera y muestra la imagen original
    std::string archivoOriginal = "original_" + nombreArchivo;
    if (formatoJpeg.guardarArchivo(archivoOriginal)) {
        std::cout << "Imagen original guardada como: " << archivoOriginal << std::endl;
        system(("xdg-open " + archivoOriginal + " &").c_str()); // Para sistemas Linux
        // En Windows, usaríamos: system(("start " + archivoInvertido).c_str());
        // En macOS, usaríamos: system(("open " + archivoInvertido).c_str());
    } else {
        std::cerr << "Error al guardar la imagen original." << std::endl;
    }

    // Invierte los píxeles de la imagen
    AlgoritmosIMG::invertirPixeles(matrizPixeles);

    // Guarda y muestra la imagen invertida
    std::string archivoInvertido = "invertido_" + nombreArchivo;
    if (formatoJpeg.modificarMatrizPixeles(matrizPixeles) && formatoJpeg.guardarArchivo(archivoInvertido)) {
        std::cout << "Imagen invertida guardada como: " << archivoInvertido << std::endl;
        system(("xdg-open " + archivoInvertido + " &").c_str());  // Para sistemas Linux
        // En Windows, usaríamos: system(("start " + archivoInvertido).c_str());
        // En macOS, usaríamos: system(("open " + archivoInvertido).c_str());
    } else {
        std::cerr << "Error al guardar la imagen invertida." << std::endl;
    }

    // Reduce el tamaño de la imagen
    if (factorReduccion > 1) {
        auto matrizReducida = AlgoritmosIMG::reducirTamaño(matrizPixeles, factorReduccion);
        std::string archivoReducido = "reducido_" + nombreArchivo;
        if (formatoJpeg.modificarMatrizPixeles(matrizReducida) && formatoJpeg.guardarArchivo(archivoReducido)) {
            std::cout << "Imagen reducida guardada como: " << archivoReducido << std::endl;
            system(("xdg-open " + archivoReducido + " &").c_str());  // Para sistemas Linux
            // En Windows, usaríamos: system(("start " + archivoInvertido).c_str());
            // En macOS, usaríamos: system(("open " + archivoInvertido).c_str());
        } else {
            std::cerr << "Error al guardar la imagen reducida." << std::endl;
        }
    }

    return 0;
}