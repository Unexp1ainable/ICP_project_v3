#pragma once

#include "Ray.h"
#include "Point.h"


/**
 * @brief Base class for objects on source -> detector axis
 */
class Axis_object
{

protected:
	
	double distance_from_source_ = 0;

public:

	/*
	 *@brief distance_from_source_ getter
	 */
	double distance_from_source() const { return distance_from_source_; }

	
	/*
	 * @brief distance_from_source_ setter
	 * @throws invalid_distance exception, when 0 or negative number is given
	 * @param distance Distance from source
	 */
	void set_distance_from_source(double distance) {
		if(distance <= 0)
		{
			throw invalid_distance();
		}

		this->distance_from_source_ = distance;
	}


	//exceptions
	class invalid_distance{};
};

