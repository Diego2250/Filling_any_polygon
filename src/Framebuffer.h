#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <vector>
#include "Color.h"
#include "Vertex2.h"

class Framebuffer {
private:
    std::vector<Color> framebuffer;
    Color currentColor;
    Color clearColor;

public:
    // Constructor
    Framebuffer(int width, int height, const Color& clearColor);

    // Métodos para dibujar en el framebuffer
    void point(const Vertex2& vertex);
    void clear();
    void setCurrentColor(const Color& color);

    // Función para guardar el contenido del framebuffer en un archivo BMP
    void renderBuffer();

    // Algoritmo de línea de Bresenham
    void drawLine(const Vertex2& start, const Vertex2& end);

    // Función para dibujar un polígono
    void drawPolygon(const std::vector<Vertex2>& points);

    // Función para rellenar un polígono
    void fillPolygon(const std::vector<Vertex2>& vertices);
};

#endif
