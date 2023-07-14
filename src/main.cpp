#include <iostream>
#include <vector>
#include "Color.h"
#include "Vertex2.h"
#include "Framebuffer.h"



// Variables globales
std::vector<Color> framebuffer; // Vector unidimensional para almacenar el framebuffer
Color currentColor(255, 255, 255); // Color actual
Color clearColor(0, 0, 0); // Color base del framebuffer

// Función para colocar un punto en la pantalla
void punto(const Vertex2& vertex) {
    // Aquí puedes agregar la lógica para dibujar un punto en la pantalla
    std::cout << "Punto dibujado en las coordenadas (" << vertex.x << ", " << vertex.y << ")"
              << " con el color (" << currentColor.getRed() << ", "
              << currentColor.getGreen() << ", " << currentColor.getBlue() << ")" << std::endl;
}

// Función para llenar el framebuffer con el color clearColor
void clear() {
    for (auto& pixel : framebuffer) {
        pixel = clearColor;
    }
}

int main() {
    // Crear un objeto Framebuffer
    Framebuffer framebuffer(800, 600, Color(0, 0, 0)); // Ancho: 800, Alto: 600, Color de borrado: Negro

    // Dibujar un polígono
    std::vector<Vertex2> polygonPoints = {
            Vertex2(165, 380),
            Vertex2(185, 360),
            Vertex2(180, 330),
            Vertex2(207, 345),
            Vertex2(233, 330),
            Vertex2(230, 360),
            Vertex2(250, 380),
            Vertex2(220, 385),
            Vertex2(205, 410),
            Vertex2(193, 383)
    };

    // Rellenar el polígono con amarillo
    framebuffer.setCurrentColor(Color(255, 255, 0)); // Amarillo
    framebuffer.fillPolygon(polygonPoints);

    // Dibujar la orilla del polígono en blanco
    framebuffer.setCurrentColor(Color(255, 255, 255)); // Blanco
    for (size_t i = 0; i < polygonPoints.size(); ++i) {
        const Vertex2& currentPoint = polygonPoints[i];
        const Vertex2& nextPoint = polygonPoints[(i + 1) % polygonPoints.size()];
        framebuffer.drawLine(currentPoint, nextPoint);
    }

    // Guardar el contenido del framebuffer en un archivo BMP
    framebuffer.renderBuffer();

    return 0;
}
