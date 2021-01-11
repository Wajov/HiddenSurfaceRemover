#include <QApplication>
#include <QLabel>
#include <QPixmap>

#include "Model.h"
#include "ScanlineZBuffer.h"

const int WIDTH = 1920, HEIGHT = 1080;

int main(int argc, char **argv) {
    Model model("model/suzanne.obj");

    QApplication application(argc, argv);
    QLabel label;
    label.resize(WIDTH, HEIGHT);
    label.setPixmap(QPixmap::fromImage(model.render(new ScanlineZBuffer(WIDTH, HEIGHT))));
    label.show();

    return QApplication::exec();
}
