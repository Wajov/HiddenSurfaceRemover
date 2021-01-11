#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "ScanlineZBuffer.h"

ScanlineZBuffer::ScanlineZBuffer(int width, int height) : ZBuffer(width, height) {}

void ScanlineZBuffer::render(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices) {
    for (auto iter = indices.begin(); iter != indices.end(); ) {
        std::vector<Vertex> polygonVertices;
        for (int i = 0; i < 3; i++)
            polygonVertices.push_back(vertices[*(iter++)]);
        polygons.push_back(Polygon(polygonVertices, MVP, width, height));
    }
    std::sort(polygons.begin(), polygons.end());

    float *zBuffer = new float[width];
    unsigned char *output = new unsigned char[height * width * 3];
    memset(output, 0, sizeof(unsigned char) * height * width * 3);
    int index = 0;
    for (int scanline = polygons.begin()->getY(); scanline < height; scanline++) {
        for (int i = 0; i < width; i++)
            zBuffer[i] = FLT_MAX;
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
                        glm::vec3 color = calculateColor(p, n);
                        for (int j = 0; j < 3; j++)
                            output[(scanline * width + i) * 3 + j] = (unsigned char)(color[j] * 255);
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

    stbi_write_png("output.jpg", width, height, 3, output, 0);
    delete[] zBuffer;
    delete[] output;
}