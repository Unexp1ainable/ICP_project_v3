#include "Source3D.h"
#include <QColor>
#include <QDiffuseSpecularMaterial>
#include <qmesh.h>
#include <QTransform>
#include <QUrl>

#include "src/gui/commonGui/Scene.h"


const QColor Source3D::diffuse_color_default = QColor(150,150,150);
const QUrl Source3D::mesh_location = QUrl::fromLocalFile("./src/gui/meshes/source.obj");

Source3D::Source3D(Qt3DCore::QEntity* root_entity)
{
	setParent(root_entity);

    // load mesh
    auto source_mesh = new Qt3DRender::QMesh;
    source_mesh->setSource(mesh_location);

    // create material
    auto material = new Qt3DExtras::QDiffuseSpecularMaterial;
    material->setAmbient(Scene::bg_color);
    material->setDiffuse(diffuse_color_default);

    // create transformation matrix
    auto transform = new Qt3DCore::QTransform;
    transform->setScale3D(QVector3D(1.f, 1.f, 1.f));

    // put it together
    addComponent(source_mesh);
    addComponent(material);
    addComponent(transform);
}
