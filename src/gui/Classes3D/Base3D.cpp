/**
 * @file Base3D.cpp
 * @author Samuel Repka
 * @date 11/05/2021
 * @brief Implementation of Base3D class
 */


#include "Base3D.h"

#include <Qt3DRender>
#include <QDiffuseSpecularMaterial>
#include <QTransform>

#include "src/gui/commonGui/Scene.h"


Base3D::Base3D(Qt3DCore::QEntity* root_entity, const QUrl* mesh_location, const QColor* diffuse_color)
{
    setParent(root_entity);

    // load mesh
    auto mesh = new Qt3DRender::QMesh;
    mesh->setSource(*mesh_location);

    // create material
    material_ = new Qt3DExtras::QDiffuseSpecularMaterial;
    material_->setAmbient(Scene::bg_color);
    material_->setDiffuse(*diffuse_color);
    material_->setAlphaBlendingEnabled(true);

    // create transformation matrix
    transform_ = new Qt3DCore::QTransform;

    // put it together
    addComponent(mesh);
    addComponent(material_);
    addComponent(transform_);
}

Qt3DExtras::QDiffuseSpecularMaterial* Base3D::get_material() const
{
    return material_;
}

Qt3DCore::QTransform* Base3D::get_transform() const
{
    return transform_;
}
