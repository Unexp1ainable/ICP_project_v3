#pragma once
class Ray
{
private:
	double _angle[2] = { 0,0 };
	double _position[2] = { 0,0 };
	double _index = 0;
	double _sourceDistance = 0;
public:
	
	

	Ray(double angleX, double angleY, double positionX, double positionY, double sourceDistance, int index);
	
	double position(int index) const { return _position[index]; }
	double angle(int index) const { return _angle[index]; }
	double index() const { return _index; }
	double sourceDistance() const { return _sourceDistance; }

	void SetAngleX(double angle);
	void SetAngleY(double angle);
	void SetSourceDistance(double sourceDistance) { _sourceDistance = sourceDistance; }
	void SetPositionX(double position){	_position[0] = position; }
	void SetPositionY(double position){	_position[1] = position; }


	void PassSystem() {};
};



