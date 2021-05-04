#pragma once
#include <qformlayout.h>
#include <qgroupbox.h>
#include <qlabel.h>
#include <qspinbox.h>
#include <QWidget>

class LensEditor : public QWidget
{
public:
	LensEditor();
//private:
	QGroupBox* group_box_;
	QFormLayout* layout;
};

