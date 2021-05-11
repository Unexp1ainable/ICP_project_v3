#pragma once
/**
 * @file MiscEditor.h
 * @author Samuel Repka
 * @date 11/05/2021
 * @brief Subwindow with field for editing detector, sample and ray cluster.
 */

#include <qpushbutton.h>
#include <qspinbox.h>
#include <QWidget>

/**
 * @brief Interface for editing miscelaneous items like sample, detector or ray cluster
 */
class MiscEditor : public QWidget
{
	Q_OBJECT

public:
	MiscEditor();
	
	/**
	 * @brief Sets editor to the edit mode.
	 */
	void edit_mode() const;
	/**
	 * @brief Default mode. Editing is not enabled.
	 */
	void default_mode() const;

	/**
	 * @brief Button Edit getter.
	 *
	 * @return button reference
	 */
	QPushButton* get_button_edit_() const;
	/**
	 * @brief Button Save getter.
	 *
	 * @return button reference
	 */
	QPushButton* get_button_save_() const;
	/**
	 * @brief Button Cancel getter.
	 *
	 * @return button reference
	 */
	QPushButton* get_button_cancel_() const;

	/**
	 * @brief Sets editable fields to supplied values.
	 * 
	 * @param rays_number Number of rays simulated
	 * @param y_tilt Tilt of the sample
	 * @param distance_s Distance of the sample
	 * @param distance_d Distance of the detector
	 * @param r_diameter Diameter of the ray cluster
	 */
	void set_configuration(unsigned rays_number, double y_tilt, double distance_s, double distance_d, double r_diameter) const;

private:
	/**
	 * @brief Stores reference to the Number of the rays editable field.
	 */
	QSpinBox* number_rays_;
	/**
	 * @brief Stores reference to the Detector distance editable field.
	 */
	QDoubleSpinBox* detector_distance_;
	/**
	 * @brief Stores reference to the Sample distance editable field.
	 */
	QDoubleSpinBox* sample_distance_;
	/**
	 * @brief Stores reference to the Sample rotation field.
	 */
	QDoubleSpinBox* sample_tilt_y_;
	/**
	 * @brief Stores reference to the Diameter of the rays editable field.
	 */
	QDoubleSpinBox* r_diameter_;
	
	/**
	 * @brief Stores reference to the button Edit.
	 */
	QPushButton* button_edit_;
	/**
	 * @brief Stores reference to the button Save.
	 */
	QPushButton* button_save_;
	/**
	 * @brief Stores reference to the button Cancel.
	 */
	QPushButton* button_cancel_;
	

public slots:
	/**
	 * @brief Slot for relaying Save button clicked signal.
	 */
	void save_slot();
	
signals:
	/**
	 * @brief Signal emitted from MiscEditor when Save button is clicked.
	 *
	 * @param rays_number Number of rays simulated
	 * @param y_tilt Tilt of the sample
	 * @param distance_s Distance of the sample
	 * @param distance_d Distance of the detector
	 * @param r_diameter Diameter of the ray cluster
	 */
	void edited_signal(unsigned rays_number,  double y_tilt, double distance_s, double distance_d, double r_diameter);
};

