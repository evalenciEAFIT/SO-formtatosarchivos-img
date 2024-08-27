#include <iostream>   // Para entrada/salida estándar
#include <string>     // Para manejar cadenas de texto
#include "FormatoJPEG.h"
#include "AlgoritmosIMG.h"
#include <cstdlib>    // Para la función system()

int main(int argc, char* argv[]) {
    // Verifica si se proporcionó el nombre del archivo como argumento
    if (argc != 2) {
        std::cerr << "Uso: " << argv[0] << " <archivo_jpeg>" << std::endl;
        return 1;
    }

    std::string nombreArchivo = argv[1];
    FormatoJPEG formatoJpeg(nombreArchivo);

    // Intenta abrir y leer el archivo JPEG
    if (!formatoJpeg.abrirArchivo()) {
        std::cerr << "No se pudo abrir el archivo JPEG." << std::endl;
        return 1;
    }

    // Obtiene la matriz de píxeles de la imagen
    auto matrizPixeles = formatoJpeg.obtenerMatrizPixeles();

    // Genera y muestra la imagen original
    std::string archivoOriginal = "original_" + nombreArchivo;
    if (formatoJpeg.guardarArchivo(archivoOriginal)) {
        std::cout << "Imagen original guardada como: " << archivoOriginal << std::endl;
        system(("xdg-open " + archivoOriginal + " &").c_str());  // Abre la imagen con el visor predeterminado (Linux)
    } else {
        std::cerr << "Error al guardar la imagen original." << std::endl;
    }

    // Invierte los píxeles de la imagen
    AlgoritmosIMG::invertirPixeles(matrizPixeles);

    // Guarda y muestra la imagen invertida
    std::string archivoInvertido = "invertido_" + nombreArchivo;
    
    // Usamos el mismo objeto FormatoJPEG, pero actualizamos su matriz de píxeles
    if (formatoJpeg.modificarMatrizPixeles(matrizPixeles) && formatoJpeg.guardarArchivo(archivoInvertido)) {
        std::cout << "Imagen invertida guardada como: " << archivoInvertido << std::endl;
        system(("xdg-open " + archivoInvertido + " &").c_str());  // Abre la imagen con el visor predeterminado (Linux)
    } else {
        std::cerr << "Error al guardar la imagen invertida." << std::endl;
    }

    return 0;
}