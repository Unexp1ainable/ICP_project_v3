#include <QGuiApplication>
#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DExtras/QTorusMesh>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DRender/QPointLight>
#include <Qt3DRender/QCamera>
#include <Qt3DCore/QTransform>
#include <Qt3DExtras/QOrbitCameraController>

Qt3DCore::QEntity *createEntity();

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    Qt3DExtras::Qt3DWindow view;
    Qt3DCore::QEntity *rootEntity = createEntity();

    Qt3DRender::QCamera *camera = view.camera();
    camera->lens()->setPerspectiveProjection(60.f, static_cast<float>(view.width()) / view.height(), 0.1f, 1000.f);
    camera->setPosition(QVector3D(0.0f,0.0f,40.0f));
    camera->setViewCenter(QVector3D(0.0f,0.0f, 0.0f));

    Qt3DExtras::QOrbitCameraController *cameraController = new Qt3DExtras::QOrbitCameraController(rootEntity);
    cameraController->setCamera(camera);
    cameraController->setLinearSpeed(-60.0f);
    cameraController->setLookSpeed(-180.0f);

    view.setRootEntity(rootEntity);

    view.show();

    return app.exec();
}

// hello
Qt3DCore::QEntity *createEntity()
{
    Qt3DCore::QEntity *resultEntity = new Qt3DCore::QEntity;
    Qt3DExtras::QTorusMesh *torusMesh = new Qt3DExtras::QTorusMesh(resultEntity);
    torusMesh->setRadius(15.0f);
    torusMesh->setMinorRadius(6.0f);
    torusMesh->setSlices(16);
    torusMesh->setRings(32);
    Qt3DExtras::QPhongMaterial *torusMaterial = new Qt3DExtras::QPhongMaterial(resultEntity);

    Qt3DCore::QTransform *torusTransform = new Qt3DCore::QTransform(resultEntity);

    resultEntity->addComponent(torusMesh);
    resultEntity->addComponent(torusMaterial);
    resultEntity->addComponent(torusTransform);

    Qt3DCore::QEntity *lightEntity = new Qt3DCore::QEntity(resultEntity);

    Qt3DRender::QPointLight * pointLight = new Qt3DRender::QPointLight(lightEntity);
    Qt3DCore::QTransform *lightTransform = new Qt3DCore::QTransform(resultEntity);
    lightTransform->setTranslation(QVector3D(0.0f, 20.0f, 30.0f));

    lightEntity->addComponent(pointLight);
    lightEntity->addComponent(lightTransform);

    return resultEntity;
}
