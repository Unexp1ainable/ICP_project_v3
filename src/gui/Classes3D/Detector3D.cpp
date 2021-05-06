#include "Detector3D.h"

#include <Qt3DRender>
#include <QDiffuseSpecularMaterial>
#include <QTransform>

#include "src/gui/commonGui/Scene.h"


const QColor Detector3D::diffuse_color_default = QColor{ 150,150,150 };
const QUrl Detector3D::mesh_location = QUrl::fromLocalFile("./src/gui/meshes/detector.obj");


Detector3D::Detector3D(Qt3DCore::QEntity* root_entity, const float distance)
{
    setParent(root_entity);

    // load mesh
    auto sample_mesh = new Qt3DRender::QMesh;
    sample_mesh->setSource(mesh_location);

    // create material
    auto material = new Qt3DExtras::QDiffuseSpecularMaterial;
    material->setAmbient(Scene::bg_color);
    material->setDiffuse(diffuse_color_default);
    material->setAlphaBlendingEnabled(true);

    // create transformation matrix
    transform_ = new Qt3DCore::QTransform;
    transform_->setScale3D(QVector3D(1.f, 1.f, 1.f));
    transform_->setTranslation(QVector3D(.0f, -distance, .0f)); // -distance

    // put it together
    addComponent(sample_mesh);
    addComponent(material);
    addComponent(transform_);
}

Qt3DCore::QTransform* Detector3D::get_transform()
{
    return transform_;
}
