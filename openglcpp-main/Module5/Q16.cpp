#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#include <iostream>
using namespace std;

GLuint sunVBO, groundVBO, groundIndexVBO, treeTrunkVBO, treeLeavesVBO;
bool sceneReady = false;

void initScene() {
    if (!sceneReady) {
        GLfloat sunVerts[] = {
             0.75f,  0.82f,  0.0f,
             0.636f, 0.737f, 0.0f,
             0.679f, 0.603f, 0.0f,
             0.821f, 0.603f, 0.0f,
             0.864f, 0.737f, 0.0f
        };
        glGenBuffers(1, &sunVBO);
        glBindBuffer(GL_ARRAY_BUFFER, sunVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(sunVerts), sunVerts, GL_STATIC_DRAW);

        GLfloat groundVerts[] = {
            -0.9f, -0.9f, 0.0f,
             0.9f, -0.9f, 0.0f,
             0.9f, -0.6f, 0.0f,
            -0.9f, -0.6f, 0.0f
        };
        GLubyte groundIndices[] = { 0, 1, 2, 0, 2, 3 };

        glGenBuffers(1, &groundVBO);
        glBindBuffer(GL_ARRAY_BUFFER, groundVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(groundVerts), groundVerts, GL_STATIC_DRAW);

        glGenBuffers(1, &groundIndexVBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, groundIndexVBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(groundIndices), groundIndices, GL_STATIC_DRAW);

        GLfloat trunkVerts[] = {
            -0.5f, -0.6f, 0.0f,
            -0.4f, -0.6f, 0.0f,
            -0.4f, -0.1f, 0.0f,
            -0.5f, -0.1f, 0.0f
        };
        glGenBuffers(1, &treeTrunkVBO);
        glBindBuffer(GL_ARRAY_BUFFER, treeTrunkVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(trunkVerts), trunkVerts, GL_STATIC_DRAW);

        GLfloat leavesVerts[] = {
            -0.45f, 0.35f, 0.0f,
            -0.70f, -0.1f, 0.0f,
            -0.20f, -0.1f, 0.0f
        };
        glGenBuffers(1, &treeLeavesVBO);
        glBindBuffer(GL_ARRAY_BUFFER, treeLeavesVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(leavesVerts), leavesVerts, GL_STATIC_DRAW);

        sceneReady = true;
    }
}

void display() {
    initScene();
    glClear(GL_COLOR_BUFFER_BIT);

    glEnableClientState(GL_VERTEX_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, sunVBO);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glColor3f(1.0f, 0.85f, 0.1f);
    glDrawArrays(GL_POLYGON, 0, 5);

    glBindBuffer(GL_ARRAY_BUFFER, groundVBO);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, groundIndexVBO);
    glColor3f(0.2f, 0.6f, 0.2f);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glBindBuffer(GL_ARRAY_BUFFER, treeTrunkVBO);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glColor3f(0.55f, 0.27f, 0.07f);
    glDrawArrays(GL_QUADS, 0, 4);

    glBindBuffer(GL_ARRAY_BUFFER, treeLeavesVBO);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glColor3f(0.1f, 0.5f, 0.1f);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDisableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Q16 - Three-Shape Scene");
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