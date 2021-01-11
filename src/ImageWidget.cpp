#include "ImageWidget.h"
#include <iostream>
ImageWidget::ImageWidget(Model &model, ZBuffer *zBuffer) : QLabel() {
    this->model = model;
    this->zBuffer = zBuffer;
}

void ImageWidget::mouseMoveEvent(QMouseEvent *event) {
    std::cout << event->x() << ' ' << event->y() << std::endl;
}