#include "Sample.h"

void Sample::calculate_intersection(std::shared_ptr<Ray> ray)
{
	double distance = this->distance_from_source_ - ray->source_distance();

	double posX = ray->postionX() + distance * tan(ray->angleX());
	double posY = ray->postionY() + distance * tan(ray->angleY());

	//rotation
	double rotX = posX * cos(rotation) - posY * sin(rotation);
	double rotY = posX * sin(rotation) + posY * cos(rotation);

	if(abs(rotX) > sizeX_/2 || abs(rotY) > sizeY_/2 )
	{
		//MISS
	}
	
}
