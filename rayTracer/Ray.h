#pragma once
class Ray
{
public:
	double angle[2] = { 0,0 };
	double distanceFromAxis[2] = { 0,0 };
	double distanceFromSource = 0;

	void passSystem() {};
};

