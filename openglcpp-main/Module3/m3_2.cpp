#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#endif
#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

int playerColor = 0;
int barrierColor = 1;
float barrierY = 1.0f;
float barrierSpeed = 0.015f;
int score = 0;
bool gameOver = false;

const float colors[3][3] = {
    {1.0f, 0.2f, 0.2f}, // Red
    {0.2f, 0.9f, 0.3f}, // Green
    {0.2f, 0.5f, 1.0f}  // Blue
};
const char* colorNames[3] = {"RED", "GREEN", "BLUE"};

void drawBitmapString(void* font, const char* str) {
    for (const char* c = str; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

void drawPlayer() {
    glColor3fv(colors[playerColor]);
    glBegin(GL_QUADS);
        glVertex2f(-0.15f, -0.6f);
        glVertex2f( 0.15f, -0.6f);
        glVertex2f( 0.15f, -0.3f);
        glVertex2f(-0.15f, -0.3f);
    glEnd();
}

void drawBarrier() {
    glColor3fv(colors[barrierColor]);
    glBegin(GL_QUADS);
        glVertex2f(-1.0f, barrierY - 0.05f);
        glVertex2f( 1.0f, barrierY - 0.05f);
        glVertex2f( 1.0f, barrierY + 0.05f);
        glVertex2f(-1.0f, barrierY + 0.05f);
    glEnd();
}

void drawDashboard() {
    char buf[64];
    glColor3f(1.0f, 1.0f, 1.0f);
    
    snprintf(buf, sizeof(buf), "Score: %d  |  Player Color: %s", score, colorNames[playerColor]);
    glRasterPos2f(-0.9f, 0.88f);
    drawBitmapString(GLUT_BITMAP_HELVETICA_18, buf);

    glRasterPos2f(-0.9f, 0.78f);
    drawBitmapString(GLUT_BITMAP_HELVETICA_12, "Controls: [R] Red  [G] Green  [B] Blue  |  [Rst] 'X' to Reset");

    if (gameOver) {
        glColor3f(1.0f, 0.3f, 0.3f);
        glRasterPos2f(-0.55f, 0.0f);
        drawBitmapString(GLUT_BITMAP_HELVETICA_18, "GATE MISMATCH! Press 'X' to Restart");
    }
}

void spawnNextBarrier() {
    barrierY = 1.0f;
    barrierColor = rand() % 3;
}

void updateBarrier(int value) {
    if (!gameOver) {
        barrierY -= barrierSpeed;


        if (barrierY <= -0.45f && barrierY >= -0.55f) {
            if (playerColor == barrierColor) {
                score++;
                barrierSpeed = min(0.045f, barrierSpeed + 0.002f);
                cout << "Match! Score: " << score << " Speed: " << barrierSpeed << endl;
                spawnNextBarrier();
            } else {
                gameOver = true;
                cout << "Mismatch! Game Over." << endl;
            }
        } else if (barrierY < -1.1f) {
            spawnNextBarrier();
        }
    }

    glutPostRedisplay();
    glutTimerFunc(16, updateBarrier, 0);
}

void display() {
    glClearColor(0.12f, 0.12f, 0.15f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    if (!gameOver) {
        drawBarrier();
        drawPlayer();
    }
    drawDashboard();

    glFlush();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'r': case 'R': playerColor = 0; break;
        case 'g': case 'G': playerColor = 1; break;
        case 'b': case 'B': playerColor = 2; break;
        case 'x': case 'X': 
            gameOver = false;
            score = 0;
            barrierSpeed = 0.015f;
            spawnNextBarrier();
            break;
        case 27: exit(0);
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(700, 700);
    glutCreateWindow("MP02 - Chroma-Shift: The Color-Matching Gate");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(16, updateBarrier, 0);
    glutMainLoop();
    return 0;
}