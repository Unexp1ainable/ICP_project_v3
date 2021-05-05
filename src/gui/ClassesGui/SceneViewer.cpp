#include "SceneViewer.h"

#include <QCamera>
#include <QForwardRenderer>
#include <QOrbitCameraController>
#include <QPointLight>
#include <QTransform>

#include "src/gui/Classes3D/GuiLens.h"
#include "src/gui/Classes3D/Line.h"
#include "src/gui/common/macros.h"
#include "src/gui/common/Scene.h"


SceneViewer::SceneViewer()
{
	// 3D view
	window_ = new Qt3DExtras::Qt3DWindow;
	window_->defaultFrameGraph()->setClearColor(Scene::bg_color);

	// 3D view as a widget
	window_widget_ = createWindowContainer(window_);
	
	// 3D root entity
	root_entity_ = create_scene();


	// world axes
	Line{ QVector3D(0.0f,0.0f,0.0f), QVector3D(100.0f,0.0f,0.0f),QColor(255,0,0), root_entity_ };
	Line{ QVector3D(0.0f,0.0f,0.0f), QVector3D(0.0f,100.0f,0.0f),QColor(0,255,0), root_entity_ };
	Line{ QVector3D(0.0f,0.0f,0.0f), QVector3D(0.0f,0.0f,100.0f),QColor(0,0,255), root_entity_ };


	add_camera(*window_, root_entity_);
	window_->setRootEntity(root_entity_);
}

Qt3DExtras::Qt3DWindow* SceneViewer::get_window()
{
	return window_;
}

QWidget* SceneViewer::get_window_widget()
{
	return window_widget_;
}



void SceneViewer::add_camera(Qt3DExtras::Qt3DWindow& view, Qt3DCore::QEntity* root_entity) {
	Qt3DRender::QCamera* camera = view.camera();
	camera->lens()->setPerspectiveProjection(60.f, static_cast<float>(view.width()) / view.height(), 0.1f, 1000.f);
	camera->setPosition(QVector3D(0.0f, 0.0f, 40.0f));
	camera->setViewCenter(QVector3D(0.0f, 0.0f, 0.0f));

	auto* camera_controller = new Qt3DExtras::QOrbitCameraController(root_entity);
	camera_controller->setCamera(camera);
	camera_controller->setLinearSpeed(-40.0f);
	camera_controller->setLookSpeed(-120.0f);
}


Qt3DCore::QEntity* SceneViewer::add_light(const QVector3D position, Qt3DCore::QNode* parent)
{
	auto light_entity = new Qt3DCore::QEntity(parent);
	auto* point_light = new Qt3DRender::QPointLight(light_entity);
	auto* light_transform = new Qt3DCore::QTransform(light_entity);
	light_transform->setTranslation(position);
	light_entity->addComponent(point_light);
	light_entity->addComponent(light_transform);

	return light_entity;
}

Qt3DCore::QEntity* SceneViewer::create_scene()
{
	const auto result_entity = new Qt3DCore::QEntity;

	add_light(QVector3D(0.0f, 20.0f, 30.0f), result_entity);
	add_light(QVector3D(0.0f, -20.0f, -30.0f), result_entity);
	add_light(QVector3D(40.0f, -20.0f, -30.0f), result_entity);

	return result_entity;
}

void SceneViewer::add_lens(float distance, float x_tilt, float z_tilt, int id)
{
	auto lens = new GuiLens{ root_entity_, distance,x_tilt, z_tilt };
	lenses_.emplace(id, lens);
}

void SceneViewer::edit_lens(int id, float x_tilt, float z_tilt, float distance)
{
	if (lenses_.find(id) == lenses_.end())
	{
		emit error_signal("3D entity you are trying to edit does not exist.");
	}
	else
	{
		auto entity = lenses_[id];
		auto transform = entity->get_transform();
		transform->setTranslation(QVector3D(0,distance,0));
		transform->setRotationX(x_tilt);
		transform->setRotationZ(z_tilt);
	}
}

void SceneViewer::remove_lens(int id)
{
	auto lens = lenses_[id];
	delete lens;
}
