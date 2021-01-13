#include <QApplication>

#include "Renderer.h"

const int WIDTH = 1024, HEIGHT = 768;

int main(int argc, char **argv) {
    QApplication application(argc, argv);
    Renderer renderer("model/bunny.obj", WIDTH, HEIGHT);
    renderer.show();

    return QApplication::exec();
}
