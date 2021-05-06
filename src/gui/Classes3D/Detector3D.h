#pragma once
#include <QDiffuseSpecularMaterial>
#include <QTransform>
#include <QEntity>

class Detector3D : public Qt3DCore::QEntity
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
	Detector3D(Qt3DCore::QEntity* root_entity, const float distance);

	/**
	 * @brief transform_ getter
	 */
	Qt3DCore::QTransform* get_transform();

private:
	/**
	 * @brief Transformation component of the entity
	 */
	Qt3DCore::QTransform* transform_;
};

