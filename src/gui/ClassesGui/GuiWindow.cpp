#include "GuiWindow.h"

#include <iostream>

#include "LensEditor.h"
#include "src/gui/Classes3D/GuiLens.h"
#include "src/gui/Classes3D/Line.h"
#include "src/gui/common/Scene.h"

GuiWindow::GuiWindow(rayEngine *engine)
{
	create_info();
	create_editor();
	create_selector();
	create_3d_view();
	
	engine_ = engine;

	auto main_layout = new QGridLayout;
	main_layout->addWidget(view_3d_widget_,0,0,5,5);
	main_layout->addWidget(selector_,0,5,2,1);
	main_layout->addWidget(editor_, 2, 5, 2, 1);
	main_layout->addWidget(info_,4,5);
	
	auto central_widget = new QWidget;
	central_widget->setLayout(main_layout);
	setCentralWidget(central_widget);
}

void GuiWindow::create_3d_view()
{
	// 3D view
	view_3d_ = new Qt3DExtras::Qt3DWindow;
	view_3d_->defaultFrameGraph()->setClearColor(Scene::bg_color);

	// 3D view as a widget
	view_3d_widget_ = createWindowContainer(view_3d_);

	// 3D root entity
	Qt3DCore::QEntity* root_entity = create_scene();


	GuiLens{ root_entity, 0.0f,.0f, .0f };


	// world axes
	Line{ QVector3D(0.0f,0.0f,0.0f), QVector3D(100.0f,0.0f,0.0f),QColor(255,0,0), root_entity };
	Line{ QVector3D(0.0f,0.0f,0.0f), QVector3D(0.0f,100.0f,0.0f),QColor(0,255,0), root_entity };
	Line{ QVector3D(0.0f,0.0f,0.0f), QVector3D(0.0f,0.0f,100.0f),QColor(0,0,255), root_entity };


	add_camera(*view_3d_, root_entity);
	view_3d_->setRootEntity(root_entity);
}

void GuiWindow::create_editor()
{
	editor_ = new QGroupBox;
	editor_->setTitle(tr("GuiLens control."));
	
	auto lens_editor = new LensEditor;
	
	auto vbox = new QVBoxLayout;
	vbox->addWidget(lens_editor);
	editor_->setLayout(vbox);

}

void GuiWindow::create_selector()
{
	selector_ = new QGroupBox;
	selector_->setTitle(tr("Lens editor."));

	auto lens_list = new LensList;
	auto w = new QWidget();
	lens_list->setParent(w);
	auto* layout = new QVBoxLayout;
	layout->addWidget(w);
	selector_->setLayout(layout);
}


void GuiWindow::button_clicked()
{
	editor_->layout()->addWidget(new LensEditor);
}


void GuiWindow::create_info()
{
	info_ = new QGroupBox;
	info_->setTitle(tr("Informations about rays on detector."));

	auto button = new QPushButton("New", this);
	connect(button, SIGNAL(clicked()), this, SLOT(button_clicked_()));
	QVBoxLayout* vbox = new QVBoxLayout;
	vbox->addWidget(button);
	info_->setLayout(vbox);
}



void GuiWindow::add_camera(Qt3DExtras::Qt3DWindow& view, Qt3DCore::QEntity* root_entity) {
	Qt3DRender::QCamera* camera = view.camera();
	camera->lens()->setPerspectiveProjection(60.f, static_cast<float>(view.width()) / view.height(), 0.1f, 1000.f);
	camera->setPosition(QVector3D(0.0f, 0.0f, 40.0f));
	camera->setViewCenter(QVector3D(0.0f, 0.0f, 0.0f));

	auto* camera_controller = new Qt3DExtras::QOrbitCameraController(root_entity);
	camera_controller->setCamera(camera);
	camera_controller->setLinearSpeed(-40.0f);
	camera_controller->setLookSpeed(-120.0f);
}


Qt3DCore::QEntity* GuiWindow::add_light(const QVector3D position, Qt3DCore::QNode* parent)
{
	auto light_entity = new Qt3DCore::QEntity(parent);
	auto* point_light = new Qt3DRender::QPointLight(light_entity);
	auto* light_transform = new Qt3DCore::QTransform(light_entity);
	light_transform->setTranslation(position);
	light_entity->addComponent(point_light);
	light_entity->addComponent(light_transform);

	return light_entity;
}

Qt3DCore::QEntity* GuiWindow::create_scene()
{
	const auto result_entity = new Qt3DCore::QEntity;

	add_light(QVector3D(0.0f, 20.0f, 30.0f), result_entity);
	add_light(QVector3D(0.0f, -20.0f, -30.0f), result_entity);
	add_light(QVector3D(40.0f, -20.0f, -30.0f), result_entity);

	return result_entity;
}