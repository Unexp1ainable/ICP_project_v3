#pragma once

#include <memory>
#include <string>
#include <utility>
#include "AxisObject.h"

class Lens:
    public Axis_object
{
	
	
private:
	int id_ = 1;
	double focal_length_ = 1;
	double optical_power_ = 1;
	double radius_ = 1;
	double deviation_[2] = { 0,0 };
	std::string name_ = "Lens";
public:
	
	
	void pass_ray(std::shared_ptr<Ray> ray);

	Lens(double distance_from_source, double radius, double optical_power, int id,double deviationX = 0, double deviationY = 0, std::string name = "Lens");

	
	double optical_power() const { return optical_power_; }
	double radius() const { return radius_; }
	double deviation_x() const { return deviation_[0]; }
	double deviation_y() const { return deviation_[1]; }
	int id() const{ return id_; }
	std::string name() const { return name_; }


	void set_optical_power(double opticalPower) {
		if(opticalPower == 0)
		{
			throw invalid_optical_power();
		}
		optical_power_ = opticalPower;
		focal_length_ = 1.0 / opticalPower;
	}
	
	void set_radius(double radius) {
		if(radius <= 0)
		{
			throw invalid_radius();
		}

		this->radius_ = radius;
	}
	
	void set_deviationX(double deviation) {
		if(abs(deviation) >= acos(0.0))
		{
			throw invalid_deviation();
		}

		deviation_[0] = deviation;
	}
	
	void set_deviationY(double deviation) {
		if(abs(deviation) >= acos(0.0))
		{
			throw invalid_deviation();
		}

		deviation_[1] = deviation;
	}
	
	void set_name(std::string name) {
		name_ = std::move(name);
	}

	//Exceptions
	class invalid_radius {};
	class invalid_deviation{};
	class invalid_optical_power{};
};



