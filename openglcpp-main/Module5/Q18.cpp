#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#include <iostream>
using namespace std;

GLuint vboData, vboIndex;

void drawInterleavedIndexedHexagon() {
    GLfloat data[] = {
         0.0f,  0.0f, 0.0f,  1.0f, 1.0f, 1.0f,
         0.0f,  0.6f, 0.0f,  1.0f, 0.0f, 0.0f,
         0.5f,  0.3f, 0.0f,  0.0f, 1.0f, 0.0f,
         0.5f, -0.3f, 0.0f,  0.0f, 0.0f, 1.0f,
         0.0f, -0.6f, 0.0f,  1.0f, 1.0f, 0.0f,
        -0.5f, -0.3f, 0.0f,  1.0f, 0.0f, 1.0f,
        -0.5f,  0.3f, 0.0f,  0.0f, 1.0f, 1.0f
    };

    GLubyte indices[] = { 0, 1, 2, 0, 2, 3, 0, 3, 4, 0, 4, 5, 0, 5, 6, 0, 6, 1 };
    GLsizei stride = 6 * sizeof(GLfloat);

    glGenBuffers(1, &vboData);
    glBindBuffer(GL_ARRAY_BUFFER, vboData);
    glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);

    glGenBuffers(1, &vboIndex);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIndex);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glVertexPointer(3, GL_FLOAT, stride, (void*)0);
    glColorPointer(3, GL_FLOAT, stride, (void*)(3 * sizeof(GLfloat)));

    glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_BYTE, 0);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &vboData);
    glDeleteBuffers(1, &vboIndex);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawInterleavedIndexedHexagon();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Q18 - Interleaved Indexed Hexagon");
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