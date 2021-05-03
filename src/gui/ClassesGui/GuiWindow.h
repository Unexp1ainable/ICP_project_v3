#pragma once
#include <qmainwindow.h>
#include <Qt3DExtras>
#include <QtWidgets>

class GuiWindow : public QMainWindow
{
	Q_OBJECT

public:
	GuiWindow();

private:
	void create_3d_view();
	void create_control();
	void create_info();
	Qt3DCore::QEntity* create_scene();
	void add_camera(Qt3DExtras::Qt3DWindow& view, Qt3DCore::QEntity* root_entity);
	Qt3DCore::QEntity* add_light(const QVector3D position, Qt3DCore::QNode* parent);

	QWidget* view_3d_widget_;
	Qt3DExtras::Qt3DWindow* view_3d_;
	QGroupBox* control_;
	QGroupBox* info_;
	QWidget *central_widget_;
};

