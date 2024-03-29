﻿/**
 * @file RayEngine.cpp
 * @author Leopold Nemček
 * @author Samuel Repka
 * @date 11/05/2021
 * @brief File definitions of methods from RayEngine class
 */
#include "RayEngine.h"

#include "../common/macros.h"
#include <cmath>
#include <sstream>

using std::sin;
using std::cos;
using std::tan;
using std::abs;

#include <algorithm>


Point RayEngine::create_normal(double deviationX, double deviationY)
{
	double a = deviationX + PI / 2;
	double b = deviationY + PI / 2;
	double sinb = sin(b);

	double x = sinb * cos(a);
	double y = cos(b);
	double z = sinb * sin(a);

	return Point(x, y, z);
}

bool RayEngine::check_intersection(double distance_from_source, double radius, double deviationX, double deviationY, int id)
{
	auto vec1 = create_normal(deviationX, deviationY);

	for (auto lens : lenses_)
	{
		if (lens->id() == id)	// skip itself if necessary
			continue;
		
		auto vec2 = create_normal(lens->deviation_x(), lens->deviation_y());
		
		auto dot_product = vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;	// calculate dot_product between normals
		dot_product = (dot_product < -1.) ? -1. : ((dot_product > 1) ? 1. : dot_product);	// clamp if necessary
		auto vec_angle = acos(dot_product);	// angle between normals
		
		if (sin(vec_angle) * radius >= std::abs(distance_from_source - lens->distance_from_source()))
			return false;
	}
	return true;
}

int RayEngine::add_lens(double distance_from_source, double radius, double optical_power, std::string name, double deviationX, double deviationY)
{
	if (!position_valid_lens(distance_from_source, 0) || !check_intersection(distance_from_source, radius, deviationX, deviationY, 0))
	{
		throw invalid_distance();
	}

	std::shared_ptr<Lens> lens = std::make_shared<Lens>(distance_from_source, radius, optical_power, lens_id_, deviationX, deviationY, name);
	insert_lens(lens);
	lens_id_++;
	return lens_id_ - 1;
}


void RayEngine::set_lens_distance_from_source(int id, double distance)
{
	auto lens = get_lens_by_id(id);

	if (!position_valid_lens(distance, id) || !check_intersection(distance, lens->radius(), lens->deviation_x(), lens->deviation_y(), id))
	{
		throw invalid_distance();
	}


	lens->set_distance_from_source(distance);
	
	remove_lens(id);
	insert_lens(lens);
}


void RayEngine::insert_lens(const std::shared_ptr<Lens>& lens)
{
	int i = 0;



	for (std::vector<std::shared_ptr<Lens>>::iterator it = lenses_.begin(); it != lenses_.end(); it++, i++)
	{
		if (lenses_[i]->distance_from_source() >= lens->distance_from_source())
		{
			
			{
				lenses_.insert(it, lens);
				lens_count_++;
				return;
			}
		}
	}
	lenses_.push_back(lens);
	lens_count_++;
}

void RayEngine::remove_lens(int id)
{

	int i = 0;
	for (std::vector<std::shared_ptr<Lens>>::iterator it = lenses_.begin(); it != lenses_.end(); it++, i++)
	{
		if (lenses_[i]->id() == id)
		{
			lenses_.erase(it);
			lens_count_--;
			return;
		}
	}

}

std::shared_ptr<Lens> RayEngine::get_lens_by_id(int id)
{
	int i = 0;
	for (std::vector<std::shared_ptr<Lens>>::iterator it = lenses_.begin(); it != lenses_.end(); it++, i++)
	{
		if (lenses_[i]->id() == id)
		{
			return lenses_[i];
		}
	}
	throw id_not_found();
}





int RayEngine::add_ray(double positionX, double positionY, double angleX, double angleY)
{
	std::shared_ptr<Ray> ray = std::make_shared<Ray>(angleX, angleY, positionX, positionY, 0, ray_id_);
	rays_.push_back(ray);
	ray_id_++;
	ray_count_++;
	return ray_id_ - 1;
}

void RayEngine::remove_ray(int id)
{

	int i = 0;
	for (std::vector<std::shared_ptr<Ray>>::iterator it = rays_.begin(); it != rays_.end(); it++, i++)
	{
		if (rays_[i]->id() == id)
		{
			rays_.erase(it);
			ray_count_--;
			return;
		}
	}
}




