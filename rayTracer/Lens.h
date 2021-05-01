#pragma once
#include "AxisObject.h"
class Lens :
    public AxisObject
{
	
	
private:
	double focalLength = 0;
public:
	double opticalPower = 0;
	double deviation[2] = { 0,0 };

	void passRay() {}

	Lens(double distanceFromSource, double radius, double opticalPower, double deviationX = 0, double deviationY = 0)
	{
		this->distanceFromSource = distanceFromSource;
		this->radius = radius;
		this->opticalPower = opticalPower;
		this->focalLength = 1.0 / opticalPower;
		this->deviation[0] = deviationX;
		this->deviation[1] = deviationY;
	}

	void ChangeLens(double distanceFromSource, double radius, double opticalPower, double deviationX = 0, double deviationY = 0)
	{
		this->distanceFromSource = distanceFromSource;
		this->radius = radius;
		this->opticalPower = opticalPower;
		this->focalLength = 1.0 / opticalPower;
		this->deviation[0] = deviationX;
		this->deviation[1] = deviationY;
	}
};

