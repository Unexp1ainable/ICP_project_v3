#include "Ray3D.h"

#include <QColor>

Ray3D::Ray3D(Qt3DCore::QEntity* parent, std::vector<std::shared_ptr<Point>> points)
{
	setParent(parent);
	
	for(unsigned i = 0; i < points.size()-1; i++)
	{
		auto a = new Line3D(toQVector3D(points[i]), toQVector3D(points[i + 1]), QColor(253, 216, 0), this);
		lines_.push_back(a);
	}
}


QVector3D Ray3D::toQVector3D(std::shared_ptr<Point> p)
{
	return QVector3D(p->y, -p->z, p->x);
}