std::shared_ptr<Ray> RayEngine::get_ray_by_id(int id)
{

	int i = 0;
	for (std::vector<std::shared_ptr<Ray>>::iterator it = rays_.begin(); it != rays_.end(); it++, i++)
	{
		if (rays_[i]->id() == id)
		{
			return rays_[i];
		}
	}
	throw id_not_found();


}

void RayEngine::set_sample_distance_from_source(double distance)
{
	if (!position_valid_sample(distance))
	{
		throw invalid_distance();
	}

	sample_->set_distance_from_source(distance);
}

void RayEngine::set_detector_distance_from_source(double distance)
{
	if (!position_valid_detector(distance))
	{
		throw invalid_distance();
	}
	detector_->set_distance_from_source(distance);
}


bool RayEngine::position_valid_lens(double distance, int id)
{
	

	if (distance < MIN_DISTANCE || distance > detector_->distance_from_source() - MIN_DISTANCE || std::abs(sample_->distance_from_source() - distance) < MIN_DISTANCE)
	{
		return false;
	}

	int i = 0;
	for (std::vector<std::shared_ptr<Lens>>::iterator it = lenses_.begin(); it != lenses_.end(); it++, i++)
	{
		if (lenses_[i]->id() != id && std::abs(lenses_[i]->distance_from_source() - distance) <= MIN_DISTANCE)
		{

			return false;
		}
	}

	return true;
}

bool RayEngine::position_valid_sample(double distance)
{
	if (distance < MIN_DISTANCE || distance > detector_->distance_from_source() - MIN_DISTANCE)
	{
		return false;
	}

	int i = 0;
	for (std::vector<std::shared_ptr<Lens>>::iterator it = lenses_.begin(); it != lenses_.end(); it++, i++)
	{
		if (std::abs(lenses_[i]->distance_from_source() - distance) < MIN_DISTANCE)
		{
			return false;
		}
	}
	return true;
}

bool RayEngine::position_valid_detector(double distance)
{
	if (distance <= 0 || distance - this->sample_->distance_from_source() < MIN_DISTANCE || distance - lenses_[lens_count_ -1]->distance_from_source() < MIN_DISTANCE)
	{
		return false;
	}
	return true;
}

void RayEngine::init_rays(double radius, int count)
{

	clear_rays();
	ray_cluster_diameter_ = radius * 2;
	double _2pi = 4 * acos(0.0);

	double rotation_angle = _2pi / count;

	double x = 0;
	double y = radius;
	add_ray(x, y, 0, 0);
	double rotX = 0;
	double rotY = 0;

	for (int i = 0; i < count - 1; i++)
	{
		rotX = x * cos(rotation_angle) - y * sin(rotation_angle);
		rotY = x * sin(rotation_angle) + y * cos(rotation_angle);
		add_ray(rotX, rotY, 0, 0);
		x = rotX;
		y = rotY;
	}

}


void RayEngine::update()
{


	ray_points_.clear();
	detector_intersect_.clear();
	sample_intersect_.clear();

	for (int i = 0; i < ray_count_; i++)
	{
		std::vector<std::shared_ptr<Point>> vector;

		auto ray = std::make_shared<Ray>(*rays_[i]);
		vector.push_back(std::make_shared<Point>(ray->positionX(), ray->positionY(), ray->source_distance()));

		for (int j = 0; j < lens_count_; j++)
		{
			if (ray->source_distance() < sample_->distance_from_source() && lenses_[j]->distance_from_source() > sample_->distance_from_source())
			{
				auto point = std::make_shared<Point>(0, 0, 0);
				if (sample_->calculate_intersection(ray, point))
				{
					sample_intersect_.push_back(point);
				}
			}
			lenses_[j]->pass_ray(ray);
			vector.push_back(std::make_shared<Point>(ray->positionX(), ray->positionY(), ray->source_distance()));
		}

		if (ray->source_distance() < sample_->distance_from_source())
		{
			auto point = std::make_shared<Point>(0, 0, 0);
			if (sample_->calculate_intersection(ray, point))
			{
				sample_intersect_.push_back(point);
			}
		}



		std::shared_ptr<Point> last_point = std::make_shared<Point>(0, 0, 0);

		if (detector_->calculate_intersection(ray, last_point)) {
			detector_intersect_.push_back(std::make_shared<Point>(*last_point));
		}
		else
		{
			detector_intersect_.push_back(std::make_shared<Point>(*last_point));
			this->cross_with_border(ray, last_point);
		}

		vector.push_back(last_point);

		ray_points_.push_back(vector);
	}

}

