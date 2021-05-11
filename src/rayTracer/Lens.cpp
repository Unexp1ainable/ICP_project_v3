/**
 * @file Lens.cpp
 * @author Leopold Nemček
 * @date 11/05/2021
 * @brief File definitions of methods from Lens class
 */
#include "Lens.h"

#include <utility>


/**
 * @brief Lens constructor
 * @throws invalid_optical_power If optical power is 0
 * @throws invalid_deviation If deviationX or deviationY is pi/2 or more
 * @throws invalid_radius If radius is less than 1
 * @param distance_from_source Distance from source of lens
 * @param radius Radius of lens
 * @param optical_power Optical power  of lens
 * @param id Id of lens
 * @param deviationX X-axis deviation in radians 
 * @param deviationY Y-axis deviation in radians
 * @param name Name of lens
 */
Lens::Lens(double distance_from_source, double radius, double optical_power, int id, double deviationX, double deviationY, std::string name)
{
	double pi2 = PI / 2.0;
	
	if(optical_power == 0)
	{
		throw invalid_optical_power();
	}

	
	if(std::abs(deviationX) >= pi2 || std::abs(deviationY) >= pi2)
	{
		throw invalid_deviation();
	}

	if(radius < 1)
	{
		throw invalid_radius();
	}

	id_ = id;
	distance_from_source_ = distance_from_source;
	radius_ = radius;
	optical_power_ = optical_power;
	focal_length_ = 1.0 / optical_power;
	deviation_[0] = deviationX;
	deviation_[1] = deviationY;
	name_ = std::move(name);
}


void Lens::pass_ray(const std::shared_ptr<Ray>& ray){
	{
		double angles[2] = { 0,0 };
		double positions[2] = { 0,0 };
		double distance_from_source = 0;
		double distances[2] = { 0,0 };
		double const pi2 = acos(0.0);
		double deviated_intersections[2] = {0,0};


		for(int i = 0; i < 2; i++) //Calculation is 2 step process, angle and with axis X is calculated first, then with Y. Next section will be commented only for first step
		{
			int j = !i;
			
			double distance = this->distance_from_source_ - ray->source_distance();


			
			//Calculation of distance added by y-axis deviation
			double intersection_position_j = ray->position(j) + distance * tan(ray->angle(j));
			

			double deviated_intersection_position_j = sin(pi2 + ray->angle(j)) * intersection_position_j / sin(pi2 - ray->angle(j) - this->deviation_[j]);
			
			double deviation_dist_j = deviated_intersection_position_j * cos(pi2 - this->deviation_[j]);//This is the added distance
			

			distance += deviation_dist_j;
			
			double deviated_angle = ray->angle(i) + this->deviation_[i]; //Angle between ray and axis of lens
			

			double intersection_position = ray->position(i) + distance * tan(ray->angle(i)); //Intersection of ray with lens without x axis deviation
			

			double deviated_intersection_position = sin(pi2 + ray->angle(i)) * intersection_position / sin(pi2 - ray->angle(i) - this->deviation_[i]); //Intersection of ray with lens with x axis deviation
			
			deviated_intersections[i] = deviated_intersection_position;


			double focal_angle_tan = deviated_intersection_position / this->focal_length_; //tangent focal angle
			

			double true_intersection_position = deviated_intersection_position * sin(pi2 - this->deviation_[i]); //distance between intersection point and source -> detector axis
			

			double deviation_distance = deviated_intersection_position * cos(pi2 - this->deviation_[i]); //Distance between intersection point and plane of source
			

			double new_angle = atan(tan(deviated_angle) - focal_angle_tan) - this->deviation_[i]; //Formula for calculating angle of ray after passing trough lens
			

			
			positions[i] = true_intersection_position;
			angles[i] = new_angle;
			distance_from_source = this->distance_from_source_ + deviation_distance + deviation_dist_j;
			distances[i] = distance_from_source;
			
		}

		
		
		
		if(sqrt(pow(deviated_intersections[0],2.0) + pow(deviated_intersections[1],2.0)) > radius_){ //check if 
			return;
		}

		if(std::abs(angles[0]) >= pi2){
			angles[0] *= -1;
		}

		if(std::abs(angles[1]) >= pi2){
			angles[1] *= -1;
		}
		ray->set_angleX(angles[0]);
		ray->set_angleY(angles[1]);
		ray->set_positionX(positions[0]);
		ray->set_positionY(positions[1]);
		ray->set_source_distance((distances[0] + distances[1]) / 2.0);

		return;
	}
}

Point Lens::create_normal()
{
	double a = deviation_[0] + PI / 2;
	double b = deviation_[1] + PI / 2;
	double sinb = sin(b);

	double x = sinb * cos(a);
	double y = cos(b);
	double z = sinb * sin(a);

	return Point(x, y, z);
}

