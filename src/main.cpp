#include "Model.h"
#include "ScanlineZBuffer.h"

int main() {
    Model model("model/cube.obj");
    model.render(new ScanlineZBuffer);
    return 0;
}
