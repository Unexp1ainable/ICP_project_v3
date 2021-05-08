#include "SceneViewer.h"

#include <QCamera>
#include <QForwardRenderer>
#include <QOrbitCameraController>
#include <QPointLight>
#include <QTransform>

#include "src/gui/Classes3D/Lens3D.h"
#include "src/gui/Classes3D/Line3D.h"
#include "src/gui/Classes3D/Source3D.h"
#include "src/common/macros.h"
#include "src/gui/Classes3D/Detector3D.h"
#include "src/gui/Classes3D/Sample3D.h"
#include "src/gui/commonGui/Scene.h"


SceneViewer::SceneViewer(float s_distance, float s_tilt, float d_distance)
{
	// 3D view
	window_ = new Qt3DExtras::Qt3DWindow;
	window_->defaultFrameGraph()->setClearColor(Scene::bg_color);

	// 3D view as a widget
	window_widget_ = createWindowContainer(window_);
	
	// 3D root entity
	root_entity_ = create_scene(s_distance, s_tilt, d_distance);


	// world axes
	Line3D{ QVector3D(0.0f,0.0f,0.0f), QVector3D(100.0f,0.0f,0.0f),QColor(255,0,0), root_entity_ };
	Line3D{ QVector3D(0.0f,0.0f,0.0f), QVector3D(0.0f,100.0f,0.0f),QColor(0,255,0), root_entity_ };
	Line3D{ QVector3D(0.0f,0.0f,0.0f), QVector3D(0.0f,0.0f,100.0f),QColor(0,0,255), root_entity_ };


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

Sample3D* SceneViewer::get_sample()
{
	return sample_;
}

Source3D* SceneViewer::get_source()
{
	return source_;
}

Detector3D* SceneViewer::get_detector()
{
	return detector_;
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

Qt3DCore::QEntity* SceneViewer::create_scene(float s_distance, float s_tilt, float d_distance)
{
	const auto result_entity = new Qt3DCore::QEntity;

	// lights
	add_light(QVector3D(0.0f, 20.0f, 30.0f), result_entity);
	add_light(QVector3D(0.0f, -20.0f, -30.0f), result_entity);
	add_light(QVector3D(40.0f, -20.0f, -30.0f), result_entity);

	// electron source
	source_ = new Source3D{ result_entity };

	// sample
	sample_ = new Sample3D{ result_entity, s_distance, s_tilt}; // placeholder value, will be changed on global init

	//
	detector_ = new Detector3D{ result_entity, d_distance }; // TODO ^ < magic numbers
	
	return result_entity;
}

void SceneViewer::add_lens(float distance, float x_tilt, float z_tilt, int id)
{
	auto lens = new Lens3D{ root_entity_, distance,x_tilt, z_tilt };
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
		transform->setTranslation(QVector3D(0,-distance,0));	// -distance, because I think that rays should go down
		transform->setRotationX(x_tilt);
		transform->setRotationZ(z_tilt);
	}
}

void SceneViewer::remove_lens(int id)
{
	auto lens = lenses_[id];
	delete lens;
}

void SceneViewer::set_active(int id)
{
	if (active_lens_ != nullptr)
	{
		active_lens_->get_material()->setDiffuse(Lens3D::diffuse_color_default);
		active_lens_ = nullptr;
	}
	
	if (id != 0)
	{
		auto lens = lenses_[id];
		lens->get_material()->setDiffuse(Lens3D::diffuse_color_selected);
		active_lens_ = lens;
	}
}

void SceneViewer::edit_sample(float distance, float tilt_y)
{
	auto transform = sample_->get_transform();
	transform->setTranslation(QVector3D(0., -distance, 0.)); //-distance
	transform->setRotationY(tilt_y);
}

void SceneViewer::edit_detector(float distance)
{
	detector_->get_transform()->setTranslation(QVector3D(0., -distance, 0.)); // -distance
}

