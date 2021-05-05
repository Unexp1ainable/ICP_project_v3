#include "LensEditor.h"

#include <qlineedit.h>
#include <qpushbutton.h>

#include "src/gui/common/macros.h"


LensEditor::LensEditor()
{	
	auto wrapper_layout = new QVBoxLayout;
	auto form_layout = new QFormLayout;

	// name
	name_ = new QLineEdit;
	form_layout->addRow(new QLabel(tr("Name")), name_);
	// tilt X
	tilt_x_ = new QDoubleSpinBox;
	form_layout->addRow(new QLabel(tr("Tilt X:")), tilt_x_);
	// tilt Z
	tilt_z_ = new QDoubleSpinBox;
	form_layout->addRow(new QLabel(tr("Tilt Y:")), tilt_z_);
	// optical power
	optical_power_ = new QDoubleSpinBox;
	form_layout->addRow(new QLabel(tr("Optical power:")), optical_power_);
	// distance from source
	distance_ = new QDoubleSpinBox;
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
	button_cancel_ = new QPushButton{ tr("Cancel") };
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



void LensEditor::load_lens(std::shared_ptr<Lens> lens)
{
	name_->setText(QString::fromStdString(lens->name()));
	name_->setDisabled(true);
	
	tilt_x_->setValue(TO_DEGREES(lens->deviation_x()));
	tilt_x_->setDisabled(true);
	
	tilt_z_->setValue(TO_DEGREES(lens->deviation_y()));
	tilt_z_->setDisabled(true);

	optical_power_->setValue(lens->optical_power());
	optical_power_->setDisabled(true);

	distance_->setValue(lens->distance_from_source());
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



void LensEditor::disable_form()
{
	name_->setDisabled(true);
	tilt_x_->setDisabled(true);
	tilt_z_->setDisabled(true);
	optical_power_->setDisabled(true);
	distance_->setDisabled(true);
}

void LensEditor::enable_form()
{
	name_->setDisabled(false);
	tilt_x_->setDisabled(false);
	tilt_z_->setDisabled(false);
	optical_power_->setDisabled(false);
	distance_->setDisabled(false);
}

void LensEditor::primary_buttons()
{
	button_new_->setHidden(false);
	button_edit_->setHidden(false);
	button_delete_->setHidden(false);

	button_save_->setHidden(true);
	button_cancel_->setHidden(true);
}

void LensEditor::secondary_buttons()
{
	button_new_->setHidden(true);
	button_edit_->setHidden(true);
	button_delete_->setHidden(true);

	button_save_->setHidden(false);
	button_cancel_->setHidden(false);
}




void LensEditor::mode_new()
{
	enable_form();
	secondary_buttons();
	
	name_->setText("New lens");
	tilt_x_->setValue(0);
	tilt_z_->setValue(0);
	optical_power_->setValue(1);
	distance_->setValue(10);
}

void LensEditor::mode_edit()
{
	// item are already loaded
	enable_form();
	secondary_buttons();
}

void LensEditor::mode_default()
{
	disable_form();
	primary_buttons();
}

void LensEditor::save_new()
{
	auto p_name = name_->text();
	auto p_x_tilt = tilt_x_->value();
	auto p_y_tilt = tilt_z_->value();
	auto p_distance = distance_->value();
	auto p_optical_power = optical_power_->value();
	
	emit save_lens_signal(p_name, p_x_tilt,p_y_tilt, p_distance, p_optical_power);
}

void LensEditor::delete_old()
{
	
}

void LensEditor::save_edit()
{
	
}
