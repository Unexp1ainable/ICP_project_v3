#pragma once
#include <qmainwindow.h>
#include <Qt3DExtras>
#include <QtWidgets>

#include "LensEditor.h"
#include "LensList.h"
#include "LensListItem.h"
#include "SceneViewer.h"
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
	QGroupBox* create_3d_view();
	
	/**
	 * Creates lens editing part of the window.
	 * Reference will be stored in editor_
	 */
	QGroupBox* create_editor();

	/**
	 * Creates part of the window with all lenses listed.
	 * Reference will be stored in selector_
	 */
	QGroupBox* create_selector();

	/**
	 * Creates informative part of the window.
	 * Reference will be stored in info_
	 */
	QGroupBox* create_info();


	QWidget* view_3d_widget_;
	SceneViewer* view_3d_;
	LensList* selector_;
	LensEditor* editor_;
	QGroupBox* info_;
	QWidget *central_widget_;
	rayEngine *engine_;

	QGridLayout *main_layout_;

private slots:
	void selection_changed(QListWidgetItem* item);
};

