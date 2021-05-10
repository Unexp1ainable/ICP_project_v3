#pragma once

#include <memory>
#include "AxisObject.h"
#include <cmath>


/**
 * \brief Detector of simulated microscope
 */
class Detector :
	public Axis_object
{
private:
	double sizeX_ = 10;
	double sizeY_ = 10;
public:
	explicit Detector(double distance)
	{
		distance_from_source_ = distance;
	}

	/*
	 * @brief sizeX_ getter
	 */
	double sizeX() const { return sizeX_; }

	/*
	 * @brief sizeY_ getter
	 */
	double sizeY()const { return sizeY_; }

	/*
	 * @brief sizeX_ setter
	 * @throws invalid_size exception, when size given is 1 or less
	 * @param size Size
	 */
	void set_sizeX(double size)
	{
		if(size < 1)
		{
			throw invalid_size();
		}
		else
		{
			sizeX_ = size;
		}
	}

	/*
	 * @brief sizeY_ setter
	 * @throws invalid_size exception, when size given is 1 or less
	 * @param size Size
	 */
	void set_sizeY(double size)
	{
		if(size <= 1)
		{
			throw invalid_size();
		}
		else
		{
			sizeY_ = size;
		}
	}

	/**
	* @brief Calculates intersection of a given ray and plane of the detector
	* @param ray Used ray
	* @param point Object, that will be filled with coordinates of intersect
	* @return True, if ray hits the detector, false if else
	*/
	bool calculate_intersection(std::shared_ptr<Ray> ray, std::shared_ptr<Point> point);

	//exceptions
	class invalid_size {};
};

