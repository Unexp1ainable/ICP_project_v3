#pragma once
#include <qmainwindow.h>
#include <QtWidgets>

#include "LensEditor.h"
#include "LensSelector.h"
#include "MiscEditor.h"
#include "SceneViewer.h"
#include "SurfaceInfoPanel.h"
#include "rayTracer/RayEngine.h"

/**
 * @brief Main interface window
 */
class GuiWindow : public QMainWindow
{
	Q_OBJECT

public:
	/**
	 * @brief Initialise rayEngine. Values used are in macros.h
	 *
	 * @param engine rayEngine instance 
	 */
	void init_engine(rayEngine* engine);

	/**
	 * @brief GuiWindow constructor.
	 *
	 * @param engine rayEngine instance
	 */
	GuiWindow(rayEngine *engine);


private:
	/**
	 * @brief Loads configuration from engine to GUI
	 */
	void load_configuration() const;

	/**
	 * Clears current configuration
	 */
	void clear_configuration() const;

	/**
	 * @brief Creates menubar
	 */
	void create_menu();
	
	/**
	 * @brief Constructs 3D viewer and scene inside.
	 * Reference will be stored in view_3d_widget_
	 */
	QGroupBox* create_3d_view();
	
	/**
	 * @brief Creates lens editing part of the window.
	 * Reference will be stored in editor_
	 */
	QGroupBox* create_lens_editor();

	/**
	 * @brief Creates part of the window with all lenses listed.
	 * Reference will be stored in selector_
	 */
	QGroupBox* create_selector();

	/**
	 * @brief Creates editor for miscelaneous items like sample, detector or ray cluster
	 * Reference will be stored in misc_editor_
	 */
	QGroupBox* create_misc_editor();

	/**
	 * @brief Creates infopanel about rays passing through the sample.
	 * Reference will be stored in sample_info_
	 */
	QGroupBox* create_sample_info();

	/**
	 * @brief Creates infopanel about rays striking the detector.
	 * Reference will be stored in detector_info_
	 */
	QGroupBox* create_detector_info();

	/**
	 * @brief Connects signals and slots 
	 */
	void connect_elements() const;

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
	void edit_lens(QString name, double x_tilt, double z_tilt, double distance, double optical_power, int id) const;

	/**
	 * @brief Creates new lens in the system
	 * 
	 * @param name Name of the lens
	 * @param x_tilt Rotation on x axis
	 * @param z_tilt Rotation on z axis (not vertical)
	 * @param distance Distance from source
	 * @param optical_power Optical power
	 */
	void create_new_lens(QString name, double x_tilt, double z_tilt, double distance, double optical_power) const;

	/**
	 *@brief Updates engine and refreshes rays in the gui
	 */
	void update_system() const;

	/**
	 * @brief SceneViewer embedded in the widget.
	 */
	QWidget* view_3d_widget_;
	/**
	 * @brief SceneViewer instance.
	 */
	SceneViewer* view_3d_;
	/**
	 * @brief LensSelector instance.
	 */
	LensSelector* selector_;
	/**
	 * @brief LensEditor instance.
	 */
	LensEditor* editor_;
	/**
	 * @brief MiscEditor instance.
	 */
	MiscEditor* misc_editor_;
	/**
	 * @brief SurfaceInfoPanel instance for sample information.
	 */
	SurfaceInfoPanel* sample_info_;
	/**
	 * @brief SurfaceInfoPanel instance for detector information.
	 */
	SurfaceInfoPanel* detector_info_;
	/**
	 * @brief MainWindow central widget.
	 */
	QWidget *central_widget_;
	/**
	 * @brief rayEngine instance.
	 */
	rayEngine *engine_;
	/**
	 * @brief Layout of the central_widget_.
	 */
	QGridLayout *main_layout_;
	/**
	 * @brief QAction instance triggered when configuration is being loaded from the file.
	 */
	QAction* load_action_;
	/**
	 * @brief QAction instance triggered when configuration is being saved to the file.
	 */
	QAction* save_action_;

	/**
	 * @brief For remembering, if LensEditor is in new or edit mode.
	 */
	bool editing_ = false;
	

private slots:
	/**
	 * @brief Slot triggered when a file is being loaded.
	 */
	void open_file_slot();
	/**
	 * @brief Slot triggered when configuration is being saved to the file.
	 */
	void save_file_slot();

	/**
	 * @brief Slot for signal from LensSelector. Triggers update of necessary components to load selected lens.
	 * 
	 * @param item Item selected
	 */
	void selection_changed_slot(QListWidgetItem* item) const;
	/**
	 * @brief Slot triggered when New button in LensEditor is pushed.
	 */
	void mode_new_slot();
	/**
	 * @brief Slot triggered when New button in LensEditor is pushed.
	 */
	void mode_edit_slot();
	/**
	 * @brief Slot triggered when Edit button in LensEditor is pushed.
	 */
	void delete_slot() const;
	/**
	 * @brief Slot triggered when Save button in LensEditor is pushed.
	 * It is relayed from LensEditor in order to fill required parameters.
	 * 
	 * @param name Name of the lens
	 * @param x_tilt Rotation on x axis
	 * @param z_tilt Rotation on Z axis
	 * @param distance Distance from the source
	 * @param optical_power Optical power of the lens
	 */
	void save_slot(QString name, double x_tilt, double z_tilt, double distance, double optical_power) const;
	/**
	 * @brief Slot triggered when Cancel button in LensEditor is pushed.
	 */
	void cancel_slot() const;

	/**
	 * @brief Slot triggered when Edit button in MiscEditor is pushed.
	 */
	void misc_editor_edit_slot_() const;
	/**
	 * @brief Slot triggered when Cancel button in MiscEditor is pushed.
	 */
	void misc_editor_cancel_slot_() const;
	/**
	 * @brief Slot triggered when Save button in MiscEditor is pushed.
	 * It is relayed from MiscEditor in order to fill required parameters.
	 * 
	 * @param rays_n Number of rays being simulated
	 * @param y_tilt Tilt of the sample on the Y axis (vertical one)
	 * @param distance_s Distance of the sample from the source
	 * @param distance_d Distance of the detector from the source
	 * @param r_diameter Diameter of the simulated ray clusters
	 */
	void misc_editor_save_slot(unsigned rays_n, double y_tilt, double distance_s, double distance_d, double r_diameter) const;

	/**
	 * @brief Slot showing error dialog with message.
	 * 
	 * @param error Message to show
	 */
	void error_slot(std::string error) const;
};

