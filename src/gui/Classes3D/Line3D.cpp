/**
 * @file Lens3D.cpp
 * @author Rémi Ducceschi
 * @date 11/05/2021
 * @brief Implementation of Line3D class
 *
 * This code was copied from https://stackoverflow.com/questions/38067867/how-do-i-draw-a-simple-line-in-qt3d
 */

#include "Line3D.h"

#include <QPhongMaterial>
#include <Qt3DRender>

Line3D::Line3D(const QVector3D& start, const QVector3D& end, const QColor& color, Qt3DCore::QEntity* root_entity)
{	
	setParent(root_entity);
	auto* geometry = new Qt3DRender::QGeometry(this);

	// position vertices (start and end)
	QByteArray buffer_bytes;
	buffer_bytes.resize(3 * 2 * sizeof(float)); // start.x, start.y, start.end + end.x, end.y, end.z
	auto positions = reinterpret_cast<float*>(buffer_bytes.data());
	*positions++ = start.x();
	*positions++ = start.y();
	*positions++ = start.z();
	*positions++ = end.x();
	*positions++ = end.y();
	*positions++ = end.z();

	auto* buf = new Qt3DRender::QBuffer(Qt3DRender::QBuffer::VertexBuffer, geometry);
	buf->setData(buffer_bytes);

	auto* position_attribute = new Qt3DRender::QAttribute(geometry);

	position_attribute->setName(Qt3DRender::QAttribute::defaultPositionAttributeName());
	position_attribute->setVertexBaseType(Qt3DRender::QAttribute::Float);
	position_attribute->setVertexSize(3);
	position_attribute->setAttributeType(Qt3DRender::QAttribute::VertexAttribute);
	position_attribute->setBuffer(buf);
	position_attribute->setByteStride(3 * sizeof(float));
	position_attribute->setCount(2);
	geometry->addAttribute(position_attribute); // We add the vertices in the geometry

	// connectivity between vertices
	QByteArray index_bytes;
	index_bytes.resize(2 * sizeof(unsigned int)); // start to end
	auto indices = reinterpret_cast<unsigned int*>(index_bytes.data());
	*indices++ = 0;
	*indices++ = 1;

	auto* index_buffer = new Qt3DRender::QBuffer(Qt3DRender::QBuffer::IndexBuffer, geometry);
	index_buffer->setData(index_bytes);

	auto* index_attribute = new Qt3DRender::QAttribute(geometry);
	index_attribute->setVertexBaseType(Qt3DRender::QAttribute::UnsignedInt);
	index_attribute->setAttributeType(Qt3DRender::QAttribute::IndexAttribute);
	index_attribute->setBuffer(index_buffer);
	index_attribute->setCount(2);
	geometry->addAttribute(index_attribute); // We add the indices linking the points in the geometry

	// mesh
	auto* line = new Qt3DRender::QGeometryRenderer(this);
	line->setGeometry(geometry);
	line->setPrimitiveType(Qt3DRender::QGeometryRenderer::Lines);
	auto* material = new Qt3DExtras::QPhongMaterial(this);
	material->setAmbient(color);

	// entity
	addComponent(line);
	addComponent(material);
}

