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
using namespace std;

GLuint parkVBO, indexVBO;
bool showPlayground = true;
bool showGarden = true;
bool showSeating = true;
int activePreset = 1; // 1: Default/All, 2: Layout A, 3: Layout B
atomic<bool> running(true);

void initBuffers() {
    GLfloat vertices[] = {
        -0.8f,  0.8f, 0.0f, // 0: Boundary NW
         0.8f,  0.8f, 0.0f, // 1: Boundary NE
         0.8f, -0.8f, 0.0f, // 2: Boundary SE
        -0.8f, -0.8f, 0.0f, // 3: Boundary SW

        -0.6f,  0.6f, 0.0f, // 4: Playground NW
        -0.2f,  0.6f, 0.0f, // 5: Playground NE
        -0.2f,  0.2f, 0.0f, // 6: Playground SE
        -0.6f,  0.2f, 0.0f, // 7: Playground SW

         0.2f,  0.6f, 0.0f, // 8: Garden NW
         0.6f,  0.6f, 0.0f, // 9: Garden NE
         0.6f,  0.2f, 0.0f, // 10: Garden SE
         0.2f,  0.2f, 0.0f, // 11: Garden SW

        -0.3f, -0.2f, 0.0f, // 12: Seating NW
         0.3f, -0.2f, 0.0f, // 13: Seating NE
         0.3f, -0.6f, 0.0f, // 14: Seating SE
        -0.3f, -0.6f, 0.0f  // 15: Seating SW
    };

    GLubyte indices[] = {
        0, 1, 2,  0, 2, 3,   // Boundary
        4, 5, 6,  4, 6, 7,   // Playground
        8, 9, 10, 8, 10, 11, // Garden
        12, 13, 14, 12, 14, 15 // Seating
    };

    glGenBuffers(1, &parkVBO);
    glBindBuffer(GL_ARRAY_BUFFER, parkVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &indexVBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glEnableClientState(GL_VERTEX_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, parkVBO);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVBO);

    glColor3f(0.85f, 0.95f, 0.85f);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, (void*)0);

    if (showPlayground) {
        if (activePreset == 3) glColor3f(0.9f, 0.4f, 0.4f);
        else glColor3f(0.2f, 0.6f, 0.9f);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, (void*)(6 * sizeof(GLubyte)));
    }

    if (showGarden) {
        if (activePreset == 3) glColor3f(0.4f, 0.9f, 0.4f);
        else glColor3f(0.3f, 0.8f, 0.3f);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, (void*)(12 * sizeof(GLubyte)));
    }

    if (showSeating) {
        if (activePreset == 2) glColor3f(0.9f, 0.7f, 0.2f);
        else glColor3f(0.7f, 0.5f, 0.3f);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, (void*)(18 * sizeof(GLubyte)));
    }

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDisableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glFlush();
}

void consoleMenuLoop() {
    while (running) {
        cout << "\n=== COMMUNITY PARK LAYOUT PLANNER ===\n"
             << "1. Show All\n"
             << "2. Toggle Playground\n"
             << "3. Toggle Garden\n"
             << "4. Toggle Seating\n"
             << "5. Layout A (Highlight Seating)\n"
             << "6. Layout B (Highlight Playground)\n"
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
        } else if (choice == 1) {
            showPlayground = true; showGarden = true; showSeating = true; activePreset = 1;
        } else if (choice == 2) {
            showPlayground = !showPlayground;
        } else if (choice == 3) {
            showGarden = !showGarden;
        } else if (choice == 4) {
            showSeating = !showSeating;
        } else if (choice == 5) {
            activePreset = 2; showPlayground = true; showGarden = true; showSeating = true;
        } else if (choice == 6) {
            activePreset = 3; showPlayground = true; showGarden = true; showSeating = true;
        } else {
            cout << "Invalid choice. Please try again.\n";
            continue;
        }
        glutPostRedisplay();
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(700, 700);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("MP02 - Community Park Layout Planner");
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