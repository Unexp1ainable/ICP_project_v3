#include "GuiWindow.h"

#include <iostream>

#include "LensEditor.h"
#include "LensSelectorItem.h"
#include "MiscEditor.h"
#include "SceneViewer.h"
#include "SurfaceInfoPanel.h"
#include "src/common/macros.h"


GuiWindow::GuiWindow(rayEngine* engine)
{
	init_engine(engine);
	
	create_menu();

	const auto editor_box = create_lens_editor();
	const auto view_3d_box = create_3d_view();
	const auto selector_box = create_selector();
	const auto misc_editor_box = create_misc_editor();
	const auto s_info_box = create_sample_info();
	const auto d_info_box = create_detector_info();

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

	load_configuration();

	update_system();
}


void GuiWindow::init_engine(rayEngine* engine)
{
	engine_ = engine;
	engine_->init_rays(INIT_RAY_RADIUS, INIT_RAY_COUNT);
	engine_->set_detector_size_x(DETECTOR_SIZE);
	engine_->set_detector_size_y(DETECTOR_SIZE);
	engine_->set_sample_size_x(SAMPLE_SIZE);
	engine_->set_sample_size_y(SAMPLE_SIZE);
}

void GuiWindow::create_menu()
{
	const QIcon openIcon = QIcon::fromTheme("document-open", QIcon(":/images/open.png"));
	auto load_act = new QAction(openIcon, tr("&Load..."), this);
	load_act->setShortcuts(QKeySequence::Open);
	load_act->setStatusTip(tr("Open an existing file"));

	const QIcon saveIcon = QIcon::fromTheme("document-save", QIcon(":/images/save.png"));
	auto save_act = new QAction(saveIcon, tr("&Save..."), this);
	load_act->setShortcuts(QKeySequence::Save);
	load_act->setStatusTip(tr("Save to file"));

	auto file_menu = menuBar()->addMenu(tr("File"));
	file_menu->addAction(load_act);
	file_menu->addAction(save_act);

	connect(load_act, &QAction::triggered, this, &GuiWindow::open_file_slot);
	connect(save_act, &QAction::triggered, this, &GuiWindow::save_file_slot);
}


QGroupBox* GuiWindow::create_3d_view()
{
	view_3d_ = new SceneViewer(engine_);
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
	editor_->mode_default();

	auto vbox = new QVBoxLayout;
	vbox->addWidget(editor_);
	e_box->setLayout(vbox);

	return e_box;
}

QGroupBox* GuiWindow::create_selector()
{
	auto s_box = new QGroupBox;
	s_box->setTitle(tr("Lens selector."));

	selector_ = new LensSelector;
	auto* layout = new QGridLayout;

	layout->addWidget(selector_);
	s_box->setLayout(layout);

	return s_box;
}

QGroupBox* GuiWindow::create_misc_editor()
{
	auto i_box = new QGroupBox;
	i_box->setTitle(tr("Sample and detector editor."));

	auto vbox = new QHBoxLayout;

	misc_editor_ = new MiscEditor;

	vbox->addWidget(misc_editor_);

	i_box->setLayout(vbox);
	return i_box;
}



QGroupBox* GuiWindow::create_sample_info()
{
	auto i_box = new QGroupBox;
	i_box->setTitle(tr("Informations about rays passing through the sample."));

	auto vbox = new QHBoxLayout;
	sample_info_ = new SurfaceInfoPanel{SAMPLE_SIZE};

	vbox->addWidget(sample_info_);
	i_box->setLayout(vbox);
	return i_box;
}

QGroupBox* GuiWindow::create_detector_info()
{
	auto i_box = new QGroupBox;
	i_box->setTitle(tr("Informations about rays striking the detector."));

	auto vbox = new QHBoxLayout;
	detector_info_ = new SurfaceInfoPanel{DETECTOR_SIZE};
	
	vbox->addWidget(detector_info_);
	i_box->setLayout(vbox);
	return i_box;
}

void GuiWindow::clear_configuration() const
{
	misc_editor_->default_mode();
	view_3d_->clear_lenses();
	selector_->clear();
}


void GuiWindow::load_configuration() const
{
	// clear
	clear_configuration();
	
	// lenses
	for (int i = 0; i < engine_->lens_count(); i++)
	{
		const auto id = engine_->lens_index_to_id(i);
		const auto distance = engine_->get_lens_distance_from_source(id);
		const auto x_tilt = TO_DEGREES(engine_->get_lens_deviation_x(id));
		const auto z_tilt = TO_DEGREES(engine_->get_lens_deviation_y(id));
		
		view_3d_->add_lens(distance, x_tilt, z_tilt, id);
		selector_->addItem(new LensSelectorItem{ id, QString::fromStdString(engine_->get_lens_name(id)) });
	}

	// detector and sample
	misc_editor_cancel_slot_(); // it will initialize values from the engine

	// misc editor
	misc_editor_->default_mode();
}


