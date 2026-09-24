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
#include <cmath>

using namespace std;


float shipX = 0.0f;
float shipY = -0.7f;
int lives = 3;
int score = 0;
bool gameOver = false;


float ast1X = -0.4f;
float ast1Y = 1.0f;
float speed1 = 0.02f;


float ast2X = 0.5f;
float ast2Y = 1.2f;
float speed2 = 0.035f;

void drawBitmapString(void* font, const char* str) {
    for (const char* c = str; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

void drawShip() {

    glColor3f(0.2f, 0.7f, 1.0f);
    glBegin(GL_POLYGON);
        glVertex2f(shipX, shipY + 0.12f);
        glVertex2f(shipX + 0.05f, shipY - 0.06f);
        glVertex2f(shipX - 0.05f, shipY - 0.06f);
    glEnd();


    glColor3f(0.9f, 0.2f, 0.3f);
    glBegin(GL_TRIANGLES);
        glVertex2f(shipX - 0.05f, shipY - 0.02f);
        glVertex2f(shipX - 0.12f, shipY - 0.08f);
        glVertex2f(shipX, shipY - 0.06f);

        glVertex2f(shipX + 0.05f, shipY - 0.02f);
        glVertex2f(shipX + 0.12f, shipY - 0.08f);
        glVertex2f(shipX, shipY - 0.06f);
    glEnd();
}

void drawAsteroid(float x, float y, float size) {
    glColor3f(0.6f, 0.55f, 0.5f);
    glBegin(GL_POLYGON);
        glVertex2f(x - size, y);
        glVertex2f(x - size * 0.5f, y + size * 0.8f);
        glVertex2f(x + size * 0.7f, y + size * 0.7f);
        glVertex2f(x + size, y - size * 0.2f);
        glVertex2f(x + size * 0.3f, y - size * 0.9f);
        glVertex2f(x - size * 0.6f, y - size * 0.7f);
    glEnd();
}

void drawHUD() {
    char buf[64];
    glColor3f(1.0f, 1.0f, 1.0f);

    snprintf(buf, sizeof(buf), "Lives: %d    Score: %d", lives, score);
    glRasterPos2f(-0.9f, 0.88f);
    drawBitmapString(GLUT_BITMAP_HELVETICA_18, buf);

    if (gameOver) {
        glColor3f(1.0f, 0.2f, 0.2f);
        glRasterPos2f(-0.45f, 0.0f);
        drawBitmapString(GLUT_BITMAP_HELVETICA_18, "GAME OVER - Press R to Restart");
    }
}

bool checkCollision(float ax, float ay, float size) {
    float dx = fabsf(shipX - ax);
    float dy = fabsf(shipY - ay);
    return (dx < (0.08f + size)) && (dy < (0.08f + size));
}

void resetAsteroid1() {
    ast1Y = 1.1f;
    ast1X = ((rand() % 160) - 80) / 100.0f; 
}

void resetAsteroid2() {
    ast2Y = 1.2f;
    ast2X = ((rand() % 160) - 80) / 100.0f;
}

void resetGame() {
    lives = 3;
    score = 0;
    shipX = 0.0f;
    shipY = -0.7f;
    resetAsteroid1();
    resetAsteroid2();
    gameOver = false;
    cout << "Game reset. Good luck!" << endl;
}

void updateGame(int value) {
    if (!gameOver) {

        ast1Y -= speed1;
        if (ast1Y < -1.1f) {
            resetAsteroid1();
            score += 10;
        }


        ast2Y -= speed2;
        if (ast2Y < -1.1f) {
            resetAsteroid2();
            score += 10;
        }


        if (checkCollision(ast1X, ast1Y, 0.07f)) {
            lives--;
            cout << "Collision! Lives remaining: " << lives << endl;
            resetAsteroid1();
            if (lives <= 0) gameOver = true;
        }
        if (checkCollision(ast2X, ast2Y, 0.06f)) {
            lives--;
            cout << "Collision! Lives remaining: " << lives << endl;
            resetAsteroid2();
            if (lives <= 0) gameOver = true;
        }
    }

    glutPostRedisplay();
    glutTimerFunc(16, updateGame, 0);
}

void display() {
    glClearColor(0.05f, 0.05f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    if (!gameOver) {
        drawShip();
        drawAsteroid(ast1X, ast1Y, 0.07f);
        drawAsteroid(ast2X, ast2Y, 0.06f);
    }
    drawHUD();

    glFlush();
}

void keyboard(unsigned char key, int x, int y) {
    if (!gameOver) {
        switch (key) {
            case 'w': case 'W': shipY += 0.08f; break;
            case 's': case 'S': shipY -= 0.08f; break;
            case 'a': case 'A': shipX -= 0.08f; break;
            case 'd': case 'D': shipX += 0.08f; break;
        }

        if (shipX > 0.85f) shipX = 0.85f;
        if (shipX < -0.85f) shipX = -0.85f;
        if (shipY > 0.85f) shipY = 0.85f;
        if (shipY < -0.85f) shipY = -0.85f;
    }

    if (key == 'r' || key == 'R') {
        resetGame();
    }
    if (key == 27) {
        exit(0);
    }

    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 700);
    glutInitWindowPosition(200, 100);
    glutCreateWindow("MP01 - The Cosmic Dodger");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(16, updateGame, 0);
    glutMainLoop();
    return 0;
}