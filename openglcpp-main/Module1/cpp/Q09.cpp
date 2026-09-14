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
    
    float cellSize = 0.4f; 
    float startX = -0.8f;
    float startY = -0.8f;

    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            
            if ((row + col) % 2 == 0) {
                glColor3f(0.2f, 0.2f, 0.2f); 
            } else {
                glColor3f(0.8f, 0.8f, 0.8f); 
            }
            
            float x0 = startX + col * cellSize;
            float y0 = startY + row * cellSize;
            float x1 = x0 + cellSize;
            float y1 = y0 + cellSize;
            
            glBegin(GL_POLYGON);
                glVertex2f(x0, y0);
                glVertex2f(x1, y0);
                glVertex2f(x1, y1);
                glVertex2f(x0, y1);
            glEnd();
        }
    }
    
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Q09 - 4x4 Checkerboard");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}