#include "Detector.h"



bool Detector::calculate_intersection(std::shared_ptr<Ray> ray, std::shared_ptr<Point> point)
{
	double distance = this->distance_from_source_ - ray->source_distance();

	double posX = ray->postionX() + distance * tan(ray->angleX());
	double posY = ray->postionY() + distance * tan(ray->angleY());

	if(abs(posX) > sizeX_/2.0 || abs(posY) > sizeY_ / 2)
	{
		point->x = 0;
		point->y = 0;
		point->z = 0;
		return false;
	}

	point->x = posX;
	point->y = posY;
	point->z = distance_from_source_;
	return true;
}
