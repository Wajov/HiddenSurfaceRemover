#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "ScanlineZBuffer.h"

void ScanlineZBuffer::render(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices) {
    for (auto iter = indices.begin(); iter != indices.end(); ) {
        std::vector<Vertex> polygonVertices;
        for (int i = 0; i < 3; i++)
            polygonVertices.push_back(vertices[*(iter++)]);
        polygons.push_back(Polygon(polygonVertices));
    }
    std::sort(polygons.begin(), polygons.end());

    int height = 1080, width = 1080;
    unsigned char *output = new unsigned char[height * width * 3];
    auto iter = polygons.begin();
    for (int scanline = 0; scanline < height; scanline++) {
        for (; iter != polygons.end() && iter->getY() == scanline; iter++)
            activePolygons.insert(std::make_pair(iter->getY() + iter->getDeltaY(), ActivePolygon(*iter)));
        for (std::pair<const int, ActivePolygon> &pair : activePolygons) {
            pair.second.check(scanline);
            int minX, maxX;
            float z, dz;
            pair.second.intersection(minX, maxX, z, dz);
            for (int i = minX; i < maxX && i < width; i++) {
                glm::vec3 color = calculateColor();
                for (int j = 0; j < 3; j++)
                    output[(scanline * width + i) * 3 + j] = (unsigned char)(color[j] * 255);
            }
        }
        while (activePolygons.begin()->first == scanline)
            activePolygons.erase(activePolygons.begin());
        for (std::pair<const int, ActivePolygon> &pair : activePolygons)
            pair.second.update();
    }

    stbi_write_png("output.jpg", width, height, 3, output, 0);
    delete[] output;
}

glm::vec3 ScanlineZBuffer::calculateColor() {
    return glm::vec3(1.0);
}