#pragma once
class Ray
{
private:
	double angle_[2] = { 0,0 };
	double position_[2] = { 0,0 };
	double index_ = 0;
	double source_distance_ = 0;
public:
	
	

	Ray(double angleX, double angleY, double positionX, double positionY, double sourceDistance, int index);
	
	double position(int index) const { return position_[index]; }
	double angle(int index) const { return angle_[index]; }
	double index() const { return index_; }
	double source_distance() const { return source_distance_; }

	void set_angleX(double angle);
	void set_angleY(double angle);
	void set_source_distance(double sourceDistance) { source_distance_ = sourceDistance; }
	void set_positionX(double position){	position_[0] = position; }
	void set_positionY(double position){	position_[1] = position; }

	void PassSystem() {}

	//Exceptions
	
	class invalid_angle {};
	class invalid_distance {};
};



