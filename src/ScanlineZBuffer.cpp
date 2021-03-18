#include "ScanlineZBuffer.h"

ScanlineZBuffer::ScanlineZBuffer(int width, int height) : ZBuffer(width, height) {}

ScanlineZBuffer::~ScanlineZBuffer() {}

QImage ScanlineZBuffer::render(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices) {
    std::vector<Polygon> polygons;
    for (auto iter = indices.begin(); iter != indices.end(); ) {
        std::vector<Vertex> polygonVertices;
        for (int i = 0; i < 3; i++)
            polygonVertices.push_back(vertices[*(iter++)]);
        Polygon polygon(polygonVertices, MVP, width, height);
        if (polygon.getDeltaX() > 0 && polygon.getDeltaY() > 0)
            polygons.push_back(polygon);
    }
    std::sort(polygons.begin(), polygons.end());

    std::multimap<int, ActivePolygon> activePolygons;
    QImage ans(width, height, QImage::Format_RGB32);
    ans.fill(QColor(0, 0, 0));
    for (int index = 0, scanlineY = polygons.begin()->getY(); scanlineY < height; ) {
        for (; index < polygons.size() && polygons[index].getY() == scanlineY; index++)
            activePolygons.insert(std::make_pair(polygons[index].getY() + polygons[index].getDeltaY(), ActivePolygon(polygons[index])));
        for (std::pair<const int, ActivePolygon> &pair : activePolygons)
            pair.second.check(scanlineY);

        if (scanlineY >= 0) {
            std::vector<float> zBuffer(width, FLT_MAX);
            for (std::pair<const int, ActivePolygon> &pair : activePolygons) {
                Segment segment = pair.second.segment();
                int x = segment.getX() + segment.getDeltaX();
                ActiveSegment activeSegment(segment);

                for (int scanlineX = segment.getX(); scanlineX <= x && scanlineX < width; scanlineX++) {
                    if (scanlineX >= 0 && activeSegment.getZ() < zBuffer[scanlineX]) {
                        zBuffer[scanlineX] = activeSegment.getZ();
                        QVector3D p = activeSegment.getP(), n = activeSegment.getN();
                        QColor color = calculateColor(p, n);
                        ans.setPixel(scanlineX, scanlineY, color.rgb());
                    }
                    activeSegment.update();
                }
            }
        }

        while (!activePolygons.empty() && activePolygons.begin()->first == scanlineY)
            activePolygons.erase(activePolygons.begin());
        for (std::pair<const int, ActivePolygon> &pair : activePolygons)
            pair.second.update();

        if (activePolygons.empty())
            scanlineY = index < polygons.size() ? polygons[index].getY() : height;
        else
            scanlineY++;
    }

    return ans;
}