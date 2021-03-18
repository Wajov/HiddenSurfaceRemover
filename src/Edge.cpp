#include "Edge.h"

Edge::Edge(Vertex &source, Vertex &target, QMatrix4x4 &MVP, int width, int height) {
    Vertex s = source, t = target;
    QVector4D p1 = MVP * QVector4D(s.getPosition(), 1.0f), p2 = MVP * QVector4D(t.getPosition(), 1.0f);
    p1 /= p1.w();
    p2 /= p2.w();
    if (p1.y() < p2.y()) {
        std::swap(s, t);
        std::swap(p1, p2);
    }
    int x1, y1, x2, y2;
    coordinateToPixel(p1.x(), p1.y(), x1, y1, width, height);
    coordinateToPixel(p2.x(), p2.y(), x2, y2, width, height);
    x = x1;
    deltaX = x2 - x1;
    y = y1;
    deltaY = y2 - y1;
    z = p1.z();
    dz = (p2.z() - p1.z()) / deltaY;
    p = s.getPosition();
    dp = (t.getPosition() - s.getPosition()) / (float)deltaY;
    n = s.getNormal();
    dn = (t.getNormal() - s.getNormal()) / (float)deltaY;
}

Edge::~Edge() {}

void Edge::coordinateToPixel(float coordinateX, float coordinateY, int &pixelX, int &pixelY, int width, int height) {
    pixelX = (int)((coordinateX + 1.0f) / 2.0f * width);
    pixelY = (int)((-coordinateY + 1.0f) / 2.0f * height);
}

bool Edge::operator <(Edge &edge) {
    if (y != edge.y)
        return y < edge.y;
    else if (y + deltaY != edge.y + edge.deltaY)
        return y + deltaY < edge.y + edge.deltaY;
    else if (x != edge.x)
        return x < edge.x;
    else
        return x + deltaX < edge.x + edge.deltaX;
}

int Edge::getX() {
    return x;
}

int Edge::getDeltaX() {
    return deltaX;
}

int Edge::getY() {
    return y;
}

int Edge::getDeltaY() {
    return deltaY;
}

float Edge::getZ() {
    return z;
}

float Edge::getDz() {
    return dz;
}

QVector3D Edge::getP() {
    return p;
}

QVector3D Edge::getDp() {
    return dp;
}

QVector3D Edge::getN() {
    return n;
}

QVector3D Edge::getDn() {
    return dn;
}