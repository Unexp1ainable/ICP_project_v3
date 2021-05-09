#include "Sample3D.h"

#include <Qt3DRender>
#include <QTransform>

#include "src/common/macros.h"
#include "src/gui/commonGui/Scene.h"


const QColor Sample3D::diffuse_color_default = QColor{ 255,102,0,100 };

const QUrl Sample3D::mesh_location = QUrl::fromLocalFile("./src/gui/meshes/sample.obj");


Sample3D::Sample3D(Qt3DCore::QEntity* root_entity, const double distance, const double tilt) : Base3D(root_entity, &mesh_location, &diffuse_color_default)
{
    transform_->setScale(SAMPLE_SIZE);
    transform_->setTranslation(QVector3D(.0f, -distance, .0f)); // -distance
    transform_->setRotationY(tilt);
}
