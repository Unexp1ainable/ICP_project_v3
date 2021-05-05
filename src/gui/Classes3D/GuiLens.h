#pragma once
#include <QEntity>
#include <QTransform>

class GuiLens : public Qt3DCore::QEntity
{
public:
	/**
	 * Diffuse color used in QDiffuseSpecularMaterial
	 */
	static const QColor diffuse_color;

	static const QUrl mesh_location;
	/**
	 * Graphical object representing lens
	 *
	 * \param root_entity Root entity of created lens
	 * \param distance Distance from electron gun on Z axis
	 * \param x_tilt Tilt on X axis
	 * \param z_tilt Tilt on Y axis
	 */
	GuiLens(Qt3DCore::QEntity* root_entity, const float distance, float x_tilt, float z_tilt);

	Qt3DCore::QTransform *get_transform();

private:
	Qt3DCore::QTransform *transform_;
};

