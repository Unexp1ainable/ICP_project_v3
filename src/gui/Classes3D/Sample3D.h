#pragma once
#include <QDiffuseSpecularMaterial>
#include <QTransform>
#include "Base3D.h"

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
	 * \param root_entity Root entity of created lens
	 * \param distance Distance from electron gun on Y axis
	 */
	Sample3D(Qt3DCore::QEntity* root_entity, const float distance);
};

