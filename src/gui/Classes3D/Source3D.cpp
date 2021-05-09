#include "Source3D.h"
#include <QColor>
#include <QUrl>

#include "src/common/macros.h"


const QColor Source3D::diffuse_color_default = QColor(150,150,150);
const QUrl Source3D::mesh_location = QUrl::fromLocalFile("./src/gui/meshes/source.obj");

Source3D::Source3D(Qt3DCore::QEntity* root_entity) : Base3D(root_entity, &mesh_location, &diffuse_color_default)
{
	transform_->setScale(SOURCE_SIZE);
}
