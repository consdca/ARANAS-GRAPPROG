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
bool ready = false;

void initQuad() {
    if (!ready) {
        GLfloat quadVerts[] = {
            -0.4f, -0.2f, 0.0f,
             0.4f, -0.2f, 0.0f,
             0.4f,  0.2f, 0.0f,
            -0.4f,  0.2f, 0.0f
        };
        glGenBuffers(1, &VBOid);
        glBindBuffer(GL_ARRAY_BUFFER, VBOid);
        glBufferData(GL_ARRAY_BUFFER, sizeof(quadVerts), quadVerts, GL_DYNAMIC_DRAW);
        ready = true;
    }
}

void drawQuad() {
    initQuad();
    glBindBuffer(GL_ARRAY_BUFFER, VBOid);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glDrawArrays(GL_QUADS, 0, 4);
    glDisableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.3f, 0.7f, 0.9f);
    drawQuad();
    glFlush();
}

void animateStep(int value) {
    static float dy = 0.03f;
    glBindBuffer(GL_ARRAY_BUFFER, VBOid);
    GLfloat* mapped = (GLfloat*)glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE);
    if (mapped != nullptr) {
        if (mapped[2] > 0.7f || mapped[2] < -0.7f) {
            dy = -dy;
        }
        for (int i = 0; i < 4; i++) {
            mapped[i * 3 + 1] += dy;
        }
        glUnmapBuffer(GL_ARRAY_BUFFER);
    }
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glutPostRedisplay();
    glutTimerFunc(50, animateStep, 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Q15 - Bouncing Quad Animation");
    glutDisplayFunc(display);
    glutTimerFunc(50, animateStep, 0);

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