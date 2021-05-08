#pragma once
#include <memory>
#include <vector>

#include "Ray3D.h"
#include "rayTracer/Point.h"

using std::vector;

class RayCluster3D : public Qt3DCore::QEntity
{
public:
	RayCluster3D(QEntity* parent, vector<vector<std::shared_ptr<Point>>> rays);

	~RayCluster3D();

	void deleteChildrenRecursively(Qt3DCore::QNode* node);

private:
	vector<Ray3D*> rays_;
};

