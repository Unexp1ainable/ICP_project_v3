#pragma once
#include <QColor>
#include <QDiffuseSpecularMaterial>
#include <QEntity>
#include <QTransform>
#include <QUrl>

class Base3D : public Qt3DCore::QEntity
{
public:
	Base3D(Qt3DCore::QEntity* root_entity, const QUrl* mesh_l, const QColor* d_color);

	Qt3DCore::QTransform* get_transform();
	Qt3DExtras::QDiffuseSpecularMaterial* get_material();

protected:
	/**
	 * @brief Transformation component of the entity
	 */
	Qt3DCore::QTransform* transform_;
	Qt3DExtras::QDiffuseSpecularMaterial* material_;
};

