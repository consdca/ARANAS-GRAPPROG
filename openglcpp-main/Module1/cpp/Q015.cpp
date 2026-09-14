#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
using namespace std;

float sqX = 0.0f;
float sqY = 0.0f;
float speed = 0.05f;
float sqSize = 0.1f;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.9f, 0.2f, 0.9f);
    
    glBegin(GL_POLYGON);
        glVertex2f(sqX - sqSize, sqY - sqSize);
        glVertex2f(sqX + sqSize, sqY - sqSize);
        glVertex2f(sqX + sqSize, sqY + sqSize);
        glVertex2f(sqX - sqSize, sqY + sqSize);
    glEnd();
    
    glFlush();
}

void specialKeys(int key, int x, int y) {
    if (key == GLUT_KEY_LEFT)  sqX -= speed;
    if (key == GLUT_KEY_RIGHT) sqX += speed;
    if (key == GLUT_KEY_DOWN)  sqY -= speed;
    if (key == GLUT_KEY_UP)    sqY += speed;
    
    if (sqX - sqSize < -1.0f) sqX = -1.0f + sqSize;
    if (sqX + sqSize >  1.0f) sqX =  1.0f - sqSize;
    if (sqY - sqSize < -1.0f) sqY = -1.0f + sqSize;
    if (sqY + sqSize >  1.0f) sqY =  1.0f - sqSize;
    
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Q15 - Move a Square");
    glutDisplayFunc(display);
    glutSpecialFunc(specialKeys);
    glutMainLoop();
    return 0;
}