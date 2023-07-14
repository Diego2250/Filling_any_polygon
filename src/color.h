#ifndef COLOR_H
#define COLOR_H

class Color {
private:
    int r, g, b;

public:
    // Constructores
    Color();
    Color(int red, int green, int blue);

    // Métodos para establecer los valores de r, g y b
    void setRed(int red);
    void setGreen(int green);
    void setBlue(int blue);

    // Métodos para obtener los valores de r, g y b
    int getRed() const;
    int getGreen() const;
    int getBlue() const;
};

#endif
