#include "GuiWindow.h"

#include <iostream>
#include <QSizePolicy>

#include "LensEditor.h"
#include "LensListItem.h"
#include "SceneViewer.h"
#include "src/gui/Classes3D/GuiLens.h"
#include "src/gui/Classes3D/Line.h"
#include "src/gui/common/Scene.h"

GuiWindow::GuiWindow(rayEngine* engine)
{
	auto info_box = create_info();
	auto editor_box = create_editor();
	auto selector_box = create_selector();
	auto view_3d_box = create_3d_view();

	engine_ = engine;

	main_layout_ = new QGridLayout;
	main_layout_->setColumnStretch(0, 4);
	
	main_layout_->addWidget(view_3d_box, 0, 0, 5, 5);
	main_layout_->addWidget(selector_box, 0, 5, 2, 1);
	main_layout_->addWidget(editor_box, 2, 5, 1, 1);
	main_layout_->addWidget(info_box, 3, 5, 2, 1);

	auto central_widget = new QWidget(this);
	central_widget->setLayout(main_layout_);
	setCentralWidget(central_widget);
	/*setLayout(main_layout_);*/

	for (int i = 0; i < engine->lens_count(); i++)
	{
		auto lens = engine->get_lens_by_index(i);
		auto distance = lens->distance_from_source();
		auto x_tilt = lens->deviation_x();
		auto z_tilt = lens->deviation_y();
		view_3d_->add_lens(distance, x_tilt, z_tilt);

		selector_->addItem(new LensListItem{ lens->id(), QString::fromStdString(lens->name()) });
	}

	connect(selector_, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(selection_changed(QListWidgetItem *)));
}

QGroupBox* GuiWindow::create_3d_view()
{
	view_3d_ = new SceneViewer();
	view_3d_widget_ = view_3d_->get_window_widget();

	auto layout = new QBoxLayout{QBoxLayout::BottomToTop};

	auto view_3d_box = new QGroupBox;
	layout->addWidget(view_3d_widget_);
	view_3d_box->setLayout(layout);
	
	return view_3d_box;
}

QGroupBox* GuiWindow::create_editor()
{
	auto e_box = new QGroupBox;
	e_box->setTitle(tr("GuiLens control."));

	editor_ = new LensEditor;

	auto vbox = new QVBoxLayout;
	vbox->addWidget(editor_);
	e_box->setLayout(vbox);

	return e_box;
}

QGroupBox* GuiWindow::create_selector()
{
	auto s_box = new QGroupBox;
	s_box->setTitle(tr("Lens editor."));

	selector_ = new LensList;
	auto* layout = new QGridLayout;

	layout->addWidget(selector_);
	s_box->setLayout(layout);

	return s_box;
}


QGroupBox* GuiWindow::create_info()
{
	auto i_box = new QGroupBox;
	i_box->setTitle(tr("Informations about rays on detector."));

	auto button = new QPushButton("New", this);
	connect(button, SIGNAL(clicked()), this, SLOT(button_clicked_()));

	QVBoxLayout* vbox = new QVBoxLayout;
	vbox->addWidget(button);
	i_box->setLayout(vbox);

	info_ = i_box; // TODO temporary
	return i_box;
}

void GuiWindow::selection_changed(QListWidgetItem* item)
{
	auto item2 = dynamic_cast<LensListItem*>(item);	// casting back so I can access id
	
	std::cerr << "AAAAAAAAAAA" << std::endl;
	auto to_load = engine_->get_lens_by_id(item2->getId());
	editor_->load_lens(to_load);
}
