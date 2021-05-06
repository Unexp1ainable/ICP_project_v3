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

	/**
	 * Connects signals and slots 
	 */
	void connect_elements();

	/**
	 * @brief This function is called when an existing lens is being edited. It sends signal to all necessary parts to edit their contents.
	 * 
	 * @param name Name of the lens
	 * @param x_tilt Tilt on the x axis
	 * @param z_tilt Tilt on the z axis
	 * @param distance Distance from source
	 * @param optical_power Optical power of the lens
	 * @param id Id of the lens that is being edited
	*/
	void edit_lens(QString name, float x_tilt, float z_tilt, float distance, float optical_power, int id);

	
	void create_new_lens(QString name, float x_tilt, float z_tilt, float distance, float optical_power);

	QWidget* view_3d_widget_;
	SceneViewer* view_3d_;
	LensList* selector_;
	LensEditor* editor_;
	QGroupBox* info_;
	QWidget *central_widget_;
	rayEngine *engine_;

	QGridLayout *main_layout_;

	bool editing_ = false;

private slots:
	void selection_changed_slot(QListWidgetItem* item);
	void mode_new_slot();
	void mode_edit_slot();
	void delete_slot();
	void save_slot(QString name, float x_tilt, float z_tilt, float distance, float optical_power);
	void cancel_slot();

	void error_slot(std::string error);
};

