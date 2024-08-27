#ifndef VISUALIZADOR_IMG_H
#define VISUALIZADOR_IMG_H

#include <SDL2/SDL.h>  // Librería SDL para la visualización gráfica
#include <vector>      // Para manejar la matriz de píxeles
#include <string>      // Para manejar títulos de ventana

class VisualizadorIMG {
private:
    SDL_Window* ventana;       // Puntero a la ventana SDL
    SDL_Renderer* renderizador;// Puntero al renderizador SDL
    SDL_Texture* textura;      // Puntero a la textura SDL para mostrar la imagen
    int ancho;                 // Ancho de la ventana
    int alto;                  // Alto de la ventana

public:
    VisualizadorIMG();
    ~VisualizadorIMG();

    // Inicializa la ventana SDL con el título y dimensiones dadas
    bool inicializar(const std::string& titulo, int ancho, int alto);

    // Muestra la matriz de píxeles como una imagen en la ventana
    void mostrarImagen(const std::vector<std::vector<unsigned char>>& matrizPixeles);

    // Espera a que el usuario cierre la ventana
    void esperarCierre();
};

#endif // VISUALIZADOR_IMG_H