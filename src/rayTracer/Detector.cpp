/**
 * @file Detector.cpp
 * @author Leopold Nemček
 * @date 11/05/2021
 * @brief File containing definition of methods from Detector class
 */

#include "Detector.h"
#include <cmath>



bool Detector::calculate_intersection(std::shared_ptr<Ray> ray, std::shared_ptr<Point> point)
{
	double distance = this->distance_from_source_ - ray->source_distance();

	double posX = ray->positionX() + distance * tan(ray->angleX());
	double posY = ray->positionY() + distance * tan(ray->angleY());


	point->x = posX;
	point->y = posY;
	point->z = distance_from_source_;

	if (std::abs(posX) > sizeX_ / 2.0 || std::abs(posY) > sizeY_ / 2.0)
	{
		return false;
	}

	return true;
}
