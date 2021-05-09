#pragma once
#include <memory>
#include <vector>

#include "Line3D.h"
#include "rayTracer/Point.h"

class Ray3D : public Qt3DCore::QEntity
{
public:
	Ray3D(Qt3DCore::QEntity *parent, std::vector<std::shared_ptr<Point>> points);
	/*~Ray3D();*/
	
	QVector3D toQVector3D(std::shared_ptr<Point> p);

private:
	std::vector<Line3D*> lines_;
};

