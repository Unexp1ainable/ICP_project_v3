#pragma once
#include <qformlayout.h>
#include <qgroupbox.h>
#include <qlabel.h>
#include <qspinbox.h>
#include <QWidget>

#include "rayTracer/Lens.h"

class LensEditor : public QWidget
{
public:
	LensEditor();
	void load_lens(std::shared_ptr<Lens> lens);
	
private:
	QGroupBox* group_box_;
	QLineEdit* name_;
	QSpinBox* tilt_x_;
	QSpinBox* tilt_z_;
	QSpinBox* optical_power_;
	QSpinBox* distance_;
};

