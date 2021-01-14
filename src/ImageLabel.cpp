#include "ImageLabel.h"

ImageLabel::ImageLabel() : QLabel() {}

ImageLabel::~ImageLabel() {}

void ImageLabel::mousePressEvent(QMouseEvent *event) {
    emit mousePressed();
}

void ImageLabel::mouseReleaseEvent(QMouseEvent *event) {
    emit mouseReleased();
}

void ImageLabel::mouseMoveEvent(QMouseEvent *event) {
    emit mouseMoved(event->x(), event->y());
}

void ImageLabel::wheelEvent(QWheelEvent *event) {
    emit wheeled(event->angleDelta().y());
}