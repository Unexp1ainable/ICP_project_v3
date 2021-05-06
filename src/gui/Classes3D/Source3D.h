#pragma once
#include "Base3D.h"

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

