/**
 * @file Sample.cpp
 * @author Leopold Nemček
 * @date 11/05/2021
 * @brief File definitions of methods from Sample class
 */
#include "Sample.h"

bool Sample::calculate_intersection(std::shared_ptr<Ray> ray, std::shared_ptr<Point> point)
{
	double distance = this->distance_from_source_ - ray->source_distance();

	double posX = ray->positionX() + distance * tan(ray->angleX());
	double posY = ray->positionY() + distance * tan(ray->angleY());

	//rotation
	double rotX = posX * cos(rotation_) - posY * sin(rotation_);
	double rotY = posX * sin(rotation_) + posY * cos(rotation_);

	

	point->x = rotX;
	point->y = rotY;
	point->z = this->distance_from_source_;
	return true;

}
