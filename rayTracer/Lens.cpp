#include "Lens.h"

Lens::Lens(double distanceFromSource, double radius, double opticalPower, double deviationX, double deviationY)
{
	if(opticalPower == 0)
	{
		throw invalid_optical_power();
	}
	
	if(abs(deviationX) >= 90.0 || abs(deviationY) >= 90.0)
	{
		throw invalid_deviation();
	}

	if(radius <= 0)
	{
		throw invalid_radius();
	}
	
	distance_from_source_ = distanceFromSource;
	radius_ = radius;
	optical_power_ = opticalPower;
	focal_length_ = 1.0 / opticalPower;
	deviation_[0] = deviationX;
	deviation_[1] = deviationY;
}

void Lens::set_radius(double radius)
{
	if(radius <= 0)
	{
		throw invalid_radius();
	}

	this->radius_ = radius;
}

void Lens::set_optical_power(double opticalPower)
{
	if(opticalPower == 0)
	{
		throw invalid_optical_power();
	}
	optical_power_ = opticalPower;
	focal_length_ = 1.0 / opticalPower;
}

void Lens::set_deviationX(double deviation)
{
	if(abs(deviation) >= 90.0)
	{
		throw invalid_deviation();
	}

	deviation_[0] = deviation;
}

void Lens::set_deviationY(double deviation)
{
	if(abs(deviation) >= 90.0)
	{
		throw invalid_deviation();
	}
	
	deviation_[1] = deviation;
}
