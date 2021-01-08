#include "Model.h"
#include "ScanlineZBuffer.h"

int main() {
    Model model("model/bunny.obj");
    model.render(new ScanlineZBuffer);
    return 0;
}
