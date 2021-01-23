#include "RenderWidget.h"

RenderWidget::RenderWidget(int width, int height) : QWidget() {
    press = false;
    lastX = lastY = INT_MAX;
    this->width = width;
    this->height = height;
    zBuffer = new NaiveZBuffer(width, height);

    modelLabel.setParent(this);
    modelLabel.setText("Select Model File:");
    modelButton.setParent(this);
    modelButton.setText("...");
    connect(&modelButton, SIGNAL(clicked(bool)), this, SLOT(selectModel()));
    miniHorizontal.addWidget(&modelLabel);
    miniHorizontal.addWidget(&modelButton);

    methodLabel.setParent(this);
    methodLabel.setText("Method:");
    naiveButton.setParent(this);
    naiveButton.setText("Naive Z-Buffer");
    naiveButton.setChecked(true);
    connect(&naiveButton, SIGNAL(clicked(bool)), this, SLOT(useNaive()));
    scanlineButton.setParent(this);
    scanlineButton.setText("Scanline Z-Buffer");
    connect(&scanlineButton, SIGNAL(clicked(bool)), this, SLOT(useScanline()));
    naiveHierarchicalButton.setParent(this);
    naiveHierarchicalButton.setText("Naive Hierarchical Z-Buffer");
    connect(&naiveHierarchicalButton, SIGNAL(clicked(bool)), this, SLOT(useNaiveHierarchical()));
    octreeHierarchicalButton.setParent(this);
    octreeHierarchicalButton.setText("Octree Hierarchical Z-Buffer");
    connect(&octreeHierarchicalButton, SIGNAL(clicked(bool)), this, SLOT(useOctreeHierarchical()));
    vertexLabel.setParent(this);
    facetLabel.setParent(this);
    timeLabel.setParent(this);
    vertical.addLayout(&miniHorizontal);
    vertical.addWidget(&methodLabel);
    vertical.addWidget(&naiveButton);
    vertical.addWidget(&scanlineButton);
    vertical.addWidget(&naiveHierarchicalButton);
    vertical.addWidget(&octreeHierarchicalButton);
    vertical.addWidget(&vertexLabel);
    vertical.addWidget(&facetLabel);
    vertical.addWidget(&timeLabel);
    vertical.addStretch();

    imageLabel.setParent(this);
    connect(&imageLabel, SIGNAL(mousePressed()), this, SLOT(imageMousePressed()));
    connect(&imageLabel, SIGNAL(mouseReleased()), this, SLOT(imageMouseReleased()));
    connect(&imageLabel, SIGNAL(mouseMoved(int, int)), this, SLOT(imageMouseMoved(int, int)));
    connect(&imageLabel, SIGNAL(wheeled(int)), this, SLOT(imageWheeled(int)));
    horizontal.addLayout(&vertical);
    horizontal.addWidget(&imageLabel);

    setLayout(&horizontal);

    calculateImage();
}

RenderWidget::~RenderWidget() {
    delete zBuffer;
}

void RenderWidget::calculateImage() {
    vertexLabel.setText(QString("Number of Vertices: %1").arg(model.numberOfVertices()));
    facetLabel.setText(QString("Number of Facets: %1").arg(model.numberOfFacets()));
    QTime timeBegin = QTime::currentTime();
    imageLabel.setPixmap(QPixmap::fromImage(model.render(zBuffer)));
    QTime timeEnd = QTime::currentTime();
    timeLabel.setText(QString("Time Assumed: %1ms").arg(timeBegin.msecsTo(timeEnd)));
}

void RenderWidget::selectModel() {
    QString path = QFileDialog::getOpenFileName(this,"Select Model",".","");
    model = Model(path.toStdString());
    calculateImage();
}

void RenderWidget::useNaive() {
    delete zBuffer;
    zBuffer = new NaiveZBuffer(width, height);
    calculateImage();
}

void RenderWidget::useScanline() {
    delete zBuffer;
    zBuffer = new ScanlineZBuffer(width, height);
    calculateImage();
}

void RenderWidget::useNaiveHierarchical() {
    delete zBuffer;
    zBuffer = new NaiveHierarchicalZBuffer(width, height);
    calculateImage();
}

void RenderWidget::useOctreeHierarchical() {
    delete zBuffer;
    zBuffer = new OctreeHierarchicalZBuffer(width, height);
    calculateImage();
}

void RenderWidget::imageMousePressed() {
    press = true;
    lastX = lastY = INT_MIN;
}

void RenderWidget::imageMouseReleased() {
    press = false;
}

void RenderWidget::imageMouseMoved(int x, int y) {
    if (press && lastX != INT_MIN && lastY != INT_MIN && (x != lastX || y != lastY)) {
        glm::vec3 a = glm::normalize(glm::vec3((float)lastX / width - 0.5f, 0.5f - (float)lastY / height, 1.0f));
        glm::vec3 b = glm::normalize(glm::vec3((float)x / width - 0.5f, 0.5f - (float)y / height, 1.0f));
        glm::vec3 axis = glm::cross(a, b);
        float angle = glm::dot(a, b);
        glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), 10.0f * std::acos(angle), axis) * zBuffer->getRotate();
        zBuffer->setRotate(rotate);
        calculateImage();
    }

    lastX = x;
    lastY = y;
}

void RenderWidget::imageWheeled(int deltaY) {
    zBuffer->setFactor(std::max(zBuffer->getFactor() + deltaY * 1e-4f, 0.01f));
    calculateImage();
}