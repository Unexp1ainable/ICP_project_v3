#include "MainGui.h"

#include <QtWidgets>

#include "ClassesGui/GuiWindow.h"

int run_gui(int argc, char* argv[])
{
    QApplication app(argc, argv);
	// TESTING
    rayEngine engine{};
    engine.add_lens(0.f, 10, 1, 0., 0.);
    engine.add_lens(10.f, 10, 1, 0.5, 0.);
	// ====
    GuiWindow window(&engine);
    window.resize(640, 480);
	
    window.show();

    return QApplication::exec();
}
