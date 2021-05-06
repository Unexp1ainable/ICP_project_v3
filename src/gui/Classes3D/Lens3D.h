#pragma once
#include <QDiffuseSpecularMaterial>
#include <QEntity>
#include <QTransform>

class Lens3D : public Qt3DCore::QEntity
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

	
	static const QUrl mesh_location;
	/**
	 * Graphical object representing lens
	 *
	 * \param root_entity Root entity of created lens
	 * \param distance Distance from electron gun on Z axis
	 * \param x_tilt Tilt on X axis
	 * \param z_tilt Tilt on Y axis
	 */
	Lens3D(Qt3DCore::QEntity* root_entity, const float distance, float x_tilt, float z_tilt);

	Qt3DCore::QTransform* get_transform();
	Qt3DExtras::QDiffuseSpecularMaterial* get_material();

private:
	Qt3DCore::QTransform *transform_;
	Qt3DExtras::QDiffuseSpecularMaterial* material_;
};