void RayEngine::cross_with_border(std::shared_ptr<Ray> ray, std::shared_ptr<Point> point)
{
	double distance = border_distance_ - ray->source_distance();

	point->x = ray->positionX() + distance * tan(ray->angleX());
	point->y = ray->positionY() + distance * tan(ray->angleY());
	point->z = border_distance_;
}

void RayEngine::save_config(std::string path)
{
	std::string delimeter = ";";

	std::ofstream file(path.c_str());
	


	if (!file.is_open())
	{
		throw file_cannot_be_opened();
	}

	file << "B" << delimeter << border_distance_ << delimeter << std::endl;
	file << "C" << delimeter << ray_cluster_diameter_ << delimeter << std::endl;
	
	
	file << "D" << delimeter << detector_->distance_from_source() << delimeter << detector_->sizeX() << delimeter << detector_->sizeY() << delimeter << std::endl;
	file << "S" << delimeter << sample_->distance_from_source() << delimeter << sample_->sizeX() << delimeter << sample_->sizeY() << delimeter << sample_->rotation() << delimeter << std::endl;


	for(int i = 0; i < lens_count_; i++)
	{
		auto lens = lenses_[i];
		file << "L" << delimeter << lens->distance_from_source() << delimeter << lens->radius() << delimeter << lens->optical_power() << delimeter << lens->deviation_x() << delimeter << lens->deviation_y() << delimeter << lens->name() << delimeter << std::endl;
	}

	for (int i = 0; i < ray_count_; i++)
	{
		auto ray = rays_[i];
		file << "R" << delimeter << ray->positionX() << delimeter << ray->positionY() << ";" << ray->angleX() << delimeter << ray->angleY() << delimeter << std::endl;
	}



	file.close();
}

void RayEngine::load_config(std::string path)
{
	clear_lenses();
	clear_rays();

	std::ifstream file(path.c_str());
	if (!file.is_open())
	{
		throw file_cannot_be_opened();
	}

	std::string line;
	std::string delimeter = ";";
	std::string token;
	std::string identifier;
	int args_count = 0;
	double args[5];



	while (std::getline(file, line))
	{
		identifier = line.substr(0, line.find(delimeter));
		line.erase(0, line.find(delimeter) + delimeter.length());
		if(identifier == "B" || identifier == "C")
		{
			args_count = 1;
		}
		else if(identifier == "D")
		{
			args_count = 3;
		}
		else if (identifier == "S" || identifier == "R")
		{
			args_count = 4;
		}
		else if (identifier == "L")
		{
			args_count = 5;
		}
		else
		{
			throw  invalid_save_file();
		}


		for (int i = 0; i < args_count; i++)
		{
			token = line.substr(0, line.find(delimeter));
			line.erase(0, line.find(delimeter) + delimeter.length());
			std::stringstream(token) >> args[i];
		}

		
		if (identifier == "D")
		{
			try
			{
				detector_->set_distance_from_source(args[0]);
				detector_->set_sizeX(args[1]);
				detector_->set_sizeY(args[2]);
			}
			catch (...)
			{
				throw invalid_save_file();
			}
		}
		else if (identifier == "S")
		{
			try
			{
				set_sample_distance_from_source(args[0]);
				sample_->set_sizeX(args[1]);
				sample_->set_sizeY(args[2]);
				sample_->set_rotation(args[3]);
			}
			catch (...)
			{
				throw invalid_save_file();
			}
		}
		else if (identifier == "L")
		{	try
			{
			add_lens(args[0], args[1], args[2], line.erase(line.find(delimeter)), args[3], args[4]);
			}
			catch (...)
			{
				throw invalid_save_file();
			}
		}
		else if (identifier == "R")
		{
			try
			{
				add_ray(args[0], args[1], args[2], args[3]);
			}
			catch (...)
			{
				throw invalid_save_file();
			}
		}else if(identifier == "B")
		{
			try
			{
				border_distance_ = args[0];
			}
			catch(...)
			{
				
				throw invalid_save_file();
			}
		}else if(identifier == "C")
		{
			try
			{
				ray_cluster_diameter_ = args[0];
			}
			catch(...)
			{
				throw invalid_save_file();
			}
		}

		//
	}

	file.close();
}

