#pragma once
#include "../common/macros.h"

/**
 * @brief Ray
 * Only data about source of ray is stored, everything else is calculated based on this
 */
class Ray
{
private:
	double angle_[2] = { 0,0 };
	double position_[2] = { 0,0 };
	double id_ = 0;
	double source_distance_ = 0;
public:
	
	

	Ray(double angleX, double angleY, double positionX, double positionY, double source_distance, int id) {
		
		
		if(angleX == PI / 2.0 || angleY == PI / 2.0)
		{
			throw invalid_angle();
		}

		
		angle_[0] = angleX;
		angle_[1] = angleY;
		position_[0] = positionX;
		position_[1] = positionY;
		source_distance_ = source_distance;
		id_ = id;
	}

	/**
	 * @brief X or Y coordinates of ray source
	 * @param index Chooses between X and Y coordinate
	 */
	double position(int index) const { return position_[index]; }

	/**
	 * @brief X position of ray source getter
	 */
	double positionX() const { return position_[0]; }

	/**
	 * @brief Y position of ray source getter
	 */
	double positionY() const { return position_[1]; }

	/**
	 * @brief Angle of ray with X or Y axis
	 * @param index Chooses between X and Y coordinate
	 * @return Angle in radians
	 */
	double angle(int index) const { return angle_[index]; }

	/**
	 * @brief Angle with X axis getter
	 * @return Angle in radians
	 */
	double angleX() const { return angle_[0]; }

	/**
	 * @brief Angle with X axis getter
	 * @return Angle in radians
	 */
	double angleY() const { return angle_[1]; }

	/**
	 * @brief Lens id getter
	 */
	double id() const { return id_; }
	double source_distance() const { return source_distance_; }

	/**
	 * @brief Angle with X axis setter
	 * @throws invalid_angle exception when right angle is passed as argument
	 * @param angle Angle in radians
	 */
	void set_angleX(double angle) {
		if(angle == PI / 2.0)
		{
			throw invalid_angle();
		}
		angle_[0] = angle;
	}

	/**
	 * @brief Angle with Y axis setter
	 * @throws invalid_angle when right angle is passed as argument
	 * @param angle Angle in radians
	 */
	void set_angleY(double angle) {
		if(angle == PI / 2.0)
		{
			throw invalid_angle();
		}

		angle_[1] = angle;
	}

	/**
	 * @brief source_distance_ setter
	 * @throws invalid_distance exception when distance is less than 0
	 * @param sourceDistance Distance from source
	 */
	void set_source_distance(double sourceDistance)
	{
		if(sourceDistance < 0)
		{
			throw invalid_distance();
		}
		source_distance_ = sourceDistance;
	}

	/**
	 * @brief X position of source setter
	 * @param position Position
	 */
	void set_positionX(double position){	position_[0] = position; }

	/**
	 * @brief Y position of source setter
	 * @param position Position
	 */
	void set_positionY(double position){	position_[1] = position; }

	

	//Exceptions
	
	class invalid_angle {};
	class invalid_distance {};
};



