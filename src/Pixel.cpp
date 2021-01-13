#include "Pixel.h"

Pixel::Pixel(int x, int y, float z, QColor &color) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->color = color;
}

Pixel::~Pixel() {}

int Pixel::getX() {
    return x;
}

int Pixel::getY() {
    return y;
}

float Pixel::getZ() {
    return z;
}

QColor Pixel::getColor() {
    return color;
}