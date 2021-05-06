#pragma once
#include <QEntity>

#include "Base3D.h"

class Source3D : public Base3D
{
	static const QColor diffuse_color_default;

	static const QUrl mesh_location;

public:
	Source3D(Qt3DCore::QEntity* root_entity);
};

