#ifndef RENDERER_H
#define RENDERER_H

#include <climits>

#include <glm/glm.hpp>
#include <QWidget>
#include <QFileDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QRadioButton>
#include <QPixmap>
#include <QTime>
#include <QString>
#include <QStringList>

#include "Model.h"
#include "ZBuffer.h"
#include "NaiveZBuffer.h"
#include "ScanlineZBuffer.h"
#include "NaiveHierarchicalZBuffer.h"
#include "OctreeHierarchicalZBuffer.h"
#include "ImageLabel.h"

class RenderWidget : public QWidget {
    Q_OBJECT
private:
    bool press;
    int lastX, lastY, width, height;
    Model model;
    ZBuffer *zBuffer;
    QVBoxLayout vertical;
    QHBoxLayout horizontal, miniHorizontal;
    QPushButton modelButton;
    QRadioButton naiveButton, scanlineButton, naiveHierarchicalButton, octreeHierarchicalButton;
    QLabel modelLabel, methodLabel, vertexLabel, facetLabel, timeLabel;
    ImageLabel imageLabel;
    void calculateImage();

public:
    RenderWidget(int width, int height);
    ~RenderWidget() override;

private slots:
    void selectModel();
    void useNaive();
    void useScanline();
    void useNaiveHierarchical();
    void useOctreeHierarchical();
    void imageMousePressed();
    void imageMouseReleased();
    void imageMouseMoved(int x, int y);
    void imageWheeled(int deltaY);
};


#endif