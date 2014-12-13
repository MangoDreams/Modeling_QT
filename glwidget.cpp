#include "glwidget.h"
#include <GL/glut.h>

GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent)
{
    _mySkeleton = new SkeletalModel();

    _mySkeleton->load("../character_animation/data/Model1.skel","../character_animation/data/Model1.obj","../character_animation/data/Model1.attach");

    _camera = new Camera();
    _skeletonVisible = true;
    _camera->SetDistance( 2 );
    _camera->SetCenter( Vector3f( 0.5, 0.5, 0.5 ) );


}

GLWidget::~GLWidget(){
    delete _mySkeleton;
    delete _camera;
}

void GLWidget::initializeGL() {
    // Setup opengl
    glShadeModel( GL_SMOOTH );
    glEnable( GL_DEPTH_TEST );
    glEnable( GL_LIGHTING );
    glEnable( GL_LIGHT0 );
    glEnable( GL_NORMALIZE );

    // Note that the lighting is applied *before* applying the camera
    // transform.  This is so the light appeared fixed on the camera.
    GLfloat Lt0diff[] = {1.0,1.0,1.0,1.0};
    GLfloat Lt0pos[] = {3.0,3.0,5.0,1.0};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, Lt0diff);
    glLightfv(GL_LIGHT0, GL_POSITION, Lt0pos);

    // These are just some default material colors
    GLfloat diffColor[] = {0.4f, 0.4f, 0.4f, 1.f};
    GLfloat specColor[] = {0.6f, 0.6f, 0.6f, 1.f};
    GLfloat shininess[] = {50.0f};

    glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, diffColor );
    glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, specColor );
    glMaterialfv( GL_FRONT_AND_BACK, GL_SHININESS, shininess );


}

void GLWidget::resizeGL(int w, int h) {

    _camera->SetDimensions(w,h);
    _camera->SetViewport(0,0,w,h);
    _camera->ApplyViewport();

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    _camera->SetPerspective( 50.0f );
    glLoadMatrixf(_camera->projectionMatrix() );
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

}

void GLWidget::paintGL() {
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    _mySkeleton->draw(_camera->viewMatrix(), _skeletonVisible );
}
