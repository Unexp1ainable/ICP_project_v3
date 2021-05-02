#ifndef RENDEROBJECTS
#define RENDEROBJECTS
#include <QEntity>
#include <QVector3D>


class Line
{
private:
    /* data */
public:

    //https://stackoverflow.com/questions/38067867/how-do-i-draw-a-simple-line-in-qt3d
    Line(const QVector3D& start, const QVector3D& end, const QColor& color, Qt3DCore::QEntity* _rootEntity);
    
};

#endif /* RENDEROBJECTS */
