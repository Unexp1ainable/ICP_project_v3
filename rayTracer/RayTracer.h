#pragma once
#include <vector>
#include <memory>
#include "Lens.h"

class RayTracer
{
private:
	int axisLength = 0;
	void InsertLens(std::shared_ptr<Lens> lens);
public:
	std::vector<std::shared_ptr<Lens>> lenses;

	void AddLens(double distanceFromSource, double radius, double opticalPower, double deviationX = 0, double deviationY = 0);

	void ChangeLens(int index, double distanceFromSource, double radius, double opticalPower, double deviationX = 0, double deviationY = 0);
	
	double* PassRays();
};

