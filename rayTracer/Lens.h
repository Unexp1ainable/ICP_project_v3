#pragma once

#include <cstdlib>
#include "AxisObject.h"
class Lens:
    public Axis_object
{
	
	
private:
	double focal_length_ = 1;
	double optical_power_ = 1;
	double radius_ = 1;
	double deviation_[2] = { 0,0 };
public:
	

	void pass_ray() {}

	Lens(double distanceFromSource, double radius, double opticalPower, double deviationX = 0, double deviationY = 0);

	
	double optical_power() const { return optical_power_; }
	double radius() const { return radius_; }
	double deviation_x() const { return deviation_[0]; }
	double deviation_y() const { return deviation_[1]; }


	void set_optical_power(double opticalPower);
	void set_radius(double radius);
	void set_deviationX(double deviation);
	void set_deviationY(double deviation);
	

	//Exceptions
	class invalid_radius {};
	class invalid_deviation{};
	class invalid_optical_power{};
};



