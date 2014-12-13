#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <GL/glut.h>
#include "SkeletalModel.h"
#include "camera.h"

class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = 0);
    ~GLWidget();

    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

    Camera* _camera;
    SkeletalModel* _mySkeleton;
    bool _skeletonVisible;

};

#endif // GLWIDGET_H
