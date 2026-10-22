#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#include <iostream>
using namespace std;

GLuint robotVBO;
float stepSize = 0.1f;
bool autoMoveActive = false;

void initBuffers() {
    GLfloat robotVerts[] = {
         0.0f,  0.15f, 0.0f,
        -0.1f, -0.05f, 0.0f,
         0.1f, -0.05f, 0.0f
    };
    glGenBuffers(1, &robotVBO);
    glBindBuffer(GL_ARRAY_BUFFER, robotVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(robotVerts), robotVerts, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void drawScene() {
    glColor3f(0.3f, 0.3f, 0.3f);
    glLineWidth(3.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.9f, 0.9f);
    glVertex2f( 0.9f, 0.9f);
    glVertex2f( 0.9f, -0.9f);
    glVertex2f(-0.9f, -0.9f);
    glEnd();

    glColor3f(0.8f, 0.3f, 0.3f);
    glBegin(GL_QUADS);
    glVertex2f(-0.8f, 0.8f); glVertex2f(-0.5f, 0.8f); glVertex2f(-0.5f, 0.5f); glVertex2f(-0.8f, 0.5f);
    glEnd();

    glColor3f(0.3f, 0.8f, 0.3f);
    glBegin(GL_QUADS);
    glVertex2f(0.5f, 0.8f); glVertex2f(0.8f, 0.8f); glVertex2f(0.8f, 0.5f); glVertex2f(0.5f, 0.5f);
    glEnd();

    glColor3f(0.3f, 0.3f, 0.8f);
    glBegin(GL_QUADS);
    glVertex2f(0.5f, -0.5f); glVertex2f(0.8f, -0.5f); glVertex2f(0.8f, -0.8f); glVertex2f(0.5f, -0.8f);
    glEnd();

    glEnableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, robotVBO);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glColor3f(1.0f, 0.9f, 0.0f);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawScene();
    glFlush();
}

void updateRobotPosition(float dx, float dy) {
    glBindBuffer(GL_ARRAY_BUFFER, robotVBO);
    GLfloat* mapped = (GLfloat*)glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE);
    if (mapped != nullptr) {
        float newX1 = mapped[0] + dx;
        float newY1 = mapped[1] + dy;
        float newX2 = mapped[3] + dx;
        float newY2 = mapped[4] + dy;
        float newX3 = mapped[6] + dx;
        float newY3 = mapped[7] + dy;

        if (newX1 >= -0.85f && newX2 >= -0.85f && newX3 >= -0.85f &&
            newX1 <=  0.85f && newX2 <=  0.85f && newX3 <=  0.85f &&
            newY1 >= -0.85f && newY2 >= -0.85f && newY3 >= -0.85f &&
            newY1 <=  0.85f && newY2 <=  0.85f && newY3 <=  0.85f) {
            mapped[0] = newX1; mapped[1] = newY1;
            mapped[3] = newX2; mapped[4] = newY2;
            mapped[6] = newX3; mapped[7] = newY3;
        }
        glUnmapBuffer(GL_ARRAY_BUFFER);
    }
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glutPostRedisplay();
}

void resetRobot() {
    glBindBuffer(GL_ARRAY_BUFFER, robotVBO);
    GLfloat* mapped = (GLfloat*)glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE);
    if (mapped != nullptr) {
        mapped[0] =  0.0f; mapped[1] =  0.15f;
        mapped[3] = -0.1f; mapped[4] = -0.05f;
        mapped[6] =  0.1f; mapped[7] = -0.05f;
        glUnmapBuffer(GL_ARRAY_BUFFER);
    }
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glutPostRedisplay();
}

void timerCallback(int value) {
    if (autoMoveActive) {
        static int phase = 0;
        if (phase == 0) updateRobotPosition(stepSize, 0.0f);
        else if (phase == 1) updateRobotPosition(0.0f, stepSize);
        else if (phase == 2) updateRobotPosition(-stepSize, 0.0f);
        else if (phase == 3) updateRobotPosition(0.0f, -stepSize);
        phase = (phase + 1) % 4;
        glutTimerFunc(400, timerCallback, 0);
    }
}

void printMenu() {
    cout << "\n========================================\n"
         << "   WAREHOUSE ROBOT ROUTE SIMULATOR (MP3)\n"
         << "========================================\n"
         << " Click on the graphics window and press:\n"
         << "  [1] Move Left\n"
         << "  [2] Move Right\n"
         << "  [3] Move Up\n"
         << "  [4] Move Down\n"
         << "  [5] Cycle Step Size (Current: " << stepSize << ")\n"
         << "  [6] Return to Start Position\n"
         << "  [7] Toggle Auto-Move Demo\n"
         << "  [0] Exit Application\n"
         << "----------------------------------------\n";
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case '1':
            autoMoveActive = false;
            updateRobotPosition(-stepSize, 0.0f);
            cout << "-> Moved Left\n";
            break;
        case '2':
            autoMoveActive = false;
            updateRobotPosition(stepSize, 0.0f);
            cout << "-> Moved Right\n";
            break;
        case '3':
            autoMoveActive = false;
            updateRobotPosition(0.0f, stepSize);
            cout << "-> Moved Up\n";
            break;
        case '4':
            autoMoveActive = false;
            updateRobotPosition(0.0f, -stepSize);
            cout << "-> Moved Down\n";
            break;
        case '5':
            stepSize += 0.025f;
            if (stepSize > 0.2f) stepSize = 0.05f;
            cout << "-> Step size updated to: " << stepSize << "\n";
            break;
        case '6':
            autoMoveActive = false;
            resetRobot();
            cout << "-> Returned to Start Position\n";
            break;
        case '7':
            autoMoveActive = !autoMoveActive;
            if (autoMoveActive) {
                glutTimerFunc(400, timerCallback, 0);
                cout << "-> Auto-Move Demo STARTED\n";
            } else {
                cout << "-> Auto-Move Demo STOPPED\n";
            }
            break;
        case '27':
        case '0':
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glDeleteBuffers(1, &robotVBO);
            cout << "Exiting application...\n";
            exit(0);
            break;
        default:
            cout << "Invalid key! Use keys 1-7 or 0.\n";
            break;
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(700, 700);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("MP03 - Warehouse Robot Route Simulator");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

#ifndef __APPLE__
    GLenum err = glewInit();
    if (err != GLEW_OK) return 1;
#endif

    initBuffers();
    printMenu();

    glutMainLoop();
    return 0;
}