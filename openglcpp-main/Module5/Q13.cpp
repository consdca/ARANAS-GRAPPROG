#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#include <iostream>
using namespace std;

GLuint vbo1, vbo2;
bool sceneLoaded = false;

void initBuffers() {
    if (!sceneLoaded) {
        GLfloat tri1[] = { -0.5f, 0.0f, 0.0f, -0.8f, -0.5f, 0.0f, -0.2f, -0.5f, 0.0f };
        GLfloat tri2[] = {  0.5f, 0.0f, 0.0f,  0.2f, -0.5f, 0.0f,  0.8f, -0.5f, 0.0f };

        glGenBuffers(1, &vbo1);
        glBindBuffer(GL_ARRAY_BUFFER, vbo1);
        glBufferData(GL_ARRAY_BUFFER, sizeof(tri1), tri1, GL_STATIC_DRAW);

        glGenBuffers(1, &vbo2);
        glBindBuffer(GL_ARRAY_BUFFER, vbo2);
        glBufferData(GL_ARRAY_BUFFER, sizeof(tri2), tri2, GL_STATIC_DRAW);

        sceneLoaded = true;
    }
}

void display() {
    initBuffers();
    glClear(GL_COLOR_BUFFER_BIT);

    glEnableClientState(GL_VERTEX_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, vbo1);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glColor3f(1.0f, 0.3f, 0.3f);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glBindBuffer(GL_ARRAY_BUFFER, vbo2);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glColor3f(0.3f, 0.3f, 1.0f);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDisableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glFlush();
}

void monitorKeyboard(unsigned char key, int x, int y) {
    if (key == 27) {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDeleteBuffers(1, &vbo1);
        glDeleteBuffers(1, &vbo2);
        exit(0);
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Q13 - ESC Cleanup Two VBOs");
    glutDisplayFunc(display);
    glutKeyboardFunc(monitorKeyboard);

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