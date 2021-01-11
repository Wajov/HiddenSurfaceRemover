#include <QApplication>
#include <QImage>

#include "Model.h"
#include "ScanlineZBuffer.h"
#include "ImageWidget.h"

const int WIDTH = 1920, HEIGHT = 1080;

int main(int argc, char **argv) {
    Model model("model/bunny.obj");

    QApplication application(argc, argv);
    ImageWidget image(model.render(new ScanlineZBuffer(WIDTH, HEIGHT)));
    image.show();

    return QApplication::exec();
}
