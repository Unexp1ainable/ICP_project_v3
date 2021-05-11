#include "Lens.h"



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

	if(radius <= 0)
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
	name_ = name;
}


void Lens::pass_ray(std::shared_ptr<Ray> ray){
	{
		double angles[2] = { 0,0 };
		double positions[2] = { 0,0 };
		double distance_from_source = 0;
		double distances[2] = { 0,0 };
		double const pi2 = acos(0.0);
		double deviated_intersections[2] = {0,0};


		for(int i = 0; i < 2; i++) //najprv sa spocita prienik paprsku po osi X, potom po osi Y
		{

			

			int j = !i;
			
			double distance = this->distance_from_source_ - ray->source_distance(); //vzdialenost medzi sosovkou a zdrojom paprsku


			//pocitanie pridanej vzdialenosti kvoli vychyleniu sosovky a uhlu paprsku pri pohlade z druhej osi
			double intersection_position_j = ray->position(j) + distance * tan(ray->angle(j)); //priesecnik so sosovkou pri pohlade z druhej osi
			

			double deviated_intersection_position_j = sin(pi2 + ray->angle(j)) * intersection_position_j / sin(pi2 - ray->angle(j) - this->deviation_[j]); //vzdialenost priesecniku paprsku a sosovky od stredu sosovky s ohladom na vychylenie sosovky pri pohlade z druhej osi
			
			double deviation_dist_j = deviated_intersection_position_j * cos(pi2 - this->deviation_[j]);
			

			distance += deviation_dist_j;
			
			double deviated_angle = ray->angle(i) + this->deviation_[i]; //uhol paprsku s osou sosovky
			

			double intersection_position = ray->position(i) + distance * tan(ray->angle(i)); //priesecnik na sosovke
			

			double deviated_intersection_position = sin(pi2 + ray->angle(i)) * intersection_position / sin(pi2 - ray->angle(i) - this->deviation_[i]); //vzdialenost priesecniku paprsku a sosovky od stredu sosovky s ohladom na vychylenie sosovky, pouzitie sinusove
			
			deviated_intersections[i] = deviated_intersection_position;


			double focal_angle_tan = deviated_intersection_position / this->focal_length_; //tangens uhlu stred_sosovky,ohnisko_sosovky,priesecnik (ohniskovy uhol)
			

			double true_intersection_position = deviated_intersection_position * sin(pi2 - this->deviation_[i]); //vzdialenost priesecniku paprsku a sosovky od osi zdroj->detektor, s ohladom na vychylenie sosovky
			

			double deviation_distance = deviated_intersection_position * cos(pi2 - this->deviation_[i]); //vzdialenost priesecniku paprsku a sosovky od zaciatku osi, ktora vznikla kvoli vychyleniu sosovky
			

			double new_angle = atan(tan(deviated_angle) - focal_angle_tan) - this->deviation_[i];//tan(novy_uhol) = tan(stary_uhol) - tan(ohniskovy_uhol)
			

			
			positions[i] = true_intersection_position;
			angles[i] = new_angle;
			distance_from_source = this->distance_from_source_ + deviation_distance + deviation_dist_j;
			distances[i] = distance_from_source;
			
		}

		
		
		
		if(sqrt(pow(deviated_intersections[0],2.0) + pow(deviated_intersections[1],2.0)) > radius_){
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

