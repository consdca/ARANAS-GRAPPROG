#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
using namespace std;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 1.0f, 1.0f);
    glLineWidth(3.0f);
    
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x00FF);
    glBegin(GL_LINES);
        glVertex2f(-0.8f, 0.3f);
        glVertex2f( 0.8f, 0.3f);
    glEnd();
    glDisable(GL_LINE_STIPPLE);
    
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(3, 0xAAAA);
    glBegin(GL_LINES);
        glVertex2f(-0.8f, -0.3f);
        glVertex2f( 0.8f, -0.3f);
    glEnd();
    glDisable(GL_LINE_STIPPLE);
    
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Q14 - Different Stipple Patterns");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}