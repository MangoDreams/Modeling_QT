#-------------------------------------------------
#
# Project created by QtCreator 2014-12-09T19:54:14
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = character_animation
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    glwidget.cpp \
    Vector3f.cpp \
    Matrix2f.cpp \
    Matrix3f.cpp \
    Matrix4f.cpp \
    Quat4f.cpp \
    Vector2f.cpp \
    Vector4f.cpp \
    MatrixStack.cpp \
    Mesh.cpp \
    SkeletalModel.cpp \
    camera.cpp

HEADERS  += mainwindow.h \
    glwidget.h \
    tuple.h \
    Matrix2f.h \
    Matrix3f.h \
    Matrix4f.h \
    Quat4f.h \
    vecmath.h \
    Vector2f.h \
    Vector3f.h \
    Vector4f.h \
    MatrixStack.h \
    Joint.h \
    Mesh.h \
    SkeletalModel.h \
    camera.h

FORMS    += mainwindow.ui

LIBS += -lglut -lGLU
