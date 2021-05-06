#include "RayEngine.h"



int rayEngine::add_lens(double distance_from_source, double radius, double optical_power, std::string name, double deviationX, double deviationY)
{
	if(!position_valid_lens(distance_from_source,0))
	{
		throw invalid_distance();
	}
	
	std::shared_ptr<Lens> lens = std::make_shared<Lens>(distance_from_source, radius, optical_power, lens_id_, deviationX, deviationY, name);
	insert_lens(lens);
	lens_id_++;
	return lens_id_ - 1;
}


void rayEngine::set_lens_distance_from_source(int id, double distance)
{
	if(!position_valid_lens(distance, id))
	{
		throw invalid_distance();
	}

	
	get_lens_by_id(id)->set_distance_from_source(distance);
	std::shared_ptr<Lens> lens = get_lens_by_id(id);
	remove_lens(id);
	insert_lens(lens);
}


void rayEngine::insert_lens(const std::shared_ptr<Lens>& lens)
{
	int i = 0;

	
	
	for(std::vector<std::shared_ptr<Lens>>::iterator it = lenses_.begin(); it != lenses_.end(); it++ , i++)
	{
		if(lenses_[i]->distance_from_source() >= lens->distance_from_source())
		{
			/*if(abs(lenses_[i]->distance_from_source() - lens->distance_from_source()) < 0.09 || abs(lenses_[abs(i-1)]->distance_from_source() - lens->distance_from_source()) < 0.09)
			{
				throw invalid_distance();
			}else*/
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

void rayEngine::remove_lens(int id)
{
	/*if(index > lens_count_ - 1 || index < 0)
	{
		throw out_of_range();
	}*/

	int i = 0;
	for(std::vector<std::shared_ptr<Lens>>::iterator it = lenses_.begin(); it != lenses_.end(); it++, i++)
	{
		if(lenses_[i]->id() == id)
		{
			lenses_.erase(it);
			lens_count_--;
			return;
		}
	}
	
}

std::shared_ptr<Lens> rayEngine::get_lens_by_id(int id)
{
	int i = 0;
	for(std::vector<std::shared_ptr<Lens>>::iterator it = lenses_.begin(); it != lenses_.end(); it++, i++)
	{
		if(lenses_[i]->id() == id)
		{
			return lenses_[i];
		}
	}
	return nullptr;
}


std::shared_ptr<Lens> rayEngine::get_lens_by_index(int index)
{
	if(index >= lens_count_|| index < 0)
	{
		throw out_of_range();
	}
	return lenses_[index];
}


int rayEngine::add_ray(double positionX, double positionY, double angleX, double angleY)
{
	std::shared_ptr<Ray> ray = std::make_shared<Ray>(angleX, angleY, positionX, positionY, 0,ray_id_);
	rays_.push_back(ray);
	ray_id_++;
	ray_count_++;
	return ray_id_ - 1;
}

void rayEngine::remove_ray(int id)
{
	//if(id > ray_id_ || id < 0)
	//{
	//	throw out_of_range();
	//}

	int i = 0;
	for(std::vector<std::shared_ptr<Ray>>::iterator it = rays_.begin(); it != rays_.end(); it++, i++)
	{
		if(rays_[i]->id() == id)
		{
			rays_.erase(it);
			ray_count_--;
			return;
		}
	}
}

std::shared_ptr<Ray> rayEngine::get_ray_by_index(int index)
{
	if(index >= ray_count_ || index < 0)
	{
		throw out_of_range();
	}

	return rays_[index];
}


std::shared_ptr<Ray> rayEngine::get_ray_by_id(int id)
{
	//if(id > ray_count_ || id < 0)
	//{
	//	throw out_of_range();
	//}
	int i = 0;
	for(std::vector<std::shared_ptr<Ray>>::iterator it = rays_.begin(); it != rays_.end(); it++, i++)
	{
		if(rays_[i]->id() == id)
		{
			return rays_[i];
		}
	}
	return nullptr;

	
}

void rayEngine::set_sample_distance_from_source(double distance)
{
	if(!position_valid_sample(distance))
	{
		throw invalid_distance();
	}

	sample_->set_distance_from_source(distance);
}

void rayEngine::set_detector_distance_from_source(double distance)
{
	if(!position_valid_detector(distance))
	{
		throw invalid_distance();
	}

	detector_->set_distance_from_source(distance);
}


bool rayEngine::position_valid_lens(double distance, int id)
{
	/*if(id != 0 && abs(this->get_lens_by_id(id)->distance_from_source() - distance) < 0.001)
	{
		return true;
	}*/
	
	if(distance < MIN_DISTANCE || distance > detector_->distance_from_source() - MIN_DISTANCE || abs(sample_->distance_from_source() - distance) < MIN_DISTANCE)
	{
		return false;
	}
	
	int i = 0;
	for(std::vector<std::shared_ptr<Lens>>::iterator it = lenses_.begin(); it != lenses_.end(); it++, i++)
	{
		if(lenses_[i]->id() != id && abs(lenses_[i]->distance_from_source() - distance) <= MIN_DISTANCE)
		{
			
			return false;
		}
	}
	return true;
}

bool rayEngine::position_valid_sample(double distance)
{
	if(distance < MIN_DISTANCE || distance > detector_->distance_from_source() - MIN_DISTANCE)
	{
		return false;
	}

	int i = 0;
	for(std::vector<std::shared_ptr<Lens>>::iterator it = lenses_.begin(); it != lenses_.end(); it++, i++)
	{
		if(abs(lenses_[i]->distance_from_source() - distance) < MIN_DISTANCE)
		{
			return false;
		}
	}
	return true;
}

bool rayEngine::position_valid_detector(double distance)
{
	if(distance <= 0 || distance - this->sample_->distance_from_source() < MIN_DISTANCE)
	{
		return false;
	}
	return true;
}

void rayEngine::init_rays(double radius, int count)
{
	double _2pi = 4 * acos(0.0);

	double rotation_angle = _2pi / count;

	double x = 0;
	double y = radius;
	add_ray(x, y, 0, 0);
	double rotX = 0;
	double rotY = 0;

	for(int i = 0; i < count - 1; i++)
	{
		rotX = x * cos(rotation_angle) - y * sin(rotation_angle);
		rotY = x * sin(rotation_angle) + y * cos(rotation_angle);
		add_ray(rotX, rotY, 0, 0);
		x = rotX;
		y = rotY;
	}
	
	/*int fraction =(count -1) / 13;
	int inner_layer_count = fraction;
	int middle_layer_count = fraction * 3;
	int outer_layer_count = count - middle_layer_count - inner_layer_count - 1;

	double outer_layer_radius = radius;
	double middle_layer_radius = radius / 3.0;
	double inner_layer_radius = radius / 9.0;

	double inner_layer_angle = _2pi / inner_layer_count;
	double middle_layer_angle = _2pi / middle_layer_count;
	double outer_layer_angle = _2pi / outer_layer_count;*/

	/*add_ray(0, 0, 0, 0);

	double x = 0;
	double y = outer_layer_radius;
	add_ray(x, y, 0, 0);
	double rotX = 0;
	double rotY = 0;

	for(int i = 0; i < outer_layer_count - 1;i++)
	{
		rotX = x * cos(outer_layer_angle) - y * sin(outer_layer_angle);
		rotY = x * sin(outer_layer_angle) + y * cos(outer_layer_angle);
		add_ray(rotX, rotY, 0, 0);
		x = rotX;
		y = rotY;
	}

	x = 0;
	y = middle_layer_radius;
	add_ray(x, y, 0, 0);
	for(int i = 0; i < middle_layer_count - 1; i++)
	{
		rotX = x * cos(middle_layer_angle) - y * sin(middle_layer_angle);
		rotY = x * sin(middle_layer_angle) + y * cos(middle_layer_angle);
		add_ray(rotX, rotY, 0, 0);
		x = rotX;
		y = rotY;
	}

	x = 0;
	y = inner_layer_radius;
	add_ray(x, y, 0, 0);
	for(int i = 0; i < inner_layer_count - 1; i++)
	{
		rotX = x * cos(inner_layer_angle) - y * sin(inner_layer_angle);
		rotY = x * sin(inner_layer_angle) + y * cos(inner_layer_angle);
		add_ray(rotX, rotY, 0, 0);
		x = rotX;
		y = rotY;
	}*/
}



std::vector<std::shared_ptr<RayPath>> rayEngine::pass_rays()
{
	std::vector<std::shared_ptr<RayPath>> vector;
	for(int i = 0; i < ray_count_; i++)
	{
		std::shared_ptr<RayPath> rayPath = std::make_shared<RayPath>();
		auto ray = std::make_shared<Ray>(*rays_[i]);
		
		rayPath->points.push_back(std::make_shared<Point>(ray->postionX(), ray->postionY(), ray->source_distance()));
		
		for(int j = 0; j < lens_count_;j++)
		{
			lenses_[j]->pass_ray(ray);
			rayPath->points.push_back(std::make_shared<Point>(ray->postionX(), ray->postionY(), ray->source_distance()));
		}
		
		vector.push_back(rayPath);
	}

	return vector;
}

void rayEngine::cross_with_border(std::shared_ptr<Ray> ray, std::shared_ptr<Point> point)
{
	double distance = border_distance_ - ray->source_distance();

	point->x = ray->postionX() + distance * tan(ray->angleX());
	point->y = ray->postionY() + distance * tan(ray->angleY());
	point->z = border_distance_;
}
