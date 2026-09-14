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
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 0.8f, 0.1f);
    glLineWidth(2.0f);
    
    glBegin(GL_LINE_LOOP);
    int points = 10;
    float outerRadius = 0.8f;
    float innerRadius = 0.3f;
    
    for (int i = 0; i < points; i++) {
        float angle = (float)i / points * 2.0f * 3.14159265f + 1.5707963f;
        float radius = (i % 2 == 0) ? outerRadius : innerRadius;
        glVertex2f(radius * cosf(angle), radius * sinf(angle));
    }
    glEnd();
    
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Q10 - Five-Pointed Star Outline");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}