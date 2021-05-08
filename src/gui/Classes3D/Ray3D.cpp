#include "Ray3D.h"

#include <QColor>

Ray3D::Ray3D(Qt3DCore::QEntity* parent, std::vector<std::shared_ptr<Point>> points)
{
	for(unsigned i = 0; i < points.size()-1; i++)
	{
		auto a = new Line3D(toQVector3D(points[i]), toQVector3D(points[i + 1]), QColor(253, 216, 0), this);
		lines_.push_back(a);
	}
	b = new Line3D{ QVector3D{0,0,0}, QVector3D{10,10,10}, QColor{255,255,255}, this };
	setParent(parent);
}

Ray3D::~Ray3D()
{
	b->setEnabled(false);
	for (auto &line : lines_)
	{
		delete line;
	}
}



QVector3D Ray3D::toQVector3D(std::shared_ptr<Point> p)
{
	return QVector3D(p->y, -p->z, p->x);
}
