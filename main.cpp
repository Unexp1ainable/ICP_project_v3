#include <QGuiApplication>
#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DExtras/QTorusMesh>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DRender/QPointLight>
#include <Qt3DRender/QCamera>
#include <Qt3DCore/QTransform>
#include <Qt3DExtras/QOrbitCameraController>
#include <Qt3DRender/QGeometry>
#include <Qt3DRender/QGeometryRenderer>
#include <Qt3DRender/QBuffer>
#include <Qt3DRender/QAttribute>
#include "src/renderObjects.h"

Qt3DCore::QEntity *createScene();
void addMockObject(Qt3DCore::QEntity *rootEntity);
void addCamera(Qt3DExtras::Qt3DWindow& view, Qt3DCore::QEntity *rootEntity);

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    Qt3DExtras::Qt3DWindow view;
    Qt3DCore::QEntity *rootEntity = createScene();

    addMockObject(rootEntity);



    Line{QVector3D(0.0f,0.0f,0.0f), QVector3D(100.0f,0.0f,0.0f),QColor(255,0,0), rootEntity};
    Line{QVector3D(0.0f,0.0f,0.0f), QVector3D(0.0f,100.0f,0.0f),QColor(0,255,0), rootEntity};
    Line{QVector3D(0.0f,0.0f,0.0f), QVector3D(0.0f,0.0f,100.0f),QColor(0,0,255), rootEntity};


    addCamera(view, rootEntity);
    view.setRootEntity(rootEntity);
    view.show();

    return app.exec();
}

void addCamera(Qt3DExtras::Qt3DWindow& view, Qt3DCore::QEntity *rootEntity){
    Qt3DRender::QCamera *camera = view.camera();
    camera->lens()->setPerspectiveProjection(60.f, static_cast<float>(view.width()) / view.height(), 0.1f, 1000.f);
    camera->setPosition(QVector3D(0.0f, 0.0f, 40.0f));
    camera->setViewCenter(QVector3D(0.0f, 0.0f, 0.0f));

    Qt3DExtras::QOrbitCameraController *cameraController = new Qt3DExtras::QOrbitCameraController(rootEntity);
    cameraController->setCamera(camera);
    cameraController->setLinearSpeed(-40.0f);
    cameraController->setLookSpeed(-120.0f);
}


// hello
Qt3DCore::QEntity *light(QVector3D position, Qt3DCore::QNode *parent)
{
    Qt3DCore::QEntity *lightEntity = new Qt3DCore::QEntity(parent);
    Qt3DRender::QPointLight *pointLight = new Qt3DRender::QPointLight(lightEntity);
    Qt3DCore::QTransform *lightTransform = new Qt3DCore::QTransform(lightEntity);
    lightTransform->setTranslation(position);
    lightEntity->addComponent(pointLight);
    lightEntity->addComponent(lightTransform);

    return lightEntity;
}

Qt3DCore::QEntity *createScene()
{
    Qt3DCore::QEntity *resultEntity = new Qt3DCore::QEntity;

    light(QVector3D(0.0f, 20.0f, 30.0f), resultEntity);
    light(QVector3D(0.0f, 20.0f, -30.0f), resultEntity);

    return resultEntity;
}

void addMockObject(Qt3DCore::QEntity *rootEntity)
{
    Qt3DCore::QEntity *torusEntity = new Qt3DCore::QEntity(rootEntity);
    Qt3DExtras::QTorusMesh *torusMesh = new Qt3DExtras::QTorusMesh;
    torusMesh->setRadius(15.0f);
    torusMesh->setMinorRadius(6.0f);
    torusMesh->setSlices(16);
    torusMesh->setRings(32);

    Qt3DExtras::QPhongMaterial *torusMaterial = new Qt3DExtras::QPhongMaterial;

    Qt3DCore::QTransform *torusTransform = new Qt3DCore::QTransform;

    torusEntity->addComponent(torusMesh);
    torusEntity->addComponent(torusMaterial);
    torusEntity->addComponent(torusTransform);
}
