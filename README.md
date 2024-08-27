# Procesador de Imágenes JPEG

Este proyecto implementa un procesador simple de imágenes JPEG que demuestra cómo las imágenes digitales se representan y manipulan como matrices de números.

## Imágenes como Matrices de Números

En el mundo digital, las imágenes se representan como matrices bidimensionales de números. Cada elemento de esta matriz se llama píxel (abreviatura de "picture element" o elemento de imagen).

### Imágenes en Escala de Grises

En una imagen en escala de grises, cada píxel se representa por un solo número que indica su intensidad, generalmente en un rango de 0 (negro) a 255 (blanco). Por ejemplo, una imagen en escala de grises de 3x3 píxeles podría representarse así:

```
[
  [120, 80, 200],
  [50, 90, 175],
  [230, 100, 70]
]
```

### Imágenes a Color (RGB)

Las imágenes a color suelen utilizar el modelo RGB (Rojo, Verde, Azul). En este caso, cada píxel se representa por tres números, uno para cada componente de color. Cada componente también varía de 0 a 255. Por ejemplo:

```
[
  [[255, 0, 0],   [0, 255, 0],   [0, 0, 255]],
  [[255, 255, 0], [255, 0, 255], [0, 255, 255]],
  [[128, 128, 128], [0, 0, 0],   [255, 255, 255]]
]
```

En este ejemplo, [255, 0, 0] representa un rojo puro, [0, 255, 0] un verde puro, y [0, 0, 255] un azul puro.

## Funcionamiento del Proyecto

Este proyecto realiza las siguientes operaciones:

1. Lee una imagen JPEG y la convierte en una matriz de píxeles.
2. Invierte los colores de la imagen (255 - valor original para cada componente de color).
3. Guarda la imagen invertida como un nuevo archivo JPEG.

### Inversión de Colores

La inversión de colores se realiza restando cada valor de píxel de 255. Por ejemplo:

- Un píxel rojo [255, 0, 0] se convierte en [0, 255, 255] (cian).
- Un píxel blanco [255, 255, 255] se convierte en [0, 0, 0] (negro).
- Un píxel gris [128, 128, 128] se mantiene igual.

## Uso del Programa

Para usar el programa:

1. Compile el proyecto usando `make`.
2. Ejecute el programa con `./procesador_jpeg nombre_de_su_imagen.jpg`.

El programa creará dos nuevos archivos:
- `original_nombre_de_su_imagen.jpg`: Una copia de la imagen original.
- `invertido_nombre_de_su_imagen.jpg`: La imagen con los colores invertidos.

## Requisitos

- Compilador C++ que soporte C++11
- Biblioteca libjpeg

## Instalación de Dependencias

En sistemas basados en Debian/Ubuntu:
```
sudo apt-get install libjpeg-dev
```

En sistemas basados en Red Hat/Fedora:
```
sudo dnf install libjpeg-devel
```

En macOS con Homebrew:
```
brew install libjpeg
```
