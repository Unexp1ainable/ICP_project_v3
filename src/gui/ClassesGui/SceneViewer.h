#pragma once
#include <QNode>
#include <Qt3DWindow>
#include <QWidget>
#include <map>

#include "rayTracer/RayEngine.h"
#include "src/gui/Classes3D/Detector3D.h"
#include "src/gui/Classes3D/Lens3D.h"
#include "src/gui/Classes3D/RayCluster3D.h"
#include "src/gui/Classes3D/Sample3D.h"
#include "src/gui/Classes3D/Source3D.h"

class SceneViewer : public QWidget
{
	Q_OBJECT

public:
	SceneViewer(rayEngine *engine);
	
	void add_lens(float distance, float x_tilt, float z_tilt, int id);
	void remove_lens(int id);
	void edit_lens(int id, float x_tilt, float z_tilt, float distance);
	void edit_sample(float distance, float tilt_y) const;
	void edit_detector(float distance) const;
	void clear_lenses();

	void set_active(int id);
	
	Qt3DExtras::Qt3DWindow* get_window() const;
	QWidget* get_window_widget() const;
	Source3D* get_source() const;
	Sample3D* get_sample() const;
	Detector3D* get_detector() const;

	void update(vector<vector<std::shared_ptr<Point>>> rays);

private:
	Qt3DExtras::Qt3DWindow *window_;
	QWidget * window_widget_;
	Qt3DCore::QEntity *root_entity_;
	Source3D* source_;
	Sample3D* sample_;
	Detector3D* detector_;
	RayCluster3D* ray_cluster_;

	Qt3DCore::QEntity* create_scene(rayEngine* engine);
	void add_camera(Qt3DExtras::Qt3DWindow& view, Qt3DCore::QEntity* root_entity);
	Qt3DCore::QEntity* add_light(const QVector3D position, Qt3DCore::QNode* parent);

	std::map<int, Lens3D*> lenses_;
	Lens3D* active_lens_ = nullptr;

signals:
	void error_signal(std::string message);
};

