#pragma once



class AxisObject
{

protected:
	double _radius = 0;
	double _distanceFromSource = 0;

public:
	double radius() const { return _radius; }
	double distanceFromSource() const { return _distanceFromSource; }

	void SetRadius(double radius);
	void SetDistanceFromSource(double distance);
	
};

