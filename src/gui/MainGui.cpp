#include "MainGui.h"

#include <QtWidgets>

#include "ClassesGui/GuiWindow.h"

int run_gui(int argc, char* argv[])
{
    QApplication app(argc, argv);
	// TESTING
    rayEngine engine{};
	// ====
    GuiWindow window(&engine);
    window.resize(640, 480);
	
    window.show();

    return QApplication::exec();
}
