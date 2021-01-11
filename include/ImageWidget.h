#ifndef IMAGE_WIDGET_H
#define IMAGE_WIDGET_H

#include <QLabel>
#include <QImage>
#include <QPixmap>
#include <QMouseEvent>

#include "Model.h"
#include "ZBuffer.h"
#include "ScanlineZBuffer.h"

class ImageWidget : public QLabel {
private:
    Model model;
    ZBuffer *zBuffer;

public:
    ImageWidget(Model &model, ZBuffer *zBuffer);
    void mouseMoveEvent(QMouseEvent *event) override;
};


#endif