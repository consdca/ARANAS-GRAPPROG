#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#include <iostream>
#include <thread>
#include <atomic>
#include <cmath>
using namespace std;

GLuint housingVBO, redLightVBO, yellowLightVBO, greenLightVBO;
int currentState = 4; // 1: Red, 2: Yellow, 3: Green, 4: All Off
atomic<bool> running(true);

const int SEGMENTS = 20;

void createCircleBuffer(GLuint& vbo, float cx, float cy, float radius) {
    GLfloat verts[(SEGMENTS + 2) * 3];
    verts[0] = cx;
    verts[1] = cy;
    verts[2] = 0.0f;

    float pi = 3.14159265f;
    for (int i = 0; i <= SEGMENTS; i++) {
        float theta = 2.0f * pi * i / SEGMENTS;
        int idx = (i + 1) * 3;
        verts[idx + 0] = cx + radius * cosf(theta);
        verts[idx + 1] = cy + radius * sinf(theta);
        verts[idx + 2] = 0.0f;
    }

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void initBuffers() {
    GLfloat housingVerts[] = {
        -0.25f,  0.75f, 0.0f,
         0.25f,  0.75f, 0.0f,
         0.25f, -0.75f, 0.0f,
        -0.25f, -0.75f, 0.0f
    };
    glGenBuffers(1, &housingVBO);
    glBindBuffer(GL_ARRAY_BUFFER, housingVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(housingVerts), housingVerts, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    createCircleBuffer(redLightVBO, 0.0f, 0.45f, 0.15f);
    createCircleBuffer(yellowLightVBO, 0.0f, 0.0f, 0.15f);
    createCircleBuffer(greenLightVBO, 0.0f, -0.45f, 0.15f);
}

void drawCircle(GLuint vbo, float r, float g, float b) {
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glColor3f(r, g, b);
    glDrawArrays(GL_TRIANGLE_FAN, 0, SEGMENTS + 2);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glEnableClientState(GL_VERTEX_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, housingVBO);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glColor3f(0.15f, 0.15f, 0.15f);
    glDrawArrays(GL_QUADS, 0, 4);

    if (currentState == 1) {
        drawCircle(redLightVBO, 1.0f, 0.0f, 0.0f);
        drawCircle(yellowLightVBO, 0.2f, 0.2f, 0.2f);
        drawCircle(greenLightVBO, 0.2f, 0.2f, 0.2f);
    } else if (currentState == 2) {
        drawCircle(redLightVBO, 0.2f, 0.2f, 0.2f);
        drawCircle(yellowLightVBO, 1.0f, 0.85f, 0.0f);
        drawCircle(greenLightVBO, 0.2f, 0.2f, 0.2f);
    } else if (currentState == 3) {
        drawCircle(redLightVBO, 0.2f, 0.2f, 0.2f);
        drawCircle(yellowLightVBO, 0.2f, 0.2f, 0.2f);
        drawCircle(greenLightVBO, 0.0f, 0.9f, 0.0f);
    } else {
        drawCircle(redLightVBO, 0.2f, 0.2f, 0.2f);
        drawCircle(yellowLightVBO, 0.2f, 0.2f, 0.2f);
        drawCircle(greenLightVBO, 0.2f, 0.2f, 0.2f);
    }

    glDisableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glFlush();
}

void consoleMenuLoop() {
    while (running) {
        cout << "\n=== CAMPUS TRAFFIC SIGNAL MENU ===\n"
             << "1. Red / Stop\n"
             << "2. Yellow / Caution\n"
             << "3. Green / Go\n"
             << "4. All Off\n"
             << "5. Reset\n"
             << "0. Exit\n"
             << "Enter choice: ";
        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }
        if (choice == 0) {
            running = false;
            exit(0);
        } else if (choice >= 1 && choice <= 5) {
            currentState = (choice == 5) ? 4 : choice;
            glutPostRedisplay();
        } else {
            cout << "Invalid choice. Please try again.\n";
        }
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 700);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("MP01 - Campus Traffic Signal Visualizer");
    glutDisplayFunc(display);

#ifndef __APPLE__
    GLenum err = glewInit();
    if (err != GLEW_OK) return 1;
#endif

    initBuffers();
    thread menuThread(consoleMenuLoop);
    menuThread.detach();

    glutMainLoop();
    return 0;
}