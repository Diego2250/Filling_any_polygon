#include "Color.h"

#include "Color.h"

// Constructor por defecto
Color::Color() : r(0), g(0), b(0) {}

// Constructor
Color::Color(int red, int green, int blue) {
    setRed(red);
    setGreen(green);
    setBlue(blue);
}

// Métodos para establecer los valores de r, g y b
void Color::setRed(int red) {
    if (red < 0)
        r = 0;
    else if (red > 255)
        r = 255;
    else
        r = red;
}

void Color::setGreen(int green) {
    if (green < 0)
        g = 0;
    else if (green > 255)
        g = 255;
    else
        g = green;
}

void Color::setBlue(int blue) {
    if (blue < 0)
        b = 0;
    else if (blue > 255)
        b = 255;
    else
        b = blue;
}

// Métodos para obtener los valores de r, g y b
int Color::getRed() const {
    return r;
}

int Color::getGreen() const {
    return g;
}

int Color::getBlue() const {
    return b;
}
