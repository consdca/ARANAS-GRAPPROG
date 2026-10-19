#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#include <iostream>
using namespace std;

GLuint VBOid;
bool initialized = false;

void setupPoint() {
    if (!initialized) {
        GLfloat pointVert[] = { -0.8f, 0.0f, 0.0f };
        glGenBuffers(1, &VBOid);
        glBindBuffer(GL_ARRAY_BUFFER, VBOid);
        glBufferData(GL_ARRAY_BUFFER, sizeof(pointVert), pointVert, GL_DYNAMIC_DRAW);
        initialized = true;
    }
}

void drawPoint() {
    setupPoint();
    glBindBuffer(GL_ARRAY_BUFFER, VBOid);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glDrawArrays(GL_POINTS, 0, 1);
    glDisableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(15.0f);
    glColor3f(1.0f, 1.0f, 1.0f);
    drawPoint();
    glFlush();
}

void animateStep(int value) {
    glBindBuffer(GL_ARRAY_BUFFER, VBOid);
    GLfloat* mapped = (GLfloat*)glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE);
    if (mapped != nullptr) {
        mapped[0] += 0.05f;
        if (mapped[0] > 0.8f) {
            mapped[0] = -0.8f;
        }
        glUnmapBuffer(GL_ARRAY_BUFFER);
    }
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glutPostRedisplay();
    glutTimerFunc(1000, animateStep, 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Q12 - Timer Moving Point");
    glutDisplayFunc(display);
    glutTimerFunc(1000, animateStep, 0);

#ifndef __APPLE__
    GLenum err = glewInit();
    if (err == GLEW_OK) {
        glutMainLoop();
    }
#else
    glutMainLoop();
#endif
    return 0;
}