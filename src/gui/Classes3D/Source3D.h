#pragma once
/**
 * @file Lens3D.h
 * @author Samuel Repka
 * @date 11/05/2021
 * @brief Class representing 3D model of the source
 */

#include "Base3D.h"

/**
 * @brief Source model.
 */
class Source3D : public Base3D
{
	/**
	 * Diffuse color used in QDiffuseSpecularMaterial
	 */
	static const QColor diffuse_color_default;

	/**
	 * @brief location of mesh in the filesystem.
	 */
	static const QUrl mesh_location;

public:
	Source3D(Qt3DCore::QEntity* root_entity);
};

