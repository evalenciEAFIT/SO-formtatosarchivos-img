#include "FormatoJPEG.h"
#include <jpeglib.h>  // Librería para manejar archivos JPEG
#include <iostream>   // Para mostrar mensajes de error

FormatoJPEG::FormatoJPEG(const std::string& nombreArchivo) : nombreArchivo(nombreArchivo), canales(0) {}

FormatoJPEG::~FormatoJPEG() {}

bool FormatoJPEG::abrirArchivo() {
    // Abre el archivo en modo binario
    FILE* archivoEntrada = fopen(nombreArchivo.c_str(), "rb");
    if (!archivoEntrada) {
        std::cerr << "Error al abrir el archivo: " << nombreArchivo << std::endl;
        return false;
    }

    // Estructuras necesarias para la descompresión JPEG
    struct jpeg_decompress_struct infoDescompresion;
    struct jpeg_error_mgr manejadorErrores;

    // Inicializa el manejador de errores y la estructura de descompresión
    infoDescompresion.err = jpeg_std_error(&manejadorErrores);
    jpeg_create_decompress(&infoDescompresion);
    jpeg_stdio_src(&infoDescompresion, archivoEntrada);

    // Lee la información del encabezado JPEG
    jpeg_read_header(&infoDescompresion, TRUE);
    jpeg_start_decompress(&infoDescompresion);

    // Obtiene información sobre la imagen
    canales = infoDescompresion.output_components;
    int ancho = infoDescompresion.output_width;
    int alto = infoDescompresion.output_height;

    // Redimensiona la matriz de píxeles
    matrizPixeles.resize(alto, std::vector<Pixel>(ancho));

    // Buffer para almacenar una fila de la imagen
    JSAMPARRAY bufferFila = (*infoDescompresion.mem->alloc_sarray)
        ((j_common_ptr)&infoDescompresion, JPOOL_IMAGE, ancho * canales, 1);

    // Lee la imagen línea por línea
    while (infoDescompresion.output_scanline < infoDescompresion.output_height) {
        jpeg_read_scanlines(&infoDescompresion, bufferFila, 1);
        int y = infoDescompresion.output_scanline - 1;
        for (int x = 0; x < ancho; x++) {
            if (canales == 3) {
                matrizPixeles[y][x].r = bufferFila[0][x * 3];
                matrizPixeles[y][x].g = bufferFila[0][x * 3 + 1];
                matrizPixeles[y][x].b = bufferFila[0][x * 3 + 2];
            } else if (canales == 1) {
                matrizPixeles[y][x].r = matrizPixeles[y][x].g = matrizPixeles[y][x].b = bufferFila[0][x];
            }
        }
    }

    // Finaliza la descompresión y libera los recursos
    jpeg_finish_decompress(&infoDescompresion);
    jpeg_destroy_decompress(&infoDescompresion);
    fclose(archivoEntrada);

    return true;
}

bool FormatoJPEG::guardarArchivo(const std::string& nuevoNombreArchivo) {
    // Abre el archivo en modo binario para escritura
    FILE* archivoSalida = fopen(nuevoNombreArchivo.c_str(), "wb");
    if (!archivoSalida) {
        std::cerr << "Error al crear el archivo: " << nuevoNombreArchivo << std::endl;
        return false;
    }

    // Estructuras necesarias para la compresión JPEG
    struct jpeg_compress_struct infoCompresion;
    struct jpeg_error_mgr manejadorErrores;

    // Inicializa el manejador de errores y la estructura de compresión
    infoCompresion.err = jpeg_std_error(&manejadorErrores);
    jpeg_create_compress(&infoCompresion);
    jpeg_stdio_dest(&infoCompresion, archivoSalida);

    // Configura los parámetros de la imagen
    infoCompresion.image_width = matrizPixeles[0].size();
    infoCompresion.image_height = matrizPixeles.size();
    infoCompresion.input_components = 3;
    infoCompresion.in_color_space = JCS_RGB;

    // Establece los parámetros de compresión
    jpeg_set_defaults(&infoCompresion);
    jpeg_set_quality(&infoCompresion, 90, TRUE);

    // Inicia la compresión
    jpeg_start_compress(&infoCompresion, TRUE);

    // Buffer para almacenar una fila de la imagen
    std::vector<unsigned char> filaBytes(infoCompresion.image_width * 3);
    JSAMPROW punteroFila[1];
    punteroFila[0] = &filaBytes[0];

    // Escribe la imagen línea por línea
    while (infoCompresion.next_scanline < infoCompresion.image_height) {
        for (unsigned int x = 0; x < infoCompresion.image_width; x++) {
            filaBytes[x * 3] = matrizPixeles[infoCompresion.next_scanline][x].r;
            filaBytes[x * 3 + 1] = matrizPixeles[infoCompresion.next_scanline][x].g;
            filaBytes[x * 3 + 2] = matrizPixeles[infoCompresion.next_scanline][x].b;
        }
        jpeg_write_scanlines(&infoCompresion, punteroFila, 1);
    }

    // Finaliza la compresión y libera los recursos
    jpeg_finish_compress(&infoCompresion);
    fclose(archivoSalida);
    jpeg_destroy_compress(&infoCompresion);

    return true;
}

bool FormatoJPEG::modificarMatrizPixeles(const std::vector<std::vector<Pixel>>& nuevaMatriz) {
    if (nuevaMatriz.empty() || nuevaMatriz[0].empty()) {
        std::cerr << "Error: La nueva matriz de píxeles está vacía." << std::endl;
        return false;
    }
    
    matrizPixeles = nuevaMatriz;
    return true;
}

std::vector<std::vector<Pixel>> FormatoJPEG::obtenerMatrizPixeles() const {
    return matrizPixeles;
}