#pragma once
#include <qmainwindow.h>
#include <Qt3DExtras>
#include <QtWidgets>

#include "LensEditor.h"
#include "LensSelector.h"
#include "LensSelectorItem.h"
#include "MiscEditor.h"
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
	void load_configuration();
	void clear_configuration();

	void create_menu();
	
	/**
	 * Constructs 3D viewer and scene inside.
	 * Reference will be stored in view_3d_widget_
	 */
	QGroupBox* create_3d_view();
	
	/**
	 * Creates lens editing part of the window.
	 * Reference will be stored in editor_
	 */
	QGroupBox* create_lens_editor();

	/**
	 * Creates part of the window with all lenses listed.
	 * Reference will be stored in selector_
	 */
	QGroupBox* create_selector();

	QGroupBox* create_misc_editor();

	/**
	 * TODO
	 */
	QGroupBox* create_sample_info();

	
	QGroupBox* create_detector_info();

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

	void update();
	
	QWidget* view_3d_widget_;
	SceneViewer* view_3d_;
	LensSelector* selector_;
	LensEditor* editor_;
	MiscEditor* misc_editor_;
	QGroupBox* sample_info_;
	QGroupBox* detector_info_;
	QWidget *central_widget_;
	rayEngine *engine_;

	QGridLayout *main_layout_;

	bool editing_ = false;
	

private slots:
	void open_file_slot();
	void save_file_slot();
	
	void selection_changed_slot(QListWidgetItem* item);
	void mode_new_slot();
	void mode_edit_slot();
	void delete_slot();
	void save_slot(QString name, float x_tilt, float z_tilt, float distance, float optical_power);
	void cancel_slot();

	void misc_editor_edit_slot_();
	void misc_editor_cancel_slot_();
	void misc_editor_save_slot(unsigned rays_n, double y_tilt, double distance_s, double distance_d);

	void error_slot(std::string error);
};

