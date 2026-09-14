#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include <cmath>
using namespace std;

void drawCircle() {
    glColor3f(1.0f, 0.5f, 0.8f); 
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(0.0f, 0.3f); 
        int segments = 40;
        float radius = 0.4f;
        for (int i = 0; i <= segments; i++) {
            float angle = (float)i / segments * 2.0f * 3.14159265f;
            glVertex2f(radius * cosf(angle), 0.3f + radius * sinf(angle));
        }
    glEnd();
}

void drawBase() {
    glColor3f(0.8f, 0.6f, 0.4f); 
    glBegin(GL_QUADS);
        glVertex2f(-0.1f, -0.6f);
        glVertex2f( 0.1f, -0.6f);
        glVertex2f( 0.4f,  0.2f);
        glVertex2f(-0.4f,  0.2f);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    drawBase();
    drawCircle();
    
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Q16 - Fan + Quad Composition");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}