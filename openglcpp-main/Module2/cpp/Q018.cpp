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
    
    glBegin(GL_QUAD_STRIP);
    int quads = 6;
    float startX = -0.9f;
    float stepX = 0.3f;
    
    for (int i = 0; i <= quads; i++) {
        if (i % 2 == 0) {
            glColor3f(0.8f, 0.2f, 0.2f); 
        } else {
            glColor3f(0.2f, 0.2f, 0.8f); 
        }
        
        float x = startX + i * stepX;
        float yOffset = (i % 2 == 0) ? 0.0f : 0.2f; 
        
        glVertex2f(x, -0.3f + yOffset); 
        glVertex2f(x,  0.3f + yOffset); 
    }
    glEnd();
    
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Q18 - Alternating-Color Ribbon");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}