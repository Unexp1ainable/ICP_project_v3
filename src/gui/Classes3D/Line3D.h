#pragma once
#include <QEntity>
#include <QVector3D>


class Line3D : public Qt3DCore::QEntity
{
public:
    //https://stackoverflow.com/questions/38067867/how-do-i-draw-a-simple-line-in-qt3d
    Line3D(const QVector3D& start, const QVector3D& end, const QColor& color, Qt3DCore::QEntity* root_entity);
    //~Line3D();
private:
    Qt3DCore::QEntity* line_entity_;
};

