#include "GuiWindow.h"

#include <iostream>

#include "LensEditor.h"
#include "LensListItem.h"
#include "MiscEditor.h"
#include "SceneViewer.h"
#include "ShapeViewer.h"
#include "src/common/macros.h"

GuiWindow::GuiWindow(rayEngine* engine)
{
	engine_ = engine;

	auto editor_box = create_lens_editor();
	auto view_3d_box = create_3d_view();
	auto selector_box = create_selector();
	auto misc_editor_box = create_misc_editor();
	auto s_info_box = create_sample_info();
	auto d_info_box = create_detector_info();

	main_layout_ = new QGridLayout;
	main_layout_->setColumnStretch(0, 4);
	main_layout_->setRowStretch(2, 1);
	main_layout_->setRowStretch(3, 1);
	main_layout_->setRowStretch(4, 1);

	main_layout_->addWidget(view_3d_box, 0, 0, 5, 5);
	main_layout_->addWidget(selector_box, 0, 5, 1, 1);
	main_layout_->addWidget(editor_box, 1, 5, 1, 1);
	main_layout_->addWidget(misc_editor_box, 2, 5, 1, 1);
	main_layout_->addWidget(s_info_box, 3, 5, 1, 1);
	main_layout_->addWidget(d_info_box, 4, 5, 1, 1);

	auto central_widget = new QWidget(this);
	central_widget->setLayout(main_layout_);
	setCentralWidget(central_widget);
	connect_elements();

}

QGroupBox* GuiWindow::create_3d_view()
{
	auto s_dist = engine_->get_sample()->distance_from_source();
	auto s_tilt = engine_->get_sample()->rotation;
	auto d_dist = engine_->get_detector()->distance_from_source();
	
	view_3d_ = new SceneViewer(s_dist, s_tilt, d_dist);
	view_3d_widget_ = view_3d_->get_window_widget();

	auto layout = new QBoxLayout{ QBoxLayout::BottomToTop };

	auto view_3d_box = new QGroupBox;
	layout->addWidget(view_3d_widget_);
	view_3d_box->setLayout(layout);

	return view_3d_box;
}

QGroupBox* GuiWindow::create_lens_editor()
{
	auto e_box = new QGroupBox;
	e_box->setTitle(tr("Lens editor."));

	editor_ = new LensEditor;
	// init editor
	editor_->disable_form();
	editor_->get_button_edit()->setDisabled(true);
	editor_->get_button_delete()->setDisabled(true);


	auto vbox = new QVBoxLayout;
	vbox->addWidget(editor_);
	e_box->setLayout(vbox);

	return e_box;
}

QGroupBox* GuiWindow::create_selector()
{
	auto s_box = new QGroupBox;
	s_box->setTitle(tr("Lens selector."));

	selector_ = new LensList;
	auto* layout = new QGridLayout;

	layout->addWidget(selector_);
	s_box->setLayout(layout);

	// initialise items
	for (int i = 0; i < engine_->lens_count(); i++)
	{
		auto lens = engine_->get_lens_by_index(i);
		auto distance = lens->distance_from_source();
		auto x_tilt = TO_DEGREES(lens->deviation_x());
		auto z_tilt = TO_DEGREES(lens->deviation_y());
		auto id = lens->id();
		view_3d_->add_lens(distance, x_tilt, z_tilt, id);

		selector_->addItem(new LensListItem{ lens->id(), QString::fromStdString(lens->name()) });
	}

	return s_box;
}

QGroupBox* GuiWindow::create_misc_editor()
{
	auto i_box = new QGroupBox;
	i_box->setTitle(tr("Sample and detector editor."));

	QHBoxLayout* vbox = new QHBoxLayout;

	misc_editor_ = new MiscEditor;
	misc_editor_cancel_slot_(); // it will initialize values from engine

	vbox->addWidget(misc_editor_);

	i_box->setLayout(vbox);
	return i_box;
}



QGroupBox* GuiWindow::create_sample_info()
{
	auto i_box = new QGroupBox;
	i_box->setTitle(tr("Informations about rays passing through the sample."));

	QHBoxLayout* vbox = new QHBoxLayout;

	vbox->addWidget(new ShapeViewer);

	i_box->setLayout(vbox);

	sample_info_ = i_box; // TODO temporary
	return i_box;
}

QGroupBox* GuiWindow::create_detector_info()
{
	auto i_box = new QGroupBox;
	i_box->setTitle(tr("Informations about rays striking the detector."));

	QHBoxLayout* vbox = new QHBoxLayout;

	vbox->addWidget(new ShapeViewer);

	i_box->setLayout(vbox);

	detector_info_ = i_box; // TODO temporary
	return i_box;
}


void GuiWindow::connect_elements()
{
	// -------- Lens Editor ---------
	// connect selection loading
	connect(selector_, &QListWidget::itemClicked, this, &GuiWindow::selection_changed_slot);
	// connect button new
	connect(editor_->get_button_new(), &QPushButton::clicked, this, &GuiWindow::mode_new_slot);
	// connect button edit
	connect(editor_->get_button_edit(), &QPushButton::clicked, this, &GuiWindow::mode_edit_slot);
	// connect button delete
	connect(editor_->get_button_delete(), &QPushButton::clicked, this, &GuiWindow::delete_slot);
	// connect button cancel
	connect(editor_->get_button_cancel(), &QPushButton::clicked, this, &GuiWindow::cancel_slot);
	// connect button save
	connect(editor_, &LensEditor::save_lens_signal, this, &GuiWindow::save_slot);

	// -------- Miscelaneous Editor ---------
	// button edit
	connect(misc_editor_->get_button_edit_(), &QPushButton::clicked, this, &GuiWindow::misc_editor_edit_slot_);
	// button cancel
	connect(misc_editor_->get_button_cancel_(), &QPushButton::clicked, this, &GuiWindow::misc_editor_cancel_slot_);
	// button save
	connect(misc_editor_, &MiscEditor::edited_signal, this, &GuiWindow::misc_editor_save_slot);


	// connect error signals
	connect(view_3d_, &SceneViewer::error_signal, this, &GuiWindow::error_slot);
}


