#include "Ray.h"

Ray::Ray(double angleX, double angleY, double positionX, double positionY, double sourceDistance, int id)
{
	if(sourceDistance < 0.1)
	{
		invalid_distance();
	}

	angle_[0] = angleX;
	angle_[1] = angleY;
	position_[0] = positionX;
	position_[1] = positionY;
	source_distance_ = sourceDistance;
	id_ = id;
}

void Ray::set_angleX(double angle)
{
	if(angle == 90.0)
	{
		throw invalid_angle();
	}
	angle_[0] = angle;
}

void Ray::set_angleY(double angle)
{
	if(angle == 90.0)
	{
		throw invalid_angle();
	}

	angle_[1] = angle;
}



