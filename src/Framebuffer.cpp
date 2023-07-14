#include <iostream>
#include <fstream>
#include "Framebuffer.h"

// Constructor
Framebuffer::Framebuffer(int width, int height, const Color& clearColor)
        : clearColor(clearColor) {
    framebuffer.resize(width * height);
    currentColor = Color(255, 255, 255);
}

// Función para colocar un punto en el framebuffer
void Framebuffer::point(const Vertex2& vertex) {
    int index = vertex.x + vertex.y * 800; // Cálculo del índice en el framebuffer
    framebuffer[index] = currentColor;
}

// Función para llenar el framebuffer con el color clearColor
void Framebuffer::clear() {
    for (auto& pixel : framebuffer) {
        pixel = clearColor;
    }
}

// Función para establecer el color actual
void Framebuffer::setCurrentColor(const Color& color) {
    currentColor = color;
}

// Función para guardar el contenido del framebuffer en un archivo BMP
void Framebuffer::renderBuffer() {

    std::ofstream file;
    std::string filePath = "out.bmp";  // Ruta y nombre de archivo personalizado
    file.open(filePath, std::ios::binary | std::ios::trunc);
    if (!file) {
        std::cerr << "Error al abrir el archivo de salida" << std::endl;
        return;
    }

    // Encabezado del archivo BMP
    const int width = 800;
    const int height = 600;
    const int fileSize = 54 + 3 * width * height;
    const int dataOffset = 54;

    char header[54] = {
            'B', 'M',               // Tipo de archivo
            static_cast<char>(fileSize & 0xFF), static_cast<char>((fileSize >> 8) & 0xFF), static_cast<char>((fileSize >> 16) & 0xFF), static_cast<char>((fileSize >> 24) & 0xFF), // Tamaño del archivo
            0, 0, 0, 0,             // Reservado
            static_cast<char>(dataOffset & 0xFF), static_cast<char>((dataOffset >> 8) & 0xFF), static_cast<char>((dataOffset >> 16) & 0xFF), static_cast<char>((dataOffset >> 24) & 0xFF), // Offset de los datos
            40, 0, 0, 0,            // Tamaño del encabezado de información
            static_cast<char>(width & 0xFF), static_cast<char>((width >> 8) & 0xFF), static_cast<char>((width >> 16) & 0xFF), static_cast<char>((width >> 24) & 0xFF), // Ancho de la imagen
            static_cast<char>(height & 0xFF), static_cast<char>((height >> 8) & 0xFF), static_cast<char>((height >> 16) & 0xFF), static_cast<char>((height >> 24) & 0xFF), // Alto de la imagen
            1, 0,                  // Número de planos
            24, 0,                 // Bits por pixel
            0, 0, 0, 0,            // Compresión
            0, 0, 0, 0,            // Tamaño de los datos de la imagen
            0, 0, 0, 0,            // Resolución horizontal
            0, 0, 0, 0,            // Resolución vertical
            0, 0, 0, 0             // Colores en la paleta
    };

    file.write(header, 54);

    // Datos de la imagen
    for (const auto& color : framebuffer) {
        char pixel[3] = {
                static_cast<char>(color.getBlue()),
                static_cast<char>(color.getGreen()),
                static_cast<char>(color.getRed())
        };

        file.write(pixel, 3);
    }
}

// Algoritmo de línea de Bresenham
void Framebuffer::drawLine(const Vertex2& start, const Vertex2& end) {
    int x0 = start.x;
    int y0 = start.y;
    int x1 = end.x;
    int y1 = end.y;

    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (true) {
        point(Vertex2(x0, y0));

        if (x0 == x1 && y0 == y1) {
            break;
        }

        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}

// Función para dibujar un polígono
void Framebuffer::drawPolygon(const std::vector<Vertex2>& points) {
    if (points.size() < 2) {
        return;  // No se puede dibujar un polígono con menos de 2 puntos
    }

    for (size_t i = 0; i < points.size() - 1; ++i) {
        drawLine(points[i], points[i + 1]);
    }

    // Dibujar línea desde el último punto hasta el primer punto
    drawLine(points.back(), points.front());
}

void Framebuffer::fillPolygon(const std::vector<Vertex2>& vertices) {
    if (vertices.size() < 3) {
        return;  // No se puede rellenar un polígono con menos de 3 vértices
    }

    // Encontrar los límites del polígono
    int minX = vertices[0].x;
    int maxX = vertices[0].x;
    int minY = vertices[0].y;
    int maxY = vertices[0].y;

    for (const auto& vertex : vertices) {
        if (vertex.x < minX) {
            minX = vertex.x;
        }
        if (vertex.x > maxX) {
            maxX = vertex.x;
        }
        if (vertex.y < minY) {
            minY = vertex.y;
        }
        if (vertex.y > maxY) {
            maxY = vertex.y;
        }
    }

    // Escanear cada línea horizontal dentro de los límites del polígono
    for (int y = minY; y <= maxY; ++y) {
        // Encontrar los puntos de intersección de la línea horizontal con los bordes del polígono
        std::vector<int> intersections;

        for (size_t i = 0; i < vertices.size(); ++i) {
            const Vertex2& currentVertex = vertices[i];
            const Vertex2& nextVertex = vertices[(i + 1) % vertices.size()];

            if ((currentVertex.y <= y && nextVertex.y > y) || (currentVertex.y > y && nextVertex.y <= y)) {
                // Calcular la intersección en la coordenada x
                int intersectionX = static_cast<int>(currentVertex.x + (static_cast<double>(y - currentVertex.y) / (nextVertex.y - currentVertex.y)) * (nextVertex.x - currentVertex.x));
                intersections.push_back(intersectionX);
            }
        }

        // Ordenar las intersecciones de menor a mayor
        std::sort(intersections.begin(), intersections.end());

        // Rellenar la región entre las intersecciones
        for (size_t i = 0; i < intersections.size(); i += 2) {
            int startX = intersections[i];
            int endX = intersections[i + 1];

            // Dibujar los puntos en la línea horizontal
            for (int x = startX; x <= endX; ++x) {
                point(Vertex2(x, y));
            }
        }
    }
}
