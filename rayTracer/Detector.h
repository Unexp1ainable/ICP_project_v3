#pragma once

#include "AxisObject.h"
class Detector :
	public Axis_object
{
public:
	Detector()
	{
		distance_from_source_ = 15;
	}
};

