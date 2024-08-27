#include "GeneradorJPEG.h"
#include <jpeglib.h>
#include <iostream>

bool GeneradorJPEG::generarJPEG(const std::string& nombreArchivo, 
                                const std::vector<std::vector<Pixel>>& matrizPixeles, 
                                int calidad) {
    if (matrizPixeles.empty() || matrizPixeles[0].empty()) {
        std::cerr << "Matriz de píxeles vacía" << std::endl;
        return false;
    }

    int alto = matrizPixeles.size();
    int ancho = matrizPixeles[0].size();

    FILE* archivoSalida = fopen(nombreArchivo.c_str(), "wb");
    if (!archivoSalida) {
        std::cerr << "No se pudo abrir el archivo de salida" << std::endl;
        return false;
    }

    struct jpeg_compress_struct cinfo;
    struct jpeg_error_mgr jerr;

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_compress(&cinfo);
    jpeg_stdio_dest(&cinfo, archivoSalida);

    cinfo.image_width = ancho;
    cinfo.image_height = alto;
    cinfo.input_components = 3;  // Siempre 3 para RGB
    cinfo.in_color_space = JCS_RGB;

    jpeg_set_defaults(&cinfo);
    jpeg_set_quality(&cinfo, calidad, TRUE);

    jpeg_start_compress(&cinfo, TRUE);

    std::vector<unsigned char> rowBuffer(ancho * 3);
    JSAMPROW row_pointer[1];

    while (cinfo.next_scanline < cinfo.image_height) {
        for (int x = 0; x < ancho; x++) {
            rowBuffer[x * 3] = matrizPixeles[cinfo.next_scanline][x].r;
            rowBuffer[x * 3 + 1] = matrizPixeles[cinfo.next_scanline][x].g;
            rowBuffer[x * 3 + 2] = matrizPixeles[cinfo.next_scanline][x].b;
        }
        row_pointer[0] = rowBuffer.data();
        jpeg_write_scanlines(&cinfo, row_pointer, 1);
    }

    jpeg_finish_compress(&cinfo);
    fclose(archivoSalida);
    jpeg_destroy_compress(&cinfo);

    return true;
}