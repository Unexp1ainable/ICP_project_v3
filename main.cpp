#include "src/gui/ClassesGui/GuiWindow.h"
#include "src/rayTracer/RayEngine.h"

#include <clocale>

int main(int argc, char *argv[])
{
    std::setlocale(LC_NUMERIC, "C");
    QApplication app(argc, argv);
    RayEngine engine{ 15., 30., 50. };
    GuiWindow window(&engine);
    window.resize(640, 480);

    window.show();

    return QApplication::exec();
}


