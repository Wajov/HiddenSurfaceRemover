#include "ZBuffer.h"

ZBuffer::ZBuffer(int width, int height) {
    this->width = width;
    this->height = height;
    ambientColor = glm::vec3(0.1f);
    diffuseColor = glm::vec3(0.6f);
    specularColor = glm::vec3(0.3f);
    cameraPosition = glm::vec3(0.0f, 0.0f, 5.0f);
    lightPosition = glm::vec3(3.0f, 3.0f, 1.0f);
    lightPower = 20.0f;
    factor = 1.0f;
    rotate = glm::mat4(1.0f);
    calculateMVP();
}

ZBuffer::~ZBuffer() {}

void ZBuffer::calculateMVP() {
    glm::mat4 model = glm::scale(rotate, glm::vec3(factor));
    glm::mat4 view = glm::lookAt(cameraPosition, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 projection = glm::perspective((float)M_PI / 4.0f, (float)width / (float)height, 0.1f, 100.0f);
    MVP = projection * view * model;
}

glm::vec3 ZBuffer::calculateColor(glm::vec3 &p, glm::vec3 &n) {
    glm::mat4 model = glm::scale(rotate, glm::vec3(factor));
    glm::vec3 vertexPosition(model * glm::vec4(p, 1.0f));
    float distance = glm::distance(vertexPosition, lightPosition);

    glm::vec3 ambient = ambientColor;

    glm::vec3 N = glm::normalize(glm::vec3(model * glm::vec4(n, 0.0f)));
    glm::vec3 L = glm::normalize(lightPosition - vertexPosition);
    glm::vec3 diffuse = diffuseColor * lightPower * glm::clamp(glm::dot(N, L), 0.0f, 1.0f) / (distance * distance);

    glm::vec3 V = glm::normalize(cameraPosition - vertexPosition);
    glm::vec3 H = glm::normalize(L + V);
    glm::vec3 specular = specularColor * lightPower * (float)glm::pow(glm::clamp(glm::dot(N, H), 0.0f, 1.0f), 5) / (distance * distance);

    return glm::clamp(ambient + diffuse + specular, 0.0f, 1.0f);
}

float ZBuffer::getFactor() {
    return factor;
}

void ZBuffer::setFactor(float factor) {
    this->factor = factor;
    calculateMVP();
}

glm::mat4 ZBuffer::getRotate() {
    return rotate;
}

void ZBuffer::setRotate(glm::mat4 &rotate) {
    this->rotate = rotate;
    calculateMVP();
}