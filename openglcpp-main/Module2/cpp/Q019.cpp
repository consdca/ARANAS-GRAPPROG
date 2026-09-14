#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
using namespace std;

void display() {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glColor4f(1.0f, 0.0f, 0.0f, 0.5f); 
    glBegin(GL_QUADS);
        glVertex2f(-0.6f, -0.2f);
        glVertex2f( 0.2f, -0.2f);
        glVertex2f( 0.2f,  0.6f);
        glVertex2f(-0.6f,  0.6f);
    glEnd();
    
    glColor4f(0.0f, 0.5f, 1.0f, 0.5f); 
    glBegin(GL_QUADS);
        glVertex2f(-0.2f, -0.6f);
        glVertex2f( 0.6f, -0.6f);
        glVertex2f( 0.6f,  0.2f);
        glVertex2f(-0.2f,  0.2f);
    glEnd();
    
    glDisable(GL_BLEND);
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Q19 - Alpha-Blended Quads");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}