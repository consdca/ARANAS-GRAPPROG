#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#include <iostream>
using namespace std;

GLuint posVBO, indexVBO;

void drawPentagonFan() {
    GLfloat vertices[] = {
         0.0f,  0.0f, 0.0f,
         0.0f,  0.6f, 0.0f,
        -0.6f,  0.2f, 0.0f,
        -0.4f, -0.5f, 0.0f,
         0.4f, -0.5f, 0.0f,
         0.6f,  0.2f, 0.0f
    };

    GLubyte indices[] = { 0, 1, 2, 3, 4, 5, 1 };

    glGenBuffers(1, &posVBO);
    glBindBuffer(GL_ARRAY_BUFFER, posVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &indexVBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glDrawElements(GL_TRIANGLE_FAN, 7, GL_UNSIGNED_BYTE, 0);

    glDisableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &posVBO);
    glDeleteBuffers(1, &indexVBO);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.9f, 0.6f, 0.1f);
    drawPentagonFan();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Q14 - Indexed Triangle Fan Pentagon");
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