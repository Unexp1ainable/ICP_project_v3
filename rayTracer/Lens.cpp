#include "Lens.h"
#include <iostream>

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
		//std::cout << "\n\nRAY ID : " << ray->id() << std::endl;
		double angles[2] = { 0,0 };
		double positions[2] = { 0,0 };
		double distance_from_source = 0;
		double distances[2] = { 0,0 };
		double const pi2 = acos(0.0);
		
		//Here, I will calculate intersection between ray and lens

		//Equation of lens
		auto normal = create_normal();

		double planeA = normal.x;
		double planeB = normal.y;
		double planeC = normal.z;

		double planeD = -1 * planeC * distance_from_source_;

		//Equations of ray

		//
		double xp = ray->positionX();
		double yp = ray->positionY();
		double zp = ray->source_distance();

		//directional vector of ray will be calculated here
		auto vec = ray->create_directional_vector();
		double xt = vec.x;
		double yt = vec.y;
		double zt = vec.z;

		//Calculation
		double rightSide = -1 * planeD - planeA * xp - planeB * yp - planeC * zp;
		double leftSide = planeA * xt + planeB * yt + planeC * zt;

		double t = rightSide / leftSide;

		//intersections
		double intersectionX = xp + xt * t;
		double intersectionY = yp + yt * t;
		double intersectionZ = zp + zt * t; // this will be source distance of ray

		double intersection_positions[2];
		intersection_positions[0] = sqrt(pow(intersectionZ - this->distance_from_source_,2.0) + pow(intersectionX,2.0));
		intersection_positions[1] = sqrt(pow(intersectionZ - this->distance_from_source_,2.0) + pow(intersectionY,2.0));

		if(intersectionX < 0){
			//std::cout << "RULE 1\n"; 
			intersection_positions[0] *= -1;
		}

		if(intersectionY < 0){
			//std::cout << "RULE 2\n"; 
			intersection_positions[1] *= -1;
		}

		if(intersectionX < 0.000000001 && intersectionX > -0.000000001)
		{
			//std::cout << "RULE 3\n"; 
			intersection_positions[0] = 0;
		}

		if(intersectionY < 0.000000001 && intersectionY > -0.000000001)
		{
			//std::cout << "RULE 4\n"; 
			intersection_positions[1] = 0;
		}

		
		//std::cout << "INTERSECTION POSITION: (" << intersectionX << ";" << intersectionY << ";"<< intersectionZ << ")\n";
		//std::cout << "INTERSECTION POSITIONS[0] = " << intersection_positions[0] << std::endl;
		//std::cout << "INTERSECTION POSITIONS[1] = " << intersection_positions[1] << std::endl;
		
		positions[0] = intersectionX;
		positions[1] = intersectionY;
		distances[0] = intersectionZ;
		distances[1] = intersectionZ;

		for(int i = 0; i < 2; i++)
		{


			double deviated_angle = ray->angle(i) + this->deviation_[i];

			double intersection_position = intersection_positions[i];

			double focal_angle_tan = intersection_position / this->focal_length_; //tangens uhlu stred_sosovky,ohnisko_sosovky,priesecnik (ohniskovy uhol)
			//std::cout << "focal_length_ = " << focal_length_ << std::endl;
			//std::cout << "focal_angle_tan = " << focal_angle_tan << std::endl;

			

			

			double new_angle = atan(tan(deviated_angle) - focal_angle_tan);//tan(novy_uhol) = tan(stary_uhol) - tan(ohniskovy_uhol)
			//std::cout << "new_angle = " << new_angle << std::endl;

			
			//positions[i] = intersection_position;
			angles[i] = new_angle - deviation_[i];
			//distance_from_source = this->distance_from_source_;
			//distances[i] = distance_from_source;
			//std::cout << std::endl << std::endl;
		}


		//std::cout << "\nDISTANCE 1: " << distances[0] << "\nDISTANCE 2: " << distances[1] << std::endl;
		
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

