#pragma once
/**
 * @file Lens3D.h
 * @author Samuel Repka
 * @date 11/05/2021
 * @brief Class representing 3D model of the ray cluster
 *
 * Ray cluster is composed of 1-n rays
 */

#include <memory>
#include <vector>

#include "Ray3D.h"

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

