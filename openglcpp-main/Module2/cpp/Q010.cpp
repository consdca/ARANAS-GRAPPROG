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
    glColor3f(1.0f, 0.9f, 0.2f);
    
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(0.0f, 0.0f); 
        int segments = 8;
        float radius = 0.6f;
        for (int i = 0; i <= segments; i++) {
            float angle = (float)i / segments * 3.14159265f; 
            glVertex2f(radius * cosf(angle), radius * sinf(angle));
        }
    glEnd();
    
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Q10 - Half-Circle Fan");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}