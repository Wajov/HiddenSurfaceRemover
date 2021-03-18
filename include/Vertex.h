#ifndef VERTEX_H
#define VERTEX_H

#include <QVector3D>

class Vertex {
private:
    QVector3D position, normal;

public:
    Vertex(QVector3D &position, QVector3D &normal);
    ~Vertex();
    QVector3D getPosition();
    void setPosition(QVector3D &position);
    QVector3D getNormal();
};

#endif