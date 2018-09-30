#include "oglwidget.h"
#include "expansion.h"
#define DELTA 1e-1
#define SEGMENT 5e-2
#define GRID 1e-3

double f(double x);
OGLWidget::OGLWidget(QWidget *parent) : QOpenGLWidget(parent)
{

}

void OGLWidget::initializeGL()
{
       glClearColor(255,255,255,1);
}

void OGLWidget::paintGL()
{
    //Рисуем коорд прямые
    //x
    glTranslated(-0.9,0,0);
    glColor3f(0,0,0);
    glBegin(GL_LINES);
        glVertex3f(-2,0,0);
        glVertex3f(2,0,0);
    glEnd();
    for ( double i = -1; i <= 2; i += DELTA){
        glBegin(GL_LINES);
            glVertex3f(i,SEGMENT,0);
            glVertex3f(i,-SEGMENT,0);
        glEnd();
     }
    //y
    glBegin(GL_LINES);
        glVertex3f(0,1,0);
        glVertex3f(0,-1,0);
    glEnd();
    for ( double i = -1; i <= 1; i += DELTA){
        glBegin(GL_LINES);
            glVertex3f(SEGMENT,i,0);
            glVertex3f(-SEGMENT,i,0);
        glEnd();
     }

    expansion Expansion;
    //Рисуем график
    glColor3f(255,0,0);
     glBegin(GL_POINT);
        for( double x = 0; x < 5; x += GRID)
            glVertex3d(x,Expansion.T(x),0);
     glEnd();
}

void OGLWidget::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
    update();

}
