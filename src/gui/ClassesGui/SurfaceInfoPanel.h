#pragma once
#include <qlabel.h>
#include <QWidget>

class SurfaceInfoPanel : public QWidget
{
public:
	SurfaceInfoPanel();

private:
	QWidget* canvas_;
	QLabel* width_;
	QLabel* height_;
};

