#pragma once
#include <QNode>
#include <Qt3DWindow>
#include <QWidget>

class SceneViewer : public QWidget
{
public:
	SceneViewer();

	void add_lens(float distance, float x_tilt, float z_tilt);
	void remove_lens();
	void edit_lens();
	Qt3DExtras::Qt3DWindow* get_window();
	QWidget* get_window_widget();

private:
	Qt3DExtras::Qt3DWindow *window_;
	QWidget * window_widget_;
	Qt3DCore::QEntity *root_entity_;

	Qt3DCore::QEntity* create_scene();
	void add_camera(Qt3DExtras::Qt3DWindow& view, Qt3DCore::QEntity* root_entity);
	Qt3DCore::QEntity* add_light(const QVector3D position, Qt3DCore::QNode* parent);
};

