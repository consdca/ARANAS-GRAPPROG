#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include <cmath>
using namespace std;

const int SEGMENT_COUNT = 60;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    glBegin(GL_TRIANGLE_FAN);
    
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(0.0f, 0.0f);
    
    float radius = 0.8f;
    for (int i = 0; i <= SEGMENT_COUNT; i++) {
        float t = (float)i / SEGMENT_COUNT;
        float angle = t * 2.0f * 3.14159265f;
        
        float r = 0.5f + 0.5f * cosf(angle + 0.0f);
        float g = 0.5f + 0.5f * cosf(angle + 2.0944f); 
        float b = 0.5f + 0.5f * cosf(angle + 4.1888f); 
        
        glColor3f(r, g, b);
        glVertex2f(radius * cosf(angle), radius * sinf(angle));
    }
    glEnd();
    
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Q20 - Procedural Rainbow Fan");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}