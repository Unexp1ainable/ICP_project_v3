#include "Sample3D.h"

#include <Qt3DRender>
#include <QDiffuseSpecularMaterial>
#include <QTorusMesh>
#include <QTransform>

#include "src/gui/commonGui/Scene.h"


const QColor Sample3D::diffuse_color_default = QColor{ 255,102,0,100 };

const QUrl Sample3D::mesh_location = QUrl::fromLocalFile("./src/gui/meshes/sample.obj");


Sample3D::Sample3D(Qt3DCore::QEntity* root_entity, const float distance)
{
    setParent(root_entity);
    auto sample_mesh = new Qt3DRender::QMesh;

    // load mesh
    sample_mesh->setSource(mesh_location);

    // create material
    auto material = new Qt3DExtras::QDiffuseSpecularMaterial;
    material->setAmbient(Scene::bg_color);
    material->setDiffuse(diffuse_color_default);
    material->setAlphaBlendingEnabled(true);

    // create transformation matrix
    transform_ = new Qt3DCore::QTransform;
    transform_->setScale3D(QVector3D(10.f, 10.f, 10.f));
    transform_->setTranslation(QVector3D(.0f, -distance, .0f)); // -distance

    // put it together
    addComponent(sample_mesh);
    addComponent(material);
    addComponent(transform_);
}

Qt3DCore::QTransform* Sample3D::get_transform()
{
    return transform_;
}
