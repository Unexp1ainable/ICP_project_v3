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
	void load_lens(std::shared_ptr<Lens> lens);

	QPushButton* get_button_new() const;
	QPushButton* get_button_edit() const;
	QPushButton* get_button_delete() const;
	QPushButton* get_button_save() const;
	QPushButton* get_button_cancel() const;
	
private:
	QGroupBox* group_box_;
	QLineEdit* name_;
	QSpinBox* tilt_x_;
	QSpinBox* tilt_z_;
	QSpinBox* optical_power_;
	QSpinBox* distance_;

	QPushButton* button_new_;
	QPushButton* button_edit_;
	QPushButton* button_delete_;
	QPushButton* button_save_;
	QPushButton* button_cancel_;

public slots:
	void mode_new();
	void default_state();
	void save_new();
	void delete_old();
	void save_edit();

signals:
	void create_new_lens(QString name, float x_tilt, float z_tilt, float distance, float optical_power);
};

