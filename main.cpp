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
class Line
{
private:
    /* data */
public:

    //https://stackoverflow.com/questions/38067867/how-do-i-draw-a-simple-line-in-qt3d
    Line(const QVector3D &start, const QVector3D &end, const QColor& color, Qt3DCore::QEntity *_rootEntity)
    {
        auto *geometry = new Qt3DRender::QGeometry(_rootEntity);

        // position vertices (start and end)
        QByteArray bufferBytes;
        bufferBytes.resize(3 * 2 * sizeof(float)); // start.x, start.y, start.end + end.x, end.y, end.z
        float *positions = reinterpret_cast<float *>(bufferBytes.data());
        *positions++ = start.x();
        *positions++ = start.y();
        *positions++ = start.z();
        *positions++ = end.x();
        *positions++ = end.y();
        *positions++ = end.z();

        auto *buf = new Qt3DRender::QBuffer(Qt3DRender::QBuffer::VertexBuffer, geometry);
        buf->setData(bufferBytes);

        auto *positionAttribute = new Qt3DRender::QAttribute(geometry);

        positionAttribute->setName(Qt3DRender::QAttribute::defaultPositionAttributeName());
        positionAttribute->setVertexBaseType(Qt3DRender::QAttribute::Float);
        positionAttribute->setVertexSize(3);
        positionAttribute->setAttributeType(Qt3DRender::QAttribute::VertexAttribute);
        positionAttribute->setBuffer(buf);
        positionAttribute->setByteStride(3 * sizeof(float));
        positionAttribute->setCount(2);
        geometry->addAttribute(positionAttribute); // We add the vertices in the geometry

        // connectivity between vertices
        QByteArray indexBytes;
        indexBytes.resize(2 * sizeof(unsigned int)); // start to end
        unsigned int *indices = reinterpret_cast<unsigned int *>(indexBytes.data());
        *indices++ = 0;
        *indices++ = 1;

        auto *indexBuffer = new Qt3DRender::QBuffer(Qt3DRender::QBuffer::IndexBuffer, geometry);
        indexBuffer->setData(indexBytes);

        auto *indexAttribute = new Qt3DRender::QAttribute(geometry);
        indexAttribute->setVertexBaseType(Qt3DRender::QAttribute::UnsignedInt);
        indexAttribute->setAttributeType(Qt3DRender::QAttribute::IndexAttribute);
        indexAttribute->setBuffer(indexBuffer);
        indexAttribute->setCount(2);
        geometry->addAttribute(indexAttribute); // We add the indices linking the points in the geometry

        // mesh
        auto *line = new Qt3DRender::QGeometryRenderer(_rootEntity);
        line->setGeometry(geometry);
        line->setPrimitiveType(Qt3DRender::QGeometryRenderer::Lines);
        auto *material = new Qt3DExtras::QPhongMaterial(_rootEntity);
        material->setAmbient(color);

        // entity
        auto *lineEntity = new Qt3DCore::QEntity(_rootEntity);
        lineEntity->addComponent(line);
        lineEntity->addComponent(material);
    }
    
};

Qt3DCore::QEntity *createScene();
void addMockObject(Qt3DCore::QEntity *rootEntity);

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    Qt3DExtras::Qt3DWindow view;
    Qt3DCore::QEntity *rootEntity = createScene();

    addMockObject(rootEntity);



    Line{QVector3D(0.0f,0.0f,0.0f), QVector3D(100.0f,0.0f,0.0f),QColor(255,0,0), rootEntity};
    Line{QVector3D(0.0f,0.0f,0.0f), QVector3D(0.0f,100.0f,0.0f),QColor(0,255,0), rootEntity};
    Line{QVector3D(0.0f,0.0f,0.0f), QVector3D(0.0f,0.0f,100.0f),QColor(0,0,255), rootEntity};

    Qt3DRender::QCamera *camera = view.camera();
    camera->lens()->setPerspectiveProjection(60.f, static_cast<float>(view.width()) / view.height(), 0.1f, 1000.f);
    camera->setPosition(QVector3D(0.0f, 0.0f, 40.0f));
    camera->setViewCenter(QVector3D(0.0f, 0.0f, 0.0f));

    Qt3DExtras::QOrbitCameraController *cameraController = new Qt3DExtras::QOrbitCameraController(rootEntity);
    cameraController->setCamera(camera);
    cameraController->setLinearSpeed(-40.0f);
    cameraController->setLookSpeed(-120.0f);

    view.setRootEntity(rootEntity);

    view.show();

    return app.exec();
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
    Qt3DExtras::QTorusMesh *torusMesh = new Qt3DExtras::QTorusMesh(rootEntity);
    torusMesh->setRadius(15.0f);
    torusMesh->setMinorRadius(6.0f);
    torusMesh->setSlices(16);
    torusMesh->setRings(32);
    Qt3DExtras::QPhongMaterial *torusMaterial = new Qt3DExtras::QPhongMaterial(rootEntity);

    Qt3DCore::QTransform *torusTransform = new Qt3DCore::QTransform(rootEntity);

    rootEntity->addComponent(torusMesh);
    rootEntity->addComponent(torusMaterial);
    rootEntity->addComponent(torusTransform);
}
