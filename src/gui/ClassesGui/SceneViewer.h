#pragma once
#include <QNode>
#include <Qt3DWindow>
#include <QWidget>
#include <map>

#include "src/gui/Classes3D/GuiLens.h"

class SceneViewer : public QWidget
{
	Q_OBJECT

public:
	SceneViewer();

	void add_lens(float distance, float x_tilt, float z_tilt, int id);
	void remove_lens();
	void edit_lens(int id, float x_tilt, float z_tilt, float distance);
	Qt3DExtras::Qt3DWindow* get_window();
	QWidget* get_window_widget();

private:
	Qt3DExtras::Qt3DWindow *window_;
	QWidget * window_widget_;
	Qt3DCore::QEntity *root_entity_;

	Qt3DCore::QEntity* create_scene();
	void add_camera(Qt3DExtras::Qt3DWindow& view, Qt3DCore::QEntity* root_entity);
	Qt3DCore::QEntity* add_light(const QVector3D position, Qt3DCore::QNode* parent);

	std::map<int, GuiLens*> lenses_;

signals:
	void error_signal(std::string message);
};

