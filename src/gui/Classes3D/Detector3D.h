#pragma once
/**
 * @file Detector3D.h
 * @author Samuel Repka
 * @date 11/05/2021
 * @brief Class representing 3D model of the detector
 */

#include "Base3D.h"

/**
 * @brief Model of detector.
 */
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
	 * @param distance Distance from electron gun on Y axis
	 */
	Detector3D(Qt3DCore::QEntity* root_entity, double distance);
};

