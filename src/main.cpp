#include <QApplication>

#include "Renderer.h"

const int WIDTH = 1920, HEIGHT = 1080;

int main(int argc, char **argv) {
    QApplication application(argc, argv);
    Renderer renderer("model/suzanne.obj", WIDTH, HEIGHT);
    renderer.show();

    return QApplication::exec();
}
