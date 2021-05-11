/**
 * @file SurfaceInfoPanel.cpp
 * @author Samuel Repka
 * @date 11/05/2021
 * @brief Implementation of the SurfaceInfoPanel class
 */

#include "SurfaceInfoPanel.h"

#include <qboxlayout.h>

#include "ShapeViewer.h"

SurfaceInfoPanel::SurfaceInfoPanel(double reference_size) : r_size(reference_size)
{
	auto main_layout = new QGridLayout;

	// headers
	main_layout->addWidget(new QLabel("Min"), 0, 1);
	main_layout->addWidget(new QLabel("Max"), 0, 2);
	main_layout->addWidget(new QLabel("Size"), 0, 3);

	main_layout->addWidget(new QLabel("X:"), 1, 0);
	main_layout->addWidget(new QLabel("Y:"), 2, 0);

	// content
	min_x_ = new QLabel();
	main_layout->addWidget(min_x_, 1, 1);
	max_x_ = new QLabel();
	main_layout->addWidget(max_x_, 1, 2);
	size_x_ = new QLabel();
	main_layout->addWidget(size_x_, 1, 3);

	min_y_ = new QLabel();
	main_layout->addWidget(min_y_, 2, 1);
	max_y_ = new QLabel();
	main_layout->addWidget(max_y_, 2, 2);
	size_y_ = new QLabel();
	main_layout->addWidget(size_y_, 2, 3);


	setLayout(main_layout);
}

void SurfaceInfoPanel::parse_points(std::vector<std::shared_ptr<Point>> points)
{
	double max_x_p;
	double min_x_p;
	double max_y_p;
	double min_y_p;

	min_max(points, min_x_p, max_x_p, min_y_p, max_y_p);

	max_x_->setNum(max_x_p);
	min_x_->setNum(min_x_p);
	size_x_->setNum(max_y_p - min_y_p);
	max_y_->setNum(max_y_p);
	min_y_->setNum(min_y_p);
	size_y_->setNum(max_x_p - min_x_p);
}

void SurfaceInfoPanel::min_max(std::vector<std::shared_ptr<Point>> points, double& min_x, double& max_x, double& min_y, double& max_y) const
{
	if (points.empty())
	{
		min_x = 0.;
		max_x = 0.;
		min_y = 0.;
		max_y = 0.;
		return;
	}
	
	double border = r_size / 2;
	double mn_x = border;
	double mn_y = border;
	double mx_x = -border;
	double mx_y = -border;

	for (auto point : points)
	{
		mn_x = std::min(mn_x, point->x);
		mx_x = std::max(mx_x, point->x);
		mn_y = std::min(mn_y, point->y);
		mx_y = std::max(mx_y, point->y);
	}

	min_x = std::max(mn_x, -border);
	max_x = std::min(mx_x, border);
	min_y = std::max(mn_y, -border);
	max_y = std::min(mx_y, border);
}
