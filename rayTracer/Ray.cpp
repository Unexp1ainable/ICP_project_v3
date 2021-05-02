#include "Ray.h"

Ray::Ray(double angleX, double angleY, double positionX, double positionY, double sourceDistance, int index)
{
	if(sourceDistance < 0)
	{
		//THROW
	}

	_angle[0] = angleX;
	_angle[1] = angleY;
	_position[0] = positionX;
	_position[1] = positionY;
	_sourceDistance = sourceDistance;
	_index = index;
}

void Ray::SetAngleX(double angle)
{
	if(angle == 90.0)
	{
		//THROW
	}

	_angle[0] = angle;
}

void Ray::SetAngleY(double angle)
{
	if(angle == 90.0)
	{
		//THROW
	}

	_angle[1] = angle;
}



