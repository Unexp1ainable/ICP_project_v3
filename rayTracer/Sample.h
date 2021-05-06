#pragma once

#include <memory>
#include "AxisObject.h"
#include "Ray.h"
class Sample :
    public Axis_object
{
private:
	double sizeX_ = 10;
	double sizeY_ = 10;
public:

	Sample(double distance)
	{
		distance_from_source_ = distance;
	}
	
	double rotation = 0;

	double sizeX() const { return sizeX_; }
	double sizeY()const { return sizeY_; }

	void set_sizeX(double size)
	{
		if(size <= 1)
		{
			throw invalid_size();
		}else
		{
			sizeX_ = size;
		}
	}

	void set_sizeY(double size)
	{
		if(size <= 1)
		{
			throw invalid_size();
		}else
		{
			sizeY_ = size;
		}
	}

	void calculate_intersection(std::shared_ptr<Ray> ray);

	//exceptions
	class invalid_size{};
};

