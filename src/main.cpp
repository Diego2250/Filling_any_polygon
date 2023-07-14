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

    // Polígono 1
    std::vector<Vertex2> polygon1Points = {
            Vertex2(165, 380), Vertex2(185, 360), Vertex2(180, 330), Vertex2(207, 345),
            Vertex2(233, 330), Vertex2(230, 360), Vertex2(250, 380), Vertex2(220, 385),
            Vertex2(205, 410), Vertex2(193, 383)
    };

    // Rellenar polígono 1 con amarillo
    framebuffer.setCurrentColor(Color(255, 255, 0)); // Amarillo
    framebuffer.fillPolygon(polygon1Points);

    // Dibujar orilla del polígono 1 en blanco
    framebuffer.setCurrentColor(Color(255, 255, 255)); // Blanco
    for (size_t i = 0; i < polygon1Points.size(); ++i) {
        const Vertex2& currentPoint = polygon1Points[i];
        const Vertex2& nextPoint = polygon1Points[(i + 1) % polygon1Points.size()];
        framebuffer.drawLine(currentPoint, nextPoint);
    }

    // Polígono 2
    std::vector<Vertex2> polygon2Points = {
            Vertex2(321, 335), Vertex2(288, 286), Vertex2(339, 251), Vertex2(374, 302)
    };

    // Rellenar polígono 2 con azul
    framebuffer.setCurrentColor(Color(0, 0, 255)); // Azul
    framebuffer.fillPolygon(polygon2Points);

    // Dibujar orilla del polígono 2 en blanco
    framebuffer.setCurrentColor(Color(255, 255, 255)); // Blanco
    for (size_t i = 0; i < polygon2Points.size(); ++i) {
        const Vertex2& currentPoint = polygon2Points[i];
        const Vertex2& nextPoint = polygon2Points[(i + 1) % polygon2Points.size()];
        framebuffer.drawLine(currentPoint, nextPoint);
    }

    // Guardar el contenido del framebuffer en un archivo BMP
    framebuffer.renderBuffer();

    return 0;
}
