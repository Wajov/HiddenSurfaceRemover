#ifndef RENDERER_H
#define RENDERER_H

#include <climits>
#include <string>

#include <glm/glm.hpp>
#include <QLabel>
#include <QPixmap>
#include <QMouseEvent>
#include <QWheelEvent>

#include "Model.h"
#include "ZBuffer.h"
#include "ScanlineZBuffer.h"
#include "NaiveHierarchicalZBuffer.h"
#include "OctreeHierarchicalZBuffer.h"

class Renderer : public QLabel {
private:
    bool press;
    int lastX, lastY, width, height;
    Model model;
    ZBuffer *zBuffer;
    void calculateImage();
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

public:
    Renderer(const std::string &path, int width, int height);
    ~Renderer() override;
};


#endif