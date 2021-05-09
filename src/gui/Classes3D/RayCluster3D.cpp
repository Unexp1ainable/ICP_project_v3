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

//RayCluster3D::~RayCluster3D()
//{
//    delete b;
//
//	for (auto ray : rays_)
//	{
//		delete ray;
//	}
////
////    /*auto children_nodes = childNodes();
////    foreach(auto * child_node, children_nodes) {
////        deleteChildrenRecursively(child_node);
////    }*/
////
//}

void RayCluster3D::deleteChildrenRecursively(Qt3DCore::QNode* node)
{
    Qt3DCore::QEntity* entity = dynamic_cast<Qt3DCore::QEntity*>(node);
    if (entity == nullptr) {
        return;
    }
    auto components_to_delete = entity->components();
    foreach(auto * component, components_to_delete) {
        entity->removeComponent(component);
        delete component;
        component = nullptr;
    }
    auto children_nodes = entity->childNodes();
    foreach(auto * child_node, children_nodes) {
        deleteChildrenRecursively(child_node);
    }
    delete entity;
    entity = nullptr;
}