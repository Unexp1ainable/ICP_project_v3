#pragma once
/**
 * @file Lens3D.h
 * @author Samuel Repka
 * @date 11/05/2021
 * @brief Class representing 3D model of the lens
 */

#include "Base3D.h"

/**
 * @brief Lens model
*/
class Lens3D : public Base3D
{
public:
	/**
	 * @brief Default diffuse color used in QDiffuseSpecularMaterial
	 */
	static const QColor diffuse_color_default;
	/**
	 * @brief Diffuse color used if the lens is currently selected
	 */
	static const QColor diffuse_color_selected;

	/**
	 * @brief location of mesh in the filesystem.
	*/
	static const QUrl mesh_location;
	/**
	 * Graphical object representing lens
	 *
	 * \param root_entity Root entity of created lens
	 * \param distance Distance from electron gun on Y axis
	 * \param x_tilt Tilt on X axis
	 * \param z_tilt Tilt on Z axis
	 */
	Lens3D(Qt3DCore::QEntity* root_entity, float distance, float x_tilt, float z_tilt);
};

