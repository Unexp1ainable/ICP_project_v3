#include "GuiLens.h"

#include <Qt3DRender>
#include <QDiffuseSpecularMaterial>
#include <QTorusMesh>
#include <QTransform>

#include "src/gui/common/Scene.h"


const QColor GuiLens::diffuse_color_default = QColor{ 200,200,255,100 };
const QColor GuiLens::diffuse_color_selected = QColor{ 200,255,200,120 };

const QUrl GuiLens::mesh_location = QUrl::fromLocalFile("./src/gui/meshes/cylinder.obj");


GuiLens::GuiLens(Qt3DCore::QEntity *root_entity, const float distance, float x_tilt, float z_tilt)
{
    setParent(root_entity);
    auto lens_mesh = new Qt3DRender::QMesh;

	// load mesh
    lens_mesh->setSource(mesh_location);

	// create material
    material_ = new Qt3DExtras::QDiffuseSpecularMaterial;
    material_->setAmbient(Scene::bg_color);
    material_->setDiffuse(diffuse_color_default);
    material_->setAlphaBlendingEnabled(true);

	// create transformation matrix
    transform_ = new Qt3DCore::QTransform;
    transform_->setScale3D(QVector3D(10.f,10.f,10.f));
    transform_->setTranslation(QVector3D(.0f, distance, .0f));
    transform_->setRotationX(x_tilt);
    transform_->setRotationZ(z_tilt);

	// put it together
    addComponent(lens_mesh);
    addComponent(material_);
    addComponent(transform_);
}

Qt3DCore::QTransform* GuiLens::get_transform()
{
    return transform_;
}

Qt3DExtras::QDiffuseSpecularMaterial* GuiLens::get_material()
{
    return material_;
}
