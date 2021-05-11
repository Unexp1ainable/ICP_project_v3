#pragma once
#include <qlabel.h>
#include <QWidget>

#include "src/rayTracer/Point.h"

/**
 * @brief Panel showing information about passing rays.
 */
class SurfaceInfoPanel : public QWidget
{
public:
	SurfaceInfoPanel(double reference_size);

	/**
	 * @brief Extracts information from the points.
	 * 
	 * @param points Group of 3D points
	 */
	void parse_points(std::vector<std::shared_ptr<Point>> points);
	/**
	 * @brief Determines maximum and minimum in horizontal axes.
	 * 
	 * @param points Group of points
	 * @param min_x Where will minimum in X axis be stored
	 * @param max_x Where will maximum in X axis be stored
	 * @param min_y Where will minimum in Y axis be stored
	 * @param max_y Where will maximum in X axis be stored
	 */
	void min_max(std::vector<std::shared_ptr<Point>> points, double& min_x, double& max_x, double& min_y, double& max_y) const;

	/**
	 * @brief Reference size of item the rays are passing through.
	 */
	const double r_size;

private:
	/**
	 * @brief Label in infopanel.
	 */
	QLabel* max_x_;
	/**
	 * @brief Label in infopanel.
	 */
	QLabel* min_x_;
	/**
	 * @brief Label in infopanel.
	 */
	QLabel* max_y_;
	/**
	 * @brief Label in infopanel.
	 */
	QLabel* min_y_;
	/**
	 * @brief Label in infopanel.
	 */
	QLabel* size_x_;
	/**
	 * @brief Label in infopanel.
	 */
	QLabel* size_y_;
};

