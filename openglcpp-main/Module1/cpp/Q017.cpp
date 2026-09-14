#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include <cmath>
using namespace std;

int activeLight = 0; 

void drawCircle(float cy, float r, float g, float b, bool active) {
    if (active) glColor3f(r, g, b);
    else glColor3f(r * 0.3f, g * 0.3f, b * 0.3f);
    
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0f, cy);
    for (int i = 0; i <= 40; i++) {
        float angle = i * 2.0f * 3.14159f / 40;
        glVertex2f(0.2f * cosf(angle), cy + 0.2f * sinf(angle));
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.3f, -0.8f);
    glVertex2f( 0.3f, -0.8f);
    glVertex2f( 0.3f,  0.8f);
    glVertex2f(-0.3f,  0.8f);
    glEnd();
    
    drawCircle(0.5f, 1.0f, 0.0f, 0.0f, activeLight == 0);
    drawCircle(0.0f, 1.0f, 1.0f, 0.0f, activeLight == 1);
    drawCircle(-0.5f, 0.0f, 1.0f, 0.0f, activeLight == 2);
    
    glFlush();
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 'n') {
        activeLight = (activeLight + 1) % 3;
        glutPostRedisplay();
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(400, 800);
    glutCreateWindow("Q17 - Traffic Light Simulator");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}