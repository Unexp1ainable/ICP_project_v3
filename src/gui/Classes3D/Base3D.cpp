#include "Base3D.h"

#include <Qt3DRender>
#include <QDiffuseSpecularMaterial>
#include <QTransform>

#include "src/gui/commonGui/Scene.h"


Base3D::Base3D(Qt3DCore::QEntity* root_entity, const QUrl* mesh_l, const QColor* d_color)
{
    setParent(root_entity);

    // load mesh
    auto mesh = new Qt3DRender::QMesh;

    mesh->setSource(*mesh_l);

    // create material
    material_ = new Qt3DExtras::QDiffuseSpecularMaterial;
    material_->setAmbient(Scene::bg_color);
    material_->setDiffuse(*d_color);
    material_->setAlphaBlendingEnabled(true);

    // create transformation matrix
    transform_ = new Qt3DCore::QTransform;

    // put it together
    addComponent(mesh);
    addComponent(material_);
    addComponent(transform_);
}

Qt3DExtras::QDiffuseSpecularMaterial* Base3D::get_material()
{
    return material_;
}

Qt3DCore::QTransform* Base3D::get_transform()
{
    return transform_;
}
