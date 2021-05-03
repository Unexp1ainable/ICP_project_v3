#pragma once
#include <qmainwindow.h>
#include <Qt3DExtras>
#include <QtWidgets>

#include "LensList.h"
#include "rayTracer/RayEngine.h"

/**
 * Main interface window
 */
class GuiWindow : public QMainWindow
{
	Q_OBJECT

public:
	GuiWindow(rayEngine *engine);

private:
	/**
	 * Constructs 3D viewer and scene inside.
	 * Reference will be stored in view_3d_widget_
	 */
	void create_3d_view();
	
	/**
	 * Creates lens editing part of the window.
	 * Reference will be stored in editor_
	 */
	void create_editor();

	/**
	 * Creates part of the window with all lenses listed.
	 * Reference will be stored in selector_
	 */
	void create_selector();

	/**
	 * Creates informative part of the window.
	 * Reference will be stored in info_
	 */
	void create_info();

	
	Qt3DCore::QEntity* create_scene();
	void add_camera(Qt3DExtras::Qt3DWindow& view, Qt3DCore::QEntity* root_entity);
	Qt3DCore::QEntity* add_light(const QVector3D position, Qt3DCore::QNode* parent);

	QWidget* view_3d_widget_;
	Qt3DExtras::Qt3DWindow* view_3d_;
	QGroupBox* selector_;
	QGroupBox* editor_;
	QGroupBox* info_;
	QWidget *central_widget_;
	rayEngine *engine_;

private slots:
	void button_clicked();
};

