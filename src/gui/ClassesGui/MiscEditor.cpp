#include "MiscEditor.h"

#include <qboxlayout.h>
#include <qformlayout.h>
#include <qlabel.h>
#include <qspinbox.h>

MiscEditor::MiscEditor()
{
	auto wrapper_layout = new QVBoxLayout;
	auto form_layout = new QFormLayout;

	// tilt Y
	sample_tilt_y_ = new QDoubleSpinBox;
	form_layout->addRow(new QLabel(tr("Sample tilt Z:")), sample_tilt_y_);
	// distance from source
	sample_distance_ = new QDoubleSpinBox;
	form_layout->addRow(new QLabel(tr("Sample distance:")), sample_distance_);
	// optical power
	detector_distance_ = new QDoubleSpinBox;
	form_layout->addRow(new QLabel(tr("Detector distance:")), detector_distance_);

	// buttons
	auto primary_button_layout = new QHBoxLayout;


	button_edit_ = new QPushButton{ tr("Edit") };
	primary_button_layout->addWidget(button_edit_);

	auto secondary_button_layout = new QHBoxLayout;
	button_save_ = new QPushButton{ tr("Save") };
	secondary_button_layout->addWidget(button_save_);
	button_cancel_ = new QPushButton{ tr("Cancel") };
	secondary_button_layout->addWidget(button_cancel_);

	wrapper_layout->addLayout(form_layout);
	wrapper_layout->addLayout(primary_button_layout);
	wrapper_layout->addLayout(secondary_button_layout);
	setLayout(wrapper_layout);

	default_mode();

	// signal substitution
	connect(button_save_, &QPushButton::clicked, this, &MiscEditor::save_slot);
}

void MiscEditor::edit_mode()
{
	sample_tilt_y_->setDisabled(false);
	sample_distance_->setDisabled(false);
	detector_distance_->setDisabled(false);

	button_save_->setHidden(false);
	button_cancel_->setHidden(false);
	button_edit_->setHidden(true);
}

void MiscEditor::default_mode()
{
	sample_tilt_y_->setDisabled(true);
	sample_distance_->setDisabled(true);
	detector_distance_->setDisabled(true);

	button_save_->setHidden(true);
	button_cancel_->setHidden(true);
	button_edit_->setHidden(false);
}

QPushButton* MiscEditor::get_button_edit_()
{
	return button_edit_;
}

QPushButton* MiscEditor::get_button_save_()
{
	return button_save_;
}
QPushButton* MiscEditor::get_button_cancel_()
{
	return button_cancel_;
}

void MiscEditor::set_configuration(double y_tilt, double distance_s, double distance_d)
{
	sample_tilt_y_->setValue(y_tilt);
	sample_distance_->setValue(distance_s);
	detector_distance_->setValue(distance_d);
}

void MiscEditor::save_slot()
{
	auto s_y = sample_tilt_y_->value();
	auto s_d = sample_distance_->value();
	auto d_d = detector_distance_->value();

	emit edited_signal(s_y, s_d, d_d);
}