void GuiWindow::selection_changed_slot(QListWidgetItem* item)
{
	auto lens_item = dynamic_cast<LensListItem*>(item);	// casting back so I can access id
	auto lens_id = lens_item->getId();

	auto to_load = engine_->get_lens_by_id(lens_id);
	editor_->load_lens(to_load);

	// enable buttons
	editor_->get_button_edit()->setDisabled(false);
	editor_->get_button_delete()->setDisabled(false);

	view_3d_->set_active(lens_id);
}

void GuiWindow::mode_new_slot()
{
	editing_ = false;
	editor_->mode_new();
	selector_->setDisabled(true);
}


void GuiWindow::mode_edit_slot()
{
	editing_ = true;
	editor_->mode_edit();
	selector_->setDisabled(true);
}

void GuiWindow::delete_slot()
{
	auto item = dynamic_cast<LensListItem*>(selector_->currentItem());
	auto id = item->getId();

	// engine
	engine_->remove_lens(id);

	// 3D view
	view_3d_->remove_lens(id);

	// selector
	selector_->remove_lens(id);

	// editor
	editor_->mode_default();

}


void GuiWindow::save_slot(QString name, float x_tilt, float z_tilt, float distance, float optical_power)
{
	if (editing_)
	{
		auto item = dynamic_cast<LensListItem*>(selector_->currentItem());
		if (engine_->position_valid_lens(distance, item->getId()))
		{
			edit_lens(name, x_tilt, z_tilt, distance, optical_power, item->getId());
		}
		else
		{
			error_slot("Invalid distance.");
		}
	}
	else
	{
		if (engine_->position_valid_lens(distance, 0))
		{
			create_new_lens(name, x_tilt, z_tilt, distance, optical_power);
			editor_->mode_default();
			selector_->setDisabled(false);
		}
		else
		{
			error_slot("Invalid distance.");
		}
	}
}

void GuiWindow::cancel_slot()
{
	editor_->mode_default();
	selector_->setDisabled(false);
	selector_->clearSelection();
	view_3d_->set_active(0);
}


void GuiWindow::create_new_lens(QString name, float x_tilt, float z_tilt, float distance, float optical_power)
{
	auto id = engine_->add_lens(distance, 10., optical_power, name.toStdString(), TO_RADIANS(x_tilt), TO_RADIANS(z_tilt));
	view_3d_->add_lens(distance, x_tilt, z_tilt, id);
	selector_->add_lens(id, name);
}


void GuiWindow::edit_lens(QString name, float x_tilt, float z_tilt, float distance, float optical_power, int id)
{
	auto std_name = name.toStdString();

	// edit engine
	auto lens = engine_->get_lens_by_id(id);

	lens->set_name(name.toStdString());

	engine_->set_lens_distance_from_source(id, distance);
	lens->set_optical_power(optical_power);
	lens->set_deviationX(TO_RADIANS(x_tilt));
	lens->set_deviationY(TO_RADIANS(z_tilt));

	// edit list
	selector_->edit_lens(name);

	// edit 3d_view
	view_3d_->edit_lens(id, x_tilt, z_tilt, distance);
}


void GuiWindow::misc_editor_edit_slot_()
{
	misc_editor_->edit_mode();
}

void GuiWindow::misc_editor_cancel_slot_()
{
	// TODO load conf
	auto sample = engine_->get_sample();
	auto rays_n = engine_->ray_count();
	auto s_distance = sample->distance_from_source();
	auto s_tilt_y = engine_->get_sample()->rotation;
	auto d_distance = engine_->get_detector()->distance_from_source();
	misc_editor_->set_configuration(rays_n, s_tilt_y, s_distance, d_distance);
	misc_editor_->default_mode();
}

void GuiWindow::misc_editor_save_slot(unsigned rays_n, double y_tilt, double distance_s, double distance_d)
{
	// engine
	if (engine_->position_valid_sample(distance_s))
	{
		engine_->set_sample_distance_from_source(distance_s);
	}
	else {
		error_slot("Sample position is invalid.");
		return;
	}

	if (engine_->position_valid_detector(distance_d))
	{
		engine_->set_detector_distance_from_source(distance_d);
	}
	else {
		error_slot("Detector position is invalid.");
		return;
	}
	// TODO not good
	engine_->get_sample()->rotation = y_tilt;
	//engine_->set_number_rays(rays_n);
	
	// 3dview
	view_3d_->edit_sample(distance_s, y_tilt);
	view_3d_->edit_detector(distance_d);
}



void GuiWindow::error_slot(std::string error)
{
	QMessageBox messageBox;
	messageBox.critical(0, "Error", QString::fromStdString(error));
	messageBox.setFixedSize(500, 200);
}

