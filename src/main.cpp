#include "Model.h"
#include "ScanlineZBuffer.h"

int main() {
    Model model("model/suzanne.obj");
    model.render(new ScanlineZBuffer(1920, 1080));
    return 0;
}
