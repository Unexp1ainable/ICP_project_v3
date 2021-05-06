#pragma once

#include <vector>
#include <memory>
#include <cmath>
#include "RayPath.h"
#include "Lens.h"
#include "Ray.h"
#include "Sample.h"
#include "Detector.h"

#define MIN_DISTANCE 0.11
#define EDGE_DISTANCE 50

class rayEngine
{
private:
	int lens_count_ = 0;
	double border_distance_ = 50;
	int lens_id_ = 1;
	int ray_count_ = 0;
	int ray_id_ = 1;
	double source_radius_ = 0.5;
	std::shared_ptr<Sample> sample_;
	std::shared_ptr<Detector> detector_;
	std::vector<std::shared_ptr<Lens>> lenses_;
	std::vector<std::shared_ptr<Ray>> rays_;
	void insert_lens(const std::shared_ptr<Lens>& lens);
	void cross_with_border(std::shared_ptr<Ray> ray, std::shared_ptr<Point> point);

public:

	rayEngine(double sample_distance, double detector_distance, double edge_distance)
	{
		if(detector_distance - sample_distance < MIN_DISTANCE || edge_distance - detector_distance < MIN_DISTANCE || edge_distance <= 0)
		{
			throw invalid_distance();
		}
		
		sample_ = std::make_shared<Sample>(sample_distance);
		detector_ = std::make_shared<Detector>(detector_distance);
		border_distance_ = edge_distance;
	}
	
	std::shared_ptr<Lens> get_lens_by_index(int index);
	std::shared_ptr<Lens> get_lens_by_id(int id);
	int lens_count() const { return lens_count_; }
	int add_lens(double distance_from_source, double radius, double optical_power,std::string name ,double deviationX = 0, double deviationY = 0);
	void remove_lens(int id);
	void set_lens_distance_from_source(int id, double distance);
	bool position_valid_lens(double distance, int id);
	void clear_lenses() { lenses_.clear(); }
	
	

	std::shared_ptr<Ray> get_ray_by_id(int id);
	std::shared_ptr<Ray> get_ray_by_index(int index);
	int ray_count() const { return ray_count_; }
	int add_ray(double positionX, double positionY, double angleX, double angleY);
	void remove_ray(int id);
	void init_rays(double radius, int count);
	void clear_rays() { rays_.clear(); }

	std::shared_ptr<Sample> get_sample() const { return sample_; }
	bool position_valid_sample(double distance);
	void set_sample_distance_from_source(double distance);

	std::shared_ptr<Detector> get_detector() const { return detector_; }
	bool position_valid_detector(double distance);
	void set_detector_distance_from_source(double distance);
	
	double edge_distance() const
	{
		return border_distance_;
	}

	void set_edge_distance(double distance)
	{
		if(border_distance_ - detector_->distance_from_source() < MIN_DISTANCE)
		{
			throw invalid_distance();
		}

		border_distance_ = distance;
	}
	
	std::vector<std::shared_ptr<RayPath>> pass_rays();

	//exceptions
	class out_of_range{};
	class invalid_distance {};
};

