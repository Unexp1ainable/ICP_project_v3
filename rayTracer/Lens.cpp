#include "Lens.h"
#include <math.h>

#define _USE_MATH_DEFINES

Lens::Lens(double distanceFromSource, double radius, double opticalPower, int id, double deviationX, double deviationY, std::string name)
{
	if(opticalPower == 0)
	{
		throw invalid_optical_power();
	}
	
	if(abs(deviationX) >= 90.0 || abs(deviationY) >= 90.0)
	{
		throw invalid_deviation();
	}

	if(radius <= 0)
	{
		throw invalid_radius();
	}

	id_ = id;
	distance_from_source_ = distanceFromSource;
	radius_ = radius;
	optical_power_ = opticalPower;
	focal_length_ = 1.0 / opticalPower;
	deviation_[0] = deviationX;
	deviation_[1] = deviationY;
	name_ = name;
}

void Lens::set_radius(double radius)
{
	if(radius <= 0)
	{
		throw invalid_radius();
	}

	this->radius_ = radius;
}

void Lens::set_optical_power(double opticalPower)
{
	if(opticalPower == 0)
	{
		throw invalid_optical_power();
	}
	optical_power_ = opticalPower;
	focal_length_ = 1.0 / opticalPower;
}

void Lens::set_deviationX(double deviation)
{
	if(abs(deviation) >= 90.0)
	{
		throw invalid_deviation();
	}

	deviation_[0] = deviation;
}

void Lens::set_deviationY(double deviation)
{
	if(abs(deviation) >= 90.0)
	{
		throw invalid_deviation();
	}
	
	deviation_[1] = deviation;
}


void Lens::pass_ray(std::shared_ptr<Ray> ray){
	{
		double angles[2] = { 0,0 };
		double heights[2] = { 0,0 };
		double distance_from_source = 0;
		double pi = 2 * acos(0.0);

		for(int i = 0; i < 2; i++)
		{
			int j = !i;

			double dist = this->distance_from_source_ - ray->source_distance();

			double intersection_height_j = (ray->position(j) + dist * tan(ray->angle(j))) * sin(pi / 2 + ray->angle(j)) / sin(pi / 2 - ray->angle(j) - this->deviation_[j]);

			double dist_by_deviation_j = intersection_height_j * cos(pi / 2 - this->deviation_[j]);

			dist += dist_by_deviation_j;

			double intersection_height = (ray->position(i) + dist * tan(ray->angle(i))) * sin(pi / 2 + ray->angle(i)) / sin(pi / 2 - ray->angle(i) - this->deviation_[i]);

			if(abs(intersection_height) > this->radius_)
			{
				return;
			}

			double focal_angle_tan = intersection_height / this->focal_length_;

			double angle = ray->angle(i) + this->deviation_[i];

			double beta = atan(tan(angle) - focal_angle_tan) - this->deviation_[i];

			double distance_by_deviation_i = intersection_height * cos(pi / 2 - this->deviation_[i]);

			double ray_distance = ray->source_distance() + dist + distance_by_deviation_i;

			intersection_height = intersection_height * sin(pi / 2 - this->deviation_[i]);

			angles[i] = beta;
			heights[i] = intersection_height;
			distance_from_source = ray_distance;
		}
		ray->set_angleX(angles[0]);
		ray->set_angleY(angles[1]);
		ray->set_source_distance(distance_from_source);
		return;
	}
}

void Lens::set_name(std::string name)
{
	name_ = name;
}
