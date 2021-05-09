#include "RayCluster3D.h"

#include <qcomponent.h>
#include <QColor>

RayCluster3D::RayCluster3D(Qt3DCore::QEntity* parent, vector<vector<std::shared_ptr<Point>>> rays)
{
    setParent(parent);
	
	for (auto ray : rays)
	{
		rays_.push_back(new Ray3D{this, ray});
	}
}