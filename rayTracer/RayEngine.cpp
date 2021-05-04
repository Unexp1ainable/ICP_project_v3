#include "RayEngine.h"


void rayEngine::add_lens(double distance_from_source, double radius, double optical_power, double deviationX, double deviationY)
{
	std::shared_ptr<Lens> lens = std::make_shared<Lens>(distance_from_source, radius, optical_power, lens_id_, deviationX, deviationY);
	insert_lens(lens);
	lens_id_++;
}


void rayEngine::set_lens_distance_from_source(int id, double distance)
{
	/*if(index > lens_count_ - 1)
	{
		throw out_of_range();
	}*/

	if(distance >= sample_->distance_from_source())
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
			if(abs(lenses_[i]->distance_from_source() - lens->distance_from_source()) < 0.09 || abs(lenses_[abs(i-1)]->distance_from_source() - lens->distance_from_source()) < 0.09)
			{
				throw invalid_distance();
			}else
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


void rayEngine::add_ray(double angleX, double angleY, double positionX, double positionY, double source_distance)
{
	std::shared_ptr<Ray> ray = std::make_shared<Ray>(angleX, angleY, positionX, positionY, source_distance,ray_id_);
	rays_.push_back(ray);
	ray_id_++;
	ray_count_++;
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
	if(distance <= lenses_[lens_count_ - 1]->distance_from_source() || distance >= detector_->distance_from_source())
	{
		throw invalid_distance();
	}

	sample_->set_distance_from_source(distance);
}

void rayEngine::set_detector_distance_from_source(double distance)
{
	if(distance <= detector_->distance_from_source())
	{
		throw invalid_distance();
	}

	detector_->set_distance_from_source(distance);
}




