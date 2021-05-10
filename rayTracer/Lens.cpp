#include "Lens.h"


Lens::Lens(double distance_from_source, double radius, double optical_power, int id, double deviationX, double deviationY, std::string name)
{
	double pi2 = acos(0.0);
	
	if(optical_power == 0)
	{
		throw invalid_optical_power();
	}

	
	if(abs(deviationX) >= pi2 || abs(deviationY) >= pi2)
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

			//std::cout << "I = " << i << std::endl;

			int j = !i;
			
			double distance = this->distance_from_source_ - ray->source_distance(); //vzdialenost medzi sosovkou a zdrojom paprsku
			//std::cout << "DISTANCE = " << distance << std::endl;


			//pocitanie pridanej vzdialenosti kvoli vychyleniu sosovky a uhlu paprsku pri pohlade z druhej osi
			double intersection_position_j = ray->position(j) + distance * tan(ray->angle(j)); //priesecnik so sosovkou pri pohlade z druhej osi
			//std::cout << "intersection_position_j = " << intersection_position_j << std::endl;

			double deviated_intersection_position_j = sin(pi2 + ray->angle(j)) * intersection_position_j / sin(pi2 - ray->angle(j) - this->deviation_[j]); //vzdialenost priesecniku paprsku a sosovky od stredu sosovky s ohladom na vychylenie sosovky pri pohlade z druhej osi
			//std::cout << "deviated_intersection_position_j = " << deviated_intersection_position_j << std::endl;

			double deviation_dist_j = deviated_intersection_position_j * cos(pi2 - this->deviation_[j]);
			//std::cout << "deviation_dist_j = " << deviation_dist_j << std::endl;
			//

			distance += deviation_dist_j;
			
			double deviated_angle = ray->angle(i) + this->deviation_[i]; //uhol paprsku s osou sosovky
			//std::cout << "deviated_angle = " << deviated_angle << std::endl;

			double intersection_position = ray->position(i) + distance * tan(ray->angle(i)); //priesecnik na sosovke
			//std::cout << "intersection_position = " << intersection_position << std::endl;

			double deviated_intersection_position = sin(pi2 + ray->angle(i)) * intersection_position / sin(pi2 - ray->angle(i) - this->deviation_[i]); //vzdialenost priesecniku paprsku a sosovky od stredu sosovky s ohladom na vychylenie sosovky, pouzitie sinusove
			//std::cout << "deviated_intersection_position = " << deviated_intersection_position << std::endl;
			deviated_intersections[i] = deviated_intersection_position;


			double focal_angle_tan = deviated_intersection_position / this->focal_length_; //tangens uhlu stred_sosovky,ohnisko_sosovky,priesecnik (ohniskovy uhol)
			//std::cout << "focal_length_ = " << focal_length_ << std::endl;
			//std::cout << "focal_angle_tan = " << focal_angle_tan << std::endl;

			double true_intersection_position = deviated_intersection_position * sin(pi2 - this->deviation_[i]); //vzdialenost priesecniku paprsku a sosovky od osi zdroj->detektor, s ohladom na vychylenie sosovky
			//std::cout << "true_intersection_position = " << true_intersection_position << std::endl;

			double deviation_distance = deviated_intersection_position * cos(pi2 - this->deviation_[i]); //vzdialenost priesecniku paprsku a sosovky od zaciatku osi, ktora vznikla kvoli vychyleniu sosovky
			//std::cout << "deviation_distance = " << deviation_distance << std::endl;

			double new_angle = atan(tan(deviated_angle) - focal_angle_tan) - this->deviation_[i];//tan(novy_uhol) = tan(stary_uhol) - tan(ohniskovy_uhol)
			//std::cout << "new_angle = " << new_angle << std::endl;

			
			positions[i] = true_intersection_position;
			angles[i] = new_angle;
			distance_from_source = this->distance_from_source_ + deviation_distance + deviation_dist_j;
			distances[i] = distance_from_source;
			//std::cout << std::endl << std::endl;
		}


		//std::cout << "\nDISTANCE 1: " << distances[0] << "\nDISTANCE 2: " << distances[1] << std::endl;
		
		if(sqrt(pow(deviated_intersections[0],2.0) + pow(deviated_intersections[1],2.0)) > radius_){
			return;
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

