#pragma once

#include <vector>
#include <memory>
#include "Lens.h"
#include "Ray.h"
#include "Sample.h"
#include "Detector.h"

class rayEngine
{
private:
	int lens_count_ = 0;
	int lens_id_ = 1;
	int ray_count_ = 0;
	int ray_id_ = 1;
	std::shared_ptr<Sample> sample_;
	std::shared_ptr<Detector> detector_;
	std::vector<std::shared_ptr<Lens>> lenses_;
	std::vector<std::shared_ptr<Ray>> rays_;
	void insert_lens(const std::shared_ptr<Lens>& lens);

public:

	rayEngine()
	{
		sample_ = std::make_shared<Sample>();
		detector_ = std::make_shared<Detector>();
	}
	
	std::shared_ptr<Lens> get_lens_by_index(int index);
	std::shared_ptr<Lens> get_lens_by_id(int id);
	int lens_count() const { return lens_count_; }
	void add_lens(double distance_from_source, double radius, double optical_power, double deviationX = 0, double deviationY = 0);
	void remove_lens(int id);
	void set_lens_distance_from_source(int id, double distance);
	

	std::shared_ptr<Ray> get_ray_by_id(int id);
	std::shared_ptr<Ray> get_ray_by_index(int index);
	int ray_count() const { return ray_count_; }
	void add_ray(double angleX, double angleY, double positionX, double positionY, double source_distance);
	void remove_ray(int id);

	std::shared_ptr<Sample> get_sample() const { return sample_; }
	void set_sample_distance_from_source(double distance);

	std::shared_ptr<Detector> get_detector() const { return detector_; }
	void set_detector_distance_from_source(double distance);
	
	double* pass_rays();

	//exceptions
	class out_of_range{};
	class invalid_distance {};
};

