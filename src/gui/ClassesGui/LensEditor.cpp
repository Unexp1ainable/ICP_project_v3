#include "LensEditor.h"

#include <qgroupbox.h>
#include <qlineedit.h>


LensEditor::LensEditor()
{
	layout = new QFormLayout;
	// sklon X
	// sklon Y
	// opticka mohutnost
	// vzdialenost od zdroja
	// tlacidla
	layout->addRow(new QLabel(tr("Name")), new QLineEdit);
	layout->addRow(new QLabel(tr("Tilt X:")), new QSpinBox);
	layout->addRow(new QLabel(tr("Tilt Y:")), new QSpinBox);
	layout->addRow(new QLabel(tr("Optical power:")), new QSpinBox);
	layout->addRow(new QLabel(tr("Distance:")), new QSpinBox);
	setLayout(layout);
}
