#include "MainGui.h"

#include <QtWidgets>
#include <string>

#include "ClassesGui/GuiWindow.h"

int run_gui(int argc, char* argv[])
{
    QApplication app(argc, argv);
	// TESTING
    rayEngine engine{15., 30., 50.};
    engine.add_lens(1.f, 10, 1, std::string("TestLens1"), 0., 0.);
    engine.add_lens(9.f, 10, 1, std::string("TestLens 2"),0.5, 0.);
	// ====
    GuiWindow window(&engine);
    window.resize(640, 480);
	
    window.show();

    return QApplication::exec();
}
