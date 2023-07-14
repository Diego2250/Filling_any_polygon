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

    // Rellenar Polígono 1 con amarillo
    framebuffer.setCurrentColor(Color(255, 255, 0)); // Amarillo
    framebuffer.fillPolygon(polygon1Points);

    // Dibujar orilla del Polígono 1 en blanco
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

    // Rellenar Polígono 2 con azul
    framebuffer.setCurrentColor(Color(0, 0, 255)); // Azul
    framebuffer.fillPolygon(polygon2Points);

    // Dibujar orilla del Polígono 2 en blanco
    framebuffer.setCurrentColor(Color(255, 255, 255)); // Blanco
    for (size_t i = 0; i < polygon2Points.size(); ++i) {
        const Vertex2& currentPoint = polygon2Points[i];
        const Vertex2& nextPoint = polygon2Points[(i + 1) % polygon2Points.size()];
        framebuffer.drawLine(currentPoint, nextPoint);
    }

    // Polígono 3
    std::vector<Vertex2> polygon3Points = {
            Vertex2(377, 249), Vertex2(411, 197), Vertex2(436, 249)
    };

    // Rellenar Polígono 3 con rojo
    framebuffer.setCurrentColor(Color(255, 0, 0)); // Rojo
    framebuffer.fillPolygon(polygon3Points);

    // Dibujar orilla del Polígono 3 en blanco
    framebuffer.setCurrentColor(Color(255, 255, 255)); // Blanco
    for (size_t i = 0; i < polygon3Points.size(); ++i) {
        const Vertex2& currentPoint = polygon3Points[i];
        const Vertex2& nextPoint = polygon3Points[(i + 1) % polygon3Points.size()];
        framebuffer.drawLine(currentPoint, nextPoint);
    }

    // Polígono 4
    std::vector<Vertex2> polygon4Points = {
            Vertex2(413, 177), Vertex2(448, 159), Vertex2(502, 88), Vertex2(553, 53),
            Vertex2(535, 36), Vertex2(676, 37), Vertex2(660, 52), Vertex2(750, 145),
            Vertex2(761, 179), Vertex2(672, 192), Vertex2(659, 214), Vertex2(615, 214),
            Vertex2(632, 230), Vertex2(580, 230), Vertex2(597, 215), Vertex2(552, 214),
            Vertex2(517, 144), Vertex2(466, 180)
    };

    // Polígono 5
    std::vector<Vertex2> polygon5Points = {
            Vertex2(682, 175), Vertex2(708, 120), Vertex2(735, 148), Vertex2(739, 170)
    };

    // Rellenar polígono 4 con verde
    framebuffer.setCurrentColor(Color(0, 255, 0)); // Verde
    framebuffer.fillPolygon(polygon4Points);

    // Rellenar polígono 5 con negro (agujero)
    framebuffer.setCurrentColor(Color(0, 0, 0)); // Negro
    framebuffer.fillPolygon(polygon5Points);

    // Dibujar la orilla del polígono 4 en blanco
    framebuffer.setCurrentColor(Color(255, 255, 255)); // Blanco
    for (size_t i = 0; i < polygon4Points.size(); ++i) {
        const Vertex2& currentPoint = polygon4Points[i];
        const Vertex2& nextPoint = polygon4Points[(i + 1) % polygon4Points.size()];
        framebuffer.drawLine(currentPoint, nextPoint);
    }

    // Guardar el contenido del framebuffer en un archivo BMP
    framebuffer.renderBuffer();

    return 0;
}
