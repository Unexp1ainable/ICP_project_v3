#include "Sample3D.h"

#include <Qt3DRender>
#include <QDiffuseSpecularMaterial>
#include <QTorusMesh>
#include <QTransform>

#include "src/gui/commonGui/Scene.h"


const QColor Sample3D::diffuse_color_default = QColor{ 255,102,0,100 };

const QUrl Sample3D::mesh_location = QUrl::fromLocalFile("./src/gui/meshes/sample.obj");


Sample3D::Sample3D(Qt3DCore::QEntity* root_entity, const float distance) : Base3D(root_entity, &mesh_location, &diffuse_color_default)
{
    transform_->setScale3D(QVector3D(10.f, 10.f, 10.f));
    transform_->setTranslation(QVector3D(.0f, -distance, .0f)); // -distance
}
