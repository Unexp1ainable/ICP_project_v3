#include "LensEditor.h"

#include <qboxlayout.h>
#include <qformlayout.h>
#include <qlabel.h>
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
	tilt_x_ = new QDoubleSpinBox;
	tilt_x_->setRange(-90.0, 90.0);
	form_layout->addRow(new QLabel(tr("Tilt X:")), tilt_x_);
	// tilt Z
	tilt_z_ = new QDoubleSpinBox;
	tilt_z_->setRange(-90.0, 90.0);
	form_layout->addRow(new QLabel(tr("Tilt Y:")), tilt_z_);
	// optical power
	optical_power_ = new QDoubleSpinBox;
	optical_power_->setRange(-1000., 1000.0);
	form_layout->addRow(new QLabel(tr("Optical power:")), optical_power_);
	// distance from source
	distance_ = new QDoubleSpinBox;
	distance_->setRange(.0, 1000.0);
	form_layout->addRow(new QLabel(tr("Distance:")), distance_);

	// buttons
	auto primary_button_layout = new QHBoxLayout;
	button_new_ = new QPushButton{ tr("New") };
	primary_button_layout->addWidget(button_new_);
	button_edit_ = new QPushButton{ tr("Edit") };
	primary_button_layout->addWidget(button_edit_);
	button_delete_ = new QPushButton{ tr("Delete") };
	primary_button_layout->addWidget(button_delete_);

	auto secondary_button_layout = new QHBoxLayout;
	button_save_ = new QPushButton{ tr("Save") };
	primary_button_layout->addWidget(button_save_);
	button_cancel_ = new QPushButton{ tr("Done") };
	primary_button_layout->addWidget(button_cancel_);
	button_save_->setHidden(true);
	button_cancel_->setHidden(true);

	wrapper_layout->addLayout(form_layout);
	wrapper_layout->addLayout(primary_button_layout);
	wrapper_layout->addLayout(secondary_button_layout);
	setLayout(wrapper_layout);

	// connect save new button to slot, so new signal with parameters is emitted
	connect(button_save_, &QPushButton::clicked, this, &LensEditor::save_new);
}



void LensEditor::load_lens(std::string name, double tilt_x, double tilt_z, double o_power, double distance) const
{
	name_->setText(QString::fromStdString(name));
	name_->setDisabled(true);
	
	tilt_x_->setValue(tilt_x);
	tilt_x_->setDisabled(true);
	
	tilt_z_->setValue(tilt_z);
	tilt_z_->setDisabled(true);

	optical_power_->setValue(o_power);
	optical_power_->setDisabled(true);

	distance_->setValue(distance);
	distance_->setDisabled(true);
}


QPushButton* LensEditor::get_button_cancel() const
{
	return button_cancel_;
}

QPushButton* LensEditor::get_button_delete() const
{
	return button_delete_;
}

QPushButton* LensEditor::get_button_edit() const
{
	return button_edit_;
}

QPushButton* LensEditor::get_button_new() const
{
	return button_new_;
}

QPushButton* LensEditor::get_button_save() const
{
	return button_save_;
}



void LensEditor::disable_form() const
{
	name_->setDisabled(true);
	tilt_x_->setDisabled(true);
	tilt_z_->setDisabled(true);
	optical_power_->setDisabled(true);
	distance_->setDisabled(true);
}

void LensEditor::enable_form() const
{
	name_->setDisabled(false);
	tilt_x_->setDisabled(false);
	tilt_z_->setDisabled(false);
	optical_power_->setDisabled(false);
	distance_->setDisabled(false);
}

void LensEditor::primary_buttons() const
{
	button_new_->setHidden(false);
	button_edit_->setHidden(false);
	button_delete_->setHidden(false);

	button_save_->setHidden(true);
	button_cancel_->setHidden(true);
}

void LensEditor::secondary_buttons() const
{
	button_new_->setHidden(true);
	button_edit_->setHidden(true);
	button_delete_->setHidden(true);

	button_save_->setHidden(false);
	button_cancel_->setHidden(false);
}

void LensEditor::mode_new() const
{
	enable_form();
	secondary_buttons();
	
	name_->setText("New lens");
	tilt_x_->setValue(0);
	tilt_z_->setValue(0);
	optical_power_->setValue(1);
	distance_->setValue(10);
}

void LensEditor::mode_edit() const
{
	// items are already loaded
	enable_form();
	secondary_buttons();
}

void LensEditor::mode_default() const
{
	disable_form();
	primary_buttons();

	button_edit_->setDisabled(true);
	button_delete_->setDisabled(true);
}

void LensEditor::save_new()
{
	const auto p_name = name_->text();
	const auto p_x_tilt = tilt_x_->value();
	const auto p_y_tilt = tilt_z_->value();
	const auto p_distance = distance_->value();
	const auto p_optical_power = optical_power_->value();
	
	emit save_lens_signal(p_name, p_x_tilt,p_y_tilt, p_distance, p_optical_power);
}
