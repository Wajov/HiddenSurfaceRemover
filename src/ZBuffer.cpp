#include "ZBuffer.h"

ZBuffer::ZBuffer(int width, int height) {
    this->width = width;
    this->height = height;
    ambientColor = QVector3D(0.1f, 0.1f, 0.1f);
    diffuseColor = QVector3D(0.6f, 0.6f, 0.6f);
    specularColor = QVector3D(0.3f, 0.3f, 0.3f);
    cameraPosition = QVector3D(0.0f, 0.0f, 5.0f);
    lightPosition = QVector3D(3.0f, 3.0f, 1.0f);
    lightPower = 20.0f;
    factor = 1.0f;
    calculateMVP();
}

ZBuffer::~ZBuffer() {}

float ZBuffer::clamp(float x, float min, float max) {
    x = std::max(x, min);
    x = std::min(x, max);
    return x;
}

void ZBuffer::calculateMVP() {
    QMatrix4x4 model, view, projection;
    model = rotate;
    model.scale(factor);
    view.lookAt(cameraPosition, QVector3D(0.0f, 0.0f, 0.0f), QVector3D(0.0f, 1.0f, 0.0f));
    projection.perspective(45.0f, (float)width / (float)height, 0.1f, 100.0f);
    MVP = projection * view * model;
}

QColor ZBuffer::calculateColor(QVector3D &p, QVector3D &n) {
    QMatrix4x4 model = rotate;
    model.scale(factor);
    QVector3D vertexPosition(model * QVector4D(p, 1.0f));
    float distance = vertexPosition.distanceToPoint(lightPosition);

    QVector3D ambient = ambientColor;

    QVector3D N = QVector3D(model * QVector4D(n, 0.0f)).normalized();
    QVector3D L = (lightPosition - vertexPosition).normalized();
    QVector3D diffuse = diffuseColor * lightPower * clamp(QVector3D::dotProduct(N, L), 0.0f, 1.0f) / (distance * distance);

    QVector3D V = (cameraPosition - vertexPosition).normalized();
    QVector3D H = (L + V).normalized();
    QVector3D specular = specularColor * lightPower * std::pow(clamp(QVector3D::dotProduct(N, H), 0.0f, 1.0f), 5) / (distance * distance);

    QVector3D color = ambient + diffuse + specular;
    for (int i = 0; i < 3; i++)
        color[i] = clamp(color[i], 0.0f, 1.0f);

    return QColor((int)(color.x() * 255), (int)(color.y() * 255), (int)(color.z() * 255));
}

float ZBuffer::getFactor() {
    return factor;
}

void ZBuffer::setFactor(float factor) {
    this->factor = factor;
    calculateMVP();
}

QMatrix4x4 ZBuffer::getRotate() {
    return rotate;
}

void ZBuffer::setRotate(QMatrix4x4 &rotate) {
    this->rotate = rotate;
    calculateMVP();
}

std::vector<Pixel> ZBuffer::calculatePixels(Polygon &polygon, int minX, int maxX, int minY, int maxY) {
    std::vector<Pixel> ans;
    ActivePolygon activePolygon(polygon);
    for (int scanlineY = polygon.getY(); scanlineY <= polygon.getY() + polygon.getDeltaY() && scanlineY <= maxY; scanlineY++) {
        activePolygon.check(scanlineY);

        if (scanlineY >= minY) {
            Segment segment = activePolygon.segment();
            ActiveSegment activeSegment(segment);

            for (int scanlineX = segment.getX(); scanlineX <= segment.getX() + segment.getDeltaX() && scanlineX <= maxX; scanlineX++) {
                if (scanlineX >= minX) {
                    float z = activeSegment.getZ();
                    QVector3D p = activeSegment.getP(), n = activeSegment.getN();
                    QColor color = calculateColor(p, n);
                    ans.push_back(Pixel(scanlineX, scanlineY, z, color));
                }
                activeSegment.update();
            }
        }
        activePolygon.update();
    }
    return ans;
}