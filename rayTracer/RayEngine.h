#pragma once

#include <vector>
#include <memory>
#include <fstream>
#include "Lens.h"
#include "Sample.h"
#include "Detector.h"

#define MIN_DISTANCE 0.11
#define EDGE_DISTANCE 50

/*
 * @brief Main class of ray-tracing part
 * This class stores all the information about lenses, rays to simulate and other data necessary for simulating electron microscope
 */
class rayEngine
{
private:
	std::vector<std::shared_ptr<Lens>> lenses_;
	int lens_count_ = 0;
	int lens_id_ = 1;
	std::shared_ptr<Lens> get_lens_by_id(int id);

	std::vector<std::shared_ptr<Ray>> rays_;
	int ray_count_ = 0;
	int ray_id_ = 1;
	double ray_cluster_diameter_ = 0;
	std::shared_ptr<Ray> get_ray_by_id(int id);

	std::shared_ptr<Sample> sample_;
	std::shared_ptr<Detector> detector_;

	double border_distance_ = 50;

	std::vector<std::vector<std::shared_ptr<Point>>> ray_points_;
	std::vector<std::shared_ptr<Point>> sample_intersect_;
	std::vector<std::shared_ptr<Point>> detector_intersect_;

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

	std::vector<std::vector<std::shared_ptr<Point>>> get_ray_points()const
	{
		return ray_points_;
	}
	std::vector<std::shared_ptr<Point>> get_sample_intersect()const { return sample_intersect_; }
	std::vector<std::shared_ptr<Point>> get_detector_intersect() const { return detector_intersect_; }


	//lens methods
	
	/*
	 * @brief Getter of distance from source of one of the lenses
	 * @throws id_not_found When no lens has the required id
	 * @param id Id of lens
	 */
	double get_lens_distance_from_source(int id) { return get_lens_by_id(id)->distance_from_source(); }

	/*
	 * @brief Getter of optical power of one of the lenses
	 * @throws id_not_found When no lens has the required id
	 * @param id Id of lens
	 */
	double get_lens_optical_power(int id) { return get_lens_by_id(id)->optical_power(); }

	/*
	 * @brief Getter of radius of one of the lenses
	 * @throws id_not_found When no lens has the required id
	 * @param id Id of lens
	 */
	double get_lens_radius(int id) { return get_lens_by_id(id)->radius(); }

	/*
	 * @brief Getter of x-axis deviation of one of the lenses
	 * @throws id_not_found When no lens has the required id
	 * @param id Id of lens
	 */
	double get_lens_deviation_x(int id) { return get_lens_by_id(id)->deviation_x(); }

	/*
	 * @brief Getter of y-axis deviation of one of the lenses
	 * @throws id_not_found When no lens has the required id
	 * @param id Id of lens
	 */
	double get_lens_deviation_y(int id) { return get_lens_by_id(id)->deviation_y(); }

	/*
	 * @brief Getter of name of one of the lenses
	 * @throws id_not_found When no lens has the required id
	 * @param id Id of lens
	 */
	std::string get_lens_name(int id) { return get_lens_by_id(id)->name(); }

	/*
	 * @brief Setter of distance from source of one of the lenses
	 * @throws id_not_found When no lens has the required id
	 * @throws invalid_distance When distance is invalid - it's too close to other lenses or it's not between source and detector
	 * @param id Id of lens
	 * @param distance Distance from source
	 */
	void set_lens_distance_from_source(int id, double distance);

	/*
	 * @brief Setter of optical of one of the lenses
	 * @throws id_not_found When no lens has the required id
	 * @throws invalid_optical_power When optical power is 0
	 * @param id Id of lens
	 * @param distance Optical power
	 */
	void set_lens_optical_power(int id, double power) { get_lens_by_id(id)->set_optical_power(power); }
	
	/*
	 * @brief Setter of optical of one of the lenses
	 * @throws id_not_found When no lens has the required id
	 * @throws invalid_radius When radius is 0 or less
	 * @param radius Radius
	 */
	void set_lens_radius(int id, double radius)
	{
		auto lens = get_lens_by_id(id);
		if(!check_intersection(lens->distance_from_source(), radius, lens->deviation_x(), lens->deviation_y(), id))
		{
			throw invalid_distance();
		}
		lens->set_radius(radius);
	}
	void set_lens_deviation_x(int id, double deviation)
	{
		auto lens = get_lens_by_id(id);
		if(!check_intersection(lens->distance_from_source(), lens->radius(), deviation, lens->deviation_y(), id))
		{
			throw invalid_distance();
		}
		lens->set_deviationX(deviation);
	}
	void set_lens_deviation_y(int id, double deviation)
	{
		auto lens = get_lens_by_id(id);
		if(!check_intersection(lens->distance_from_source(), lens->radius(), lens->deviation_x(), deviation, id))
		{
			throw invalid_distance();
		}
		lens->set_deviationY(deviation);
	}
	void set_lens_name(int id, std::string name) { get_lens_by_id(id)->set_name(name); }

