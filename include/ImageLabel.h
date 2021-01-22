#ifndef IMAGE_LABEL_H
#define IMAGE_LABEL_H

#include <QLabel>
#include <QMouseEvent>
#include <QWheelEvent>

class ImageLabel : public QLabel {
    Q_OBJECT
private:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

public:
    ImageLabel();
    ~ImageLabel() override;

signals:
    void mousePressed();
    void mouseReleased();
    void mouseMoved(int x, int y);
    void wheeled(int deltaY);
};

#endif