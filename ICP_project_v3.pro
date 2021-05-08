######################################################################
# Automatically generated by qmake (3.1) Sat May 8 21:42:28 2021
######################################################################

TEMPLATE = app
TARGET = ICP_project_v3
INCLUDEPATH += .
QMAKE_CXXFLAGS += -lm
QT +=  3dcore 3drender 3dinput 3dlogic 3dextras 3danimation widgets

# You can make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# Please consult the documentation of the deprecated API in order to know
# how to port your code away from it.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Input
HEADERS += rayTracer/AxisObject.h \
           rayTracer/Detector.h \
           rayTracer/Lens.h \
           rayTracer/Point.h \
           rayTracer/Ray.h \
           rayTracer/RayEngine.h \
           rayTracer/Sample.h \
           src/common/macros.h \
           src/gui/MainGui.h \
           src/gui/Classes3D/Base3D.h \
           src/gui/Classes3D/Detector3D.h \
           src/gui/Classes3D/Lens3D.h \
           src/gui/Classes3D/Line3D.h \
           src/gui/Classes3D/Sample3D.h \
           src/gui/Classes3D/Source3D.h \
           src/gui/ClassesGui/GuiWindow.h \
           src/gui/ClassesGui/LensEditor.h \
           src/gui/ClassesGui/LensList.h \
           src/gui/ClassesGui/LensListItem.h \
           src/gui/ClassesGui/MiscEditor.h \
           src/gui/ClassesGui/SceneViewer.h \
           src/gui/ClassesGui/ShapeViewer.h \
           src/gui/ClassesGui/SurfaceInfoPanel.h \
           src/gui/commonGui/Scene.h
SOURCES += main.cpp \
           rayTracer/Detector.cpp \
           rayTracer/Lens.cpp \
           rayTracer/RayEngine.cpp \
           rayTracer/Sample.cpp \
           src/gui/MainGui.cpp \
           src/gui/Classes3D/Base3D.cpp \
           src/gui/Classes3D/Detector3D.cpp \
           src/gui/Classes3D/Lens3D.cpp \
           src/gui/Classes3D/Line3D.cpp \
           src/gui/Classes3D/Sample3D.cpp \
           src/gui/Classes3D/Source3D.cpp \
           src/gui/ClassesGui/GuiWindow.cpp \
           src/gui/ClassesGui/LensEditor.cpp \
           src/gui/ClassesGui/LensList.cpp \
           src/gui/ClassesGui/LensListItem.cpp \
           src/gui/ClassesGui/MiscEditor.cpp \
           src/gui/ClassesGui/SceneViewer.cpp \
           src/gui/ClassesGui/ShapeViewer.cpp \
           src/gui/ClassesGui/SurfaceInfoPanel.cpp \
           src/gui/commonGui/Scene.cpp
