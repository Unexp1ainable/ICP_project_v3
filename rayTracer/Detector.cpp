#include "Detector.h"



void Detector::calculate_intersection(std::shared_ptr<Ray> ray)
{
	double distance = this->distance_from_source_ - ray->source_distance();

	double posX = ray->postionX() + distance * tan(ray->angleX());
	double posY = ray->postionY() + distance * tan(ray->angleY());

	if(abs(posX) > sizeX_/2.0 || abs(posY) > sizeY_ / 2)
	{
		//MISS
	}
}
