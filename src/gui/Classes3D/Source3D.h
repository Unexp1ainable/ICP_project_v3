#pragma once
#include <QEntity>

class Source3D : public Qt3DCore::QEntity
{
	static const QColor diffuse_color_default;

	static const QUrl mesh_location;

public:
	Source3D(Qt3DCore::QEntity* root_entity);
};

