#include "main-gui.h"

#include <QGuiApplication>
#include <QOrbitCameraController>
#include <QPhongMaterial>
#include <QPointLight>
#include <Qt3DWindow>
#include <QTorusMesh>
#include <QTransform>
#include "renderObjects.h"
#include <Qt3DRender/QCamera>

int run_gui(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);
    Qt3DExtras::Qt3DWindow view;
    Qt3DCore::QEntity* root_entity = create_scene();

    add_mock_object(root_entity);



    Line{ QVector3D(0.0f,0.0f,0.0f), QVector3D(100.0f,0.0f,0.0f),QColor(255,0,0), root_entity };
    Line{ QVector3D(0.0f,0.0f,0.0f), QVector3D(0.0f,100.0f,0.0f),QColor(0,255,0), root_entity };
    Line{ QVector3D(0.0f,0.0f,0.0f), QVector3D(0.0f,0.0f,100.0f),QColor(0,0,255), root_entity };


    add_camera(view, root_entity);
    view.setRootEntity(root_entity);
    view.show();

    return QGuiApplication::exec();
}

void add_camera(Qt3DExtras::Qt3DWindow& view, Qt3DCore::QEntity* root_entity) {
    Qt3DRender::QCamera* camera = view.camera();
    camera->lens()->setPerspectiveProjection(60.f, static_cast<float>(view.width()) / view.height(), 0.1f, 1000.f);
    camera->setPosition(QVector3D(0.0f, 0.0f, 40.0f));
    camera->setViewCenter(QVector3D(0.0f, 0.0f, 0.0f));

    auto* camera_controller = new Qt3DExtras::QOrbitCameraController(root_entity);
    camera_controller->setCamera(camera);
    camera_controller->setLinearSpeed(-40.0f);
    camera_controller->setLookSpeed(-120.0f);
}


// hello
Qt3DCore::QEntity* light(const QVector3D position, Qt3DCore::QNode* parent)
{
	auto light_entity = new Qt3DCore::QEntity(parent);
	auto* point_light = new Qt3DRender::QPointLight(light_entity);
	auto* light_transform = new Qt3DCore::QTransform(light_entity);
    light_transform->setTranslation(position);
    light_entity->addComponent(point_light);
    light_entity->addComponent(light_transform);

    return light_entity;
}

Qt3DCore::QEntity* create_scene()
{
	const auto result_entity = new Qt3DCore::QEntity;

    light(QVector3D(0.0f, 20.0f, 30.0f), result_entity);
    light(QVector3D(0.0f, 20.0f, -30.0f), result_entity);

    return result_entity;
}

void add_mock_object(Qt3DCore::QEntity* root_entity)
{
	auto torus_entity = new Qt3DCore::QEntity(root_entity);
	auto torus_mesh = new Qt3DExtras::QTorusMesh;
    torus_mesh->setRadius(15.0f);
    torus_mesh->setMinorRadius(6.0f);
    torus_mesh->setSlices(16);
    torus_mesh->setRings(32);

	const auto torus_material = new Qt3DExtras::QPhongMaterial;

	const auto torus_transform = new Qt3DCore::QTransform;

    torus_entity->addComponent(torus_mesh);
    torus_entity->addComponent(torus_material);
    torus_entity->addComponent(torus_transform);
}