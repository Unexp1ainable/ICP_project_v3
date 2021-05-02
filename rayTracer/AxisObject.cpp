#include "AxisObject.h"

void AxisObject::SetRadius(double radius)
{
	if(radius < 0)
	{
		//THROW
	}

	this->_radius = radius;
}

void AxisObject::SetDistanceFromSource(double distance)
{
	if(distance <= 0)
	{
		//THROW
	}

	this->_distanceFromSource = distance;
}
