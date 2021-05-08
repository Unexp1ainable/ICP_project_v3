#pragma once

#include "Ray.h"
#include "Point.h"

class Axis_object
{

protected:
	
	double distance_from_source_ = 0;

public:
	
	double distance_from_source() const { return distance_from_source_; }

	
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

