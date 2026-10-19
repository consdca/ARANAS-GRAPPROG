#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#include <iostream>
using namespace std;

GLuint leftVBO, rightVBO;

void drawScene() {
    GLfloat leftVerts[] = {
        -0.5f,  0.3f, 0.0f,
        -0.8f, -0.3f, 0.0f,
        -0.2f, -0.3f, 0.0f
    };

    GLfloat rightVerts[] = {
         0.5f,  0.3f, 0.0f,
         0.2f, -0.3f, 0.0f,
         0.8f, -0.3f, 0.0f
    };

    glGenBuffers(1, &leftVBO);
    glBindBuffer(GL_ARRAY_BUFFER, leftVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(leftVerts), leftVerts, GL_STATIC_DRAW);

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    
    glColor3f(1.0f, 0.4f, 0.2f);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glGenBuffers(1, &rightVBO);
    glBindBuffer(GL_ARRAY_BUFFER, rightVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(rightVerts), rightVerts, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, rightVBO);
    glVertexPointer(3, GL_FLOAT, 0, 0);

    glColor3f(0.2f, 0.4f, 1.0f);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDisableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &leftVBO);
    glDeleteBuffers(1, &rightVBO);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawScene();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Q05 - Two Separate VBOs Side by Side");
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