void GuiWindow::connect_elements() const
{
	// -------- Lens Editor ---------
	// connect selection loading
	connect(selector_, &QListWidget::itemClicked, this, &GuiWindow::selection_changed_slot);
	// connect button new
	connect(editor_->get_button_new(), &QPushButton::clicked, this, &GuiWindow::mode_new_slot);
	// connect button edit
	connect(editor_->get_button_edit(), &QPushButton::clicked, this, &GuiWindow::mode_edit_slot); //infopanels

	// 3d view;
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

void GuiWindow::open_file_slot()
{
	const auto fileName = QFileDialog::getOpenFileName(this,
		tr("Open configuration"), "", tr("*.re"));

	if (fileName.compare("") == 0)
		return;

	engine_->load_config(fileName.toStdString());
	load_configuration();
	update_system();
}

void GuiWindow::save_file_slot()
{
	const auto fileName = QFileDialog::getSaveFileName(this,
		tr("Open configuration"), "", tr("*.re"));

	if (fileName.compare("") == 0)
		return;

	engine_->save_config(fileName.toStdString());
}


void GuiWindow::selection_changed_slot(QListWidgetItem* item) const
{
	const auto lens_item = dynamic_cast<LensSelectorItem*>(item);	// casting back so I can access id
	const auto id = lens_item->getId();
	
	const auto name = engine_->get_lens_name(id);
	const auto distance = engine_->get_lens_distance_from_source(id);
	const auto x_tilt = TO_DEGREES(engine_->get_lens_deviation_x(id));
	const auto z_tilt = TO_DEGREES(engine_->get_lens_deviation_y(id));
	const auto o_power = engine_->get_lens_optical_power(id);
	
	editor_->load_lens(name, x_tilt, z_tilt, o_power, distance);

	// enable buttons
	editor_->get_button_edit()->setDisabled(false);
	editor_->get_button_delete()->setDisabled(false);

	view_3d_->set_active(id);
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
	update_system();
}

void GuiWindow::delete_slot()
{
	auto item = dynamic_cast<LensSelectorItem*>(selector_->currentItem());
	auto id = item->getId();

	// engine
	engine_->remove_lens(id);

	// 3D view
	view_3d_->remove_lens(id);

	// selector
	selector_->remove_lens(id);

	// editor
	editor_->mode_default();

	update_system();
}


void GuiWindow::save_slot(QString name, double x_tilt, double z_tilt, double distance, double optical_power)
{
	if (editing_)
	{
		auto item = dynamic_cast<LensSelectorItem*>(selector_->currentItem());
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

	update_system();
}

void GuiWindow::cancel_slot() const
{
	editor_->mode_default();
	selector_->setDisabled(false);
	selector_->clearSelection();
	view_3d_->set_active(0);
}


void GuiWindow::create_new_lens(QString name, double x_tilt, double z_tilt, double distance, double optical_power) const
{
	try
	{
		auto id = engine_->add_lens(distance, 10., optical_power, name.toStdString(), TO_RADIANS(x_tilt), TO_RADIANS(z_tilt));
		view_3d_->add_lens(distance, x_tilt, z_tilt, id);
		selector_->add_lens(id, name);
	}
	catch (rayEngine::invalid_distance)
	{
		error_slot("Invalid lens distance.");
	}
	catch (Lens::invalid_optical_power)
	{
		error_slot("Invalid optical power.");
	}
	catch (Lens::invalid_deviation)
	{
		error_slot("Invalid rotation.");
	}
	catch (Lens::invalid_radius)
	{
		error_slot("Invalid radius.");
	}
	
}


void GuiWindow::edit_lens(QString name, double x_tilt, double z_tilt, double distance, double optical_power, int id) const
{
	auto std_name = name.toStdString();

	try {
		// edit engine
		engine_->set_lens_distance_from_source(id, distance);
		engine_->set_lens_optical_power(id, optical_power);
		engine_->set_lens_deviation_x(id, TO_RADIANS(x_tilt));
		engine_->set_lens_deviation_y(id, TO_RADIANS(z_tilt));
		engine_->set_lens_name(id, name.toStdString());

		// edit list
		selector_->edit_lens(name);

		// edit 3d_view
		view_3d_->edit_lens(id, x_tilt, z_tilt, distance);

	}
	catch (rayEngine::invalid_distance)
	{
		error_slot("Invalid lens distance.");
	}
	catch (Lens::invalid_optical_power)
	{
		error_slot("Invalid optical power.");
	}
	catch (Lens::invalid_deviation)
	{
		error_slot("Invalid rotation.");
	}
	catch (Lens::invalid_radius)
	{
		error_slot("Invalid radius.");
	}
}


void GuiWindow::misc_editor_edit_slot_() const
{
	misc_editor_->edit_mode();
}

void GuiWindow::misc_editor_cancel_slot_() const
{
	auto rays_n = engine_->ray_count();
	auto r_diameter = engine_->get_ray_cluster_diameter();
	auto s_distance = engine_->get_sample_distance_from_source();
	auto s_tilt_y = engine_->get_sample_rotation();
	auto d_distance = engine_->get_detector_distance_from_source();
	
	misc_editor_->set_configuration(rays_n, s_tilt_y, s_distance, d_distance, r_diameter);
	misc_editor_->default_mode();
}

void GuiWindow::misc_editor_save_slot(unsigned rays_n, double y_tilt, double distance_s, double distance_d, double r_diameter)
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
	
	engine_->set_sample_rotation(y_tilt);

	engine_->init_rays(r_diameter, rays_n);
	

	// 3dview
	view_3d_->edit_sample(distance_s, y_tilt);
	view_3d_->edit_detector(distance_d);

	update_system();
}



void GuiWindow::error_slot(std::string error) const
{
	QMessageBox message_box;
	QMessageBox::critical(nullptr, "Error", QString::fromStdString(error));
	message_box.setFixedSize(500, 200);
}

void GuiWindow::update_system() const
{
	engine_->update();
	view_3d_->update(engine_->get_ray_points());
	sample_info_->parse_points(engine_->get_sample_intersect());
	detector_info_->parse_points(engine_->get_detector_intersect());
}
