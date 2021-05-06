#pragma once
#include "Ray.h"


class Axis_object
{

protected:
	
	double distance_from_source_ = 0;

public:
	
	double distance_from_source() const { return distance_from_source_; }

	
	void set_distance_from_source(double distance);


	//exceptions
	class invalid_distance{};
};

