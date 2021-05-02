#pragma once
#include "AxisObject.h"
class Lens :
    public AxisObject
{
	
	
private:
	double _focalLength = 0;
	double _opticalPower = 0;
	double _deviation[2] = { 0,0 };
public:
	

	void passRay() {}

	Lens(double distanceFromSource, double radius, double opticalPower, double deviationX = 0, double deviationY = 0);

	
	double opticalPower() const { return _opticalPower; }
	double deviationX() const { return _deviation[0]; }
	double deviationY() const { return _deviation[1]; }

	
	void SetOpticalPower(double opticalPower);
	void SetDeviationX(double deviation);
	void SetDeviationY(double deviation);
};



