#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
using namespace std;

bool stippleOn = false;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 1.0f, 1.0f);
    glLineWidth(3.0f);
    
    if (stippleOn) {
        glEnable(GL_LINE_STIPPLE);
        glLineStipple(2, 0x00FF);
    } else {
        glDisable(GL_LINE_STIPPLE);
    }
    
    glBegin(GL_LINE_LOOP);
        glVertex2f(-0.5f, -0.5f);
        glVertex2f( 0.5f, -0.5f);
        glVertex2f( 0.5f,  0.5f);
        glVertex2f(-0.5f,  0.5f);
    glEnd();
    
    glFlush();
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 's' || key == 'S') {
        stippleOn = !stippleOn;
        glutPostRedisplay();
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Q17 - Toggle Stipple");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}