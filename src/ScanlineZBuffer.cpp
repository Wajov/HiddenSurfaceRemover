#include "ScanlineZBuffer.h"

ScanlineZBuffer::ScanlineZBuffer(int width, int height) : ZBuffer(width, height) {}

QImage ScanlineZBuffer::render(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices) {
    for (auto iter = indices.begin(); iter != indices.end(); ) {
        std::vector<Vertex> polygonVertices;
        for (int i = 0; i < 3; i++)
            polygonVertices.push_back(vertices[*(iter++)]);
        polygons.push_back(Polygon(polygonVertices, MVP, width, height));
    }
    std::sort(polygons.begin(), polygons.end());

    QImage ans(width, height, QImage::Format_RGB32);
    int index = 0;
    for (int scanline = polygons.begin()->getY(); scanline <= polygons.rbegin()->getY() + polygons.rbegin()->getDeltaY() && scanline < height; scanline++) {
        std::vector<float> zBuffer(width, FLT_MAX);
        for (; index < polygons.size() && polygons[index].getY() == scanline; index++)
            activePolygons.insert(std::make_pair(polygons[index].getY() + polygons[index].getDeltaY(), ActivePolygon(polygons[index])));
        if (scanline >= 0)
            for (std::pair<const int, ActivePolygon> &pair : activePolygons) {
                pair.second.check(scanline);
                int minX, maxX;
                float z, dz;
                glm::vec3 p, dp, n, dn;
                pair.second.intersection(minX, maxX, z, dz, p, dp, n, dn);
                for (int i = minX; i <= maxX && i < width; i++) {
                    if (i >= 0 && z < zBuffer[i]) {
                        zBuffer[i] = z;
                        glm::vec3 colorTemp = calculateColor(p, n);
                        QColor color((int)(colorTemp.x * 255), (int)(colorTemp.y * 255), (int)(colorTemp.z * 255));
                        ans.setPixel(i, scanline, color.rgb());
                    }
                    z += dz;
                    p += dp;
                    n += dn;
                }
            }
        while (!activePolygons.empty() && activePolygons.begin()->first == scanline)
            activePolygons.erase(activePolygons.begin());
        for (std::pair<const int, ActivePolygon> &pair : activePolygons)
            pair.second.update();
    }

    return ans;
}