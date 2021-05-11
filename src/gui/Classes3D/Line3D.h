#pragma once
/**
 * @file Lens3D.h
 * @author Rémi Ducceschi
 * @date 11/05/2021
 * @brief Simple line in 3D
 *
 * This code was copied from https://stackoverflow.com/questions/38067867/how-do-i-draw-a-simple-line-in-qt3d
 */

#include <QEntity>
#include <QVector3D>


class Line3D : public Qt3DCore::QEntity
{
public:
    Line3D(const QVector3D& start, const QVector3D& end, const QColor& color, Qt3DCore::QEntity* root_entity);
private:
    Qt3DCore::QEntity* line_entity_;
};

