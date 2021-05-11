#pragma once

#include <memory>
#include <string>
#include <utility>
#include "AxisObject.h"
#include "../common/macros.h"
#include <cmath>

/**
 * @brief Lens of microscope
 */
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
	
	
	/**
	 * @brief Calculates trajectory of ray after passing lens
	 * @param ray Ray to be calculated with
	 */
	void pass_ray(std::shared_ptr<Ray> ray);

	Lens(double distance_from_source, double radius, double optical_power, int id,double deviationX = 0, double deviationY = 0, std::string name = "Lens");

	/**
	 * @brief Calculate normal of the lens
	 * @return Normal vector
	 */
	Point create_normal();

	/**
	 * @brief optical_power_ getter
	 */
	double optical_power() const { return optical_power_; }

	/**
	 * @brief radius_ getter
	 */
	double radius() const { return radius_; }
	
	/**
	 * @brief x-axis deviation getter
	 * @return Deviation in radians
	 */
	double deviation_x() const { return deviation_[0]; }

	/**
	 * @brief y-axis deviation getter
	 * @return Deviation in radians
	 */
	double deviation_y() const { return deviation_[1]; }

	/**
	 * @brief id_ getter
	 */
	int id() const{ return id_; }

	/**
	 * @brief name_ getter
	 */
	std::string name() const { return name_; }

	/**
	 * @brief optical_power_ setter
	 * @throws invalid_optical_power exception if 0 is passed as argument
	 * @param opticalPower Optical power
	 */
	void set_optical_power(double opticalPower) {
		if(opticalPower == 0)
		{
			throw invalid_optical_power();
		}
		optical_power_ = opticalPower;
		focal_length_ = 1.0 / opticalPower;
	}

	/**
	 * @brief radius_ setter
	 * @throws invalid_radius, if radius is 0 or less
	 * @param radius Radius
	 */
	void set_radius(double radius) {
		if(radius <= 0)
		{
			throw invalid_radius();
		}

		this->radius_ = radius;
	}

	/**
	 * @brief x-axis deviation setter
	 * @param deviation X-axis deviation in radians
	 * @throws invalid_deviation When deviation is pi/2 or more
	 */
	void set_deviationX(double deviation) {
		if(std::abs(deviation) >= PI / 2)
		{
			throw invalid_deviation();
		}

		deviation_[0] = deviation;
	}

	/**
	 * @brief y-axis deviation setter
	 * @param deviation Y-axis deviation in radians
	 * @throws invalid_deviation When deviation is pi/2 or more
	 */
	void set_deviationY(double deviation) {
		if(std::abs(deviation) >= PI / 2)
		{
			throw invalid_deviation();
		}

		deviation_[1] = deviation;
	}

	/**
	 * @brief name_ setter
	 * @param name Name
	 */
	void set_name(std::string name) {
		name_ = std::move(name);
	}

	//Exceptions
	class invalid_radius {};
	class invalid_deviation{};
	class invalid_optical_power{};
};



