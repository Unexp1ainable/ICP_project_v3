#include "AxisObject.h"



void Axis_object::set_distance_from_source(double distance)
{
	if(distance <= 0)
	{
		throw invalid_distance();
	}

	this->distance_from_source_ = distance;
}
