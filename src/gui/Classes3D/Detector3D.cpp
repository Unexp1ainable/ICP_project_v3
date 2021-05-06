#include "Detector3D.h"

#include <Qt3DRender>
#include <QDiffuseSpecularMaterial>
#include <QTransform>

#include "src/gui/commonGui/Scene.h"


const QColor Detector3D::diffuse_color_default = QColor{ 150,150,150 };
const QUrl Detector3D::mesh_location = QUrl::fromLocalFile("./src/gui/meshes/detector.obj");


Detector3D::Detector3D(Qt3DCore::QEntity* root_entity, const float distance) : Base3D(root_entity, &mesh_location, &diffuse_color_default)
{
    
    transform_->setTranslation(QVector3D(.0f, -distance, .0f)); // -distance
}
