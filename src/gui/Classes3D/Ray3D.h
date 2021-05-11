#pragma once
#include <memory>
#include <vector>

#include "Line3D.h"
#include "src/rayTracer/Point.h"

/**
 * @brief Ray model
*/
class Ray3D : public Qt3DCore::QEntity
{
public:
	Ray3D(Qt3DCore::QEntity *parent, std::vector<std::shared_ptr<Point>> points);

	/**
	 * @brief Transforms Point to QVector3D.
	 * 
	 * @param p Point to transform
	 * @return Transformed vector
	 */
	QVector3D toQVector3D(std::shared_ptr<Point> p);

private:
	/**
	 * @brief Every line of the ray.
	 */
	std::vector<Line3D*> lines_;
};

