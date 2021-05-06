#pragma once
#include "Base3D.h"

class Detector3D : public Base3D
{
public:
	/**
	 * @brief Diffuse color used in QDiffuseSpecularMaterial
	 */
	static const QColor diffuse_color_default;

	/**
	 * @brief location of mesh in the filesystem.
	*/
	static const QUrl mesh_location;
	
	/**
	 * @brief Graphical object representing lens
	 *
	 * @param root_entity Root entity of created lens
	 * @param distance Distance from electron gun on Z axis
	 * @param x_tilt Tilt on X axis
	 * @param z_tilt Tilt on Y axis
	 */
	Detector3D(Qt3DCore::QEntity* root_entity, float distance);
};

