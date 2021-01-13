#include "NaiveZBuffer.h"

NaiveZBuffer::NaiveZBuffer(int width, int height) : ZBuffer(width, height) {}

NaiveZBuffer::~NaiveZBuffer() {}

QImage NaiveZBuffer::render(std::vector <Vertex> &vertices, std::vector<unsigned int> &indices) {
    std::vector<std::vector<float>> zBuffer(width);
    for (std::vector<float> &vector : zBuffer)
        vector = std::vector<float>(height, FLT_MAX);

    QImage ans(width, height, QImage::Format_RGB32);
    ans.fill(QColor(0, 0, 0));
    for (auto iter = indices.begin(); iter != indices.end(); ) {
        std::vector<Vertex> polygonVertices;
        for (int i = 0; i < 3; i++)
            polygonVertices.push_back(vertices[*(iter++)]);
        Polygon polygon(polygonVertices, MVP, width, height);
        if (polygon.getDeltaX() > 0 && polygon.getDeltaY() > 0) {
            std::vector<Pixel> pixels = calculatePixels(polygon, 0, width - 1, 0, height - 1);
            for (Pixel &pixel : pixels)
                if (pixel.getZ() < zBuffer[pixel.getX()][pixel.getY()]) {
                    zBuffer[pixel.getX()][pixel.getY()] = pixel.getZ();
                    ans.setPixel(pixel.getX(), pixel.getY(), pixel.getColor().rgb());
                }
        }
    }
    return ans;
}