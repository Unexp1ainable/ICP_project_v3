#pragma once

#include <memory>
#include "AxisObject.h"
#include "Point.h"
#include <cmath>
class Sample :
    public Axis_object
{
private:
	double rotation_ = 0;
	double sizeX_ = 10;
	double sizeY_ = 10;
public:
	explicit Sample(double distance)
	{
		distance_from_source_ = distance;
	}


	
	/**
	 * @brief Getter of x-size of sample
	 */
	double sizeX() const { return sizeX_; }

	/**
	 * @brief Getter of y-size of sample
	 */
	double sizeY()const { return sizeY_; }

	/**
	 * @brief Getter of rotation of sample
	 */
	double rotation()const { return rotation_; }

	/**
	 * @brief Setter of rotation of sample
	 * @param rotation New rotation
	 */
	void set_rotation(double rotation)
	{
		this->rotation_ = rotation;
	}

	/**
	 * @brief Setter of x-size of sample
	 * @throws invalid_size If size is less than 1
	 * @param size New size
	 */
	void set_sizeX(double size)
	{
		if(size < 1)
		{
			throw invalid_size();
		}
		sizeX_ = size;
	}

	/**
	 * @brief Setter of y-size of sample
	 * @throws invalid_size If size is less than 1
	 * @param size New size
	 */
	void set_sizeY(double size)
	{
		if(size < 1)
		{
			throw invalid_size();
		}
		sizeY_ = size;
	}

	/**
	 * @brief Calculates intersection of ray and sample
	 * @param ray Ray
	 * @param point Intersection coordinates will be stored here
	 * @returns True if ray intersects with sample, false if not
	 */
	bool calculate_intersection(std::shared_ptr<Ray> ray, std::shared_ptr<Point> point);

	//exceptions
	class invalid_size{};
};






