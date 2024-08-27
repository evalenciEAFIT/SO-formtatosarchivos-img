#include "VisualizadorIMG.h"
#include <iostream>    // Para mostrar mensajes de error

VisualizadorIMG::VisualizadorIMG() : ventana(nullptr), renderizador(nullptr), textura(nullptr), ancho(0), alto(0) {}

VisualizadorIMG::~VisualizadorIMG() {
    // Libera los recursos de SDL
    if (textura) SDL_DestroyTexture(textura);
    if (renderizador) SDL_DestroyRenderer(renderizador);
    if (ventana) SDL_DestroyWindow(ventana);
    SDL_Quit();
}

bool VisualizadorIMG::inicializar(const std::string& titulo, int ancho, int alto) {
    this->ancho = ancho;
    this->alto = alto;

    // Inicializa SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Error al inicializar SDL: " << SDL_GetError() << std::endl;
        return false;
    }

    // Crea la ventana
    ventana = SDL_CreateWindow(titulo.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ancho, alto, SDL_WINDOW_SHOWN);
    if (!ventana) {
        std::cerr << "Error al crear la ventana: " << SDL_GetError() << std::endl;
        return false;
    }

    // Crea el renderizador
    renderizador = SDL_CreateRenderer(ventana, -1, SDL_RENDERER_ACCELERATED);
    if (!renderizador) {
        std::cerr << "Error al crear el renderizador: " << SDL_GetError() << std::endl;
        return false;
    }

    // Crea la textura
    textura = SDL_CreateTexture(renderizador, SDL_PIXELFORMAT_RGB24, SDL_TEXTUREACCESS_STREAMING, ancho, alto);
    if (!textura) {
        std::cerr << "Error al crear la textura: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

void VisualizadorIMG::mostrarImagen(const std::vector<std::vector<unsigned char>>& matrizPixeles) {
    if (matrizPixeles.empty() || matrizPixeles[0].empty()) {
        std::cerr << "Matriz de píxeles vacía" << std::endl;
        return;
    }

    int altoMatriz = matrizPixeles.size();
    int anchoMatriz = matrizPixeles[0].size();

    // Convierte la matriz 2D en un array 1D de píxeles RGB
    std::vector<unsigned char> pixelesPlanos(altoMatriz * anchoMatriz * 3);
    for (int y = 0; y < altoMatriz; ++y) {
        for (int x = 0; x < anchoMatriz; ++x) {
            unsigned char valor = matrizPixeles[y][x];
            int index = (y * anchoMatriz + x) * 3;
            pixelesPlanos[index] = valor;     // R
            pixelesPlanos[index + 1] = valor; // G
            pixelesPlanos[index + 2] = valor; // B
        }
    }

    // Actualiza la textura con los nuevos píxeles
    SDL_UpdateTexture(textura, NULL, pixelesPlanos.data(), anchoMatriz * 3);
    SDL_RenderClear(renderizador);
    SDL_RenderCopy(renderizador, textura, NULL, NULL);
    SDL_RenderPresent(renderizador);
}

void VisualizadorIMG::esperarCierre() {
    SDL_Event evento;
    bool salir = false;
    while (!salir) {
        // Maneja eventos SDL hasta que se cierre la ventana
        while (SDL_PollEvent(&evento) != 0) {
            if (evento.type == SDL_QUIT) {
                salir = true;
            }
        }
    }
}