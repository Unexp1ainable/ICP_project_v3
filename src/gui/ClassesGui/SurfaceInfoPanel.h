#pragma once
#include <qlabel.h>
#include <QWidget>

#include "rayTracer/Point.h"

class SurfaceInfoPanel : public QWidget
{
public:
	SurfaceInfoPanel(double reference_size);

	void parse_points(std::vector<std::shared_ptr<Point>> points);
	void min_max(std::vector<std::shared_ptr<Point>> points, double& min_x, double& max_x, double& min_y, double& max_y);

	const double r_size;

private:
	QLabel* max_x_;
	QLabel* min_x_;
	QLabel* max_y_;
	QLabel* min_y_;
	QLabel* size_x_;
	QLabel* size_y_;
};

