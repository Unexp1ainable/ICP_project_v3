#pragma once
#include <memory>
#include <vector>

#include "Ray3D.h"
#include "rayTracer/Point.h"

using std::vector;

/**
 * @brief Ray cluster model
*/
class RayCluster3D : Qt3DCore::QEntity
{
public:
	RayCluster3D(Qt3DCore::QEntity* parent, vector<vector<std::shared_ptr<Point>>> rays);

private:
	/**
	 * @brief Collection of rays.
	 */
	vector<Ray3D*> rays_;
};

