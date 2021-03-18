#ifndef Z_BUFFER_H
#define Z_BUFFER_H

#include <cmath>
#include <algorithm>
#include <vector>

#include <QVector3D>
#include <QVector4D>
#include <QMatrix4x4>
#include <QColor>
#include <QImage>

#include "Vertex.h"
#include "Pixel.h"
#include "Polygon.h"
#include "ActivePolygon.h"
#include "Segment.h"
#include "ActiveSegment.h"

class ZBuffer {
protected:
    int width, height;
    float factor, lightPower;
    QVector3D ambientColor, diffuseColor, specularColor, cameraPosition, lightPosition;
    QMatrix4x4 rotate, MVP;
    float clamp(float x, float min, float max);
    void calculateMVP();
    QColor calculateColor(QVector3D &p, QVector3D &n);

public:
    ZBuffer(int width, int height);
    virtual ~ZBuffer();
    float getFactor();
    void setFactor(float factor);
    QMatrix4x4 getRotate();
    void setRotate(QMatrix4x4 &rotate);
    std::vector<Pixel> calculatePixels(Polygon &polygon, int minX, int maxX, int minY, int maxY);
    virtual QImage render(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices) = 0;
};

#endif