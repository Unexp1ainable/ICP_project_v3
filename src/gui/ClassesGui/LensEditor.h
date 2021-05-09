#pragma once
#include <qformlayout.h>
#include <qgroupbox.h>
#include <qlabel.h>
#include <qpushbutton.h>
#include <qspinbox.h>
#include <QWidget>

#include "rayTracer/Lens.h"

/**
 * @brief Editable fields and interface for editing selected lens.
 */
class LensEditor : public QWidget
{
	Q_OBJECT

public:
	LensEditor();

	/**
	 * @brief Load data from lens to editable fields.
	 *
	 * @param name Name of the lens
	 * @param tilt_x Rotation on X axis
	 * @param tilt_z Rotation on Z axis
	 * @param o_power Optical power
	 * @param distance Distance from the source
	 */
	void load_lens(std::string name, double tilt_x, double tilt_z, double o_power, double distance) const;

	/**
	 * @brief Button New getter.
	 *
	 * @return button reference
	 */
	QPushButton* get_button_new() const;
	/**
	 * @brief Button Edit getter.
	 *
	 * @return button reference
	 */
	QPushButton* get_button_edit() const;
	/**
	 * @brief Button Delete getter.
	 *
	 * @return button reference
	 */
	QPushButton* get_button_delete() const;
	/**
	 * @brief Button Save getter.
	 *
	 * @return button reference
	 */
	QPushButton* get_button_save() const;
	/**
	 * @brief Button Cancel getter.
	 *
	 * @return button reference
	 */
	QPushButton* get_button_cancel() const;

	/**
	 * @brief Disables editing of the fields.
	 */
	void disable_form() const;
	/**
	 * @brief Enablees editing of the fields.
	 */
	void enable_form() const;
	/**
	 * @brief Switches to the primary buttons (New, Edit, Delete).
	 */
	void primary_buttons() const;
	/**
	 * @brief Switches to the secondaryy buttons (Save, Done).
	 */
	void secondary_buttons() const;

private:
	/**
	 * @brief Stores reference to the Lens name editable field.
	 */
	QLineEdit* name_;
	/**
	 * @brief Stores reference to the X rotation editable field.
	 */
	QDoubleSpinBox* tilt_x_;
	/**
	 * @brief Stores reference to the Z rotation editable field.
	 */
	QDoubleSpinBox* tilt_z_;
	/**
	 * @brief Stores reference to the Optical power editable field.
	 */
	QDoubleSpinBox* optical_power_;
	/**
	 * @brief Stores reference to the name distance field.
	 */
	QDoubleSpinBox* distance_;

	/**
	 * @brief Stores reference to the button New.
	 */
	QPushButton* button_new_;
	/**
	 * @brief Stores reference to the button Edit.
	 */
	QPushButton* button_edit_;
	/**
	 * @brief Stores reference to the button Delete.
	 */
	QPushButton* button_delete_;
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
	 * @brief	Sets editor to mode for creating new lens.
	*/
	void mode_new() const;
	/**
	 * @brief Sets editor to the mode for editing existing lens.
	 */
	void mode_edit() const;
	/**
	 * @brief Sets editor to mode with disabled editable fields, with primary buttons shown.
	 */
	void mode_default() const;
	/**
	 * @brief For catching signal from button Save, in order to relay it to the signal with parameters.
	*/
	void save_new();

signals:
	/**
	 * @brief Signal emitted when button save has been triggered.
	 *
	 * @param name Name of the lens
	 * @param x_tilt Rotation on X axis
	 * @param z_tilt Rotation on Z axis
	 * @param optical_power Optical power
	 * @param distance Distance from the source
	 */
	void save_lens_signal(QString name, double x_tilt, double z_tilt, double distance, double optical_power);
};