	int add_lens(double distance_from_source, double radius, double optical_power,std::string name ,double deviationX = 0, double deviationY = 0);
	void remove_lens(int id);

	/**
	 * Calculate normal of the lens from given deviation.
	 * 
	 * @param deviationX x rotation
	 * @param deviationY y rotation
	 * @return Point Normal vector
	 */
	Point create_normal(double deviationX, double deviationY);

	/**
	 * Checks if lens is going to intersect other lens.
	 * 
	 * @param distance_from_source Distance from source
	 * @param radius Radius of the lens
	 * @param deviationX X rotation
	 * @param deviationY Y rotation
	 * @return True if position is good, false otherwise.
	 */
	bool check_intersection(double distance_from_source, double radius, double deviationX, double deviationY, int id);
	bool position_valid_lens(double distance, int id);
	int lens_count() const { return lens_count_; }
	void clear_lenses()
	{
		lens_id_ = 1;
		lens_count_ = 0;
		lenses_.clear();
	}
	
	int lens_index_to_id(int index)
	{
		if(index < 0 || index >= lens_count_)
		{
			throw out_of_range();
		}

		return lenses_[index]->id();
	}

	
	//ray methods
	double get_ray_position_x(int id) { return get_ray_by_id(id)->positionX(); }
	double get_ray_position_y(int id) { return get_ray_by_id(id)->positionY(); }
	double get_ray_angle_x(int id) { return get_ray_by_id(id)->angleX(); }
	double get_ray_angle_y(int id) { return get_ray_by_id(id)->angleY(); }
	double get_ray_source_distance(int id) { return get_ray_by_id(id)->source_distance(); }
	double get_ray_cluster_diameter()const { return ray_cluster_diameter_; }

	void set_ray_position_x(int id, double position) { get_ray_by_id(id)->set_positionX(position); }
	void set_ray_position_y(int id, double position) { get_ray_by_id(id)->set_positionY(position); }
	void set_ray_angle_x(int id, double angle) { get_ray_by_id(id)->set_angleX(angle); }
	void set_ray_angle_y(int id, double angle) { get_ray_by_id(id)->set_angleY(angle); }
	
	int add_ray(double positionX, double positionY, double angleX, double angleY);
	void remove_ray(int id);
	void init_rays(double radius, int count);
	int ray_count() const { return ray_count_; }
	void clear_rays()
	{
		ray_cluster_diameter_ = 0;
		ray_id_ = 1;
		ray_count_ = 0;
		rays_.clear();
	}


	//sample methods
	double get_sample_distance_from_source() const { return sample_->distance_from_source(); }
	double get_sample_size_x() const { return sample_->sizeX(); }
	double get_sample_size_y() const { return sample_->sizeY(); }
	double get_sample_rotation() const { return sample_->rotation(); }

	void set_sample_distance_from_source(double distance);
	void set_sample_size_x(double size) const { sample_->set_sizeX(size); }
	void set_sample_size_y(double size) const { sample_->set_sizeY(size); }
	void set_sample_rotation(double rotation) const { sample_->set_rotation(rotation); }
	
	bool position_valid_sample(double distance);
	

	//detector methods
	double get_detector_distance_from_source() const { return detector_->distance_from_source(); }
	double get_detector_size_x() const { return detector_->sizeX(); }
	double get_detector_size_y() const { return detector_->sizeY(); }

	void set_detector_distance_from_source(double distance);
	void set_detector_size_x(double size) const { detector_->set_sizeX(size); }
	void set_detector_size_y(double size) const { detector_->set_sizeY(size); }
	
	bool position_valid_detector(double distance);
	

	//configuration methods
	void update();
	void save_config(std::string path);
	void load_config(std::string path); 
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

	

	//exceptions
	class out_of_range{};
	class invalid_distance {};
	class file_cannot_be_opened{};
	class invalid_save_file{};
	class id_not_found{};
	
};

