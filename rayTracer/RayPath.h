#pragma once

#include <vector>
#include <memory>
#include "Point.h"

class RayPath
{
public:
	RayPath()
	{
		sample_cross = std::make_shared<Point>(0, 0, 0);
		detector_cross = std::make_shared<Point>(0, 0, 0);
	}
	std::vector<std::shared_ptr<Point>> points;
	std::shared_ptr<Point> sample_cross;
	std::shared_ptr<Point> detector_cross;
	
};

