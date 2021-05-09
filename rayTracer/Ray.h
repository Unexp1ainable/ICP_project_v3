#pragma once

#include "Point.h"

class Ray
{
private:
	double angle_[2] = { 0,0 };
	double position_[2] = { 0,0 };
	double id_ = 0;
	double source_distance_ = 0;
public:
	
	

	Ray(double angleX, double angleY, double positionX, double positionY, double source_distance, int id) {
		if(source_distance < 0.1)
		{
			invalid_distance();
		}

		angle_[0] = angleX;
		angle_[1] = angleY;
		position_[0] = positionX;
		position_[1] = positionY;
		source_distance_ = source_distance;
		id_ = id;
	}
	
	double position(int index) const { return position_[index]; }
	double positionX() const { return position_[0]; }
	double positionY() const { return position_[1]; }
	double angle(int index) const { return angle_[index]; }
	double angleX() const { return angle_[0]; }
	double angleY() const { return angle_[1]; }
	double id() const { return id_; }
	double source_distance() const { return source_distance_; }

	void set_angleX(double angle) {
		if(angle == 90.0)
		{
			throw invalid_angle();
		}
		angle_[0] = angle;
	}
	
	void set_angleY(double angle) {
		if(angle == 90.0)
		{
			throw invalid_angle();
		}

		angle_[1] = angle;
	}
	
	void set_source_distance(double sourceDistance)
	{
		if(sourceDistance < 0)
		{
			throw invalid_distance();
		}
		source_distance_ = sourceDistance;
	}
	void set_positionX(double position){	position_[0] = position; }
	void set_positionY(double position){	position_[1] = position; }

	Point create_directional_vector()
	{
		auto vec = Point(0,0,1);
		return vec;
	}

	//Exceptions
	
	class invalid_angle {};
	class invalid_distance {};
};



