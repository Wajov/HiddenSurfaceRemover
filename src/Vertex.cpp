#include "Vertex.h"

Vertex::Vertex(QVector3D &position, QVector3D &normal) {
    this->position = position;
    this->normal = normal;
}

Vertex::~Vertex() {}

QVector3D Vertex::getPosition() {
    return position;
}

void Vertex::setPosition(QVector3D &position) {
    this->position = position;
}

QVector3D Vertex::getNormal() {
    return normal;
}