#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#include <iostream>
using namespace std;

GLuint shipPosVBO, shipColorVBO, groundVBO, groundIndexVBO;
bool capstoneReady = false;

void initCapstone() {
    if (!capstoneReady) {
        GLfloat shipPos[] = {
             0.0f,  0.5f,  0.0f,
            -0.3f,  0.2f,  0.0f,
             0.3f,  0.2f,  0.0f
        };
        GLfloat shipColor[] = {
            0.9f, 0.3f, 0.3f,
            0.3f, 0.9f, 0.3f,
            0.3f, 0.3f, 0.9f
        };
        GLfloat groundVerts[] = {
            -0.9f, -0.9f, 0.0f,
             0.9f, -0.9f, 0.0f,
             0.9f, -0.5f, 0.0f,
            -0.9f, -0.5f, 0.0f
        };
        GLubyte groundIndices[] = { 0, 1, 2, 0, 2, 3 };

        glGenBuffers(1, &shipPosVBO);
        glBindBuffer(GL_ARRAY_BUFFER, shipPosVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(shipPos), shipPos, GL_DYNAMIC_DRAW);

        glGenBuffers(1, &shipColorVBO);
        glBindBuffer(GL_ARRAY_BUFFER, shipColorVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(shipColor), shipColor, GL_STATIC_DRAW);

        glGenBuffers(1, &groundVBO);
        glBindBuffer(GL_ARRAY_BUFFER, groundVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(groundVerts), groundVerts, GL_STATIC_DRAW);

        glGenBuffers(1, &groundIndexVBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, groundIndexVBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(groundIndices), groundIndices, GL_STATIC_DRAW);

        capstoneReady = true;
    }
}

void display() {
    initCapstone();
    glClear(GL_COLOR_BUFFER_BIT);

    glEnableClientState(GL_VERTEX_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, groundVBO);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, groundIndexVBO);
    glColor3f(0.3f, 0.5f, 0.3f);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glEnableClientState(GL_COLOR_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, shipPosVBO);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, shipColorVBO);
    glColorPointer(3, GL_FLOAT, 0, 0);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glFlush();
}

void animateStep(int value) {
    static float dy = -0.02f;
    glBindBuffer(GL_ARRAY_BUFFER, shipPosVBO);
    GLfloat* mapped = (GLfloat*)glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE);
    if (mapped != nullptr) {
        if (mapped[1] > 0.7f || mapped[1] < 0.3f) {
            dy = -dy;
        }
        mapped[1] += dy;
        mapped[4] += dy;
        mapped[7] += dy;
        glUnmapBuffer(GL_ARRAY_BUFFER);
    }
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glutPostRedisplay();
    glutTimerFunc(100, animateStep, 0);
}

void monitorKeyboard(unsigned char key, int x, int y) {
    if (key == 27) {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glDeleteBuffers(1, &shipPosVBO);
        glDeleteBuffers(1, &shipColorVBO);
        glDeleteBuffers(1, &groundVBO);
        glDeleteBuffers(1, &groundIndexVBO);
        exit(0);
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Q20 - Capstone Scene");
    glutDisplayFunc(display);
    glutKeyboardFunc(monitorKeyboard);
    glutTimerFunc(100, animateStep, 0);

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