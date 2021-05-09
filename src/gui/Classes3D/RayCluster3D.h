#pragma once
#include <memory>
#include <vector>

#include "Ray3D.h"
#include "rayTracer/Point.h"

using std::vector;

class RayCluster3D : Qt3DCore::QEntity
{
public:
	RayCluster3D(Qt3DCore::QEntity* parent, vector<vector<std::shared_ptr<Point>>> rays);

private:
	vector<Ray3D*> rays_;
};
