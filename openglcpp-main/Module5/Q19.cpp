#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#include <iostream>
using namespace std;

GLuint posVBO, colorVBO;
int colorState = 0;
bool buffersReady = false;

void initBuffers() {
    if (!buffersReady) {
        GLfloat positions[] = {
             0.0f,  0.75f, 0.0f,
            -0.75f, -0.5f, 0.0f,
             0.75f, -0.5f, 0.0f
        };
        GLfloat colors[] = {
            1.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 1.0f
        };

        glGenBuffers(1, &posVBO);
        glBindBuffer(GL_ARRAY_BUFFER, posVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

        glGenBuffers(1, &colorVBO);
        glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_DYNAMIC_DRAW);

        buffersReady = true;
    }
}

void display() {
    initBuffers();
    glClear(GL_COLOR_BUFFER_BIT);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, posVBO);
    glVertexPointer(3, GL_FLOAT, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
    glColorPointer(3, GL_FLOAT, 0, 0);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glFlush();
}

void monitorKeyboard(unsigned char key, int x, int y) {
    if (key == 'c' || key == 'C') {
        colorState = (colorState + 1) % 3;
        glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
        GLfloat* mapped = (GLfloat*)glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE);
        if (mapped != nullptr) {
            if (colorState == 0) {
                mapped[0] = 1.0f; mapped[1] = 0.0f; mapped[2] = 0.0f;
                mapped[3] = 0.0f; mapped[4] = 1.0f; mapped[5] = 0.0f;
                mapped[6] = 0.0f; mapped[7] = 0.0f; mapped[8] = 1.0f;
            } else if (colorState == 1) {
                mapped[0] = 1.0f; mapped[1] = 1.0f; mapped[2] = 0.0f;
                mapped[3] = 1.0f; mapped[4] = 0.0f; mapped[5] = 1.0f;
                mapped[6] = 0.0f; mapped[7] = 1.0f; mapped[8] = 1.0f;
            } else {
                mapped[0] = 0.2f; mapped[1] = 0.8f; mapped[2] = 0.9f;
                mapped[3] = 0.9f; mapped[4] = 0.2f; mapped[5] = 0.8f;
                mapped[6] = 0.8f; mapped[7] = 0.9f; mapped[8] = 0.2f;
            }
            glUnmapBuffer(GL_ARRAY_BUFFER);
        }
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glutPostRedisplay();
    } else if (key == 27) {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDeleteBuffers(1, &posVBO);
        glDeleteBuffers(1, &colorVBO);
        exit(0);
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Q19 - Key-Triggered Color Change");
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