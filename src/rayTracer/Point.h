/**
 * @file Point.h
 * @author Leopold Nemček
 * @date 11/05/2021
 * @brief File containing definition of Point class
 */
#pragma once

/**
 * @brief Point with 3 coordinates
 */
class Point
{
	
public:
	Point(double x,double y,double z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
	double x = 0;
	double y = 0;
	double z = 0;
};

