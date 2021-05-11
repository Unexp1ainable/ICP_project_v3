#pragma once
/**
 * @file Base3D.h
 * @author Samuel Repka
 * @date 11/05/2021
 * @brief Base class for 3D models of parts of microscope
 */

#include <QDiffuseSpecularMaterial>
#include <QEntity>
#include <QTransform>

/**
 * @brief Base class of 3D microscope parts.
 */
class Base3D : public Qt3DCore::QEntity
{
public:
	/**
	 * Base class of 3D microscope parts
	 * 
	 * @param root_entity Parent entity
	 * @param mesh_location Location of mesh in the filesystem
	 * @param diffuse_color Diffuse color of the material
	 */
	Base3D(Qt3DCore::QEntity* root_entity, const QUrl* mesh_location, const QColor* diffuse_color);

	/**
	 * @brief  tranform_ getter
	 */
	Qt3DCore::QTransform* get_transform() const;

	/**
	 * @brief  material_ getter
	 */
	Qt3DExtras::QDiffuseSpecularMaterial* get_material() const;

protected:
	/**
	 * @brief Transformation component of the entity
	 */
	Qt3DCore::QTransform* transform_;
	
	/**
	 * @brief Material component of the entity
	 */
	Qt3DExtras::QDiffuseSpecularMaterial* material_;
};

