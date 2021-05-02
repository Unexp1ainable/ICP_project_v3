#pragma once

#include <vector>
#include <memory>
#include "Lens.h"
#include "Ray.h"

class MicroscopeAxis
{
private:
	int _lensCount = 0;
	int _rayCount = 0;
	std::vector<std::shared_ptr<Lens>> _lenses;
	std::vector<std::shared_ptr<Ray>> _rays;
	void InsertLens(const std::shared_ptr<Lens>& lens);

public:
	const std::shared_ptr<Lens> GetLens(int index);
	int lensCount() const { return _lensCount; }
	void AddLens(double distanceFromSource, double radius, double opticalPower, double deviationX = 0, double deviationY = 0);
	void RemoveLens(int index);
	void ChangeLensDistanceFromSource(int index, double distance);

	const std::shared_ptr<Ray> GetRay(int index);
	int rayCount() const { return _rayCount; }
	void AddRay(double angleX, double angleY, double positionX, double positionY, double sourceDistance);
	void RemoveRay(int index);


	double* PassRays();
};

