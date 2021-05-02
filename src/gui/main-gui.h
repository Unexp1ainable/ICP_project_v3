#pragma once
#include <QEntity>
#include <Qt3DWindow>

int run_gui(int argc, char* argv[]);

Qt3DCore::QEntity* create_scene();
void add_mock_object(Qt3DCore::QEntity* root_entity);
void add_camera(Qt3DExtras::Qt3DWindow& view, Qt3DCore::QEntity* root_entity);