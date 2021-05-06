#include "SurfaceInfoPanel.h"

#include <qboxlayout.h>

#include "ShapeViewer.h"

SurfaceInfoPanel::SurfaceInfoPanel()
{
	auto main_layout = new QHBoxLayout;

	auto l_layout = new QVBoxLayout;
	canvas_ = new ShapeViewer;
	l_layout->addWidget(canvas_);


	auto r_layout = new QVBoxLayout;
	height_ = new QLabel;
	height_->setText("This is about height.");

	width_ = new QLabel;
	width_->setText("This is about width.");
	r_layout->addWidget(height_);
	r_layout->addWidget(width_);

	main_layout->addLayout(l_layout);
	main_layout->addLayout(r_layout);

	setLayout(main_layout);
}
