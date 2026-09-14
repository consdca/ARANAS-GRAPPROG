#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include <cmath>
using namespace std;

const int STRIPE_COUNT = 13;

void drawStar() {
    glColor3f(1.0f, 1.0f, 1.0f); 
    glBegin(GL_POLYGON);
    int points = 10;
    float outerRadius = 0.2f;
    float innerRadius = 0.08f;
    
    for (int i = 0; i < points; i++) {
        float angle = (float)i / points * 2.0f * 3.14159f + 1.5708f;
        float radius = (i % 2 == 0) ? outerRadius : innerRadius;
        glVertex2f(-0.6f + radius * cosf(angle), 0.6f + radius * sinf(angle));
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    float stripeHeight = 2.0f / STRIPE_COUNT;
    
    for (int i = 0; i < STRIPE_COUNT; i++) {
        if (i % 2 == 0) glColor3f(0.8f, 0.1f, 0.1f); 
        else glColor3f(1.0f, 1.0f, 1.0f); 
        
        float top = 1.0f - i * stripeHeight;
        float bottom = top - stripeHeight;
        
        glBegin(GL_POLYGON);
        glVertex2f(-1.0f, bottom);
        glVertex2f( 1.0f, bottom);
        glVertex2f( 1.0f, top);
        glVertex2f(-1.0f, top);
        glEnd();
    }
    
    glColor3f(0.0f, 0.2f, 0.6f);
    glBegin(GL_POLYGON);
    glVertex2f(-1.0f, 0.3f);
    glVertex2f(-0.2f, 0.3f);
    glVertex2f(-0.2f, 1.0f);
    glVertex2f(-1.0f, 1.0f);
    glEnd();
    
    drawStar();
    
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 500);
    glutCreateWindow("Q20 - Procedural Striped Flag");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}