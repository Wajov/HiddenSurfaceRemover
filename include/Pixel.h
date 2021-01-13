#ifndef PIXEL_H
#define PIXEL_H

#include <QColor>

class Pixel {
private:
    int x, y;
    float z;
    QColor color;

public:
    Pixel(int x, int y, float z, QColor &color);
    ~Pixel();
    int getX();
    int getY();
    float getZ();
    QColor getColor();
};

#endif