#pragma once
/**
 * @file SceneViewer.h
 * @author Samuel Repka
 * @date 11/05/2021
 * @brief 3D view of the scene.
 */

#include <Qt3DWindow>
#include <QWidget>
#include <map>

#include "src/gui/Classes3D/Detector3D.h"
#include "src/gui/Classes3D/Lens3D.h"
#include "src/gui/Classes3D/RayCluster3D.h"
#include "src/gui/Classes3D/Sample3D.h"
#include "src/gui/Classes3D/Source3D.h"
#include "src/rayTracer/RayEngine.h"

/**
 * @brief 3D viewer.
 */
class SceneViewer : public QWidget
{
	Q_OBJECT

public:
	SceneViewer(RayEngine* engine);

	/**
	 * @brief Adds lens to the view.
	 *
	 * @param distance Distance from the source
	 * @param x_tilt Rotation on X axis
	 * @param z_tilt Rotation on Z axis
	 * @param id ID of the lens from the engine
	 */
	void add_lens(float distance, float x_tilt, float z_tilt, int id);
	/**
	 * @brief Removes lens from the scene.
	 *
	 * @param id Id of the lens.
	 */
	void remove_lens(int id);
	/**
	 * @brief Edits already existing lens.
	 *
	 * @param id Id of the lens
	 * @param x_tilt Rotation on X axis
	 * @param z_tilt Rotation on Z axis
	 * @param distance Distance from the source
	 */
	void edit_lens(int id, float x_tilt, float z_tilt, float distance);
	/**
	 * @brief Edits parameters of the sample.
	 *
	 * @param distance Distance from the source
	 * @param tilt_y Rotation on Y axis
	 */
	void edit_sample(float distance, float tilt_y) const;
	/**
	 * @brief Edits parameter of the detector.
	 *
	 * @param distance Distance from the source
	 */
	void edit_detector(float distance) const;
	/**
	 * @brief Removes every lens.
	 */
	void clear_lenses();

	/**
	 * @brief Changes Diffuse color of the lens that is selected and removes different color from the previous if necessary.
	 *
	 * @param id Id of the lens
	 */
	void set_active(int id);

	/**
	 * @brief Main 3D window getter.
	 *
	 * @return Reference to the main window
	 */
	Qt3DExtras::Qt3DWindow* get_window() const;
	/**
	 * @brief Main 3D window widget getter.
	 *
	 * @return Reference to the main window widget
	 */
	QWidget* get_window_widget() const;
	/**
	 * @brief Source getter.
	 *
	 * @return Reference to the source
	 */
	Source3D* get_source() const;
	/**
	 * @brief Sample getter.
	 *
	 * @return Reference to the sample
	 */
	Sample3D* get_sample() const;
	/**
	 * @brief Detector getter.
	 *
	 * @return Reference to the detector
	 */
	Detector3D* get_detector() const;

	/**
	 * @brief Redraws RayCluster.
	 * 
	 * @param rays new rays to draw
	 */
	void update(vector<vector<std::shared_ptr<Point>>> rays);

private:
	/**
	 * @brief Reference to the main 3D window.
	 */
	Qt3DExtras::Qt3DWindow* window_;
	/**
	 * @brief Reference to the main 3D window widget.
	 */
	QWidget* window_widget_;
	/**
	 * @brief Reference to the root entity of the scene.
	 */
	Qt3DCore::QEntity* root_entity_;
	/**
	 * @brief Reference to the source.
	 */
	Source3D* source_;
	/**
	 * @brief Reference to the sample.
	 */
	Sample3D* sample_;
	/**
	 * @brief Reference to the  detector.
	 */
	Detector3D* detector_;
	/**
	 * @brief Reference to the  ray cluster.
	 */
	RayCluster3D* ray_cluster_;
	/**
	 * @brief Storage for all lenses.
	 */
	std::map<int, Lens3D*> lenses_;
	/**
	 * @brief Currently active lens.
	 */
	Lens3D* active_lens_ = nullptr;

	/**
	 * @brief Initializes scene with information from the engine.
	 *
	 * @param engine rayEngine instance
	 */
	Qt3DCore::QEntity* create_scene(RayEngine* engine);
	/**
	 * @brief Adds camera to the scene.
	 *
	 * @param  view Where to add the camera
	 * @param root_entity What will be the parent of the camera
	 */
	void add_camera(Qt3DExtras::Qt3DWindow& view, Qt3DCore::QEntity* root_entity);
	/**
	 * @brief Adds light to the scene.
	 *
	 * @param position Where to add the light
	 * @param parent Parent of the light
	 */
	Qt3DCore::QEntity* add_light(const QVector3D position, Qt3DCore::QNode* parent);


signals:
	/**
	 * @brief Signal emmited when error occurs
	 *
	 * @param message Message to show
	*/
	void error_signal(std::string message);
};

