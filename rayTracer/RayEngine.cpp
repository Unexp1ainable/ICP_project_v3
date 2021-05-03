#include "RayEngine.h"


void rayEngine::add_lens(double distance_from_source, double radius, double optical_power, double deviationX, double deviationY)
{
	std::shared_ptr<Lens> lens = std::make_shared<Lens>(distance_from_source, radius, optical_power, deviationX, deviationY);
	insert_lens(lens);
}


void rayEngine::set_lens_distance_from_source(int index, double distance)
{
	if(index > lens_count_ - 1)
	{
		throw out_of_range();
	}

	if(distance >= sample_->distance_from_source())
	{
		throw invalid_distance();
	}
	
	lenses_[index]->set_distance_from_source(distance);
	std::shared_ptr<Lens> lens = lenses_[index];
	remove_lens(index);
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

void rayEngine::remove_lens(int index)
{
	if(index > lens_count_ - 1 || index < 0)
	{
		throw out_of_range();
	}

	int i = 0;
	for(std::vector<std::shared_ptr<Lens>>::iterator it = lenses_.begin(); it != lenses_.end(); it++, i++)
	{
		if(i == index)
		{
			lenses_.erase(it);
			lens_count_--;
			return;
		}
	}
	
}

std::shared_ptr<Lens> rayEngine::get_lens(int index)
{
	if(index > lens_count_ - 1 || index < 0)
	{
		throw out_of_range();
	}
	return lenses_[index];
}


void rayEngine::add_ray(double angleX, double angleY, double positionX, double positionY, double source_distance)
{
	std::shared_ptr<Ray> ray = std::make_shared<Ray>(angleX, angleY, positionX, positionY, source_distance,this->ray_count_);
	rays_.push_back(ray);
	ray_count_++;
}

void rayEngine::remove_ray(int index)
{
	if(index > ray_count_ - 1 || index < 0)
	{
		throw out_of_range();
	}

	int i = 0;
	for(std::vector<std::shared_ptr<Ray>>::iterator it = rays_.begin(); it != rays_.end(); it++, i++)
	{
		if(i == index)
		{
			rays_.erase(it);
			ray_count_--;
			return;
		}
	}
}

std::shared_ptr<Ray> rayEngine::get_ray(int index)
{
	if(index > ray_count_ - 1 || index < 0)
	{
		throw out_of_range();
	}
	return rays_[index];
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




