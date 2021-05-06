#pragma once
#include <qpushbutton.h>
#include <qspinbox.h>
#include <QWidget>

class MiscEditor : public QWidget
{
	Q_OBJECT

public:
	MiscEditor();

	void edit_mode();
	void default_mode();

	QPushButton* get_button_edit_();
	QPushButton* get_button_save_();
	QPushButton* get_button_cancel_();
	
	void set_configuration(unsigned rays_number, double y_tilt, double distance_s, double distance_d);
	

private:
	QSpinBox* number_rays_;
	QDoubleSpinBox* detector_distance_;
	QDoubleSpinBox* sample_distance_;
	QDoubleSpinBox* sample_tilt_y_;
	QPushButton* button_edit_;
	QPushButton* button_save_;
	QPushButton* button_cancel_;

public slots:
	void save_slot();
	
signals:
	void edited_signal(unsigned rays_number,  double y_tilt, double distance_s, double distance_d);
};

