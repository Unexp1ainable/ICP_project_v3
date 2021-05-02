#include "Lens.h"

Lens::Lens(double distanceFromSource, double radius, double opticalPower, double deviationX, double deviationY)
{
	if(deviationX == 90.0 || deviationY == 90.0)
	{
		//THROW
	}
	_distanceFromSource = distanceFromSource;
	_radius = radius;
	_opticalPower = opticalPower;
	_focalLength = 1.0 / opticalPower;
	_deviation[0] = deviationX;
	_deviation[1] = deviationY;
}

void Lens::SetOpticalPower(double opticalPower)
{
	_opticalPower = opticalPower;
	_focalLength = 1.0 / opticalPower;
}

void Lens::SetDeviationX(double deviation)
{
	if(deviation == 90.0)
	{
		//THROW
	}

	_deviation[0] = deviation;
}

void Lens::SetDeviationY(double deviation)
{
	if(deviation == 90.0)
	{
		//THROW
	}

	_deviation[1] = deviation;
}
