#include "MainGui.h"

#include <QtWidgets>

#include "ClassesGui/GuiWindow.h"

int run_gui(int argc, char* argv[])
{
    QApplication app(argc, argv);
    GuiWindow window;
	
    window.show();

    return QApplication::exec();
}
