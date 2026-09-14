#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include <cmath>
using namespace std;

void display() {
    glClearColor(0.5f, 0.8f, 1.0f, 1.0f); 
    glClear(GL_COLOR_BUFFER_BIT);
    
    glColor3f(0.2f, 0.8f, 0.2f);
    glBegin(GL_POLYGON);
        glVertex2f(-1.0f, -1.0f);
        glVertex2f( 1.0f, -1.0f);
        glVertex2f( 1.0f, -0.3f);
        glVertex2f(-1.0f, -0.3f);
    glEnd();
    
    glColor3f(1.0f, 0.9f, 0.0f);
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(0.6f, 0.6f); 
        int segments = 40;
        float radius = 0.15f;
        for (int i = 0; i <= segments; i++) {
            float angle = (float)i / segments * 2.0f * 3.14159265f;
            glVertex2f(0.6f + radius * cosf(angle), 0.6f + radius * sinf(angle));
        }
    glEnd();
    
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowPosition(100, 100); 
    glutInitWindowSize(800, 400);     
    glutCreateWindow("Q14 - Simple Landscape");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}