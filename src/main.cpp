#include <QApplication>

#include "RenderWidget.h"

const int WIDTH = 1600, HEIGHT = 900;

int main(int argc, char **argv) {
    QApplication application(argc, argv);
    RenderWidget renderer(WIDTH, HEIGHT);
    renderer.show();

    return QApplication::exec();
}
