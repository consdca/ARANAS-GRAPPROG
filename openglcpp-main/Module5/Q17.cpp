#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#include <iostream>
#include <cmath>
using namespace std;

const int DASH_COUNT = 30;
GLuint VBOid;

void drawDashRing() {
    GLfloat verts[DASH_COUNT * 6];
    float radius = 0.6f;
    float pi = 3.14159265f;

    for (int i = 0; i < DASH_COUNT; i++) {
        float angle = (float)i / DASH_COUNT * 2.0f * pi;
        float x1 = cosf(angle) * (radius - 0.08f);
        float y1 = sinf(angle) * (radius - 0.08f);
        float x2 = cosf(angle) * radius;
        float y2 = sinf(angle) * radius;

        int b = i * 6;
        verts[b + 0] = x1; verts[b + 1] = y1; verts[b + 2] = 0.0f;
        verts[b + 3] = x2; verts[b + 4] = y2; verts[b + 5] = 0.0f;
    }

    glGenBuffers(1, &VBOid);
    glBindBuffer(GL_ARRAY_BUFFER, VBOid);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glLineWidth(2.0f);
    glDrawArrays(GL_LINES, 0, DASH_COUNT * 2);

    glDisableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &VBOid);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.2f, 0.9f, 0.8f);
    drawDashRing();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Q17 - Procedural Dash Ring");
    glutDisplayFunc(display);

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