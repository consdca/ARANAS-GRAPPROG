#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include <cmath>
using namespace std;

float handAngle = 1.5708f; 

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 1.0f, 1.0f);
    
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 60; i++) {
        float angle = i * 2.0f * 3.14159f / 60;
        glVertex2f(0.8f * cosf(angle), 0.8f * sinf(angle));
    }
    glEnd();
    
    glBegin(GL_LINES);
    for (int i = 0; i < 12; i++) {
        float angle = i * 2.0f * 3.14159f / 12;
        glVertex2f(0.7f * cosf(angle), 0.7f * sinf(angle));
        glVertex2f(0.8f * cosf(angle), 0.8f * sinf(angle));
    }
    glEnd();
    
    glColor3f(1.0f, 0.0f, 0.0f);
    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.6f * cosf(handAngle), 0.6f * sinf(handAngle));
    glEnd();
    
    glFlush();
}

void idle() {
    handAngle -= 0.005f; 
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Q18 - Rotating Clock Hand");
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutMainLoop();
    return 0;
}