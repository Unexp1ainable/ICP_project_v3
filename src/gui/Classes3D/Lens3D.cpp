#include "Lens3D.h"

#include <Qt3DRender>
#include <QTransform>

#include "src/common/macros.h"
#include "src/gui/commonGui/Scene.h"


const QColor Lens3D::diffuse_color_default = QColor{ 200,200,255,100 };
const QColor Lens3D::diffuse_color_selected = QColor{ 200,255,200,120 };

const QUrl Lens3D::mesh_location = QUrl::fromLocalFile("./src/gui/meshes/lens.obj");


Lens3D::Lens3D(Qt3DCore::QEntity *root_entity, const float distance, float x_tilt, float z_tilt) : Base3D(root_entity, &mesh_location, &diffuse_color_default)
{
    transform_->setScale(LENS_SIZE);
    transform_->setTranslation(QVector3D(.0f, -distance, .0f)); // -distance
    transform_->setRotationX(x_tilt);
    transform_->setRotationZ(z_tilt);
}