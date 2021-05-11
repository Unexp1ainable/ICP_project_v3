#include "src/gui/ClassesGui/GuiWindow.h"
#include "src/rayTracer/RayEngine.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    rayEngine engine{ 15., 30., 50. };
    GuiWindow window(&engine);
    window.resize(640, 480);

    window.show();

    return QApplication::exec();
}


