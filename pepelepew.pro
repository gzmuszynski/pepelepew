#-------------------------------------------------
#
# Project created by QtCreator 2018-01-31T16:47:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = pepelepew
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        contextwindow.cpp \
    buffer.cpp \
    float4.cpp \
    vertex.cpp \
    rasterizer.cpp \
    vertexprocessor.cpp \
    fragmentprocessor.cpp \
    mesh.cpp \
    trianglefunction.cpp \
    camera.cpp \
    postprocessor.cpp \
    cube.cpp \
    light.cpp \
    deferredshading.cpp \
    curvilineartrianglefunction.cpp \
    noperspectivevertexshader.cpp \
    curvilinearvertexshader.cpp \
    barreldistortionpostprocess.cpp \
    material.cpp \
    sphericalvertexshader.cpp \
    curvilinearvertexshader2.cpp \
    mrtrasterizer.cpp \
    cubicprojection.cpp

HEADERS += \
        contextwindow.h \
    buffer.h \
    float4.h \
    vertex.h \
    rasterizer.h \
    vertexprocessor.h \
    fragmentprocessor.h \
    mat4.h \
    mesh.h \
    trianglefunction.h \
    camera.h \
    postprocessor.h \
    cube.h \
    light.h \
    deferredshading.h \
    curvilineartrianglefunction.h \
    noperspectivevertexshader.h \
    curvilinearvertexshader.h \
    barreldistortionpostprocess.h \
    material.h \
    sphericalvertexshader.h \
    curvilinearvertexshader2.h \
    mrtrasterizer.h \
    cubicprojection.h

FORMS += \
        contextwindow.ui
