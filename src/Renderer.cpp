#include "Renderer.h"

Renderer::Renderer(const std::string &path, int width, int height) : QLabel() {
    lastX = lastY = INT_MAX;
    this->width = width;
    this->height = height;
    model = Model(path);
    zBuffer = new ScanlineZBuffer(width, height);
    resize(width, height);
    calculateImage();
}

Renderer::~Renderer() {}

void Renderer::calculateImage() {
    setPixmap(QPixmap::fromImage(model.render(zBuffer)));
}

void Renderer::mousePressEvent(QMouseEvent *event) {
    press = true;
    lastX = lastY = INT_MIN;
}

void Renderer::mouseReleaseEvent(QMouseEvent *event) {
    press = false;
}

void Renderer::mouseMoveEvent(QMouseEvent *event) {
    if (press && lastX != INT_MIN && lastY != INT_MIN) {
        glm::vec3 a = glm::normalize(glm::vec3((float)lastX / width - 0.5f, 0.5f - (float)lastY / height, 1.0f));
        glm::vec3 b = glm::normalize(glm::vec3((float)event->x() / width - 0.5f, 0.5f - (float)event->y() / height, 1.0f));
        glm::vec3 axis = glm::cross(a, b);
        float angle = glm::dot(a, b);
        glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), 10.0f * std::acos(angle), axis) * zBuffer->getRotate();
        zBuffer->setRotate(rotate);
        calculateImage();
    }

    lastX = event->x();
    lastY = event->y();
}

void Renderer::wheelEvent(QWheelEvent *event) {
    zBuffer->setFactor(std::max(zBuffer->getFactor() + event->angleDelta().y() * 1e-4f, 0.01f));
    calculateImage();
}