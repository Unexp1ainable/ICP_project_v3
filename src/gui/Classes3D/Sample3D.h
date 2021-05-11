#pragma once
/**
 * @file Lens3D.h
 * @author Samuel Repka
 * @date 11/05/2021
 * @brief Class representing 3D model of the sample
 */

#include "Base3D.h"

/**
 * @brief Sample model.
 */
class Sample3D : public Base3D
{
public:
	/**
	 * Diffuse color used in QDiffuseSpecularMaterial
	 */
	static const QColor diffuse_color_default;

	/**
	 * @brief location of mesh in the filesystem.
	 */
	static const QUrl mesh_location;

	/**
	 * Graphical object representing lens
	 *
	 * @param root_entity Root entity of created lens
	 * @param distance Distance from electron gun on Y axis
	 * @param tilt rotation on Y axis
	 */
	Sample3D(Qt3DCore::QEntity* root_entity, double distance, double tilt);
};

