#pragma once
#include <qformlayout.h>
#include <qgroupbox.h>
#include <qlabel.h>
#include <qpushbutton.h>
#include <qspinbox.h>
#include <QWidget>

#include "rayTracer/Lens.h"

class LensEditor : public QWidget
{
	Q_OBJECT

public:
	LensEditor();

	/**
	 * Load data from lens to editable fields.
	 * 
	 * @param name
	 * @param tilt_x
	 * @param tilt_z
	 * @param o_power
	 * @param distance
	 */
	void load_lens(std::string name, double tilt_x, double tilt_z, double o_power, double distance);

	QPushButton* get_button_new() const;
	QPushButton* get_button_edit() const;
	QPushButton* get_button_delete() const;
	QPushButton* get_button_save() const;
	QPushButton* get_button_cancel() const;

	void disable_form();
	void enable_form();
	void primary_buttons();
	void secondary_buttons();
	
private:
	QGroupBox* group_box_;
	QLineEdit* name_;
	QDoubleSpinBox* tilt_x_;
	QDoubleSpinBox* tilt_z_;
	QDoubleSpinBox* optical_power_;
	QDoubleSpinBox* distance_;

	QPushButton* button_new_;
	QPushButton* button_edit_;
	QPushButton* button_delete_;
	QPushButton* button_save_;
	QPushButton* button_cancel_;

public slots:
	void mode_new();
	void mode_edit();
	void mode_default();
	void save_new();

signals:
	void save_lens_signal(QString name, float x_tilt, float z_tilt, float distance, float optical_power);
};

