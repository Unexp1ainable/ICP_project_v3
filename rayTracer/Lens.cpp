#include "Lens.h"
#include "../src/common/macros.h"


Lens::Lens(double distance_from_source, double radius, double optical_power, int id, double deviationX, double deviationY, std::string name)
{
	double pi2 = PI/2;
	
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
		double intersection_positions[2];
		double const pi2 = PI/2;
		
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

		//Solving equations
		double rightSide = -1 * planeD - planeA * xp - planeB * yp - planeC * zp;
		double leftSide = planeA * xt + planeB * yt + planeC * zt;

		double t = rightSide / leftSide;

		//Intersections
		double intersectionX = xp + xt * t;
		double intersectionY = yp + yt * t;
		double intersectionZ = zp + zt * t; // this will be source distance of ray


		intersection_positions[0] = intersectionX / sin(pi2 - deviation_[0]);
		intersection_positions[1] = intersectionY / sin(pi2 - deviation_[1]);

		if(intersection_positions[0] > radius_ || intersection_positions[1] > radius_){
			return;
		}

		for(int i = 0; i < 2; i++)
		{


			double deviated_angle = ray->angle(i) + deviation_[i];

			double intersection_position = intersection_positions[i];

			double focal_angle_tan = intersection_position / this->focal_length_; //tangens of focal angle

			

			

			double new_angle = atan(tan(deviated_angle) - focal_angle_tan);//Equation for calculating angle of ray passing trough len


			

			angles[i] = new_angle - deviation_[i];

		}


		
		ray->set_angleX(angles[0]);
		ray->set_angleY(angles[1]);
		ray->set_positionX(intersectionX);
		ray->set_positionY(intersectionY);
		ray->set_source_distance(intersectionZ);
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

