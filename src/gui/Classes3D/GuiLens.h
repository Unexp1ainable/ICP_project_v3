#pragma once
#include <QEntity>

class GuiLens
{
public:
	/**
	 * Diffuse color used in QDiffuseSpecularMaterial
	 */
	static const QColor diffuse_color;

	/**
	 * Graphical object representing lens
	 *
	 * \param root_entity Root entity of created lens
	 * \param distance Distance from electron gun on Z axis
	 * \param x_tilt Tilt on X axis
	 * \param y_tilt Tilt on Y axis
	 */
	GuiLens(Qt3DCore::QEntity* root_entity, float distance, float x_tilt, float y_tilt);
};

