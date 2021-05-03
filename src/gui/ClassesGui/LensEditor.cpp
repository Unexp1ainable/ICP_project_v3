#include "LensEditor.h"

#include <qgroupbox.h>


LensEditor::LensEditor()
{
	//group_box_ = new QGroupBox(tr("Form layout"));
	auto layout = new QFormLayout;

	// sklon X
	// sklon Y
	// opticka mohutnost
	// vzdialenost od zdroja
	// tlacidla
	layout->addRow(new QLabel(tr("Tilt X:")), new QSpinBox);
	layout->addRow(new QLabel(tr("Tilt Y:")), new QSpinBox);
	layout->addRow(new QLabel(tr("Optical power:")), new QSpinBox);
	layout->addRow(new QLabel(tr("Distance:")), new QSpinBox);
	setLayout(layout);
}
