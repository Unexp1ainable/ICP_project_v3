#pragma once

#include "AxisObject.h"
class Sample :
    public Axis_object
{
private:
	double sizeX_ = 10;
	double sizeY_ = 10;
public:

	Sample()
	{
		distance_from_source_ = 10;
	}
	
	double rotationX = 0;
	double rotationY = 0;

	double positionX = 0;
	double postitionY = 0;

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


	//exceptions
	class invalid_size{};
};

