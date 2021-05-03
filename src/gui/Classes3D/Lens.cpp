#include "Lens.h"

#include <Qt3DRender>
#include <QDiffuseSpecularMaterial>
#include <QTorusMesh>
#include <QTransform>

#include "src/gui/common/Scene.h"


const QColor Lens::diffuse_color = QColor{ 200,200,255,100 };


Lens::Lens(Qt3DCore::QEntity *root_entity, const float distance, float x_tilt, float z_tilt)
{
    auto lens_entity = new Qt3DCore::QEntity(root_entity);
    auto lens_mesh = new Qt3DRender::QMesh;

	// load mesh
    const auto url = QUrl::fromLocalFile("./src/gui/meshes/cylinder.obj");
    lens_mesh->setSource(url);

	// create material
    const auto lens_material = new Qt3DExtras::QDiffuseSpecularMaterial;
    lens_material->setAmbient(Scene::bg_color);
    lens_material->setDiffuse(diffuse_color);
    lens_material->setAlphaBlendingEnabled(true);

	// create transformation matrix
    const auto lens_transform = new Qt3DCore::QTransform;
    lens_transform->setScale3D(QVector3D(10.f,10.f,10.f));
    lens_transform->setTranslation(QVector3D(.0f, distance, .0f));
    lens_transform->setRotationX(x_tilt);
    lens_transform->setRotationZ(z_tilt);

	// put it together
    lens_entity->addComponent(lens_mesh);
    lens_entity->addComponent(lens_material);
    lens_entity->addComponent(lens_transform);
}
