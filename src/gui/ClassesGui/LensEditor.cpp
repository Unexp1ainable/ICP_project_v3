#include "LensEditor.h"

#include <qgroupbox.h>
#include <qlineedit.h>
#include <qpushbutton.h>


LensEditor::LensEditor()
{

	auto wrapper_layout = new QVBoxLayout;
	
	auto form_layout = new QFormLayout;

	// name
	name_ = new QLineEdit;
	form_layout->addRow(new QLabel(tr("Name")), name_);
	// tilt X
	tilt_x_ = new QSpinBox;
	form_layout->addRow(new QLabel(tr("Tilt X:")), tilt_x_);
	// tilt Z
	tilt_z_ = new QSpinBox;
	form_layout->addRow(new QLabel(tr("Tilt Y:")), tilt_z_);
	// optical power
	optical_power_ = new QSpinBox;
	form_layout->addRow(new QLabel(tr("Optical power:")), optical_power_);
	// distance from source
	distance_ = new QSpinBox;
	form_layout->addRow(new QLabel(tr("Distance:")), distance_);

	// buttons
	auto button_layout = new QHBoxLayout;
	button_layout->addWidget(new QPushButton{ tr("New") });
	button_layout->addWidget(new QPushButton{ tr("Edit") });
	button_layout->addWidget(new QPushButton{ tr("Delete") });

	wrapper_layout->addLayout(form_layout);
	wrapper_layout->addLayout(button_layout);
	setLayout(wrapper_layout);
}

void LensEditor::load_lens(std::shared_ptr<Lens> lens)
{
	name_->setText(QString::fromStdString(lens->name()));
	tilt_x_->setValue(lens->deviation_x());
	tilt_z_->setValue(lens->deviation_y());
	optical_power_->setValue(lens->optical_power());
	distance_->setValue(lens->distance_from_source());
}

